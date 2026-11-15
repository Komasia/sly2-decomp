// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
/* PatchIsNeeded (libkernel): old kernels drop the "version" field (bits 13-15) of the OSD config word. Write
   version 1, read it back, restore the original; if it reads back as 0 the ExecPS2 patch is needed. */
#define OSD_VERSION_SHIFT 13
#define OSD_VERSION_MASK  (7 << OSD_VERSION_SHIFT)
int func_00234AD0(unsigned int *);  /* GetOsdConfigParam (syscall 0x4B) */
int func_00234AC0(unsigned int *);  /* SetOsdConfigParam (syscall 0x4A) */

int PatchIsNeeded(void)
{
    unsigned int saved, probe;
    func_00234AD0(&saved);
    probe = (saved & ~OSD_VERSION_MASK) | (1 << OSD_VERSION_SHIFT);
    func_00234AC0(&probe);
    func_00234AD0(&probe);
    func_00234AC0(&saved);
    return ((probe >> OSD_VERSION_SHIFT) & 7) == 0;
}
