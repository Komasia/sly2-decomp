// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* Loadfile module version check: nonzero if the IOP server version (D_0044C268) matches neither the library\n   version nor the alternate one, and those two differ. */
extern char D_0044C268[];   /* version reported by the IOP server */
extern char D_002C49E4[];   /* library version */
extern void *D_002C4A9C;    /* alternate accepted version */
int memcmp(const void *, const void *, unsigned int);
int func_00238E70(void)
{
    char *lib = D_002C49E4;
    char *iop = D_0044C268;
    int mismatch = 0;
    if (memcmp(iop, lib, 4) && memcmp(iop, D_002C4A9C, 4))
        mismatch = memcmp(lib, D_002C4A9C, 4) != 0;
    return mismatch;
}
