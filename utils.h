#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

FILE* safe_fopen(const char* filepath, const char* mode, int error_code);
unsigned int str_count_char(const char* string, const char c);

#endif
