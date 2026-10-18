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
int scePadPortOpen(int portArgument, int slot, void *addr)
{
    register int port asm("$19")=portArgument;
    int i;
    PadData *p;
    register PadCmd *c asm("$6");
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
    {
        register int stateOffset asm("$3")=slot*0x1C;
        register int portOffset asm("$7")=port*0x70;
        register PadSt *stateBase asm("$4")=(PadSt *)D_004505D0;
        register PadSt *opened asm("$2");
        register PadSt *dmaState asm("$5");
        register PadSt *iopState asm("$7");
        register PadSt *commandState asm("$4");
        register int returnedBuffer asm("$8");
        stateOffset=stateOffset+portOffset;
        opened=stateBase;
        opened=(PadSt *)((char *)opened+stateOffset);
        __asm__ __volatile__("lw %3,%5\n\t"
                             "sw %6,%4\n\t"
                             "daddu %0,%7,$0\n\t"
                             "daddu %1,%7,$0\n\t"
                             "sw $0,%2"
                             : "=&r"(dmaState), "=&r"(iopState), "=m"(c->x0),
                               "=&r"(returnedBuffer), "=m"(opened->open)
                             : "m"(D_004507C0[5]), "r"(1), "r"(opened));
        dmaState->dmaid = 0;
        iopState->iopbuf = returnedBuffer;
        __asm__ __volatile__("daddu %0,%2,$0\n\t"
                             "sw %3,%1"
                             : "=&r"(commandState), "=m"(((PadSt *)((char *)stateBase+stateOffset))->buf)
                             : "r"(dmaState), "r"(addr));
        __asm__ __volatile__("sw %1,%0" : "=m"(commandState->cmd) : "r"(c));
    }
    return D_004507C0[3];
}
