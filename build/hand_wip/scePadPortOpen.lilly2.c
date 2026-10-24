// scePadPortOpen (0x243088) WIP, lilly2 (Claude agent, 2026-10-23): 11/121 differ, aligned 9. Plain C, no asm.
// = lilly1 + -fstrict-aliasing (as sceFsInit and other Sony libs) + field types: dmaid void *, cmd PadCmd *, and the
// IOP buffer address read from rdata as a pointer (unsigned char *), so its lw no longer waits for the open store.
// Left: target stores open, x0, dmaid, iopbuf, buf, cmd in that order; ours open, iopbuf, buf, x0, cmd, dmaid
// (void */PadCmd * fields leave the int store chain; making them int swaps s2/s3). See notes/23C000.md.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int x8; unsigned char data[0x14]; } PadCmd;
typedef struct { int buf; PadCmd *cmd; int iopbuf; void *dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];
extern PadCmd D_004506C0[2][4];
extern char D_00450580[];
extern int D_004507C0[];
extern int D_002C830C;
extern char D_002AB6F0[];
extern char D_002AB720[];
typedef struct { unsigned char x0[0x58]; int frame; int x5C; int len; int x64; unsigned char x68[8]; unsigned char state; unsigned char req; unsigned char ok; unsigned char x73[0xD]; } PadData;
int func_00236960(const char *, ...);
void *func_002333B4(void *, int, int);
int func_00237288(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int scePadPortOpen(int port, int slot, void *addr)
{
    int i;
    PadData *p;
    PadCmd *c;

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
    D_004505D0[port][slot].open = 1;
    c->x0 = 0;
    D_004505D0[port][slot].dmaid = 0;
    D_004505D0[port][slot].iopbuf = (int)((unsigned char **)p)[5];
    D_004505D0[port][slot].buf = (int)addr;
    D_004505D0[port][slot].cmd = c;
    return ((int *)p)[3];
}
