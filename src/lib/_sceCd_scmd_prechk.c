// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
#define CD_RPC_SCMD 0x80000593
extern RpcCD D_002C82C0;            /* S-command RPC client */
extern volatile int D_002C676C;     /* S-command semaphore */
extern int D_002C6750;              /* debug print level */
extern int D_002C6758;              /* command in progress */
extern int D_002C6794;              /* <0 until bound */
extern char D_002AB530[];           /* "Scmd fail sema cur_cmd:%d keep_cmd:%d\n" */
extern char D_002AB558[];           /* "Libcdvd bind err S cmd\n" */
void cmd_sem_init(void);
int PollSema(int);
int SignalSema(int);
int scePrintf(const char *, ...);
int sceCdSyncS(int);
void sceSifInitRpc(int);
int sceSifBindRpc(void *, unsigned int, int);
static __inline__ void nopdelay(void)
{
    int delay = 0x100000;
    while (delay--) ;
}
/* _sceCd_scmd_prechk (libcdvd): before an S-command (status/config query): take the command semaphore,
   make sure no other S-command is running and bind the S-command RPC server if needed. Returns 1 if ok. */
int _sceCd_scmd_prechk(int cmd)
{
    cmd_sem_init();
    if (D_002C676C != PollSema(D_002C676C)) {
        if (D_002C6750 > 0) scePrintf(D_002AB530, cmd, D_002C6758);
        return 0;
    }
    D_002C6758 = cmd;
    if (sceCdSyncS(1)) {
        SignalSema(D_002C676C);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_002C6794 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_002C82C0, CD_RPC_SCMD, 0) < 0) {
                if (D_002C6750 > 0) scePrintf(D_002AB558);
                nopdelay();
                continue;
            }
            if (D_002C82C0.server != 0) break;
            nopdelay();
        }
        D_002C6794 = 0;
    }
    return 1;
}
