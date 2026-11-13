// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
extern char D_0044C268[];
extern char D_002C49E4[];
extern void *D_002C4A9C;
int memcmp(const void *, const void *, unsigned int);
int func_00238E70(void)
{
    char *b = D_002C49E4;
    char *a = D_0044C268;
    int r = 0;
    if (memcmp(a, b, 4) && memcmp(a, D_002C4A9C, 4))
        r = memcmp(b, D_002C4A9C, 4) != 0;
    return r;
}
