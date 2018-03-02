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
        if (e_identa->ei_mag[0] != EI_MAG_BYTES_0 ||
                        e_identa->ei_mag[1] != EI_MAG_BYTES_1 ||
                        e_identa->ei_mag[2] != EI_MAG_BYTES_2 ||
                        e_identa->ei_mag[3] != EI_MAG_BYTES_3) {
                debug_print("ei_mag bytes were invalid (%02x %02x %02x %02x)\n", 
                                e_identa->ei_mag[0], e_identa->ei_mag[1],
                                e_identa->ei_mag[2], e_identa->ei_mag[3]);
                return ELF_FORMAT_INVALID;
        }
        
        if (e_identa->ei_class != EI_CLASS){
                debug_print("ei_class invalid (%02x)", e_identa->ei_class);
                return ELF_FORMAT_INVALID;
        }

        if (e_identa->ei_data != EI_DATA){
                debug_print("ei_data invalid (%02x)", e_identa->ei_data);
                return ELF_FORMAT_INVALID;
        }

        if (e_identa->ei_version != EI_VERSION){
                debug_print("ei_version invalid (%02x)", e_identa->ei_version);
                return ELF_FORMAT_INVALID;
        }

        return SUCCESS;
}

/**
 * @brief       Take a buffer containing an ELF file and parse it, checking for
 *              errors and reading it into the ELF structure.
 *
 * @param       *elf            The elf object to be filled in.
 * @param       *buffer         A buffer containing the ELF file.
 */
int parse_elf(struct ELF32_hdr* elf, uint8_t* buf, uint32_t buflen)
{
        
        if (buflen < sizeof(struct ELF32_hdr)){
                debug_print("The ELF is to short to contain a valid ELF.\n");
                return  ELF_FORMAT_INVALID;
        }

        struct ELF_e_identa* e_identa = (struct ELF_e_identa *)buf;
        int err = parse_elf_e_identa(e_identa);
        if (err != SUCCESS){
                debug_print("Error parsing e_identa.\n");
                return err;
        }

        return SUCCESS;
}
