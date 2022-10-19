#ifndef MAGIC_MAGIC_SHOW_H
#define MAGIC_MAGIC_SHOW_H

#include "object_creator.h"

#define MAX_NUM_OBJECTS 50
#define MAX_POINTS      2048
#define DIM             3
#define WIDTH           100
#define HEIGHT          50
#define MAX_Z           1e6
#define WIDTH_RATE      1
#define HEIGHT_RATE     1.5

void render(double ***all_points, char **color_points, const int *num_points, int num_objects, std::string &screen);

void show_magic();

#endif //MAGIC_MAGIC_SHOW_H
