#include "mat.h"
struct LO { char pad[0x154]; int x154; };
struct S {
    int a[4]; float g10, g14, g18, g1c, g20, g24, g28, g2c; int n30; int pad34[3];
    struct MATRIX3 mat;
    float g70, g74; int pad78; struct LO *x7C; int x80;
};
struct J { char pad[0x103C]; float a, b; char p1[0x1070 - 0x1044]; float c, d; char p2[0x10B4 - 0x1078]; int x10B4; int p3; int x10BC; };
extern int g_grfjoyt;
extern struct J g_joy;
extern struct J D_002E0D00;
extern char D_002DDFA0[];
void ClearPadctl__FP6PADCTL(struct S *p);
void DecomposeRotateMatrixPanTilt(void *pv, float *pa, float *pb) asm("DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1");
struct MATRIX3 BuildPanTiltMatrix__FPvff(float a, float b);
void TurnPadctlStick__FPffN50(struct S *p, float g, float *px, float *py, float *pang, float *pr, float *pr2);
void StampPadctlState__FP6PADCTL(struct S *p);
// name: SafeHouse port (UpdatePadctl)
void UpdatePadctl__FP6PADCTL(struct S *p)
{
    float a, b;
    struct J *pj;
    b = 0.0f;
    a = 0.0f;
    switch (p->x80) {
    case 0:
        ClearPadctl__FP6PADCTL(p);
        break;
    case 1:
        pj = (g_grfjoyt & 2) ? &g_joy : &D_002E0D00;
        p->g10 = pj->a;
        p->g14 = pj->b;
        p->g20 = pj->c;
        p->g24 = pj->d;
        p->n30 = (pj->x10B4 & ~pj->x10BC) | p->x7C->x154;
        DecomposeRotateMatrixPanTilt(D_002DDFA0, &a, &b);
        break;
    }
    p->mat = BuildPanTiltMatrix__FPvff(a, b);
    TurnPadctlStick__FPffN50(p, a, &p->g10, &p->g14, &p->g18, &p->g1c, &p->g70);
    TurnPadctlStick__FPffN50(p, a, &p->g20, &p->g24, &p->g28, &p->g2c, &p->g74);
    StampPadctlState__FP6PADCTL(p);
}
