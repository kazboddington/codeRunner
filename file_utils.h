#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include "error.h"
#include <inttypes.h>
#include <stdio.h>

int file_to_buffer(uint8_t **buf, const char *filename);
long get_file_size(FILE *fd);


#endif /* FILE_UTILS_H */
