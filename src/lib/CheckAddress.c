// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* CheckAddress: map an address in the 0x7xxxxxxx range (scratchpad / kernel-mode alias) to its KSEG0 form. */
unsigned int CheckAddress(unsigned int addr)
{
    if ((addr >> 28) == 7) {
        addr &= 0x0FFFFFFF;
        addr |= 0x80000000;
    }
    return addr;
}
