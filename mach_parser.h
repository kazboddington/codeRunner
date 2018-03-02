#ifndef MACH_PARSER_H
#define MACH_PARSER_H
#include "mach_structs.h"

int parse_mach(struct Mach *mach, uint8_t* buf, uint32_t buflen);

#endif /* MACH_PARSER_H */
