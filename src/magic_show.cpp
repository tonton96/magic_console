#include "magic_show.h"

void move_object(double **points, int num_points, double *center, const double *position) {
    for (int j = 0; j < DIM; j++) {
        double delta = position[j] - center[j];
        for (int i = 0; i < num_points; i++) {
            points[j][i] += delta;
        }
        center[j] = position[j];
    }
}

void add_heart(double size, double **points, char *color_points, int *num_points, double *center) {
    const int num_bgs = 2;
    const std::string bgs[num_bgs] = {"|HAPPY BIRTH DAY TO ME|", "<3"};
    const char line = (char)219;

    int len_bgs[num_bgs];
    for (int i = 0; i < num_bgs; i++) {
        len_bgs[i] = (int) bgs[i].size();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, num_bgs - 1);
    int bid = distr(gen);

    const double step_x = 0.5, step_y = 0.5;
    int pid = 0, bi = 0;
    center[0] = center[1] = center[2] = 0;

    double x = -2 * size;
    while (x <= 2 * size) {
        double y = std::sqrt(size * size - (std::abs(x) - size) * (std::abs(x) - size));
        points[0][pid] = x;
        points[1][pid] = y;
        points[2][pid] = 0;
        color_points[pid] = line;
        pid++;

        center[0] += x;
        center[1] += y;

        if (bid < num_bgs) {
            double y0 = size * std::acos(1 - std::abs(x / size)) - size * M_PI;
            while (y > y0) {
                points[0][pid] = x;
                points[1][pid] = y;
                points[2][pid] = 0;
                color_points[pid] = bgs[bid][bi++];
                if (bi == len_bgs[bid]) {
                    bi = 0;
                }
                pid++;

                center[0] += x;
                center[1] += y;
                y -= step_y;
            }
        }

        x += step_x;
    }

    x = -2 * size;
    while (x <= 2 * size) {
        double y = size * std::acos(1 - std::abs(x / size)) - size * M_PI;
        points[0][pid] = x;
        points[1][pid] = y;
        points[2][pid] = 0;
        color_points[pid] = line;
        pid++;

        center[0] += x;
        center[1] += y;
        x += step_x;
    }

    *num_points = pid;
    center[0] /= pid;
    center[1] /= pid;
}

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
        if (active_objects[id]) {
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

void handle_magic() {
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

    auto trans_x = (double *) malloc(MAX_NUM_OBJECTS * sizeof(double));
    auto trans_y = (double *) malloc(MAX_NUM_OBJECTS * sizeof(double));
    auto rotate_x = (double *) malloc(MAX_NUM_OBJECTS * sizeof(double));
    auto rotate_y = (double *) malloc(MAX_NUM_OBJECTS * sizeof(double));
    auto rotate_z = (double *) malloc(MAX_NUM_OBJECTS * sizeof(double));
    auto axis = malloc_double_matrix(MAX_NUM_OBJECTS, DIM);

    uint64_t sum_time = 300 * 1000;
    uint64_t crt_time = 0;

    int time_span = 0, time_span0 = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> time_rd(TIME_SPAN0, TIME_SPAN1);
    std::uniform_int_distribution<int> heart_rd(HEART_SIZE_0, HEART_SIZE_1);
    std::uniform_real_distribution<double> trans_x_rd(TRANS0, TRANS1);
    std::uniform_real_distribution<double> trans_y_rd(TRANS0, TRANS1 * 2);
    std::uniform_real_distribution<double> rotate_x_rd(0, ROTATE0);
    std::uniform_real_distribution<double> rotate_y_rd(0, ROTATE1);
    std::uniform_real_distribution<double> rotate_z_rd(0, ROTATE0);
    std::uniform_real_distribution<double> pos_x_rd(0, WIDTH * WIDTH_RATE);
    std::uniform_real_distribution<double> pos_z_rd(0, WIDTH * WIDTH_RATE);

    while (crt_time < sum_time) {
        if (time_span >= time_span0) {
            time_span = 0;
            time_span0 = time_rd(gen);
            for (int i = 0; i < MAX_NUM_OBJECTS; i++) {
                if (!active_objects[i]) {
                    active_objects[i] = true;

                    add_heart(heart_rd(gen), points[i], color_points[i], &num_points[i], center_objects[i]);
                    rotate3d_z(points[i], num_points[i], M_PI, center_objects[i]);

                    double new_pos[3] = {pos_x_rd(gen), Y0, pos_z_rd(gen)};
                    move_object(points[i], num_points[i], center_objects[i], new_pos);

                    trans_x[i] = 1;
                    trans_y[i] = trans_y_rd(gen);
                    rotate_x[i] = rotate_x_rd(gen);
                    rotate_y[i] = rotate_y_rd(gen);
                    rotate_z[i] = rotate_z_rd(gen);
                    axis[i][0] = center_objects[i][0] + pos_x_rd(gen) / 10;
                    axis[i][1] = Y0;
                    axis[i][2] = center_objects[i][2] + pos_z_rd(gen) / 10;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_NUM_OBJECTS; i++) {
            if (active_objects[i]) {
                rotate3d_x(points[i], num_points[i], rotate_x[i], center_objects[i]);
                rotate3d_y(points[i], num_points[i], rotate_y[i], axis[i]);
                rotate3d_z(points[i], num_points[i], rotate_z[i], center_objects[i]);
                trans3d(points[i], num_points[i], trans_x[i], trans_y[i], 0);
                center_objects[i][0] += trans_x[i];
                center_objects[i][1] += trans_y[i];
            }
        }

        render(points, color_points, num_points, MAX_NUM_OBJECTS, active_objects, screen);

        display_magic(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_LOOP));

        for (int i = 0; i < MAX_NUM_OBJECTS; i++) {
            if (center_objects[i][1] > 1.2 * HEIGHT_RATE * HEIGHT) {
                active_objects[i] = false;
            }
        }

        crt_time += TIME_LOOP;
        time_span += TIME_LOOP;
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

    free(trans_x);
    free(trans_y);
    free(rotate_x);
    free(rotate_y);
    free(rotate_z);
    free_matrix(axis, MAX_NUM_OBJECTS);
}
