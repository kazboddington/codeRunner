/**
 * @file        elf_parser.c
 * 
 * @brief       Various utilities used for parsing an ELF file.
 */

#include <inttypes.h>
#include <stdlib.h>
#include "elf_parser.h"
#include "error.h"
#include "debug.h"

/** 
 * @brief       Check the e_identa values, print them and return error if not 
 *              valid values
 *
 * @param       *e_identa       The e_identa to parse and print.
 *
 * @return      SUCCESS if the e_identa is valid. 
 *              INVALID_ELF if the e_identa is invalid.
 */
int parse_elf_e_identa(struct ELF_e_identa *e_identa)
{

        return SUCCESS;
}


/**
 * @brief       Take a buffer containing an ELF file and parse it, checking for
 *              errors and reading it into the ELF structure.
 *
 * @param       *elf            The elf object to be filled in.
 * @param       *buffer         A buffer containing the ELF file.
 */

int parse_elf(struct ELF* elf, uint8_t* buf)
{

        struct ELF_e_identa* e_identa = (struct ELF_e_identa *)buf;
        int err = parse_elf_e_identa(e_identa);
        int a;
        if (err != SUCCESS){
                debug_print("Error parsing e_identa %d.\n");
                return err;
        }


        return SUCCESS;
}
