// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "sif_rpc.h"
/* sceSifInitRpc (libkernel sifrpc): set up the RPC layer once: the packet tables (uncached), the four RPC
   command handlers, and, if the IOP side is not ready yet, send SIF_CMD_INIT_CMD and wait for it.
   DIntr must return int (its unused result keeps hi(pkt table) out of $v0), and the fields are set in
   struct order with pid last, as in ps2sdk's SifInitRpc. */
typedef struct {
    int pid;
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    void *rdata_table;
    int rdata_table_len;
    void *client_table;
    int client_table_len;
    int client_table_idx;
} RpcData;
typedef struct { int psize_dsize, dest, cid, opt; } SifCmdHeaderWords;
#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))
extern int D_002C49F0;                  /* _rpc_inited */
extern unsigned char D_00448E00[];      /* packet table, 32 x 64 bytes */
extern unsigned char D_00449600[];      /* answer (rdata) packet ring */
extern unsigned char D_00449E00[];      /* client packet table */
extern RpcData D_0044A600;              /* the RPC module state */
int DIntr(void);
void EIntr(void);
void sceSifInitCmd(void);
void sceSifAddCmdHandler(unsigned int cid, void (*h)(void *, void *), void *data);
int sceSifGetReg(unsigned int reg);
void func_00234E20(unsigned int reg, int val);   /* sceSifSetReg */
unsigned int sceSifSendCmd(unsigned int cid, void *pkt, int size, void *src, void *dst, int n);
int func_0023AAC8(int);        /* sceSifGetSreg: software register set by the IOP */
void _request_end(void *, void *);
void _request_bind(void *, void *);
void _request_call(void *, void *);
void _request_rdata(void *, void *);
void sceSifInitRpc(unsigned int mode)
{
    SifCmdHeaderWords *cmd;
    DIntr();
    if (D_002C49F0) {
        EIntr();
        return;
    }
    D_002C49F0 = 1;
    EIntr();
    sceSifInitCmd();
    DIntr();
    D_0044A600.pkt_table = UNCACHED(D_00448E00);
    D_0044A600.pkt_table_len = 32;
    D_0044A600.unused1 = 0;
    D_0044A600.unused2 = 0;
    D_0044A600.rdata_table = UNCACHED(D_00449600);
    D_0044A600.rdata_table_len = 32;
    D_0044A600.client_table = UNCACHED(D_00449E00);
    D_0044A600.client_table_len = 32;
    D_0044A600.client_table_idx = 0;
    D_0044A600.pid = 1;
    sceSifAddCmdHandler(SIF_CMD_RPC_END, _request_end, &D_0044A600);
    sceSifAddCmdHandler(SIF_CMD_RPC_BIND, _request_bind, &D_0044A600);
    sceSifAddCmdHandler(SIF_CMD_RPC_CALL, _request_call, &D_0044A600);
    sceSifAddCmdHandler(SIF_CMD_RPC_RDATA, _request_rdata, &D_0044A600);
    EIntr();
    if (sceSifGetReg(SIF_SYSREG_RPCINIT) != 0)
        return;
    cmd = (SifCmdHeaderWords *)(D_00448E00 + 0x40);
    cmd->opt = 1;
    sceSifSendCmd(SIF_CMD_INIT_CMD, cmd, 16, 0, 0, 0);
    while (func_0023AAC8(0) == 0)
        ;
    func_00234E20(SIF_SYSREG_RPCINIT, 1);
}
