/**
 * @file        file_utils
 * @brief       Simple file utilities used for various projects.
 */
#include "error.h"
#include "file_utils.h"
#include "stddef.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief       Gets the size of a given file.
 *
 * @param       fd              The file descriptor of an open file.
 * 
 * @returns     The size of the file, in bytes, or a negative number if an error 
 *              occurred (propagated from ftell). In case of error, the position
 *              of the file may have changed.
 */
long get_file_size(FILE *fd)
{
        long len, fpos;
        fpos = ftell(fd);
        if (fpos < 0)
                return FILE_OPERATION_ERR;
        if (fseek(fd, 0L, SEEK_END) != 0)
                return FILE_OPERATION_ERR;
        len = ftell(fd);
        if (len < 0)
                return FILE_OPERATION_ERR;
        if (fseek(fd, fpos, SEEK_SET) != 0)
                return FILE_OPERATION_ERR;
        return len;
}

/**
 * @brief       Reads a file into the buffer provided.
 * 
 * @param       *buf            A buffer large enough to hold the file.
 * @param       *fd             The file to read into the buffer.
 * @param       fileSize        The size of the file, in bytes.
 */
static int read_into_buffer(uint8_t *buf, FILE *fd, size_t fileSize)
{
        if (buf == NULL || fd == NULL)
                return NULL_ARG;
        fread(buf, sizeof(uint8_t), fileSize, fd);
        if (ferror(fd) != 0)
                return FILE_OPERATION_ERR;
        return SUCCESS;
}

/**
 * @brief       Given a file, read into into a buffer.
 *
 * @param       **buf           A pointer where the resulting buffer should be 
 *                              stored.
 * @param       *buflen         The returned length of buf.
 * @param       *filename       The name of the file to read.
 *
 * @returns     Success if no error occured, the error otherwise.
 */
int file_to_buffer(uint8_t **buf, uint32_t* retlen, const char *filename)
{
        if (buf == NULL || filename == NULL || retlen == NULL)
                return NULL_ARG;
        
        FILE *fd = fopen(filename, "rb");
        if (fd == NULL)
                return FILE_OPERATION_ERR;

        int size = get_file_size(fd);
        if (size < 0)
                return FILE_OPERATION_ERR;
        if (size == 0)
                return FILE_ZERO_LENGTH;
        *buf = (uint8_t *)malloc(size * sizeof(uint8_t));
        *retlen = size * sizeof(uint8_t);
        if (*buf == NULL)
                return OUT_OF_MEMORY;
        
        int err = read_into_buffer(*buf, fd, size);
        if (err != SUCCESS)
                return err;
        
        return SUCCESS; 
}





