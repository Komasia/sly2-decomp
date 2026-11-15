// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
typedef struct {
    SifCmdHeader hdr;
    int size;
    int flag;
    char arg[80];
} SifCmdResetData;
typedef struct {
    void *src;
    void *dest;
    int size;
    int attr;
} SifDmaTransfer;
/* sceSifResetIop (libkernel): send SIF_CMD_RESET with the reboot argument string straight into the IOP
   command buffer, and clear the SIF flags/registers so both sides re-initialise. Returns 1 if sent. */
#define SIF_STAT_SIFINIT  0x10000
#define SIF_STAT_BOOTEND  0x40000
extern SifCmdResetData D_0044C280 __attribute__((aligned(64)));
void sceSifExecNotifyHandler(int, int);
void func_00234CF0(void);       /* sceSifExitCmd-like shutdown of command handling */
unsigned int sceSifGetReg(unsigned int);
unsigned int func_00234E20(unsigned int, unsigned int);    /* sceSifSetReg */
void sceSifWriteBackDCache(void *, int);
unsigned int sceSifSetDma(SifDmaTransfer *, int);
int sceSifResetIop(const char *arg, int mode)
{
    SifDmaTransfer dmat;
    void *dest;
    int i;

    sceSifExecNotifyHandler(0, 0);
    sceSifExecNotifyHandler(1, 0);
    func_00234CF0();
    dest = (void *)sceSifGetReg(SIF_SYSREG_SUBADDR);
    D_0044C280.flag = mode;
    for (i = 0; arg[i] != 0; i++)
        D_0044C280.arg[i] = arg[i];
    D_0044C280.hdr.dest = 0;
    D_0044C280.hdr.dsize = 0;
    D_0044C280.size = i;
    D_0044C280.hdr.cid = SIF_CMD_RESET;
    D_0044C280.hdr.psize = sizeof(SifCmdResetData);
    dmat.src = &D_0044C280;
    dmat.dest = dest;
    dmat.size = sizeof(SifCmdResetData);
    dmat.attr = 0x44;   /* ERT | INT_O */
    sceSifWriteBackDCache(&D_0044C280, sizeof(SifCmdResetData));
    func_00234E20(SIF_REG_SMFLAG, SIF_STAT_BOOTEND);
    if (sceSifSetDma(&dmat, 1) != 0) {
        func_00234E20(SIF_REG_SMFLAG, SIF_STAT_SIFINIT);
        func_00234E20(SIF_REG_SMFLAG, SIF_STAT_CMDINIT);
        func_00234E20(SIF_SYSREG_RPCINIT, 0);
        func_00234E20(SIF_SYSREG_SUBADDR, 0);
        return 1;
    }
    return 0;
}

