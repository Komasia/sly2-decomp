// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -fno-exceptions -G0
// SLY2_ASM: gnu-reorder-db
extern "C" int D_0045022C;
extern "C" void __do_global_ctors(void);
void __main(void)
{
    if (D_0045022C == 0) {
        D_0045022C = 1;
        __do_global_ctors();
    }
}
