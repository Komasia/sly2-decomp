// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
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
static inline void *SetHandlerGP(void *const *home)
{
    void *old;
    __asm__ volatile("lw $3,%1\n\tmove %0,$gp\n\tmove $gp,$3" : "=&r"(old) : "m"(*home) : "$3", "memory");
    return old;
}
#define FID (((CmdHdr *)buf)->fid)
int _sceSifCmdIntrHdlr(void)
{
    qword buf[7];
    CmdData *cd = &D_0044EDD8;
    register CmdHdr *pkt asm("$7") = cd->pktbuf;
    int size = *(volatile unsigned char *)&pkt->size;
    void (*func)(void *, void *);
    int id;
    void *old;
    register qword *src asm("$6");
    register int i asm("$4");

    if (size == 0)
        return 0;
    size = (size + 15) / 16;
    pkt->size = 0;
    src = (qword *)pkt;
    i = size;
    if (size > 0) {
        qword *dest = buf;
        do { *dest++ = *src++; } while (--i);
    }
    func_00234E10();
    {
        register int firstId asm("$3") = FID;
        if (firstId < 0) {
            id = FID & 0x7FFFFFFF;
            if (id < cd->nsys) {
                func = cd->sys[id].func;
                if (func) {
                    old = SetHandlerGP(&cd->sys[id].gp);
                    func(buf, cd->sys[id].data);
                    SetGP(old);
                }
            }
        } else {
            id = FID;
            if (id < cd->nusr) {
                func = cd->usr[id].func;
                if (func) {
                    old = SetHandlerGP(&cd->usr[id].gp);
                    func(buf, cd->usr[id].data);
                    SetGP(old);
                }
            }
        }
    }
    __asm__ volatile("sync\n\tei" : : : "memory");
    return 0;
}
