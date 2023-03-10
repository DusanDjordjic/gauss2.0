#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    unsigned int cols;
    unsigned int rows;
    double** data;
} Matrix;

void matrix_init(Matrix* matrix);
void matrix_free(Matrix* matrix);
void matrix_print(Matrix* matrix);
void matrix_add_row(Matrix* matrix, double* row);
double* matrix_parse_row(char* row, unsigned int* len);
int matrix_row_score(const double* row, unsigned int n);
void matrix_sort_rows(Matrix* matrix, unsigned int start);

#endif
