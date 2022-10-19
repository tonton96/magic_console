#include "math_handler.h"

uint8_t **malloc_uint8_matrix(int num_rows, int num_cols) {
    auto mat = (uint8_t **) malloc(num_rows * (int) sizeof(uint8_t *));
    for (int i = 0; i < num_rows; i++) {
        mat[i] = (uint8_t *) malloc(num_cols * (int) sizeof(uint8_t));
    }
    return mat;
}

char **malloc_char_matrix(int num_rows, int num_cols) {
    auto mat = (char **) malloc(num_rows * (int) sizeof(char *));
    for (int i = 0; i < num_rows; i++) {
        mat[i] = (char *) malloc(num_cols * (int) sizeof(char));
    }
    return mat;
}

void free_matrix(uint8_t **mat, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

void free_matrix(char **mat, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

double **malloc_double_matrix(int num_rows, int num_cols) {
    auto mat = (double **) malloc(num_rows * (int) sizeof(double *));
    for (int i = 0; i < num_rows; i++) {
        mat[i] = (double *) malloc(num_cols * (int) sizeof(double));
    }
    return mat;
}

void free_matrix(double **mat, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

void mul_matrix(double **a, double **b, double **c, int n, int m, int k) {
    for (int nn = 0; nn < n; nn++) {
        for (int kk = 0; kk < k; kk++) {
            double val = 0;
            for (int mm = 0; mm < m; mm++) {
                val += a[nn][mm] * b[mm][kk];
            }
            c[nn][kk] = val;
        }
    }
}

void trans2d(double **mat, int num_cols, double x0, double y0) {
    for (int i = 0; i < num_cols; i++) {
        mat[0][i] += x0;
        mat[1][i] += y0;
    }
}

void trans3d(double **mat, int num_cols, double x0, double y0, double z0) {
    for (int i = 0; i < num_cols; i++) {
        mat[0][i] += x0;
        mat[1][i] += y0;
        mat[2][i] += z0;
    }
}

void rotate2d(double **mat, int num_cols, double alpha, const double *p) {
    auto temp = malloc_double_matrix(2, num_cols);
    auto trans = malloc_double_matrix(2, 2);
    trans[0][0] = std::cos(alpha);
    trans[0][1] = -std::sin(alpha);
    trans[1][0] = std::sin(alpha);
    trans[1][1] = std::cos(alpha);

    if (p == nullptr) {
        mul_matrix(trans, mat, temp, 2, 2, num_cols);
    } else {
        trans2d(mat, num_cols, -p[0], -p[1]);
        mul_matrix(trans, mat, temp, 2, 2, num_cols);
        trans2d(temp, num_cols, p[0], p[1]);
    }

    memcpy(mat[0], temp[0], num_cols * sizeof(double));
    memcpy(mat[1], temp[1], num_cols * sizeof(double));

    free_matrix(trans, 2);
    free_matrix(temp, 2);
}

void rotate3d_x(double **mat, int num_cols, double alpha, const double *p) {
    auto temp = malloc_double_matrix(3, num_cols);
    auto trans = malloc_double_matrix(3, 3);
    trans[0][0] = 1;
    trans[0][1] = 0;
    trans[0][2] = 0;
    trans[1][0] = 0;
    trans[1][1] = std::cos(alpha);
    trans[1][2] = -std::sin(alpha);
    trans[2][0] = 0;
    trans[2][1] = std::sin(alpha);
    trans[2][2] = std::cos(alpha);

    if (p == nullptr) {
        mul_matrix(trans, mat, temp, 3, 3, num_cols);
    } else {
        trans3d(mat, num_cols, 0, -p[1], -p[2]);
        mul_matrix(trans, mat, temp, 3, 3, num_cols);
        trans3d(temp, num_cols, 0, p[1], p[2]);
    }

    memcpy(mat[0], temp[0], num_cols * sizeof(double));
    memcpy(mat[1], temp[1], num_cols * sizeof(double));
    memcpy(mat[2], temp[2], num_cols * sizeof(double));

    free_matrix(trans, 3);
    free_matrix(temp, 3);
}

void rotate3d_y(double **mat, int num_cols, double alpha, const double *p) {
    auto temp = malloc_double_matrix(3, num_cols);
    auto trans = malloc_double_matrix(3, 3);
    trans[0][0] = std::cos(alpha);
    trans[0][1] = 0;
    trans[0][2] = std::sin(alpha);
    trans[1][0] = 0;
    trans[1][1] = 1;
    trans[1][2] = 0;
    trans[2][0] = -std::sin(alpha);
    trans[2][1] = 0;
    trans[2][2] = std::cos(alpha);

    if (p == nullptr) {
        mul_matrix(trans, mat, temp, 3, 3, num_cols);
    } else {
        trans3d(mat, num_cols, -p[0], 0, -p[2]);
        mul_matrix(trans, mat, temp, 3, 3, num_cols);
        trans3d(temp, num_cols, p[0], 0, p[2]);
    }

    memcpy(mat[0], temp[0], num_cols * sizeof(double));
    memcpy(mat[1], temp[1], num_cols * sizeof(double));
    memcpy(mat[2], temp[2], num_cols * sizeof(double));

    free_matrix(trans, 3);
    free_matrix(temp, 3);
}

void rotate3d_z(double **mat, int num_cols, double alpha, const double *p) {
    auto temp = malloc_double_matrix(3, num_cols);
    auto trans = malloc_double_matrix(3, 3);
    trans[0][0] = std::cos(alpha);
    trans[0][1] = -std::sin(alpha);
    trans[0][2] = 0;
    trans[1][0] = std::sin(alpha);
    trans[1][1] = std::cos(alpha);
    trans[1][2] = 0;
    trans[2][0] = 0;
    trans[2][1] = 0;
    trans[2][2] = 1;

    if (p == nullptr) {
        mul_matrix(trans, mat, temp, 3, 3, num_cols);
    } else {
        trans3d(mat, num_cols, -p[0], -p[1], -p[2]);
        mul_matrix(trans, mat, temp, 3, 3, num_cols);
        trans3d(temp, num_cols, p[0], p[1], p[2]);
    }

    memcpy(mat[0], temp[0], num_cols * sizeof(double));
    memcpy(mat[1], temp[1], num_cols * sizeof(double));
    memcpy(mat[2], temp[2], num_cols * sizeof(double));

    free_matrix(trans, 3);
    free_matrix(temp, 3);
}