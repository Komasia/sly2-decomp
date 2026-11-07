struct VTE { short d; short pad; void (*pfn)(void *, int, int, int, int, int); };
struct S { char pad[0xC]; struct VTE *vt; char p2[0x1F0]; int a; int b; };
extern char g_sw[];
void ApplyRsmg__FP2LOiP4RSMGii(void *g, int a, int *pb, struct S *p, int n);
void func_00181780(struct S *p)
{
    struct VTE *e;
    ApplyRsmg__FP2LOiP4RSMGii(g_sw, p->a, &p->b, p, 1);
    e = &p->vt[3];
    e->pfn((char *)p + e->d, 5, 0, 0, 0, 0);
}
