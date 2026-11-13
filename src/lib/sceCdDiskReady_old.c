// (Claude agent) libcdvd sceCdDiskReady_old: bind retry loop sets the bound flag before break; both failure exits written out (gcc cross-jumps them).
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_002C6750;
extern int D_002C6780;
extern volatile int D_002C676C;
extern int D_002C6790;
extern sceSifClientData D_00450510;
extern int D_00450550[];
extern int D_002C7940[];
int printf(const char *fmt, ...);
int DIntr(void);
int EIntr(void);
void cmd_sem_init(void);
int PollSema(int);
int sceCdSyncS(int);
void sceSifInitRpc(int);
int sceSifBindRpc(sceSifClientData *, unsigned int, int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int SignalSema(int);

static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}
int sceCdDiskReady_old(int mode)
{
    int r;
    if (D_002C6750 > 0) printf("DiskReady 0\n");
    r = DIntr();
    D_002C6780 = 1;
    if (r) EIntr();
    cmd_sem_init();
    if (D_002C676C != PollSema(D_002C676C)) return 6;
    if (sceCdSyncS(1)) {
        SignalSema(D_002C676C);
        if (mode == 8) return -1;
        return 6;
    }
    sceSifInitRpc(0);
    if (D_002C6790 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00450510, 0x8000059A, 0) < 0) {
                if (D_002C6750 > 0) printf("Bind error\n");
                nopdelay();
                continue;
            }
            if (D_00450510.serve != 0) { D_002C6790 = 0; break; }
            nopdelay();
        }
    }
    D_00450550[0] = mode;
    sceSifWriteBackDCache(D_00450550, 4);
    if (sceSifCallRpc(&D_00450510, 0, 0, D_00450550, 4, D_002C7940, 4, 0, 0) < 0) {
        SignalSema(D_002C676C);
        if (mode == 8) return -1;
        return 6;
    }
    if (D_002C6750 > 0) printf("DiskReady ended\n");
    r = *(int *)((unsigned int)D_002C7940 | 0x20000000);
    SignalSema(D_002C676C);
    return r;
}
