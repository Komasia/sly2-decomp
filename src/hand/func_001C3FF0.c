struct G { char pad[0x3B0]; int a; };
struct S { char pad[0x16C]; void *p; };
extern struct G g_cm;
void SetZoneForced__FP2LOi(void *p, int f);
void SetCmPolicy__FP2CM3CPPP5CPLCYii(struct G *pg, int n, void *pv, void *p, int m);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(struct G *pg, int a, int b, void *c, void *d, int e);
// name: SafeHouse port (SetCmFocusObject)
void SetCmFocusObject__FP2LOi(struct S *p, int f)
{
    if (f) {
        if (p->p) SetZoneForced__FP2LOi(p->p, 1);
        else SetCmPolicy__FP2CM3CPPP5CPLCYii(&g_cm, 1, &g_cm.a, p, 0);
    } else {
        if (p->p) SetZoneForced__FP2LOi(p->p, 0);
        else RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(&g_cm, 0xF, 1, &g_cm.a, p, 0);
    }
}
