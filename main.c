/**
 * @file        main.c 
 * @brief       The main entry point into the program.
 */

#include <stdio.h> 
#include <inttypes.h>
#include "debug.h"
#include "file_utils.h"
#include "elf_parser.h"

/**
 * FUNCITON NAME:       main
 * 
 * DESCRIPTION:         Main entry point of program, will load and run an ELF file
 */
int main(int argc, const char *argv[])
{
       
        if (argc < 2){
                printf("Usage: %s [elf_binary] [arguments]\n", argv[0]);
                return 0;
        }

        uint8_t *dest;
        const char *filename = argv[1];

        int err = file_to_buffer(&dest, filename);
        if (err != SUCCESS){
                debug_print("Failed to read file into buffer error: %d.\n", err);
                return err;
        }

        struct ELF elf;
        err = parse_elf(&elf, dest);
        if (err != SUCCESS){
                debug_print("Failed to parse ELF, error %d.\n", err);
                return err;
        }

            
        return 0;
}
