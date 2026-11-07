struct G { int a; };
extern struct G g_sw;
extern int D_002E1E00;
extern char g_game[];
struct S { char pad[0x184]; int n184; char pad2[0x38]; int n1C0; };
int IsSwHandsOff__FP2SW(struct G *g);
int FHackSoHit__FP2LOP5CTMSG(struct S *p, int *pn);
void UpdateHackHud__FP2LO(struct S *p);
void BroadcastTaskEvent__FP2SWiP2LO(void *g, int n, int m);
void SetShipState__FP2LOi(struct S *p, int n);
// name: SafeHouse port (FAcceptShipContact)
int FAcceptShipContact__FP3ALOP5CTMSG(struct S *p, int *pn) {
    if (p->n1C0 < 5) { if (p->n1C0 >= 2) return 0; }
    if (IsSwHandsOff__FP2SW(&g_sw)) return 0;
    if (D_002E1E00 & 1) return 0;
    if (!FHackSoHit__FP2LOP5CTMSG(p, pn)) return 0;
    UpdateHackHud__FP2LO(p);
    if (p->n184 > 0) { BroadcastTaskEvent__FP2SWiP2LO(g_game, 0xF, *pn); SetShipState__FP2LOi(p, 2); }
    else SetShipState__FP2LOi(p, 4);
    return 1;
}
