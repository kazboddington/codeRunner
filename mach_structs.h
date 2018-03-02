#ifndef MACH_STRUCTS_H
#define MACH_STRUCTS_H

enum ECPU_TYPE {
        ECPU_ANY        = -1,
        ECPU_VAX        = 1,
        ECPU_MC680x0    = 6,
        ECPU_x86        = 7,
        ECPU_MC98000    = 10,
        ECPU_HPPA       = 11,
        ECPU_ARM        = 12,
        ECPU_MC88000    = 13,
        ECPU_SPARC      = 14,
        ECPU_I860       = 15,
        ECPU_POWERPC    = 18,
        ECPU_x86_64     = 16777223,
        ECPU_POWERPC_64 = 16777234
};

/* Declaration for the mach magic numbers. */
#define MACH_HDR_MAGIC 0xFEEDFACF

/* Definitions for the cpu subtype field in the mach-o header */
#define CPU_SUBTYPE_MASK        0xff000000      /* mask for feature flags */
#define CPU_SUBTYPE_LIB64       0x80000000      /* 64 bit libraries */
#define CPU_SUBTYPE_I386_ALL    3
#define CPU_SUBTYPE_MULTIPLE    -1

/* Definitions for the filetype field in the mach-o header */
#define	MH_OBJECT	0x1		/* relocatable object file */
#define	MH_EXECUTE	0x2		/* demand paged executable file */
#define	MH_FVMLIB	0x3		/* fixed VM shared library file */
#define	MH_CORE		0x4		/* core file */
#define	MH_PRELOAD	0x5		/* preloaded executable file */
#define	MH_DYLIB	0x6		/* dynamically bound shared library */
#define	MH_DYLINKER	0x7		/* dynamic link editor */
#define	MH_BUNDLE	0x8		/* dynamically bound bundle file */
#define	MH_DYLIB_STUB	0x9		/* shared library stub for static */
					/*  linking only, no section contents */
#define	MH_DSYM		0xa		/* companion file with only debug */
					/*  sections */
#define	MH_KEXT_BUNDLE	0xb		/* x86_64 kexts */

/* Constants for the flags field of the mach_header */
#define	MH_NOUNDEFS	0x1		/* the object file has no undefined
					   references */

struct __attribute__((__packed__)) Mach_header { 
        uint32_t magic;
        uint32_t cputype;
        uint32_t cpusubtype;
        uint32_t filetype;
        uint32_t ncmds;
        uint32_t sizeofcmds;
        uint32_t flags;
}; 

struct __attribute__((__packed__)) Load_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
};

struct __attribute__((__packed__)) Uuid_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        uint8_t  uuid[16]; 
};

struct __attribute__((__packed__)) Segment_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        char     segname[16]; 
        uint32_t vmaddr; 
        uint32_t vmsize; 
        uint32_t fileoff; 
        uint32_t filesize; 
        uint32_t maxprot; 
        uint32_t initprot; 
        uint32_t nsects; 
        uint32_t flags; 
};

struct __attribute__((__packed__)) Segment_command_64 { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        char     segname[16]; 
        uint64_t vmaddr; 
        uint64_t vmsize; 
        uint64_t fileoff; 
        uint64_t filesize; 
        uint32_t maxprot;        
        uint32_t initprot; 
        uint32_t nsects; 
        uint32_t flags; 
};

struct __attribute__((__packed__)) Section { 
        char     sectname[16]; 
        char     segname[16]; 
        uint32_t addr; 
        uint32_t size; 
        uint32_t offset; 
        uint32_t align; 
        uint32_t reloff;
        uint32_t nreloc; 
        uint32_t flags; 
        uint32_t reserved1; 
        uint32_t reserved2; 
};

struct __attribute__((__packed__)) Section_64 { 
        char     sectname[16]; 
        char     segname[16]; 
        uint64_t addr; 
        uint64_t size; 
        uint32_t offset; 
        uint32_t align; 
        uint32_t reloff;
        uint32_t nreloc; 
        uint32_t flags; 
        uint32_t reserved1; 
        uint32_t reserved2; 
};

struct __attribute__((__packed__)) Twolevel_hints_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        uint32_t offset; 
        uint32_t nhints; 
};

struct __attribute__((__packed__)) Twolevel_hint { 
        uint32_t isub_image:8, itoc:24; 
};

union __attribute__((__packed__)) Lc_str { 
        uint32_t offset; 
        // Pointer may be here, but not used in Mach-O files.
};

struct __attribute__((__packed__)) Dylib { 
        union Lc_str    name; 
        uint32_t        timestamp; 
        uint32_t        current_version; 
        uint32_t        compatibility_version; 
};

struct Dylib_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        struct Dylib dylib; 
};

struct Dylinker_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        union Lc_str name; 
};

struct Prebound_dylib_command { 
        uint32_t        cmd; 
        uint32_t        cmdsize; 
        union Lc_str    name; 
        uint32_t        nmodules; 
        union Lc_str    linked_modules; 
};

struct Thread_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        /* uint32_t flavor;*/ 
        /* uint32_t count; */ 
        /* struct cpu_thread_state state;*/ 
};

struct Routines_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        uint32_t init_address; 
        uint32_t init_module; 
        uint32_t reserved[6]; 
};

struct Routines_command_64 { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        uint64_t init_address; 
        uint64_t init_module; 
        uint64_t reserved[6]; 
};

struct Sub_framework_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        union Lc_str umbrella; 
};

struct Symtab_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        uint32_t symoff; 
        uint32_t nsyms; 
        uint32_t stroff; 
        uint32_t strsize; 
};

struct Nlist { 
        union { 
                // if LP64 may have other field here.
                int32_t n_strx; 
        } n_un; 
        uint8_t n_type; 
        uint8_t n_sect; 
        int16_t n_desc;
        uint32_t n_value; 
};

struct Nlist_64 { 
        union { uint32_t n_strx; } n_un; 
        uint8_t n_type; 
        uint8_t n_sect; 
        uint16_t n_desc; 
        uint64_t n_value; 
};

struct Dysymtab_command { 
        uint32_t cmd; 
        uint32_t cmdsize; 
        uint32_t ilocalsym; 
        uint32_t nlocalsym; 
        uint32_t iextdefsym; 
        uint32_t nextdefsym;
        uint32_t iundefsym; 
        uint32_t nundefsym; 
        uint32_t tocoff; 
        uint32_t ntoc; 
        uint32_t modtaboff; 
        uint32_t nmodtab; 
        uint32_t extrefsymoff;
        uint32_t nextrefsyms; 
        uint32_t indirectsymoff; 
        uint32_t nindirectsyms; 
        uint32_t extreloff; 
        uint32_t nextrel; 
        uint32_t locreloff; 
        uint32_t nlocrel; 
};

struct Dylib_table_of_contents { 
        uint32_t symbol_index; 
        uint32_t module_index; 
};
struct Dylib_module { 
        uint32_t module_name; 
        uint32_t iextdefsym; 
        uint32_t nextdefsym; 
        uint32_t irefsym; 
        uint32_t nrefsym; 
        uint32_t ilocalsym; 
        uint32_t nlocalsym; 
        uint32_t iextrel; 
        uint32_t nextrel; 
        uint32_t iinit_iterm; 
        uint32_t ninit_nterm; 
        uint32_t objc_module_info_addr; 
        uint32_t objc_module_info_size; 
};

struct Dylib_module_64 { 
        uint32_t module_name; 
        uint32_t iextdefsym; 
        uint32_t nextdefsym; 
        uint32_t irefsym; 
        uint32_t nrefsym; 
        uint32_t ilocalsym; 
        uint32_t nlocalsym; 
        uint32_t iextrel; 
        uint32_t nextrel; 
        uint32_t iinit_iterm; 
        uint32_t ninit_nterm; 
        uint32_t objc_module_info_size; 
        uint64_t objc_module_info_addr; 
};

struct Dylib_reference { 
        uint32_t isym:24, flags:8; 
};

struct Relocation_info { 
        int32_t r_address; 
        uint32_t r_symbolnum:24, 
                 r_pcrel:1, 
                 r_length:2, 
                 r_extern:1, 
                 r_type:4;
};
struct Scattered_relocation_info { 
#ifdef __BIG_ENDIAN__ 
        uint32_t r_scattered:1, 
                 r_pcrel:1, 
                 r_length:2, 
                 r_type:4, 
                 r_address:24; 
        int32_t r_value;
#else  /* (little endian assumed) */
        uint32_t r_address:24, 
                 r_type:4, 
                 r_length:2, 
                 r_pcrel:1, 
                 r_scattered:1; 
        int32_t r_value; 
#endif /* __LITTLE_ENDIAN__ */ 
};

struct __attribute__((__packed__)) Mach {
        struct Mach_header mach_header;

};

#endif /* MACH_STRUCTS_H */
