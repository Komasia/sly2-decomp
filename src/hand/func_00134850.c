struct VTE { short d; short pad; void *pfn; };
struct PO { char pad[0x1C]; float g1C; char pad1[0x30 - 0x20]; int x30; };
struct P {
    char pad[0xC]; struct VTE *vt; char pad0[0x150 - 0x10]; struct PO *p150;
    char pad1[0x20C - 0x154]; float g20C; char pad2[0x2C0 - 0x210]; char a2C0[0x4C0 - 0x2C0];
    int x4C0; char pad3[0x4C8 - 0x4C4]; int x4C8; char pad4[0xDF0 - 0x4CC]; char aDF0[0xF00 - 0xDF0];
    char aF00[0xF50 - 0xF00]; char aF50[0x1030 - 0xF50]; void *p1030; void *p1034; char pad5[0x11B0 - 0x1038];
    char a11B0[0x13D0 - 0x11B0]; int state; float t13D4; char pad6[0x16B4 - 0x13D8]; int x16B4;
    char pad7[0x1870 - 0x16B8]; int x1870;
};
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern float D_002BC930;
void SetJumpKind__FP4JUMPiiP2LO(void *pv, int a, int b, int c);
int FActorTargetInReach__FP5ACTORi(struct P *p, int n);
void SetBentleyState__FP7BENTLEYi(struct P *p, int n);
int GrfPadctlTakePressed__FP6PADCTL(struct PO *po, int grf, float g);
int GrfPadctlPressedWithin__FP6PADCTLUif(struct PO *po, int grf, float g);
void ForgetPadctlPresses__FP6PADCTLUi(struct PO *po, int grf);
void UpdateJumpTransitions__FP4JUMP(void *pv);
void UpdateInteractTransitions__FP5ACTOR(void *pv);
void UpdateDamageTransitions__FP5ACTOR(void *pv);
void OpenBinoc__FP5ACTORiP2LOT2(void *pv, int a, int b, int c);
void FInteractCircle__FP5ACTOR(void *pv, int a, int b);
int CbFromSaak(struct P *p, int n) asm("CbFromSaak__F4SAAK");
void UpdateClimbTransitions__FP5ACTOR(void *pv);
void UpdateBentleyHold__FP7BENTLEY(struct P *p);
void func_001367D8(struct P *p);
void UpdateJtThrow__FP7JTTHROW(void *pv);
int FAsegaRetracted(void *pv) asm("FAsegaRetracted__FP5ASEGA");
int FSmaRetracted(void *pv) asm("FSmaRetracted__FP3SMA");
void UpdateBentleyState2__FP7BENTLEY(struct P *p);

#define VCALL99(p, a) ((int (*)(void *, int))(p)->vt[99].pfn)((char *)(p) + (p)->vt[99].d, a)

// name: SafeHouse port (UpdateBentleyTransitions)
void UpdateBentleyTransitions__FP7BENTLEY(struct P *p)
{
    int s;
    do {
        s = p->state;
        switch (s) {
        case 2:
        case 4:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
            break;
        case 3:
            if (p->x4C8 == 1 || p->x4C8 == 12)
                break;
            if (0.1f < g_clock.t - p->g20C)
                SetJumpKind__FP4JUMPiiP2LO(p->a2C0, 0, 0, 0);
            break;
        case 5:
        case 7:
        case 12:
        default:
            if (0.1f < g_clock.t - p->g20C)
                SetJumpKind__FP4JUMPiiP2LO(p->a2C0, 0, 0, 0);
            break;
        }
        switch (p->state) {
        case 0:
        case 1:
        case 7:
            if (!(p->p150->x30 & 8) && FActorTargetInReach__FP5ACTORi(p, 0)) {
                SetBentleyState__FP7BENTLEYi(p, 5);
            } else if (GrfPadctlTakePressed__FP6PADCTL(p->p150, 0x40, 0.1f)) {
                SetJumpKind__FP4JUMPiiP2LO(p->a2C0, 1, 0, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(p->p150, 0x400, 0.15f) && VCALL99(p, 3)) {
                ForgetPadctlPresses__FP6PADCTLUi(p->p150, 0x400);
                OpenBinoc__FP5ACTORiP2LOT2(p->aF00, 0, 0, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(p->p150, 0x10, 0.15f) && VCALL99(p, p->x1870)) {
                ForgetPadctlPresses__FP6PADCTLUi(p->p150, 0x10);
                p->x16B4 = CbFromSaak(p, p->x1870);
                SetBentleyState__FP7BENTLEYi(p, 6);
            } else if (GrfPadctlTakePressed__FP6PADCTL(p->p150, 0x20, 0.2f)) {
                FInteractCircle__FP5ACTOR(&p->x4C0, 0xF8FE, 0);
            } else {
                float g = p->p150->g1C;
                if ((p->state == 0 && 0.1f < g) || (p->state != 0 && 0.0f < g)) {
                    if (p->p150->x30 & 8)
                        SetBentleyState__FP7BENTLEYi(p, 1);
                    else
                        SetBentleyState__FP7BENTLEYi(p, 7);
                } else {
                    SetBentleyState__FP7BENTLEYi(p, 0);
                }
            }
            break;
        case 2:
            UpdateJumpTransitions__FP4JUMP(p->a2C0);
            if (GrfPadctlPressedWithin__FP6PADCTLUif(p->p150, 0x10, 0.15f) && VCALL99(p, p->x1870)) {
                ForgetPadctlPresses__FP6PADCTLUi(p->p150, 0x10);
                p->x16B4 = CbFromSaak(p, p->x1870);
                SetBentleyState__FP7BENTLEYi(p, 6);
            }
            break;
        case 3:
            UpdateInteractTransitions__FP5ACTOR(&p->x4C0);
            break;
        case 4:
            UpdateDamageTransitions__FP5ACTOR(p->aDF0);
            break;
        case 5:
            if ((p->p150->x30 & 8) || !FActorTargetInReach__FP5ACTORi(p, 1)) {
                SetBentleyState__FP7BENTLEYi(p, 0);
            } else if (GrfPadctlTakePressed__FP6PADCTL(p->p150, 0x40, 0.1f)) {
                SetJumpKind__FP4JUMPiiP2LO(p->a2C0, 1, 0, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(p->p150, 0x400, 0.15f) && VCALL99(p, 3)) {
                ForgetPadctlPresses__FP6PADCTLUi(p->p150, 0x400);
                OpenBinoc__FP5ACTORiP2LOT2(p->aF00, 0, 0, 0);
            } else if (GrfPadctlTakePressed__FP6PADCTL(p->p150, 0x20, 0.2f)) {
                FInteractCircle__FP5ACTOR(&p->x4C0, 0xF8FE, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(p->p150, 0x10, 0.15f) && VCALL99(p, p->x1870)) {
                ForgetPadctlPresses__FP6PADCTLUi(p->p150, 0x10);
                p->x16B4 = CbFromSaak(p, p->x1870);
                SetBentleyState__FP7BENTLEYi(p, 6);
            }
            break;
        case 13:
            UpdateClimbTransitions__FP5ACTOR(p->aF50);
            break;
        case 6:
            UpdateBentleyHold__FP7BENTLEY(p);
            break;
        case 8:
            func_001367D8(p);
            break;
        case 12:
            UpdateJtThrow__FP7JTTHROW(p->a11B0);
            break;
        case 10:
            if (p->p1030 && FAsegaRetracted(p->p1030))
                SetBentleyState__FP7BENTLEYi(p, 0);
            else if (p->p1034 && FSmaRetracted(p->p1034))
                SetBentleyState__FP7BENTLEYi(p, 0);
            break;
        case 14:
            if (D_002BC930 < g_clock.t - p->t13D4)
                SetBentleyState__FP7BENTLEYi(p, 0);
            break;
        }
        UpdateBentleyState2__FP7BENTLEY(p);
    } while (p->state != s);
}
