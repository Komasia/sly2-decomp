// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceCdRead (libcdvd): start reading `sectors` sectors from `lbn` into `buf` (non-blocking; sceCdSync waits).
   The IOP sends the unaligned head/tail separately (_sceCd_cd_read_intr). Returns 1 if the read started. */
#define SCECdSecS2048 0
#define SCECdSecS2328 1
#define SCECdSecS2340 2
#define SCECdNotReady 6
typedef struct { unsigned char trycount, spindlctrl, datapattern, pad; } sceCdRMode;
typedef struct {
    unsigned int lbn;
    unsigned int sectors;
    void *buf;
    sceCdRMode mode;
    void *eedest;
    void *eeaddr;
} CdReadArg;
extern volatile int D_002C6778;     /* bit 0: skip the ready check, bit 1: no cache write-back */
extern int D_002C6750;              /* debug print level */
extern volatile int D_002C67A0;     /* command in progress */
extern volatile int D_002C6774;     /* callback pending */
extern volatile int D_002C6768;     /* N-command semaphore */
extern CdReadArg D_002C6840;        /* read RPC arguments */
extern char D_002C7840[];           /* head/tail fix-up packet */
extern int D_002C7900;              /* read position, updated by the IOP */
extern char D_002C7910[];           /* N-command RPC client */
extern char D_002AB608[];           /* "call cdread cmd\n" */
extern char D_002AB620[];           /* "cdread end\n" */
void _sceCd_cd_read_intr(void *);
int sceCdNcmdDiskReady(void);
int _sceCd_ncmd_prechk(int);
void sceSifWriteBackDCache(void *, int);
int scePrintf(const char *, ...);
int SignalSema(int);
int sceSifCallRpc(void *, int, unsigned int, void *, int, void *, int, void *, void *);
int sceCdRead(unsigned int lbn, unsigned int sectors, void *buf, sceCdRMode *mode)
{
    CdReadArg *rd = &D_002C6840;
    int size;
    if (!(D_002C6778 & 1)) {
        if (sceCdNcmdDiskReady() == SCECdNotReady)
            return 0;
    }
    if (_sceCd_ncmd_prechk(4) == 0)
        return 0;
    rd->lbn = lbn;
    rd->sectors = sectors;
    rd->buf = buf;
    rd->mode.trycount = mode->trycount;
    rd->mode.spindlctrl = mode->spindlctrl;
    rd->mode.datapattern = mode->datapattern;
    rd->eedest = D_002C7840;
    rd->eeaddr = &D_002C7900;
    switch (mode->datapattern) {
    case SCECdSecS2328:
        size = sectors * 2328;
        break;
    case SCECdSecS2340:
        size = sectors * 2340;
        break;
    case SCECdSecS2048:
    default:
        size = sectors << 11;
        break;
    }
    D_002C7900 = 0;
    if (!(D_002C6778 & 2))
        sceSifWriteBackDCache(buf, size);
    sceSifWriteBackDCache(D_002C7840, 0x90);
    sceSifWriteBackDCache(rd, 0x18);
    sceSifWriteBackDCache(&D_002C7900, 4);
    if (D_002C6750 > 0)
        scePrintf(D_002AB608);
    D_002C67A0 = 1;
    D_002C6774 = 1;
    if (sceSifCallRpc(D_002C7910, 1, 1 /* SIF_RPCM_NOWAIT */, rd, 0x18, 0, 0, _sceCd_cd_read_intr, D_002C7840) < 0) {
        D_002C67A0 = 0;
        D_002C6774 = 0;
        SignalSema(D_002C6768);
        return 0;
    }
    if (D_002C6750 > 0)
        scePrintf(D_002AB620);
    return 1;
}
