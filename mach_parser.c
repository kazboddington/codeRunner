/**
 * @file        mach_parser.c
 *
 * @brief       Parse a mach-o file.
 */
#include <inttypes.h>
#include "error.h"
#include "mach_structs.h"
#include "debug.h"

/**
 * @brief       Given a VALID mach-o headder, prints out the values in human
 *              readable form.
 *
 * @param       header  The mach header to verify.
 * @return      SUCCESS if the format is valid, relevant error otherwise.
 */
void print_mach_hdr(struct Mach_header* header)
{
        if (header == NULL)
                debug_print("Can't print mach-o headder - arg is NULL");
        printf("MACH-O HEADER\n");
        printf("\tMagic is: 0x%08x\n", header->magic);
        printf("\tCputype is 0x%8x, subtype 0x%8x\n", 
                        header->cputype, header->cpusubtype);
        printf("\tFiletype is %u\n", header->filetype);
        printf("\tNumber of commands is %u\n", header->ncmds);
        printf("\tTotal size of commands is %u\n", header->sizeofcmds);
        printf("\tFlags set are: ");
        uint32_t flags = header->flags;
        for (int i = 31; i >= 0; i--) 
                printf("%0x", (flags >> i) & 0x01);
        
        printf("\n");
}

/**
 * @brief       Check the values in the mach_header are valid.
 *
 * @param       header  The mach header to verify.
 * @return      SUCCESS if the format is valid, relevant error otherwise.
 */
int verify_mach_hdr(struct Mach_header* header)
{
        if (header == NULL)
                return NULL_ARG;
        
        if (header->magic != MACH_HDR_MAGIC) {
                debug_print("Magic was invalid.\n");
                return INVALID_MACHO;
        }

        if (header->cputype != ECPU_x86_64) {
                debug_print("cputype not valid or not implemented (%u).\n", 
                                header->cputype);
                return INVALID_MACHO;
        }

        if (header->cpusubtype != (CPU_SUBTYPE_I386_ALL | CPU_SUBTYPE_LIB64)) {
                debug_print("cpu subtype not recognise (%08x)\n", 
                                header->cpusubtype);
                return INVALID_MACHO;
        }
        
        if (header->filetype != MH_EXECUTE) {
                debug_print("No an executtable mach-o (filetype is %u).",
                                header->filetype);
                debug_print("This file type is currently not supported\n");
                return MACH_NOT_SUPPORTED;
        }

        if (!(header->flags & MH_NOUNDEFS)) {
                debug_print("Cannot execute, undefined refs flag set.\n");
                return INVALID_MACHO;
        }
        
        return SUCCESS;
}


/**
 * @brief       Take a buffer containing a mach-o file, validate it and parse
 *              it into the MACH structire.
 *
 * @param       *mach  The structure to be filled in by the parser.
 * @param       *buf    The buffer containing the mach file.
 * @param       buflen  The lenght of buf.
 *
 * @returns     SUCCESS or the relevant error (int).
 */
int parse_mach(struct Mach *mach, uint8_t* buf, uint32_t buflen)
{
        int bufoff = 0;
        if (buflen < sizeof(struct Mach_header)){
                debug_print("Mach not large enough to be valid.\n");
                return INVALID_MACHO;
        }

        struct Mach_header* hdr = (struct Mach_header *) buf;
        bufoff += sizeof(struct Mach_header *);
        int err = verify_mach_hdr(hdr);
        if (err  != SUCCESS)
                return err;
        print_mach_hdr(hdr);
         
        




        
        return SUCCESS;
}
