typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct VO { char pad[0xC]; struct VTE *vt; };
struct ASEG { char pad[0x74]; float g74; };
struct ASEGP { int x0; struct ASEG *pasega; };
struct X1030 { char pad[0x14]; struct ASEG *pasega; char pad1[0x1C - 0x18]; float g1C; };
struct P {
    char pad[0xC]; struct VTE *vt; char pad0[0x58 - 0x10]; void *p58; void *p5C;
    char pad1[0x190 - 0x60]; qword q190; float g1A0; char pad2[0x2C0 - 0x1A4]; char a2C0[0x4C0 - 0x2C0];
    char a4C0[8]; int x4C8; char pad3[0xDF0 - 0x4CC]; char aDF0[0xF00 - 0xDF0]; char aF00[0xF50 - 0xF00];
    char aF50[0x1028 - 0xF50]; void *p1028; void *p102C; struct X1030 *p1030; int x1034;
    char pad4[0x108C - 0x1038]; int x108C; char pad5[0x11B0 - 0x1090]; char a11B0[0x1320 - 0x11B0];
    struct ASEGP x1320; char pad6[0x1374 - 0x1328]; struct ASEG *p1374; char pad7[0x13D0 - 0x1378];
    int state; float t13D4; char pad8[0x14E0 - 0x13D8]; struct ASEG *p14E0; char pad9[0x1600 - 0x14E4];
    struct ASEGP x1600; char pad10[0x16D0 - 0x1608]; struct VO *p16D0; struct VO *p16D4;
    char pad11[0x181C - 0x16D8]; int x181C; struct ASEG *p1820; char pad12[0x186C - 0x1824]; struct VO *p186C;
    char pad13[0x1878 - 0x1870]; struct ASEG *p1878;
};
#include "clock.h"
extern qword D_002A2DD0;
void SetXfMode__FP3ALOP2XFi(struct P *, void *, int);
void ActorNextLookTime(struct P *) asm("ActorNextLookTime__FP5ACTOR");
void ExplodeExpl__FP4EXPL(struct VO *);
void SetJumpAnimState__FP4JUMPiP2LO(void *, int, int);
void SetInteractState__FP5ACTORi(void *, int);
void SetDamageState__FP5ACTORi(void *, int);
void SetClimbState__FP5ACTORi(void *, int);
void ReleaseBentleyCarried__FP7BENTLEY(struct P *);
void SetBentleyHold__FP7BENTLEYi(struct P *, int);
void SetBentleyCarried__FP7BENTLEYi(struct P *, int);
void SetJtThrowState__FP7JTTHROWi(void *, int);
int IsmsFindSmOptional(void *, int) asm("IsmsFindSmOptional__FP2SM3OID");
int GrfActorLookMask__FP5ACTOR(struct P *);
void ActorSetLookFlag__FP5ACTORi(struct P *, int);
void ResetGaitFeet__FP4GAIT(struct ASEGP *);
void SetBinocState__FP5ACTORi(void *, int);
void RetractAsegaPp__FPP5ASEGA(void *);
void ClearSmaHandle__FPP3SMA(void *);
void ApplyAsegCur(struct ASEG *, struct P *, int, void *, float, float) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void ReplaceSmaHandleMask__FP2SMi3OIDiUiPP3SMA(void *, struct P *, int, int, int, void *);

#define VCALL0(p, n) ((void (*)(void *))(p)->vt[n].pfn)((char *)(p) + (p)->vt[n].d)
#define VCALL1(p, n, a) ((void (*)(void *, int))(p)->vt[n].pfn)((char *)(p) + (p)->vt[n].d, a)

// name: SafeHouse port (SetBentleyState)
void SetBentleyState__FP7BENTLEYi(struct P *p, int k)
{
    int kOld;
    struct ASEG *pasega;
    void *pjt;
    int c;
    int anim;
    int n;
    float g;
    float rate;
    struct ASEGP *pa;

    if (k == p->state)
        return;
    switch (p->state) {
    case 0:
        SetXfMode__FP3ALOP2XFi(p, p->p58, 2);
        SetXfMode__FP3ALOP2XFi(p, p->p5C, 2);
        ActorNextLookTime(p);
        break;
    case 9:
    case 10:
    case 11:
        SetXfMode__FP3ALOP2XFi(p, p->p58, 2);
        SetXfMode__FP3ALOP2XFi(p, p->p5C, 2);
        break;
    case 2:
        if (p->x108C == 0) {
            struct VO *po = 0;
            if (k >= 0) {
                if (k < 2) {
                    po = p->p16D0;
                } else if (k == 3) {
                    switch (p->x4C8) {
                    case 1:
                        break;
                    case 3:
                    case 4:
                        po = p->p16D4;
                        break;
                    default:
                        po = p->p16D0;
                        break;
                    }
                }
            }
            if (po) {
                VCALL0(po, 8);
                ExplodeExpl__FP4EXPL(po);
                VCALL0(po, 9);
            }
        }
        SetJumpAnimState__FP4JUMPiP2LO(p->a2C0, -1, 0);
        break;
    case 3:
        SetInteractState__FP5ACTORi(p->a4C0, -1);
        break;
    case 4:
        SetDamageState__FP5ACTORi(p->aDF0, -1);
        break;
    case 13:
        SetClimbState__FP5ACTORi(p->aF50, -1);
        break;
    case 6:
        if (p->p186C) {
            VCALL1(p->p186C, 76, 1);
            ReleaseBentleyCarried__FP7BENTLEY(p);
        }
        SetBentleyHold__FP7BENTLEYi(p, -1);
        break;
    case 8:
        SetBentleyCarried__FP7BENTLEYi(p, -1);
        VCALL1(p, 79, 1);
        break;
    case 1:
    case 7:
        p->g1A0 = p->p1030->g1C / p->p1030->pasega->g74;
        break;
    case 12:
        SetJtThrowState__FP7JTTHROWi(p->a11B0, -1);
        break;
    }
    kOld = p->state;
    p->state = k;
    pasega = 0;
    pjt = 0;
    n = 1;
    anim = -1;
    c = 4;
    g = 0.0f;
    rate = 1.0f;
    p->t13D4 = g_clock.t;
    switch (k) {
    case 0:
        SetXfMode__FP3ALOP2XFi(p, p->p58, 1);
        SetXfMode__FP3ALOP2XFi(p, p->p5C, 1);
        if (p->x181C) {
            pasega = p->p1820;
            n = 9;
        } else {
            pjt = p->p1028;
            if (kOld != 2)
                anim = kOld != 7 ? 0x175 : 0x176;
            else
                anim = 0x178;
            if (IsmsFindSmOptional(pjt, anim) < 0)
                anim = -1;
        }
        p->q190 = D_002A2DD0;
        c = GrfActorLookMask__FP5ACTOR(p);
        ActorSetLookFlag__FP5ACTORi(p, 1);
        break;
    case 1:
        pasega = p->x1320.pasega;
        pa = &p->x1320;
        goto L1;
    case 7:
        pasega = p->x1600.pasega;
        pa = &p->x1600;
    L1:
        n = 9;
        g = p->g1A0 * pasega->g74;
        ResetGaitFeet__FP4GAIT(pa);
        break;
    case 4:
        SetBinocState__FP5ACTORi(p->aF00, -1);
        break;
    case 5:
        pasega = p->p14E0;
        n = 9;
        break;
    case 13:
        SetClimbState__FP5ACTORi(p->aF50, 0);
        return;
    case 6:
        SetBentleyHold__FP7BENTLEYi(p, 0);
        return;
    case 8:
        SetBentleyCarried__FP7BENTLEYi(p, 0);
        return;
    case 9:
        pjt = p->p102C;
    case 10:
    case 11:
        SetXfMode__FP3ALOP2XFi(p, p->p58, 1);
        SetXfMode__FP3ALOP2XFi(p, p->p5C, 1);
        p->q190 = D_002A2DD0;
        break;
    case 14:
        pasega = p->p1878;
        if (!pasega) {
            pasega = p->p1374;
            rate = 1.5f;
        }
        n = 9;
        break;
    case 12:
        return;
    }
    RetractAsegaPp__FPP5ASEGA(&p->p1030);
    ClearSmaHandle__FPP3SMA(&p->x1034);
    ApplyAsegCur(pasega, p, n, &p->p1030, g, rate);
    ReplaceSmaHandleMask__FP2SMi3OIDiUiPP3SMA(pjt, p, anim, n, c, &p->x1034);
    VCALL0(p, 90);
}
