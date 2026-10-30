// scePadPortOpen (0x243088) WIP, lilly9 (Claude agent, T1636, 2026-10-24): 5/121 differ, aligned 1 (lilly3: 3). Plain C, no asm.
// Found by a full sweep (alias-set partition of the 6 tail stores + the 2 rdata reads x all store orders, ~500k compiles).
// Everything matches except the dmaid store: ours is issued last, the target issues it right after c->x0.
// Why the types: with strict aliasing the field types decide which tail stores conflict (all PadSt addresses share the
// D_004505D0 base), and that decides both schedulers' order. open/dmaid (int) conflict with each other; cmd and the IOP
// command address (PadCmd *) conflict; buf (PadData *) and the rdata[5]/[3] reads (void *) are alone. The rdata reads
// go through the reused loop pointer p, which has no alias base (alias.c: set twice), so the last read stays last.
// See notes/23C000.md (T1636) for the scheduler analysis and what is still open.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int x8; unsigned char data[0x14]; } PadCmd;
typedef struct { unsigned char x0[0x58]; int frame; int x5C; int len; int x64; unsigned char x68[8]; unsigned char state; unsigned char req; unsigned char ok; unsigned char x73[0xD]; } PadData;
typedef struct { PadData *buf; PadCmd *cmd; PadCmd *iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];
extern PadCmd D_004506C0[2][4];
extern char D_00450580[];
extern int D_004507C0[];
extern int D_002C830C;
extern char D_002AB6F0[];
extern char D_002AB720[];
int func_00236960(const char *, ...);
void *func_002333B4(void *, int, int);
int func_00237288(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int scePadPortOpen(int port, int slot, void *addr)
{
    int i;
    PadData *p;
    PadCmd *c;
    void *t;
    if ((int)addr & 0x3F) {
        if (D_002C830C) func_00236960(D_002AB6F0, addr);
        return 0;
    }
    if (D_004505D0[port][slot].open == 1) {
        if (D_002C830C) func_00236960(D_002AB720, port, slot);
        return 0;
    }
    p = (PadData *)addr;
    for (i = 0; i < 2; i++) {
        p->frame = 0;
        p->state = 5;
        p->req = 2;
        p->x68[-1] = 0;
        func_002333B4(p, 0xFF, 0x20);
        p->len = 0;
        p++;
    }
    p = (PadData *)D_004507C0;
    ((int *)p)[0] = 1;
    ((int *)p)[1] = port;
    ((int *)p)[2] = slot;
    ((int *)p)[4] = (int)addr;
    if (func_00237288(D_00450580, 1, 0, p, 0x80, p, 0x80, 0, 0) < 0)
        return 0;
    c = &D_004506C0[port][slot];
    t = ((void **)p)[5];
    D_004505D0[port][slot].open = 1;
    D_004505D0[port][slot].iopcmd = t;
    D_004505D0[port][slot].buf = addr;
    D_004505D0[port][slot].cmd = c;
    c->x0 = 0;
    D_004505D0[port][slot].dmaid = 0;
    return (int)((void **)p)[3];
}
