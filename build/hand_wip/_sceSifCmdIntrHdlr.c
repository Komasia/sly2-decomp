// WIP (Claude agent): 24/82 diffs, register allocation only: target keeps size in a1 + separate loop counter a0 (src a2); gp-table loads v1/v0 swapped.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
typedef int qword __attribute__((mode(TI)));
typedef struct { void (*func)(void *, void *); void *data; void *gp; } CmdHandler;
typedef struct { unsigned char size; unsigned char dsize; unsigned short pad; void *dest; int fid; int opt; } CmdHdr;
typedef struct {
    CmdHdr *pktbuf;
    int x4, x8;
    CmdHandler *sys;
    int nsys;
    CmdHandler *usr;
    int nusr;
} CmdData;
extern CmdData D_0044EDD8;
void func_00234E10(void);
static inline void *SetGP(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $gp\n\tmove $gp, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
#define FID (*(volatile int *)&((CmdHdr *)buf)->fid)
int _sceSifCmdIntrHdlr(void)
{
    qword buf[7];
    CmdData *cd = &D_0044EDD8;
    CmdHdr *pkt = cd->pktbuf;
    int size = *(volatile unsigned char *)&pkt->size;
    void (*func)(void *, void *);
    int id;
    void *old;
    qword *src, *dst;
    int i;

    if (size == 0)
        return 0;
    size = (size + 15) / 16;
    pkt->size = 0;
    src = (qword *)pkt;
    dst = buf;
    for (i = 0; i < size; i++)
        *dst++ = *src++;
    func_00234E10();
    if (FID < 0) {
        id = FID & 0x7FFFFFFF;
        if (id < cd->nsys) {
            func = cd->sys[id].func;
            if (func) {
                old = SetGP(cd->sys[id].gp);
                func(buf, cd->sys[id].data);
                SetGP(old);
            }
        }
    } else {
        id = FID;
        if (id < cd->nusr) {
            func = cd->usr[id].func;
            if (func) {
                old = SetGP(cd->usr[id].gp);
                func(buf, cd->usr[id].data);
                SetGP(old);
            }
        }
    }
    __asm__ volatile("sync\n\tei");
    return 0;
}
