// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
int sceSifGetReg(int);
void sceSifSetReg(int, int);
void sceSifExitCmd(void);
int sceSifSyncIop(void)
{
    if (!(sceSifGetReg(4) & 0x40000)) return 0;
    sceSifExitCmd();
    sceSifSetReg(1, 1);
    sceSifSetReg(0, 1);
    return 1;
}
