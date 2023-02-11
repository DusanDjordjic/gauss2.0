#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix_st {
    unsigned int cols;
    unsigned int rows;
    double** data;
} Matrix;

const char* variables = "xyzabcdefgh";

FILE* safe_fopen(const char* filepath, const char* mode, int error_code);
unsigned int str_count_char(const char* string, const char c)
{
    unsigned int count = 0;
    while (*string != '\0') {
        if (*string == c) {
            count++;
        }
        string++;
    }

    return count;
}

void matrix_init(Matrix* matrix)
{
    matrix->cols = 0;
    matrix->rows = 0;
    matrix->data = NULL;
}

void matrix_free(Matrix* matrix);
void matrix_print(Matrix* matrix);
void matrix_add_row(Matrix* matrix, double* row);
double* matrix_parse_row(char* row, unsigned int* len);
int matrix_row_score(const double* row, unsigned int n);
void matrix_sort_rows(Matrix* matrix, unsigned int start);

int main(int argc, char** argv)
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Load linear system of equations in some matrix
    Matrix mat;
    matrix_init(&mat);

    FILE* in = safe_fopen(argv[1], "r", EXIT_FAILURE);

    char* line = NULL;
    size_t line_len = 0;

    double* row_data;
    while (getline(&line, &line_len, in) != EOF) {
        matrix_add_row(&mat, matrix_parse_row(line, &mat.cols));
    }

    matrix_sort_rows(&mat, 0);
    matrix_print(&mat);
    matrix_free(&mat);
    fclose(in);
    return 0;
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

FILE* safe_fopen(const char* filepath, const char* mode, int error_code)
{
    FILE* fp = fopen(filepath, mode);
    if (fp == NULL) {
        fprintf(stderr, "Unable to open file \"%s\"\n", filepath);
        exit(error_code);
    }

    return fp;
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
            printf("%6.2lf%c\t", matrix->data[r][c], variables[c]);
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
