#include "magic_show.h"

void render(double ***all_points, char **color_points, const int *num_points, int num_objects,
            const int *active_objects, std::string &screen) {
    double **dist_mat = malloc_double_matrix(WIDTH, HEIGHT);
    for (int w = 0; w < WIDTH; w++) {
        for (int h = 0; h < HEIGHT; h++) {
            dist_mat[w][h] = MAX_Z;
            screen[h * (WIDTH + 1) + w] = ' ';
        }
    }
    for (int id = 0; id < num_objects; id++) {
        if(active_objects[id]) {
            for (int n = 0; n < num_points[id]; n++) {
                int w = (int) (all_points[id][0][n] / WIDTH_RATE);
                int h = (int) (all_points[id][1][n] / HEIGHT_RATE);
                if (w >= 0 && w < WIDTH && h >= 0 && h < HEIGHT) {
                    if (all_points[id][2][n] < dist_mat[w][h]) {
                        dist_mat[w][h] = all_points[id][2][n];
                        screen[h * (WIDTH + 1) + w] = color_points[id][n];
                    }
                }
            }
        }
    }
    free_matrix(dist_mat, WIDTH);
}

void show_magic() {
    std::string screen;
    screen.resize((WIDTH + 1) * HEIGHT);
    for (int h = 0; h < HEIGHT; h++) {
        screen[(h + 1) * (WIDTH + 1) - 1] = '\n';
    }

    auto active_objects = (int *) malloc(MAX_NUM_OBJECTS * sizeof(int));
    auto points = (double ***) malloc(MAX_NUM_OBJECTS * sizeof(double **));
    auto color_points = (char **) malloc(MAX_NUM_OBJECTS * sizeof(char *));
    auto num_points = (int *) malloc(MAX_NUM_OBJECTS * sizeof(int));
    auto center_objects = (double **) malloc(MAX_NUM_OBJECTS * sizeof(double *));
    for (int i = 0; i < MAX_NUM_OBJECTS; i++) {
        active_objects[i] = false;
        points[i] = malloc_double_matrix(DIM, MAX_POINTS);
        color_points[i] = (char *) malloc(MAX_POINTS * sizeof(char));
        center_objects[i] = (double *) malloc(DIM * sizeof(double));
    }

    uint64_t sum_time = 300 * 1000;    //microseconds
    uint64_t crt_time = 0;

    int crt_id = 0;
    add_heart(8, points[crt_id], color_points[crt_id], &num_points[crt_id], center_objects[crt_id]);

    while (crt_time < sum_time) {
        auto start = std::chrono::high_resolution_clock::now();

        rotate3d_x(points[crt_id], num_points[crt_id], 0.2, center_objects[crt_id]);
        rotate3d_y(points[crt_id], num_points[crt_id], 0.2, center_objects[crt_id]);

        render(points, color_points, num_points, MAX_NUM_OBJECTS, active_objects, screen);

        std::system("cls");
        std::cout << screen;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        crt_time += duration.count();
    }

    for (int i = 0; i < MAX_NUM_OBJECTS; i++) {
        free_matrix(points[i], DIM);
        free(color_points[i]);
        free(center_objects[i]);
    }
    free(active_objects);
    free(points);
    free(num_points);
    free(color_points);
    free(center_objects);
}
