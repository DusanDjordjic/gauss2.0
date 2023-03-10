#include "matrix.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matrix_load_from_file(FILE* fp, Matrix* mat);

int main(int argc, char** argv)
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Matrix mat;
    matrix_init(&mat);

    FILE* in = safe_fopen(argv[1], "r", EXIT_FAILURE);
    matrix_load_from_file(in, &mat);

    matrix_sort_rows(&mat, 0);
    matrix_print(&mat);
    matrix_free(&mat);
    fclose(in);
    return 0;
}

void matrix_load_from_file(FILE* fp, Matrix* mat)
{
    char* line = NULL;
    size_t line_len = 0;

    double* row_data;
    while (getline(&line, &line_len, fp) != EOF) {
        matrix_add_row(mat, matrix_parse_row(line, &mat->cols));
    }

    free(line);
}
