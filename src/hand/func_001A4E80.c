struct E { unsigned int x0; int x4; void *x8; int xC; int x10; int x14; int x18; };
struct S { int x0; struct E a[16]; int x1C4; };
struct P { char pad[0x108]; int x108; };
struct H { char pad[0x44]; int x44; };
extern struct P D_002F66B0;
extern struct H D_002E6550;
extern char g_sw[], D_002BFCA0[], g_game[];
int func_001A4E70(struct S *s);
void QueueMovie__FPUcPv(struct P *p, int n);
void RequestTransition__FP2SWPUc3OIDT2iT2(void *g, void *a, int b, int c, int d, int e);
void RequestTaskStartByOid__FP2SWi3OID(void *g, int a, int b);
void func_001ACC38(struct H *h, int n);
void func_001A4E80(struct S *s)
{
    struct E *e;
    struct P *p;
    if (!func_001A4E70(s))
        return;
    e = &s->a[s->x1C4++];
    switch (e->x0) {
    case 0:
    case 1:
        p = &D_002F66B0;
        QueueMovie__FPUcPv(p, e->x4);
        if (e->x0 == 1)
            p->x108 = e->x0;
        RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, D_002BFCA0, 0x189, -1, 0, -1);
        break;
    case 2:
        RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, e->x8, e->xC, -1, e->x10, 0x30A);
        break;
    case 3:
        RequestTaskStartByOid__FP2SWi3OID(g_game, e->x14, e->x18);
        break;
    case 4:
        break;
    case 5:
        if (!D_002E6550.x44)
            func_001ACC38(&D_002E6550, 1);
        func_001A4E80(s);
        break;
    }
}
