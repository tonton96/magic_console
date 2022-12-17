#ifndef MAGIC_MAGIC_SHOW_H
#define MAGIC_MAGIC_SHOW_H

#include "math_handler.h"

#define MAX_NUM_OBJECTS 15
#define MAX_POINTS      10240
#define DIM             3
#define WIDTH           200
#define HEIGHT          45
#define MAX_Z           1e6
#define WIDTH_RATE      1
#define HEIGHT_RATE     2
#define TIME_SPAN0      1000
#define TIME_SPAN1      2000
#define TIME_LOOP       120
#define TRANS0          0.25
#define TRANS1          0.50
#define ROTATE0         0.01
#define ROTATE1         0.05
#define Y0              -10
#define HEART_SIZE_0    3
#define HEART_SIZE_1    8

void handle_magic();

void display_magic(const std::string &content);

#endif //MAGIC_MAGIC_SHOW_H
