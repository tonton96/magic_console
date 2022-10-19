#include "object_creator.h"

void add_heart(double size, double **points, char *color_points, int *num_points, double *center) {
    const int num_lines = 2;
    const int num_backgrounds = 5;
    const std::string lines[num_lines] = {"|Happy Viet Nam women's day 20/10|", "|I <3 U|"};
    const char background[num_backgrounds] = {'+', 'o', '*', 'x'};

    int len_lines[num_lines];
    for(int i = 0; i < num_lines; i++){
        len_lines[i] = (int)lines[i].size();
    }
    int lid = std::rand() % num_lines;
    int bid = std::rand() % num_backgrounds;

    const double step_x = 0.5, step_y = 0.5;
    int pid = 0, li = 0;
    center[0] = center[1] = center[2] = 0;

    double x = -2 * size;
    while (x <= 2 * size) {
        double y = std::sqrt(size * size - (std::abs(x) - size) * (x - size));
        points[0][pid] = x;
        points[1][pid] = y;
        points[2][pid] = 0;
        color_points[pid] = lines[lid][li++];

        pid++;
        if (li == len_lines[lid]) {
            li = 0;
        }

        center[0] += x;
        center[1] += y;

        if(bid != num_backgrounds - 1) {
            double y0 = size * std::acos(1 - std::abs(x / size)) - size * M_PI;
            while (y > y0) {
                points[0][pid] = x;
                points[1][pid] = y;
                points[2][pid] = 0;
                color_points[pid] = background[bid];
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
        color_points[pid] = lines[lid][li++];

        pid++;
        if (li == len_lines[lid]) {
            li = 0;
        }

        center[0] += x;
        center[1] += y;
        x += step_x;
    }

    *num_points = pid;
    center[0] /= pid;
    center[1] /= pid;
}


