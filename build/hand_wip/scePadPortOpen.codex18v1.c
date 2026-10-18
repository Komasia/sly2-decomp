// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int x8; unsigned char data[0x14]; } PadCmd;
typedef struct { unsigned char *buf; PadCmd *cmd; int iopbuf; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004505D0[2][4];
extern PadCmd D_004506C0[2][4];
extern char D_00450580[];
extern volatile int D_004507C0[];
extern int D_002C830C;
extern char D_002AB6F0[];
extern char D_002AB720[];
typedef struct { unsigned char x0[0x58]; int frame; int x5C; int len; int x64; unsigned char x68[8]; unsigned char state; unsigned char req; unsigned char ok; unsigned char x73[0xD]; } PadData;
int func_00236960(const char *, ...);
void *func_002333B4(void *, int, unsigned int);
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
        ((unsigned char *)p)[0x67] = 0;
        func_002333B4(p, 0xFF, 0x20);
        p->len = 0;
        p++;
    }
    D_004507C0[0] = 1;
    D_004507C0[1] = port;
    D_004507C0[2] = slot;
    D_004507C0[4] = (int)addr;
    if (func_00237288(D_00450580, 1, 0, (void *)D_004507C0, 0x80, (void *)D_004507C0, 0x80, 0, 0) < 0)
        return 0;
    c = &D_004506C0[port][slot];
    D_004505D0[port][slot].open = 1;
    c->x0 = 0;
    D_004505D0[port][slot].dmaid = 0;
    D_004505D0[port][slot].iopbuf = D_004507C0[5];
    D_004505D0[port][slot].buf = addr;
    D_004505D0[port][slot].cmd = c;
    return D_004507C0[3];
}
