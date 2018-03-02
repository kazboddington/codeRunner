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
#define CPU_SUBTYPE_MASK       0xff000000      /* mask for feature flags */
#define CPU_SUBTYPE_LIB64      0x80000000      /* 64 bit libraries */
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
        uint32_t  magic;
        uint32_t cputype;
        uint32_t cpusubtype;
        uint32_t filetype;
        uint32_t ncmds;
        uint32_t sizeofcmds;
        uint32_t flags;
}; 

struct Mach {
        struct Mach_header mach_header;
};
#endif /* MACH_STRUCTS_H */
