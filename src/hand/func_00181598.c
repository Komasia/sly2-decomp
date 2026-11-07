struct S { char pad[0x200]; int a; int b; };
extern char g_sw[];
void ResetHackSoBase__FP2LO(struct S *p);
void SetDockState__FP2LOi(struct S *p, int n);
void ApplyRsmg__FP2LOiP4RSMGii(void *g, int a, int *pb, struct S *p, int n);
// name: SafeHouse port (ResetDock)
void ResetDock__FP2LO(struct S *p)
{
    ResetHackSoBase__FP2LO(p);
    SetDockState__FP2LOi(p, 0);
    ApplyRsmg__FP2LOiP4RSMGii(g_sw, p->a, &p->b, p, 0);
}
