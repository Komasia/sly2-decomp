/* sceFsInit (fileio): bind the IOP fileio server (0x80000001), install the read-end / power-off SIF command
   handlers, clear the iob table and fetch the server version. 0 on success, -22 if the bind fails. */
// codegen: -fstrict-aliasing is what fixes the prologue: flag (int) and next (pointer) get different alias
// sets, so the two stores before DIntr are independent and the s0 save/lui chain outranks the s1 save in sched2.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; } ClientData;
typedef struct { char c[4]; } B4;
struct iob { int fd, busy, x8, xC; };
struct FsPoffData { int flag; void *next; };
extern struct FsPoffData D_0044BE00;   /* power-off callback data */
extern char D_0044BDC0[];              /* read-end handler data */
extern ClientData D_0044BD80;          /* fileio RPC client */
extern int D_002C4A88;                 /* iob table semaphore */
extern struct iob D_0044BB80[32];      /* open-file table */
extern void *D_0044A640[2];            /* init arguments: the two EE receive buffers */
extern char D_0044B300[];              /* EE receive buffers (2 x 0x440) */
extern B4 D_0044B2C0[2];               /* init reply (read uncached) */
extern B4 D_0044BDA8;                  /* IOP fileio version */
extern int D_002C4A7C;                 /* fileio initialised */
extern int D_002C4A80;                 /* version-2 server */
void sceSifInitRpc(int);
int DIntr(void);
int EIntr(void);
void *sceSifAddCmdHandler(unsigned int, void *, void *);
void _sceFs_Rcv_Intr(void *);
void _sceFs_Poff_Intr(void *);
int sceSifBindRpc(ClientData *, unsigned int, unsigned int);
void _sceFsIobSemaMK(void);
int WaitSema(int);
int SignalSema(int);
int sceFsSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *, int);
int sceFsInit(void)
{
    int oldei, i;
    struct iob *io;
    B4 tmp;
    struct FsPoffData *p = &D_0044BE00;
    sceSifInitRpc(0);
    D_0044BE00.flag = 0;
    p->next = 0;
    oldei = DIntr();
    sceSifAddCmdHandler(0x80000011, _sceFs_Rcv_Intr, D_0044BDC0);   /* read finished */
    sceSifAddCmdHandler(0x80000013, _sceFs_Poff_Intr, p);            /* power off */
    if (oldei) EIntr();
    while (1) {
        if (sceSifBindRpc(&D_0044BD80, 0x80000001, 0) < 0)
            return -22;
        if (D_0044BD80.serve != 0)
            break;
        i = 0x100000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    _sceFsIobSemaMK();
    WaitSema(D_002C4A88);
    for (io = D_0044BB80; io < &D_0044BB80[32]; io++)
        { __asm__ volatile(""); io->busy = 0; }
    SignalSema(D_002C4A88);
    D_0044A640[0] = D_0044B300;
    D_0044A640[1] = D_0044B300 + 0x440;
    if (sceFsSifCallRpc(&D_0044BD80, 0xFF, 0, D_0044A640, 8, D_0044B2C0, 8, 0, 0, 0) < 0)
        return 0xFFFEFFFF;
    D_0044BDA8 = *(B4 *)((unsigned int)&D_0044B2C0[0] | 0x20000000);
    tmp = *(B4 *)((unsigned int)&D_0044B2C0[1] | 0x20000000);
    D_002C4A80 = *(int *)&tmp == 2;
    D_002C4A7C = 1;
    return 0;
}
