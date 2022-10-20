#ifndef MAGIC_MATH_HANDLER_H
#define MAGIC_MATH_HANDLER_H

#include "iostream"
#include "cstdio"
#include "cmath"
#include "chrono"
#include "thread"
#include "random"

uint8_t **malloc_uint8_matrix(int num_rows, int num_cols);

void free_matrix(char **mat, int num_rows);

char **malloc_char_matrix(int num_rows, int num_cols);

void free_matrix(uint8_t **mat, int num_rows);

double **malloc_double_matrix(int num_rows, int num_cols);

void free_matrix(double **mat, int num_rows);

void mul_matrix(double **a, double **b, double **c, int n, int m, int k);

void trans2d(double **mat, int num_cols, double x0, double y0);

void trans3d(double **mat, int num_cols, double x0, double y0, double z0);

void rotate2d(double **mat, int num_cols, double alpha, const double *p = nullptr);

void rotate3d_x(double **mat, int num_cols, double alpha, const double *p = nullptr);

void rotate3d_y(double **mat, int num_cols, double alpha, const double *p = nullptr);

void rotate3d_z(double **mat, int num_cols, double alpha, const double *p = nullptr);

#endif //MAGIC_MATH_HANDLER_H
