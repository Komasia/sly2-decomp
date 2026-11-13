// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
extern RpcCD D_002C82C0;
extern volatile int D_002C676C;
extern int D_002C6750;
extern int D_002C6758;
extern int D_002C6794;
extern char D_002AB530[];
extern char D_002AB558[];
void cmd_sem_init(void);
int PollSema(int);
int SignalSema(int);
int func_00236960(const char *, ...);
int sceCdSyncS(int);
void sceSifInitRpc(int);
int sceSifBindRpc(void *, unsigned int, int);
static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}
int _sceCd_scmd_prechk(int cmd)
{
    int i;
    cmd_sem_init();
    if (D_002C676C != PollSema(D_002C676C)) {
        if (D_002C6750 > 0) func_00236960(D_002AB530, cmd, D_002C6758);
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
            if (sceSifBindRpc(&D_002C82C0, 0x80000593, 0) < 0) {
                if (D_002C6750 > 0) func_00236960(D_002AB558);
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
