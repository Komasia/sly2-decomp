// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
extern RpcCD D_002C7910;
extern volatile int D_002C6768;
extern int D_002C6750;
extern int D_002C675C;
extern int D_002C677C;
extern char D_002AB4D0[];
extern char D_002AB4F8[];
void cmd_sem_init(void);
int PollSema(int);
int SignalSema(int);
int scePrintf(const char *, ...);
int sceCdSync(int);
void sceSifInitRpc(int);
int sceSifBindRpc(void *, unsigned int, int);
static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}
int _sceCd_ncmd_prechk(int cmd)
{
    int i;
    cmd_sem_init();
    if (D_002C6768 != PollSema(D_002C6768)) {
        if (D_002C6750 > 0) scePrintf(D_002AB4D0, cmd, D_002C675C);
        return 0;
    }
    D_002C675C = cmd;
    if (sceCdSync(1)) {
        SignalSema(D_002C6768);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_002C677C < 0) {
        while (1) {
            if (sceSifBindRpc(&D_002C7910, 0x80000595, 0) < 0) {
                if (D_002C6750 > 0) scePrintf(D_002AB4F8);
                nopdelay();
                continue;
            }
            if (D_002C7910.server != 0) break;
            nopdelay();
        }
        D_002C677C = 0;
    }
    return 1;
}
