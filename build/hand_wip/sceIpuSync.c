// SLY2_CC: tools/compilers/ee-gcc2.96
// SLY2_CFLAGS: -O2 -G0
int sceIpuSync(int mode, unsigned short timeout)
{
    int r = 0;
    switch (mode) {
    case 0:
        while ((int)*(volatile unsigned int *)0x10002010 < 0)
            ;
        r = 0;
        break;
    case 1:
        r = *(volatile unsigned int *)0x10002010 >> 31;
        break;
    }
    return r;
}
