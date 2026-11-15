// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* Fileio module version check: nonzero if the IOP server version (D_0044BDA8) matches neither the library\n   version nor the alternate one, and those two differ. */
extern char D_0044BDA8[];   /* version reported by the IOP server */
extern char D_002C49E4[];   /* library version */
extern void *D_002C4A90;    /* alternate accepted version */
int memcmp(const void *, const void *, unsigned int);
int func_00237DE0(void)
{
    char *lib = D_002C49E4;
    char *iop = D_0044BDA8;
    int mismatch = 0;
    if (memcmp(iop, lib, 4) && memcmp(iop, D_002C4A90, 4))
        mismatch = memcmp(lib, D_002C4A90, 4) != 0;
    return mismatch;
}
