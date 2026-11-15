// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -fno-exceptions -G0
// SLY2_ASM: gnu-reorder-db
/* __main (libgcc): run the global constructors once. */
extern "C" int D_0045022C;              /* initialized */
extern "C" void func_0023B728(void);    /* __do_global_ctors */
void __main(void)
{
    if (D_0045022C == 0) {
        D_0045022C = 1;
        func_0023B728();
    }
}
