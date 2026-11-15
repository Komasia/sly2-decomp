/* libpad_rpc.h - controller library (libpad) protocol as used by src/lib/scePad*.c. Command numbers are the
 * function codes the EE sends to the IOP padman server in word 0 of the 0x80-byte RPC buffer; state values follow
 * the SDK's scePadState* / scePadReqState* constants. Macros only (the files keep their own struct views, whose
 * member types matter for scheduling). */
#ifndef LIBPAD_RPC_H
#define LIBPAD_RPC_H

#define PAD_RPC_ID_CMD   0x80000100     /* padman command server */
#define PAD_RPC_ID_EXT   0x80000101     /* padman second server */
#define PAD_SIF_CMD_INTR 0x80000019     /* SIF command: pad DMA buffer updated */

/* RPC function codes (word 0 of the request) */
#define PAD_RPCCMD_OPEN        0x01
#define PAD_RPCCMD_SET_MMODE   0x06     /* scePadSetMainMode */
#define PAD_RPCCMD_SET_ACTALIGN 0x08
#define PAD_RPCCMD_SET_BTNINFO 0x0A     /* scePadSetButtonInfo */
#define PAD_RPCCMD_INIT        0x10
#define PAD_RPCCMD_GET_MODVER  0x12

/* scePadGetState results */
#define scePadStateDiscon   0
#define scePadStateFindPad  1
#define scePadStateFindCTP1 2
#define scePadStateExecCmd  5
#define scePadStateStable   6
#define scePadStateError    7
/* scePadGetReqState results */
#define scePadReqStateComplete 0
#define scePadReqStateFaild    1
#define scePadReqStateBusy     2

#define PAD_ERR_NOT_OPEN 99             /* scePadGetState on a port that is not open */

/* byte offsets in one 0x80-byte frame of the pad DMA buffer (two frames, newest by frame counter) */
#define PADDMA_FRAME     0x58           /* int: frame counter */
#define PADDMA_LEN       0x60           /* int: bytes of button data in the frame */
#define PADDMA_PHASE     0x64           /* mode-information phase */
#define PADDMA_ID        0x65           /* controller id (type << 4 | data words) */
#define PADDMA_ACTPHASE  0x66
#define PADDMA_STATE     0x70           /* scePadState* */
#define PADDMA_REQSTATE  0x71           /* scePadReqState* */
#define PADDMA_OK        0x72           /* 1 when the frame is valid */
#define PADDMA_BTNMASK   0x79           /* 4 bytes: pressure-sensitive button mask */

#endif /* LIBPAD_RPC_H */
