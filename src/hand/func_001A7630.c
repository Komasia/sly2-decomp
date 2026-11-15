/* func_001A7630 (0x1A7630): the IOP start-up (Sly 1 main.c StartupSif's shape): SIF / CD / file system init (spinning forever
 * without a valid CD mode); unless D_002E2058 is set the IOP is rebooted with the image D_002A6A48 and everything
 * re-initialised; then each IRX module of the table D_004E5D80..D_004E5E38 is copied by SIF DMA (in chunks of at most
 * 0xFFFC0 bytes) into one IOP heap buffer as large as the largest and loaded (sceSifLoadModuleBuffer). */
struct E { int bytes; unsigned int source; int argumentBytes; const char *arguments; int unknown10; };  /* an IRX module: its size, EE address, load arguments */
struct DMA { unsigned int source; unsigned int destination; int bytes; int attributes; };
extern struct E *g_airxFirst __asm__("D_004E5D80");
extern struct E *g_airxEnd __asm__("D_004E5E38");
extern int g_fNoIopReboot __asm__("D_002E2058");
extern char g_szIopImage[] __asm__("D_002A6A48");  /* the IOP reboot image's path */
void sceSifInitRpc(int n);
int sceSifLoadFileReset(void);
int sceCdInit(int n);
int FValidCdMmode__Fv(void);
void SetCdMmode(void) asm("SetCdMmode__Fv");
int sceFsReset(void);
void CdPath(char *p, char *s, int n) asm("CdPath__FPcT0i");
int sceSifRebootIop(const char *p);
int sceSifSyncIop(void);
int sceCdDiskReady(int n);
int FCdCompleted(int n) asm("FCdCompleted__Fi");
int sceSifInitIopHeap(void);
void *sceSifAllocIopHeap(int cb);
void FlushCache(int n);
int sceSifSetDma(struct DMA *p, int n);
int sceSifLoadModuleBuffer(void *h, int argumentBytes, const char *arguments);
int func_00238D40(void *h);
static inline int CopyLimit(int value)
{
    int copy;
    __asm__("daddu %0,%1,$zero" : "=r"(copy) : "r"(value));
    return copy;
}
void func_001A7630(void)
{
    union { char buf[0x100]; struct DMA dma; } u;
    struct E *pe;
    int cbMax;
    void *h;
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceCdInit(0);
    if (!FValidCdMmode__Fv())
        while (1)
            ;
    SetCdMmode();
    sceFsReset();
    if (!g_fNoIopReboot) {
        CdPath(u.buf, g_szIopImage, 1);
        while (!sceSifRebootIop(u.buf))
            ;
        while (!sceSifSyncIop())
            ;
        sceSifInitRpc(0);
        sceSifLoadFileReset();
        sceCdInit(0);
        if (!FValidCdMmode__Fv())
            while (1)
                ;
        SetCdMmode();
        sceFsReset();
    }
    sceCdDiskReady(0);
    (void)FCdCompleted(1);
    sceSifInitIopHeap();
    cbMax = 0;
    {
        struct E *p;
        for (p = g_airxFirst; p < g_airxEnd; p++)
            if (p->bytes >= cbMax)
                cbMax = p->bytes;
    }
    h = sceSifAllocIopHeap(cbMax);
    for (pe = g_airxFirst; pe < g_airxEnd; pe++) {
        int cb = pe->bytes;
        int off = 0;
        while (cb) {
            register int limit __asm__("$2") = 0xF0000;
            int c;
            const int zeroOperation = 0, limitLow = 0xFFC0;
            register unsigned int destination __asm__("$5");
            register int operation __asm__("$4");
            __asm__("ori %0,%0,%1" : "+r"(limit) : "i"(limitLow));
            __asm__("addu %0,%1,%2" : "=r"(destination) : "r"(h), "r"(off));
            c = CopyLimit(limit);
            __asm__("slt %0,%1,%0" : "+r"(limit) : "r"(cb));
            __asm__("movn %0,%1,%2" : "+r"(c) : "r"(cb), "r"(limit));
            u.dma.source = pe->source + off;
            __asm__("daddu %0,%z3,$zero\n\tsw %2,%1"
                    : "=r"(operation), "=m"(u.dma.destination)
                    : "r"(destination), "rJ"(zeroOperation));
            u.dma.bytes = c;
            u.dma.attributes = 0;
            FlushCache(operation);
            while (!sceSifSetDma(&u.dma, 1))
                ;
            cb -= c;
            off += c;
        }
        while (sceSifLoadModuleBuffer(h, pe->argumentBytes, pe->arguments) < 0)
            ;
    }
    func_00238D40(h);
}

typedef char offset_0_bytes[(unsigned)&((struct E*)0)->bytes==0?1:-1];
typedef char offset_0_source[(unsigned)&((struct E*)0)->source==4?1:-1];
typedef char offset_0_argumentBytes[(unsigned)&((struct E*)0)->argumentBytes==8?1:-1];
typedef char offset_0_arguments[(unsigned)&((struct E*)0)->arguments==12?1:-1];
typedef char offset_0_unknown10[(unsigned)&((struct E*)0)->unknown10==16?1:-1];
typedef char offset_1_source[(unsigned)&((struct DMA*)0)->source==0?1:-1];
typedef char offset_1_destination[(unsigned)&((struct DMA*)0)->destination==4?1:-1];
typedef char offset_1_bytes[(unsigned)&((struct DMA*)0)->bytes==8?1:-1];
typedef char offset_1_attributes[(unsigned)&((struct DMA*)0)->attributes==12?1:-1];
typedef char size_0[sizeof(struct E)==20?1:-1];
typedef char size_1[sizeof(struct DMA)==16?1:-1];
typedef char size_2[sizeof(int)==4?1:-1];
typedef char size_3[sizeof(unsigned int)==4?1:-1];
typedef char size_4[sizeof(void*)==4?1:-1];
typedef char size_5[sizeof(char)==1?1:-1];
typedef char alignment_0[__alignof__(struct E)==4?1:-1];
typedef char alignment_1[__alignof__(struct DMA)==4?1:-1];
