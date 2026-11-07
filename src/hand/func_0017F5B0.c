struct K { short x; short y; int i; };
extern const struct K D_002A5630;
struct G { int a; };
extern struct G g_sw;
struct S { char pad[0x18C]; int n18C; };
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(struct G *g, void *p, struct K k, int n);
// name: SafeHouse port (PostKillHackSo)
void PostKillHackSo__FP2LOi(struct S *p, int n) { if (p->n18C) return; p->n18C = 1; PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(&g_sw, p, D_002A5630, n); }
