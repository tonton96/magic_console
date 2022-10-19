#ifndef MAGIC_MAGIC_SHOW_H
#define MAGIC_MAGIC_SHOW_H

#include "math_handler.h"

#define MAX_NUM_OBJECTS 15
#define MAX_POINTS      10240
#define DIM             3
#define WIDTH           250
#define HEIGHT          60
#define MAX_Z           1e6
#define WIDTH_RATE      1
#define HEIGHT_RATE     2
#define TIME_SPAN0      1000
#define TIME_SPAN1      2000
#define TIME_LOOP       100
#define TRANS0          0.5
#define TRANS1          1.0
#define ROTATE0         0.02
#define ROTATE1         0.1
#define Y0              -10
#define HEART_SIZE_0    3
#define HEART_SIZE_1    8

void add_heart(double size, double **points, char *color_points, int *num_points, double *center);

void move_object(double **points, int num_points, double *center, const double *position);

void render(double ***all_points, char **color_points, const int *num_points, int num_objects, std::string &screen);

void show_magic();

#endif //MAGIC_MAGIC_SHOW_H
