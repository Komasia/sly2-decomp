// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
void SetT2(volatile int *addr, int val);
// name: libkernel SetT2_COUNT (SetT2 of 0xB0001000; suggested by l1)
void SetT2_COUNT(int val)
{
    SetT2((volatile int *)0xB0001000, val);
}
