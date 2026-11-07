struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern int D_002E1E40;
extern char g_game[];
struct VE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VE *vt; char pad1[0x38 - 0x10]; int x38; char pad2[4]; int x40; };
struct S { char pad[0x10]; int x10; char pad1[4]; int x18; char pad2[0x30 - 0x1C]; int x30; float f34; int x38; };
void Save__9JOBSCRIPTP11SAVEDSCRIPT(int a, int b);
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(int a, int b);
void SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(struct O *o, int a, int b, int c);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int a, int b);
#define VCALL0(o, n) ((void (*)())(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
// name: SafeHouse port (JOBPROX::SetProxState)
void SetProxState__7JOBPROXi(struct S *p, int st)
{
    if (st == p->x30) return;
    if (p->x30 == 0) Save__9JOBSCRIPTP11SAVEDSCRIPT(p->x18, p->x10 + 0x1090);
    EndChildJob__FPP5AIJOB(&p->x18);
    p->x30 = st;
    p->f34 = g_clock.t;
    switch (st) {
    case 0: {
        struct O *o = func_00205438(p->x10, 0xA9);
        SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(o, p->x38, 0, p->x10 + 0x1090);
        VCALL0(o, 8);
        break;
    }
    case 1: {
        struct O *o = func_00205438(p->x10, 0x9E);
        o->x38 = D_002E1E40;
        VCALL0(o, 8);
        break;
    }
    case 2: {
        struct O *o = func_00205438(p->x10, 0x9D);
        o->x40 = p->x10 + 0x1060;
        VCALL0(o, 8);
        BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x33, p->x10);
        break;
    }
    }
}
