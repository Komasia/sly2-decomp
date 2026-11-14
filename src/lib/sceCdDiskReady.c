// (Claude agent) libcdvd sceCdDiskReady (0x2425F0; falls back to the older sceCdDiskReady_old at 0x2423D8 when the bind keeps failing): both delay loops share one function-scope counter `i` (same reg in both, like the target).
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_002C6750;
extern int D_002C6780;
extern volatile int D_002C6770;
extern int D_002C6790;
extern sceSifClientData D_00450510;
extern int D_00450550[];
extern int D_002C81C0[];
int scePrintf(const char *fmt, ...);
int DIntr(void);
int EIntr(void);
void cmd_sem_init(void);
int PollSema(int);
void sceSifInitRpc(int);
int sceSifBindRpc(sceSifClientData *, unsigned int, int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int SignalSema(int);
int sceCdDiskReady_old(int mode);

int sceCdDiskReady(int mode)
{
    int r;
    int cnt;
    int i;
    if (D_002C6750 > 0) scePrintf("NEW DiskReady Call\n");
    cmd_sem_init();
    if (D_002C6770 != PollSema(D_002C6770)) {
        if (mode == 8) return -1;
        return 6;
    }
    sceSifInitRpc(0);
    cnt = 0;
    if (D_002C6790 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00450510, 0x8000059C, 0) < 0) {
                if (D_002C6750 > 0) scePrintf("Libcdvd bind err CdDiskReady\n");
                i = 0x100000; while (i--) ;
                continue;
            }
            if (D_00450510.serve != 0) { D_002C6790 = 0; break; }
            if (cnt > 0x10) {
                SignalSema(D_002C6770);
                return sceCdDiskReady_old(mode);
            }
            i = 0x100000; while (i--) ;
            cnt++;
        }
    }
    r = DIntr();
    D_002C6780 = 0;
    if (r) EIntr();
    D_00450550[0] = mode;
    sceSifWriteBackDCache(D_00450550, 4);
    if (sceSifCallRpc(&D_00450510, 0, 0, D_00450550, 4, D_002C81C0, 4, 0, 0) < 0) {
        SignalSema(D_002C6770);
        if (mode == 8) return -1;
        return 6;
    }
    if (D_002C6750 > 0) scePrintf("DiskReady ended\n");
    r = *(int *)((unsigned int)D_002C81C0 | 0x20000000);
    SignalSema(D_002C6770);
    return r;
}
