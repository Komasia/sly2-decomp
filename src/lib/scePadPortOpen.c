#include "libpad_rpc.h"
/* scePadPortOpen (libpad): open (port, slot) with the 64-byte aligned, 256-byte DMA buffer `addr`; returns 1 on success. */
// codegen: plain C. The key: the IOP request buffer D_004507C0 is used directly (lilly9 reused the loop pointer p, which has no alias base).
// With strict aliasing the field types decide which tail stores conflict: open/dmaid/x0 (int) conflict, cmd/iopcmd
// (PadCmd *) conflict, buf (PadData *) and the void * read of D_004507C0[5] are alone. The int return read
// D_004507C0[3] has a known base in sched1, so it stays independent of the PadSt stores there; in sched2 (hard-reg
// addresses are baseless) it depends on the int stores, which raises the dmaid store's priority so it issues right
// after c->x0 like the target. See notes/23C000.md (T1636, T1642).
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int x8; unsigned char data[0x14]; } PadCmd;
typedef struct { unsigned char x0[0x58]; int frame; int x5C; int len; int x64; unsigned char x68[8]; unsigned char state; unsigned char req; unsigned char ok; unsigned char x73[0xD]; } PadData;
typedef struct { PadData *buf; PadCmd *cmd; PadCmd *iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];
extern PadCmd D_004506C0[2][4];
extern char D_00450580[];   /* padman RPC client */
extern int D_004507C0[];    /* RPC request/reply buffer */
extern int D_002C830C;      /* debug prints enabled */
extern char D_002AB6F0[];   /* "libpad: buffer addr is not 64 byte align. %08x\n" */
extern char D_002AB720[];   /* "libpad: pad port is already open [%d][%d]\n" */
int scePrintf(const char *, ...);
void *s1_memset(void *, int, int) asm("memset");
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int scePadPortOpen(int port, int slot, void *addr)
{
    int i;
    PadData *p;
    PadCmd *c;
    void *t;
    if ((int)addr & 0x3F) {
        if (D_002C830C) scePrintf(D_002AB6F0, addr);
        return 0;
    }
    if (D_004505D0[port][slot].open == 1) {
        if (D_002C830C) scePrintf(D_002AB720, port, slot);
        return 0;
    }
    p = (PadData *)addr;
    for (i = 0; i < 2; i++) {
        p->frame = 0;
        p->state = scePadStateExecCmd;
        p->req = scePadReqStateBusy;
        p->x68[-1] = 0;
        s1_memset(p, 0xFF, 0x20);
        p->len = 0;
        p++;
    }
    D_004507C0[0] = PAD_RPCCMD_OPEN;
    D_004507C0[1] = port;
    D_004507C0[2] = slot;
    D_004507C0[4] = (int)addr;
    if (sceSifCallRpc(D_00450580, 1, 0, D_004507C0, 0x80, D_004507C0, 0x80, 0, 0) < 0)
        return 0;
    c = &D_004506C0[port][slot];
    t = ((void **)D_004507C0)[5];
    D_004505D0[port][slot].open = 1;
    D_004505D0[port][slot].iopcmd = t;
    D_004505D0[port][slot].buf = addr;
    D_004505D0[port][slot].cmd = c;
    c->x0 = 0;
    D_004505D0[port][slot].dmaid = 0;
    return D_004507C0[3];
}
