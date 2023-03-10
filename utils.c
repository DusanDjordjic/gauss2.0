#include "utils.h"
#include <stdlib.h>

FILE* safe_fopen(const char* filepath, const char* mode, int error_code)
{
    FILE* fp = fopen(filepath, mode);
    if (fp == NULL) {
        fprintf(stderr, "Unable to open file \"%s\"\n", filepath);
        exit(error_code);
    }

    return fp;
}

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
