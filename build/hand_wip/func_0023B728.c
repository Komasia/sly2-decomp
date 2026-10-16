// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* __do_global_ctors (libgcc2 DO_GLOBAL_CTORS_BODY, no atexit); D_002C85C0 = __CTOR_LIST__. */
/* WIP (Claude agent): 10/44 - only s0/s1 swap between loop counter i and the strength-reduced pointer in the
   ctor-call loop. Tried int/unsigned/long i, decl order, while/do forms, explicit pointer, C++, 2.9 variants, -O3. */
typedef void (*func_ptr)(void);
extern func_ptr D_002C85C0[];

void func_0023B728(void)
{
    unsigned long nptrs = (unsigned long)D_002C85C0[0];
    unsigned i;
    if (nptrs == (unsigned long)-1)
        for (nptrs = 0; D_002C85C0[nptrs + 1] != 0; nptrs++);
    for (i = nptrs; i >= 1; i--)
        D_002C85C0[i]();
}
