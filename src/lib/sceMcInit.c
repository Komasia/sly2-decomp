// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
extern RpcCD D_00450880;
extern char D_00450900[];
extern int D_00451E40[];
extern int D_002C8354;
extern int D_002C8358;
extern char D_002AB7B0[], D_002AB7C0[], D_002AB7D8[], D_002AB7F0[], D_002AB818[];
int CreateSema(struct SemaParam *);
int DeleteSema(int);
int SignalSema(int);
int WaitSema(int);
void sceMcSync(int, int, int);
void sceSifInitRpc(int);
int scePrintf(const char *, ...);
int sceSifBindRpc(void *, unsigned int, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
static inline int bindmc(void)
{
    if (sceSifBindRpc(&D_00450880, 0x80000400, 0) < 0) {
        scePrintf(D_002AB7D8);
        while (1) ;
    }
    return D_00450880.server;
}
int sceMcInit(void)
{
    struct SemaParam sp;
    int i = 0;
    int j;
    int r;

    if (D_002C8354 < 0) {
        int m1 = -1;
        sp.initCount = 1;
        sp.option = (unsigned int)D_002AB7B0;
        sp.maxCount = 1;
        D_002C8354 = CreateSema(&sp);
        if (D_002C8354 == m1)
            return -101;
        sp.maxCount = 1;
        sp.initCount = 0;
        sp.option = (unsigned int)D_002AB7C0;
        r = CreateSema(&sp);
        D_002C8358 = r;
        if (r == m1) {
            DeleteSema(D_002C8354);
            D_002C8354 = r;
            return -101;
        }
    }
    sceMcSync(0, 0, 0);
    WaitSema(D_002C8354);
    sceSifInitRpc(0);
    while (bindmc() == 0) {
        j = 0x100000;
        while (--j) ;
        if (++i >= 0x200) {
            scePrintf(D_002AB7D8);
            return -91;
        }
    }
    r = sceSifCallRpc(&D_00450880, 0xFE, 0, D_00450900, 0x30, D_00451E40, 0xC, 0, 0);
    SignalSema(D_002C8354);
    if (r < 0) {
        D_00450880.server = 0;
        return -91;
    }
    if (D_00451E40[1] < 0x20A) {
        scePrintf(D_002AB7F0);
        D_00450880.server = 0;
        return -120;
    }
    if (D_00451E40[2] < 0x20E) {
        scePrintf(D_002AB818);
        D_00450880.server = 0;
        return -121;
    }
    return D_00451E40[0];
}
