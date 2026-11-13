struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad1[0x158 - 0x10]; int x158; char pad2[0x1A0 - 0x15C]; int x1A0; };
struct Q { int x0; };
struct P { char pad[0x150]; void *p150; char pad0[0x20C - 0x154]; float g20C; char padA[0x2C0 - 0x210]; char a2C0[0x1030 - 0x2C0]; void *p1030;
    char pad1[0x13D0 - 0x1034]; int x13D0; char pad2[0x16B0 - 0x13D4]; int x16B0; struct Q *pq; char pad3[0x186C - 0x16B8]; struct O *po; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
int FAsegaRetracted(void *pv) asm("FAsegaRetracted__FP5ASEGA");
void SetBentleyHold__FP7BENTLEYi(struct P *p, int n);
void LandCarry__FP2LOT0(struct O *po, int n);
int func_00141EA8(struct P *p, int n);
int func_001C4728(void *pv, int n);
void ReleaseBentleyCarried__FP7BENTLEY(struct P *p);
void SetJumpKind__FP4JUMPiiP2LO(void *pv, int a, int b, int c);
// name: SafeHouse port (UpdateBentleyHold)
void UpdateBentleyHold__FP7BENTLEY(struct P *p)
{
    int s;
    for (;;) {
        s = p->x16B0;
        switch (s) {
        case 0:
            if (FAsegaRetracted(p->p1030))
                SetBentleyHold__FP7BENTLEYi(p, 1);
            break;
        case 1:
        case 2: {
            struct O *po = p->po;
            if (po->x158 == 2) {
                LandCarry__FP2LOT0(po, po->x1A0);
                goto common;
            }
            if (po->x158 == 4 || !func_001C4728(p->p150, func_00141EA8(p, p->pq->x0) | 0x10)) {
                ((void (*)(void *, int))po->vt[76].pfn)((char *)po + po->vt[76].d, 1);
            common:
                ReleaseBentleyCarried__FP7BENTLEY(p);
                SetJumpKind__FP4JUMPiiP2LO(p->a2C0, 0xB, 0, 0);
            } else if (0.1f < g_clock.t - p->g20C) {
                SetBentleyHold__FP7BENTLEYi(p, 2);
            } else {
                SetBentleyHold__FP7BENTLEYi(p, 1);
            }
            break;
        }
        }
        if (p->x16B0 == s || p->x13D0 != 6)
            break;
    }
}
