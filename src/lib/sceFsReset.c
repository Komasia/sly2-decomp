// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceFsReset (fileio): forget the fileio server binding (sceFsInit runs again on the next call). */
extern int D_002C4A7C;      /* fileio initialised */
extern char D_0044BDA8[];   /* IOP fileio version */
void *s1_memset(void *p, int c, unsigned int n) asm("memset");
int sceFsReset(void)
{
    D_002C4A7C = 0;
    s1_memset(D_0044BDA8, 0, 4);
    return 0;
}
