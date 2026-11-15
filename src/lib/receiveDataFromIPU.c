// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* receiveDataFromIPU (libmpeg): start a fromIPU (channel 3) DMA of `size` bytes to `addr`. */
int DIntr(void);
int EIntr(void);
void receiveDataFromIPU(unsigned int addr, int size)
{
    int r = DIntr();
    if ((addr >> 28) == 7) {           /* scratchpad */
        addr &= 0x0FFFFFFF;
        addr |= 0x80000000;            /* MADR.SPR */
    } else
        addr &= 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B010 = addr;        /* D3_MADR */
    *(volatile unsigned int *)0x1000B020 = size >> 4;   /* D3_QWC */
    *(volatile unsigned int *)0x1000B000 = 0x100;       /* D3_CHCR: to memory, normal mode, start */
    if (r) EIntr();
}
