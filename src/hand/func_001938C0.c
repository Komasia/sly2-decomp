struct O { char pad[0x10C]; int x10c; };
struct E { struct O *x0; int x4; float x8; int pad[9]; };
struct G { char pad[0x4678]; int c; int pad2; struct E ae[1]; };
extern struct G g_sw;
extern float D_002BF660;
extern int D_002E1E40;
struct P { int x0; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *o, int n);
void StartInteract__FP5ACTORii3JTL(struct P *p, int n, struct O *o, int a);
// name: SafeHouse port (FInteractCircle)
int FInteractCircle__FP5ACTOR(struct P *p)
{
    struct G *g = &g_sw;
    int n = g->c;
    int i;
    for (i = 0; i < n; i++) {
        struct E *e = &g->ae[i];
        struct O *o;
        int k;
        if (e->x8 > D_002BF660) break;
        o = e->x0;
        if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x13) || FIsBasicDerivedFrom__FP5BASIC3CID(o, 0xB))
            k = (p->x0 == D_002E1E40) ? 6 : 5;
        else if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x1B))
            k = 8;
        else if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0xC))
            k = 0;
        else if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x22))
            k = 0;
        else if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x26))
            k = e->x0->x10c;
        else
            k = FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x23) ? 7 : -1;
        if (k != -1) {
            StartInteract__FP5ACTORii3JTL(p, k, o, e->x4);
            return 1;
        }
    }
    return 0;
}
