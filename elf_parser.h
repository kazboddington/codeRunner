#ifndef ELF_PARSER_H
#define ELF_PARSER_H


struct __attribute__((__packed__)) ELF_e_identa {
        uint32_t ei_mag;
        uint8_t ei_class;
        uint8_t ei_data;
        uint32_t ei_version;
};

struct ELF {
        struct ELF_e_identa e_ident;
};


int parse_elf(struct ELF* elf, uint8_t* buf);

#endif /* ELF_PARSER_H */
