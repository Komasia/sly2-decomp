struct VT { short d; short pad; void *pfn; };
struct A { char pad[0x30]; int x30; };
struct O { char pad[0xC]; struct VT *pvt; char pad2[0x150 - 0x10]; struct A *pa; };
struct P { struct O *po; int x4; int x8; int xC; int x10; int x14; char pad[0xE0 - 0x18]; void *pE0; };
int FAsegaRetracted(void *p) asm("FAsegaRetracted__FP5ASEGA");
void SetBentleySubMode__FP7BENTLEYi(struct P *p, int k);
int GrfPadctlPressedWithin__FP6PADCTLUif(struct A *pa, float g, int n);
void ForgetPadctlPresses__FP6PADCTLUi(struct A *pa, int n);
// name: SafeHouse port (UpdateBentleySub)
void UpdateBentleySub__FP7BENTLEYi(struct P *p, int k)
{
    if (p->pE0 && FAsegaRetracted(p->pE0))
        SetBentleySubMode__FP7BENTLEYi(p, -1);
    if (k != p->x4 && p->x4 != -1)
        SetBentleySubMode__FP7BENTLEYi(p, k);
    if (k != -1 && (p->x4 == -1 || p->xC)) {
        if (GrfPadctlPressedWithin__FP6PADCTLUif(p->po->pa, 0.1f, 0x80)) {
            struct O *po = p->po;
            if (((int (*)(void *, int))po->pvt[99].pfn)((char *)po + po->pvt[99].d, 2)) {
                ForgetPadctlPresses__FP6PADCTLUi(p->po->pa, 0x80);
                SetBentleySubMode__FP7BENTLEYi(p, -1);
                SetBentleySubMode__FP7BENTLEYi(p, k);
            }
        }
    }
    if (!(p->po->pa->x30 & 0x80))
        p->x14 = 1;
}
