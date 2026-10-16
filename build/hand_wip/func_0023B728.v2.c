// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* WIP (Claude agent): 7/44. __do_global_ctors body. Count-up loop gives the target's s0=pointer/s1=counter, but
   gcc then tests n with blez and copies n into the counter (daddu). Down-count forms all give the s0/s1 swap (10). */
typedef void (*func_ptr)(void);
extern func_ptr D_002C85C0[];
void func_0023B728(void)
{
    unsigned long nptrs = (unsigned long)D_002C85C0[0];
    int i, n;
    if (nptrs == (unsigned long)-1)
        for (nptrs = 0; D_002C85C0[nptrs + 1] != 0; nptrs++);
    n = nptrs;
    for (i = 0; i < n; i++)
        D_002C85C0[n - i]();
}
