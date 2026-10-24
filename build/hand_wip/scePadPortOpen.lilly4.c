// scePadPortOpen (0x243088) WIP, lilly4 (Claude agent, T1567, 2026-10-24): 14/121 differ, aligned 11. Plain C, no asm.
// Natural shape taken from the Crash: Wrath of Cortex PS2 decomp (github.com/denzi-gh/crashwoc-decomp-ps2,
// src/sdk/sce/libpad.c, their scePadPortOpen is also a ~96% near-miss): RPC buffer as a global struct, command =
// &cmds[port][slot].command, stores opened, sequence, dma_id, dma, iop_addr, command. Registers, frame and all 121
// instructions line up; only the tail store order differs. Same blocker as lilly3: the target's sequence store must
// depend on the dma_id store (command pointer with no alias base). No statement order (3360 tried) beats 11.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
typedef struct { unsigned int sequence; int type; int size; unsigned char data[20]; } PadIopCommand;
typedef struct { PadIopCommand command; } PadIopBuffer;
typedef struct { unsigned char data[0x58]; int frame; int retries; int length; unsigned char x64[3]; unsigned char data_ready; unsigned char x68[8]; unsigned char state; unsigned char req_state; unsigned char x72[0xE]; } PadDmaFrame;
typedef struct { PadDmaFrame *dma; PadIopCommand *command; void *iop_addr; int dma_id; int opened; int reserved[2]; } PadSlot;
typedef struct { int command; union { struct { int port; int slot; int result; int param; void *iop_addr; } common; } u; char pad[0x80 - 0x18]; } PadRpcBuffer;
extern PadSlot D_004505D0[2][4];
extern PadIopBuffer D_004506C0[2][4];
extern char D_00450580[];
extern PadRpcBuffer D_004507C0;
extern int D_002C830C;
extern char D_002AB6F0[];
extern char D_002AB720[];
int func_00236960(const char *, ...);
void *func_002333B4(void *, int, int);
int func_00237288(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int scePadPortOpen(int port, int slot, void *addr)
{
    PadDmaFrame *frame;
    PadIopCommand *command;
    int i;

    if ((unsigned int)addr & 0x3F) {
        if (D_002C830C) func_00236960(D_002AB6F0, addr);
        return 0;
    }
    if (D_004505D0[port][slot].opened == 1) {
        if (D_002C830C) func_00236960(D_002AB720, port, slot);
        return 0;
    }
    frame = addr;
    for (i = 0; i < 2; i++) {
        frame->frame = 0;
        frame->state = 5;
        frame->req_state = 2;
        frame->data_ready = 0;
        func_002333B4(frame->data, 0xFF, 0x20);
        frame->length = 0;
        frame++;
    }
    D_004507C0.command = 1;
    D_004507C0.u.common.port = port;
    D_004507C0.u.common.slot = slot;
    D_004507C0.u.common.param = (int)addr;
    if (func_00237288(D_00450580, 1, 0, &D_004507C0, 128, &D_004507C0, 128, 0, 0) < 0)
        return 0;
    command = &D_004506C0[port][slot].command;
    D_004505D0[port][slot].opened = 1;
    command->sequence = 0;
    D_004505D0[port][slot].dma_id = 0;
    D_004505D0[port][slot].dma = addr;
    D_004505D0[port][slot].iop_addr = D_004507C0.u.common.iop_addr;
    D_004505D0[port][slot].command = command;

    return D_004507C0.u.common.result;
}
