// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; char q[0x28 - 0x28]; } RpcCD;
extern RpcCD D_00450580[2];
extern int D_002C8308;
extern int D_002C830C;
extern char D_002AB680[];
extern char D_002AB6A8[];
int sceSifBindRpc(void *, unsigned int, int);
int scePadGetModVersion(void);
int scePrintf(const char *, ...);
int scePadInit2(int);
int scePadInit(int mode)
{
    int i;
    int ver;
    D_002C8308 = 1;
    while (sceSifBindRpc(&D_00450580[0], 0x80000100, 0), D_00450580[0].server == 0) {
        i = 0x10000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    while (sceSifBindRpc(&D_00450580[1], 0x80000101, 0), D_00450580[1].server == 0) {
        i = 0x10000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    ver = scePadGetModVersion();
    if ((ver >> 8) != 4) {
        if (D_002C830C) {
            scePrintf(D_002AB680);
            scePrintf(D_002AB6A8, 4, 0, ver >> 8, ver & 0xFF);
        }
        return 0;
    }
    return scePadInit2(mode);
}
