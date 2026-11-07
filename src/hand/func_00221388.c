struct K { int a, b; };
extern struct K D_002A96F0;
extern char g_sw[];
struct S { char pad[0x13C]; int x; };
void UpdateLo__FP2LO(struct S *p);
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(void *g, struct S *p, struct K k, int z);
// name: SafeHouse port (UpdateZone)
void UpdateZone__FP2LO(struct S *p)
{
    UpdateLo__FP2LO(p);
    if (p->x) PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(g_sw, p, D_002A96F0, 0);
}
