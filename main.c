/**
 * @file        main.c 
 * @brief       The main entry point into the program.
 */

#include <stdio.h> 
#include <inttypes.h>
#include "debug.h"
#include "file_utils.h"
#include "mach_parser.h"
#include "mach_structs.h"

/**
 * @brief       Main entry point of program, will load and run an ELF file
 */
int main(int argc, const char *argv[])
{
        if (argc < 2){
                printf("Usage: %s [Mach-o file] [arguments]\n", argv[0]);
                return 0;
        }

        uint8_t *dest;
        const char *filename = argv[1];

        uint32_t destlen = 0;
        int err = file_to_buffer(&dest, &destlen, filename);
        if (err != SUCCESS){
                debug_print("Failed to read file into buf error: %d.\n", err);
                return err;
        }

        struct Mach mach;
        err = parse_mach(&mach, dest, destlen);
        if (err != SUCCESS){
                debug_print("Failed to parse Mach, error %d.\n", err);
                return err;
        }
            
        return 0;
}
