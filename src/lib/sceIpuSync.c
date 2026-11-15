// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceIpuSync (libipu): mode 0 waits until the IPU is idle; mode 1 returns 1 while it is busy (IPU_CTRL.BUSY). */
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
