// NOTE (Claude agent): now MATCHED in src/lib/InitTimer.c with -Os + gnu-reorg + manually strength-reduced loop.
// WIP (Claude agent): structure right (use SLY2_ASM gnu-reorg for the nop-slot init loop). Remaining: register numbering - target keeps %hi(D_002C5A30) in s2 directly (lui s2) and ts in s1, ours lui v1 + copy to s4; loop counter/value regs v0/v1 swapped vs ours v1/a0.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
typedef struct Counter { struct Counter *next; int pad[15]; } Counter;
typedef struct { long time; int id; int pad; int x10; Counter *free; } TimerSys;
extern TimerSys D_002C5A30;
extern Counter D_0044C300[128];
void cbTimerHandler(void);
void *func_002333B4(void *, int, int);
void func_0023A618(void);
int func_00234710(int, void *, int, void *);
int func_00239450(void);
void func_00239AB0(int);
void func_00239AC0(int);
void func_00239AD0(int);
int func_00235178(int);
int func_002394A0(void);
int InitTimer(int mode)
{
    TimerSys *ts = &D_002C5A30;
    Counter *p;
    int i, r, oldei;
    unsigned int m;
    if (ts->id >= 0)
        return 0x80008001;
    ts->time = 0;
    ts->x10 = 0;
    func_002333B4(D_0044C300, 0, sizeof(D_0044C300));
    ts->free = D_0044C300;
    for (i = 127; i >= 0; i--)
        D_0044C300[i].next = &D_0044C300[i + 1];
    D_0044C300[127].next = 0;
    func_0023A618();
    r = func_00234710(0xB, cbTimerHandler, 0, 0);
    if (r < 0)
        return 0x80009021;
    D_002C5A30.id = r;
    oldei = func_00239450();
    m = *(volatile unsigned int *)0x10001010;
    m = (m & ~3) | mode;
    m |= 0x300;
    if (!(m & 0x80)) {
        func_00239AB0(0);
        m |= 0xC80;
        func_00239AD0(0xFFFF);
    }
    func_00239AC0(m);
    func_00235178(0xB);
    if (oldei) func_002394A0();
    return 0;
}
