struct S;
struct VTE { short d; short pad; void (*pfn)(); };
struct S { int x0, x4, x8; struct VTE *vt; char pad[0x134 - 0x10]; int x134; int pad1; int k; char pad2[0x158 - 0x140]; float t; int pad3; float dt; int x164; char a168[4]; };
struct G;
extern struct G g_sw;
extern char g_cm[];
extern char g_game[];
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
void SetExitState__FP2LOi(struct S *p, int k);
struct S *func_002280D0(struct G *pg);
void ApplyCheckpointTasks__FP2SWiP2LOPv(void *a, int b, void *c, struct S *p);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *a, int b, int c, void *d, int e, int f);
// name: SafeHouse port (TriggerExit)
void TriggerExit__FP4EXIT(struct S *p)
{
    if (p->k != 3) return;
    if (p->x134) {
        struct S *q;
        SetExitState__FP2LOi(p, 0);
        q = func_002280D0(&g_sw);
        if (q) TriggerExit__FP4EXIT(q);
        return;
    }
    ApplyCheckpointTasks__FP2SWiP2LOPv(g_game, p->x164, p->a168, p);
    RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 2, -1, g_cm + 0x450, 0, 0);
    RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 2, -1, g_cm + 0x520, 0, 0);
    SetExitState__FP2LOi(p, 4);
    p->t = g_clock.t + p->dt;
    p->vt[3].pfn((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
}
