// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceCdDiskReady (libcdvd): drive state, SCECdComplete (2) or SCECdNotReady (6); mode 0 waits for the drive,
   mode 8 does not (-1 when busy). Falls back to sceCdDiskReady_old if the new server never binds.
   codegen: both delay loops share one function-scope counter `i`. */
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_002C6750;    /* debug print level */
extern int D_002C6780;              /* 1 while the old DiskReady server is used */
extern volatile int D_002C6770;     /* DiskReady semaphore */
extern int D_002C6790;              /* DiskReady server bound (0) or not (-1) */
extern sceSifClientData D_00450510; /* DiskReady RPC client */
extern int D_00450550[];            /* DiskReady send buffer */
extern int D_002C81C0[];            /* DiskReady receive buffer */
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
        if (mode == 8) return -1;   /* non-blocking: busy */
        return 6;                   /* SCECdNotReady */
    }
    sceSifInitRpc(0);
    cnt = 0;
    if (D_002C6790 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00450510, 0x8000059C /* DiskReady (new) */, 0) < 0) {
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
