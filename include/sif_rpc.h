/* sif_rpc.h - SIF command / RPC protocol of the EE libkernel (sifcmd, sifrpc) as used by src/lib.
 *
 * Layouts follow the SDK's public sifcmd.h / sifrpc.h structures; the private packet layouts and field names
 * follow the open-source ps2sdk reimplementation. Types and macros only, no prototypes.
 */
#ifndef SIF_RPC_H
#define SIF_RPC_H

/* ---- system command ids (top bit set) ---- */
#define SIF_CMD_CHANGE_SADDR 0x80000000     /* tell the IOP where our command buffer is */
#define SIF_CMD_SET_SREG     0x80000001
#define SIF_CMD_INIT_CMD     0x80000002
#define SIF_CMD_RESET        0x80000003
#define SIF_CMD_RPC_END      0x80000008     /* RPC reply (bind/call/rdata finished) */
#define SIF_CMD_RPC_BIND     0x80000009
#define SIF_CMD_RPC_CALL     0x8000000A
#define SIF_CMD_RPC_RDATA    0x8000000C
#define SIF_CMD_POWEROFF     0x80000012
#define SIF_CMD_SYSTEM       0x80000000     /* system-command flag */

/* SIF registers (sceSifGetReg / sceSifSetReg); the top-bit ones are kept by the kernel */
#define SIF_REG_SUBADDR     2               /* IOP's command buffer address */
#define SIF_REG_SMFLAG      4
#define SIF_STAT_CMDINIT    0x20000         /* SMFLAG: IOP sifcmd is ready */
#define SIF_SYSREG_SUBADDR  0x80000000      /* IOP's command buffer (saved) */
#define SIF_SYSREG_MAINADDR 0x80000001      /* our command data */
#define SIF_SYSREG_RPCINIT  0x80000002      /* RPC layer initialised */

/* sceSifSendCmd mode bits */
#define SIF_CMD_M_INTR  1                   /* called from an interrupt handler */
#define SIF_CMD_M_WBDC  4                   /* write back the data cache over the extra data */

/* sceSifCallRpc / sceSifBindRpc mode bits */
#define SIF_RPCM_NOWAIT 1                   /* return at once; end function / semaphore signals completion */
#define SIF_RPCM_NOWBDC 2                   /* don't write back the data cache over send/receive */

#define SIF_RPC_PACKET_SIZE 0x40

/* ---- command packet header (sceSifCmdHdr) ---- */
typedef struct {
    unsigned int psize:8;   /* packet size in bytes */
    unsigned int dsize:24;  /* size of the extra data DMAed with it */
    unsigned int dest;      /* where the extra data goes */
    unsigned int cid;       /* command id */
    unsigned int opt;
} SifCmdHeader;

/* a registered command handler */
typedef struct {
    void (*func)(void *packet, void *data);
    void *data;
    void *gp;               /* $gp of the module that registered it */
} SifCmdHandler;

#endif /* SIF_RPC_H */
