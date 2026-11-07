struct G;
extern struct G g_sw;
struct O { char pad[0x58]; int n58; char p2[0xEC]; unsigned long fl; };
struct S { char pad[0x34]; struct O *o; char p2[0x28]; int f60; int p64; char x68[4]; };
void DeleteCtrl__FPP4CTRL(void *pv);
void SetXfMode__FP3ALOP2XFi(struct O *o, int n, int m);
void RecalcSwOxfFilterForObject__FP2SWP2SO(struct G *pg, struct O *o);
// name: SafeHouse port (ReleaseK2Ballistic)
void ReleaseK2Ballistic__FP6K2PLAY(struct S *p)
{
    if (p->f60) {
        p->f60 = 0;
        if (*(int *)p->x68) {
            DeleteCtrl__FPP4CTRL(p->x68);
            SetXfMode__FP3ALOP2XFi(p->o, p->o->n58, 2);
            p->o->fl &= ~(1L << 26);
            RecalcSwOxfFilterForObject__FP2SWP2SO(&g_sw, p->o);
        }
    }
}
