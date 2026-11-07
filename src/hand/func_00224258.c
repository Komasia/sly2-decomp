struct VTE { short d; short pad; void (*pf)(); };
struct O { int a[3]; struct VTE *vt; char pad[0x14C]; int k; };
struct Q { char pad[0x18]; int k; };
void ReparentBooty__FP3ALOii(struct O *p, struct Q *q, int a);
// name: SafeHouse port (LandCarry)
void LandCarry__FP2LOT0(struct O *p, struct Q *q)
{
    int k = p->k;
    if (k == 0x1A || k == 0x29) p->vt[76].pf((char *)p + p->vt[76].d, 3);
    else {
        ReparentBooty__FP3ALOii(p, q->k == 1 ? 0 : q, 3);
        p->vt[76].pf((char *)p + p->vt[76].d, 2);
    }
}
