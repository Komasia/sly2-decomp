struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0x18]; struct VTE *vt; };
struct S { char pad[0x80]; float gMin; float gMax; float *pg; int pad1; struct O *po; int pad2; short k; short state; };
void ResetXfParams__FP2XFPv(void *pa, struct S *p);
void SetXfMode__FP3ALOP2XFi(void *pa, struct S *p, int state);
// name: SafeHouse port (RefreshXf)
void RefreshXf__FP3ALOP2XF(void *pa, struct S *p)
{
    float g = *p->pg;
    if (g < p->gMin || p->gMax < g || p->state >= 3) {
        if (p->po) {
            p->po->vt[4].pfn((char *)p->po + p->po->vt[4].d);
            switch (p->k) {
            case 10:
                if (p->state == 3 || p->state == 4) SetXfMode__FP3ALOP2XFi(pa, p, 7);
                else if (p->state != 2) SetXfMode__FP3ALOP2XFi(pa, p, 6);
                break;
            case 6:
                if (p->state == 3 || p->state == 4) SetXfMode__FP3ALOP2XFi(pa, p, 7);
                break;
            case 19:
                if (p->state != 2) SetXfMode__FP3ALOP2XFi(pa, p, 0x12);
                break;
            case 12:
                if (p->state != 2) SetXfMode__FP3ALOP2XFi(pa, p, 0xB);
                break;
            }
        } else {
            p->state = 0;
            ResetXfParams__FP2XFPv(pa, p);
            SetXfMode__FP3ALOP2XFi(pa, p, 0);
        }
    }
}
