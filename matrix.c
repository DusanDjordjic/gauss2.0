#include "matrix.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void matrix_init(Matrix* matrix)
{
    matrix->cols = 0;
    matrix->rows = 0;
    matrix->data = NULL;
}

double* matrix_parse_row(char* row, unsigned int* len)
{
    unsigned int count = str_count_char(row, ',');
    double* data = malloc(sizeof(double) * (count + 1));
    unsigned int index = 0;

    char* token = strtok(row, ",");
    data[index] = strtod(token, NULL);

    index++;
    while ((token = strtok(NULL, ",")) != NULL) {
        data[index++] = strtod(token, NULL);
    }

    if (len != NULL) {
        *len = count + 1;
    }

    return data;
}

void matrix_free(Matrix* matrix)
{
    for (unsigned int r = 0; r < matrix->rows; r++) {
        free(matrix->data[r]);
    }

    free(matrix->data);
    matrix->data = NULL;
    matrix->rows = 0;
    matrix->cols = 0;
}

void matrix_print(Matrix* matrix)
{
    printf("%uX%u\n", matrix->rows, matrix->cols);
    for (unsigned int r = 0; r < matrix->rows; r++) {
        for (unsigned int c = 0; c < matrix->cols - 1; c++) {
            printf("%6.2lf\t", matrix->data[r][c]);
        }

        printf("= %6.2lf\n", matrix->data[r][matrix->cols - 1]);
    }
}

void matrix_add_row(Matrix* matrix, double* row)
{
    matrix->rows++;
    matrix->data = realloc(matrix->data, sizeof(double*) * matrix->rows);
    matrix->data[matrix->rows - 1] = row;
}

int matrix_row_score(const double* row, unsigned int n)
{
    int score = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (row[i] != 0) {
            return score;
        }
        score--;
    }

    return score;
}

void matrix_sort_rows(Matrix* matrix, unsigned int start)
{
    double* tmp;
    int best_score = 0;
    int tmp_score = 0;
    unsigned int to_swap_index;

    for (unsigned int i = start; i < matrix->rows - 1; i++) {
        to_swap_index = i;
        best_score = matrix_row_score(matrix->data[i], matrix->cols);

        for (unsigned int j = i + 1; j < matrix->rows; j++) {
            tmp_score = matrix_row_score(matrix->data[j], matrix->cols);
            if (tmp_score > best_score) {
                to_swap_index = j;
                best_score = tmp_score;
            }
        }

        tmp = matrix->data[to_swap_index];
        matrix->data[to_swap_index] = matrix->data[i];
        matrix->data[i] = tmp;
    }
}
