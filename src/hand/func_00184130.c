struct VTE { short d; short pad; void (*pfn)(); };
struct S { char pad[0xC]; struct VTE *vt; char p1[0xFC]; int x10c; char p2[4]; void *x114; int x118; int x11c; char p3[0x3C]; int x15c; int x160; };
extern char g_sw[], g_game[];
void ApplyRsmg__FP2LOiP4RSMGii(void *g, int a, int *pb, struct S *p, int n);
void ApplyCheckpointTasks__FP2SWiP2LOPv(void *g, int a, int *pb, struct S *p);
void StartScptImpl__FP2LOi(void *p, int n);
void func_00184130(struct S *p, int n)
{
    struct VTE *e;
    p->x10c = n;
    e = &p->vt[4];
    ((void (*)(void *, int, struct S *))e->pfn)((char *)p + e->d, 6, p);
    ApplyRsmg__FP2LOiP4RSMGii(g_sw, p->x118, &p->x11c, p, 1);
    ApplyCheckpointTasks__FP2SWiP2LOPv(g_game, p->x15c, &p->x160, p);
    e = &p->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)((char *)p + e->d, 5, 0, 0, 0, 0);
    if (p->x114) StartScptImpl__FP2LOi(p->x114, n);
}
