#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#define EI_MAG_BYTES_0  0xCF
#define EI_MAG_BYTES_1  0xFA
#define EI_MAG_BYTES_2  0xED
#define EI_MAG_BYTES_3  0xFE
#define EI_CLASS        0x01
#define EI_DATA         0x01
#define EI_VERSION      0x01

struct __attribute__((__packed__)) ELF_e_identa {
        uint8_t                 ei_mag[4];
        uint8_t                 ei_class;
        uint8_t                 ei_data;
        uint32_t                ei_version;
};

struct __attribute__((__packed__)) ELF32_hdr {
        struct ELF_e_identa     e_ident;
        uint16_t                e_type;
        uint16_t                e_machine;
        uint32_t                e_version;
        uint32_t                e_entry;
        uint32_t                e_phoff;
        uint32_t                e_shoff;
        uint32_t                e_flags;
        uint16_t                e_ehsize;
        uint16_t                e_phentsize;
        uint16_t                e_phnum;
        uint16_t                e_shentsize;
        uint16_t                e_shnum;
        uint16_t                e_shstrndx;
};


int parse_elf(struct ELF32_hdr* elf, uint8_t* buf, uint32_t buflen);

#endif /* ELF_PARSER_H */
