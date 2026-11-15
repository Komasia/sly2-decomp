// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
#include "ee_kernel.h"
/* sceSifInitCmd (libkernel sifcmd): set up SIF command handling once: the uncached receive buffer, the
   system handler table (SET_SREG and CHANGE_SADDR handlers built in), the software registers and the SIF0
   DMA interrupt; then exchange command buffer addresses with the IOP (waiting for it to be ready if it has
   not set the CHANGE_SADDR register yet). The handler func field must be a function pointer type. */
#define DMAC_SIF0 5
typedef struct { void (*func)(void *, void *); void *data; int gp; } HANDLER;
typedef struct {
    void *pktbuf;       /* 0x00 where the IOP DMAs command packets (uncached) */
    void *unused;       /* 0x04 */
    void *iopbuf;       /* 0x08 IOP-side command buffer */
    HANDLER *sys;       /* 0x0C system command handlers */
    int nsys;           /* 0x10 */
    HANDLER *usr;       /* 0x14 user command handlers */
    int nusr;           /* 0x18 */
    int *sreg;          /* 0x1C software registers */
} CMDDATA;
typedef struct { unsigned int size; void *dest; int cid; unsigned int opt; void *buf; } SifSaddrPkt;

extern int D_002C5A60;              /* _sif_cmd_inited */
extern unsigned char D_0044ED00[0x80];  /* command receive buffer */
extern unsigned char D_0044ED80[0x40];
extern SifSaddrPkt D_0044EDC0;
extern int D_0044EDD4;              /* _sif_cmd_handler_id */
extern CMDDATA D_0044EDD8;          /* the sifcmd module state */
extern HANDLER D_0044EE00[32];      /* system handlers */
extern int D_0044EF80[32];          /* software registers */

int DIntr(void);
void EIntr(void);
void FlushCache(int);
void sceSifSetDChain(void);
int func_00234730(int, void *, int);    /* AddDmacHandler (syscall 0x12) */
int EnableDmac(int);                 /* EnableDmac */
unsigned int sceSifGetReg(unsigned int);
unsigned int func_00234E20(unsigned int, unsigned int);    /* sceSifSetReg (syscall 0x79) */
void sceSifSendCmd(unsigned int, void *, unsigned int, void *, void *, unsigned int);
void func_0023AAB8(void *, void *);     /* SIF_CMD_CHANGE_SADDR handler */
void func_0023AA98(void *, void *);     /* SIF_CMD_SET_SREG handler */
void _sceSifCmdIntrHdlr(void);

void sceSifInitCmd(void)
{
    int i;

    DIntr();
    if (D_002C5A60) {
        EIntr();
        return;
    }
    D_002C5A60 = 1;
    D_0044EDD8.pktbuf = (void *)((unsigned int)D_0044ED00 | 0x20000000);   /* uncached alias */
    D_0044EDD8.unused = (void *)((unsigned int)D_0044ED80 | 0x20000000);
    D_0044EDD8.iopbuf = 0;
    D_0044EDD8.sys = D_0044EE00;
    D_0044EDD8.nsys = 32;
    D_0044EDD8.usr = 0;
    D_0044EDD8.nusr = 0;
    D_0044EDD8.sreg = D_0044EF80;
    for (i = 0; i < 32; i++) {
        D_0044EE00[i].func = 0;
        D_0044EE00[i].data = 0;
    }
    for (i = 0; i < 32; i++)
        D_0044EF80[i] = 0;
    D_0044EE00[0].func = func_0023AAB8;
    D_0044EE00[0].data = &D_0044EDD8;
    D_0044EE00[1].func = func_0023AA98;
    D_0044EE00[1].data = &D_0044EDD8;
    EIntr();
    FlushCache(WRITEBACK_DCACHE);
    if (*(volatile unsigned int *)0x1000E010 & (1 << DMAC_SIF0))     /* D_STAT: clear a stale SIF0 interrupt */
        *(volatile unsigned int *)0x1000E010 = 1 << DMAC_SIF0;
    if (!(*(volatile unsigned int *)0x1000C000 & 0x100))     /* D5_CHCR.STR: start the SIF0 chain if idle */
        sceSifSetDChain();
    D_0044EDD4 = func_00234730(DMAC_SIF0, (void *)_sceSifCmdIntrHdlr, 0);
    EnableDmac(DMAC_SIF0);
    D_0044EDD8.iopbuf = (void *)sceSifGetReg(SIF_SYSREG_SUBADDR);
    if (D_0044EDD8.iopbuf) {
        D_0044EDC0.buf = D_0044ED00;
        sceSifSendCmd(SIF_CMD_CHANGE_SADDR, &D_0044EDC0, 0x14, 0, 0, 0);
        return;
    }
    {
        while (!(sceSifGetReg(SIF_REG_SMFLAG) & SIF_STAT_CMDINIT))
            ;
        D_0044EDD8.iopbuf = (void *)sceSifGetReg(SIF_REG_SUBADDR);
        func_00234E20(SIF_SYSREG_SUBADDR, (unsigned int)D_0044EDD8.iopbuf);
        func_00234E20(SIF_SYSREG_MAINADDR, (unsigned int)&D_0044EDD8);
        D_0044EDC0.buf = D_0044ED00;
        D_0044EDC0.opt = 0;
        sceSifSendCmd(SIF_CMD_INIT_CMD, &D_0044EDC0, 0x14, 0, 0, 0);
    }
}
