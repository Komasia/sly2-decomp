// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
int sceSifGetReg(int);
void sceSifSetReg(int, int);
void func_0023A9C8(void);

/* sceSifSyncIop (libkernel): has the rebooted IOP finished booting? If so, finish the handshake and return 1. */
int sceSifSyncIop(void)
{
    if (!(sceSifGetReg(4 /* SIF_REG_SMFLAG */) & 0x40000 /* SIF_STAT_BOOTEND */)) return 0;
    func_0023A9C8();
    sceSifSetReg(1, 1);
    sceSifSetReg(0, 1);
    return 1;
}
