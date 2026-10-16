// WIP: only diff is the sibcall `j EIntr` with frame teardown (Sony compiler sibcalls; 114 cannot).
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
int DIntr(void);
int EIntr(void);
void setD3_CHCR(unsigned int v)
{
    int r = DIntr();
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
    *(volatile unsigned int *)0x1000B000 = v;
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
    if (r) EIntr();
}
