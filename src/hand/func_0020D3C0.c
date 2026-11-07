typedef int qword __attribute__((mode(TI)));
typedef struct { short d; short pad; void *pfn; } VTE;
struct O { char pad[0xC]; VTE *vt; char pad2[0x184 - 0x10]; int n184; int n188; };
struct S { struct O *po; int state; float t; struct O *pc; };
struct L { struct O *pc; int pad; struct O *po; int a; int b; int pad2[3]; qword v20; qword v30; char pad3[0x20]; };
extern struct { float t; float dt; } g_clock;
void func_002333B4(void *p, int c, int n);
qword func_001A62E8(struct O *po);
void PaloAcceptContact__FP5CTMSG(struct L *pl);
// name: SafeHouse port (SetWatchB)
void SetWatchB__FP6WATCHBi(struct S *p, int state)
{
    if (state != p->state) {
        p->state = state;
        p->t = g_clock.t;
        if (state == 2) {
            struct L l;
            func_002333B4(&l, 0, sizeof(l));
            l.pc = p->pc;
            l.po = p->po;
            l.a = p->pc->n188;
            l.b = p->pc->n184;
            l.v20 = func_001A62E8(p->po);
            l.v30 = ((qword (*)(void *))p->po->vt[33].pfn)((char *)p->po + p->po->vt[33].d);
            PaloAcceptContact__FP5CTMSG(&l);
        }
    }
}
