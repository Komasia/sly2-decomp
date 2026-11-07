struct E { int n; int a, b, c; };
struct T { char pad[0xA70]; struct E ae[1]; };
struct T2 { char pad[0xF64]; void *pF64; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x2C]; struct E *p40; char pad3[0xC]; int n50; char pad4[8]; void *p5C; };
extern char g_game[];
int IbitLow__FUi(void *p);
void Enter__6JOBHIT(struct S *p);
void BroadcastTaskEvent__FP2SWiP2LO(void *g, int n, void *p);
void func_00154038(void *p, int a, int b);
// name: SafeHouse port (JOBHIT1::Enter)
void Enter__7JOBHIT1(struct S *p) {
    p->p40 = &p->pt->ae[IbitLow__FUi(p->p5C)];
    if (p->p40->n == -1) p->p40 = 0;
    Enter__6JOBHIT(p);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x15, p->pt);
    func_00154038(((struct T2 *)p->pt)->pF64, p->n50, 2);
}
