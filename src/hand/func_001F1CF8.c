struct X { char pad[0x54]; int n54; };
struct O { char pad[0x230]; struct X *px; };
struct Ent { int a0; int a4; int a8; int aC; };
struct P { char pad[0x404]; struct Ent a[8]; int n484; int n488; int n48C; int n490; int n494; };
struct G;
extern struct G g_sw;
struct O *func_0015E938(struct G *, int, int, int);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *, int);
int NReadyReward__FP2LOT0iPv(int, struct O *, int, int);
void UpdatePocketMode__FP2LO(struct P *);
// name: SafeHouse port (NextPocketPrize)
void NextPocketPrize__FP2LO(struct P *p)
{
    p->n48C = 0;
    for (; p->n488 < p->n484; p->n488++) {
        struct Ent *pe = &p->a[p->n488];
        struct O *po = func_0015E938(&g_sw, 4, pe->a0, p->n494);
        int a8, k;
        if (!po) continue;
        a8 = pe->a8;
        k = 0x2B0;
        if (FIsBasicDerivedFrom__FP5BASIC3CID(po, 0x5C)) {
            struct X *px = po->px;
            if (px) {
                int n = px->n54;
                if (n == -1 || n == 0) { p->n48C = 1; break; }
                if (n != 1) continue;
            }
            k = 0x2B1;
        }
        if (NReadyReward__FP2LOT0iPv(p->n494, po, a8, k) == 1) p->n48C = 1;
        break;
    }
    UpdatePocketMode__FP2LO(p);
}
