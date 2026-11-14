typedef int qword __attribute__((mode(TI)));
struct P8 { int a, b; };
struct W { char pad[0x1000]; int x1000; };
struct O { char pad[0xE0]; int xE0; };
struct S {
    struct W *x0; int x4; float x8; char p0[0x1C - 0xC]; float x1C;
    char p1[0x30 - 0x20]; void *x30; int x34; void *x38;
    char p2[0x80 - 0x3C]; int x80; struct O *x84; int x88; struct O *x8C; int x90;
    int x94; int x98; int x9C; int xA0; int xA4; float xA8;
};
#include "clock.h"
extern struct P8 D_002A77C8;
extern char g_sw[];
void DeleteCtrl__FPP4CTRL(int *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *p, int n);
qword PosOfLo__FP2LO(struct W *p);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct O *p, qword q, int a, int b, int c, int d, int *pn);
struct O *PloReachGrip__FP5ACTORi(struct W *pw, struct O *po);
qword VecXfValue__FP2XFP7MATRIX4(void *a, void *b);
int PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct W *p, void *q, int a, int b, int c, qword d);
void RecalcBlend__FP6ASEGBL(void *p);
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(void *pg, struct W *pw, struct P8 p8, struct S *p);
// name: SafeHouse port (SetReachState)
void SetReachState__FP5REACHi(struct S *p, int n)
{
    if (n == p->xA4) return;
    if (p->xA4 == 1) {
        DeleteCtrl__FPP4CTRL(&p->x94);
        DeleteCtrl__FPP4CTRL(&p->x9C);
    }
    p->xA4 = n;
    p->xA8 = g_clock.t;
    switch (n) {
    case 0:
    case 1:
        p->x8C = p->x84;
        p->x90 = 1;
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x84, 10)) {
            struct O *po = p->x84;
            NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(po, PosOfLo__FP2LO(p->x0), 0, 0, 0, 0, &p->x88);
            p->x90 = 0;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x84, 0x14) && (p->x84->xE0 & p->x0->x1000)) {
            p->x90 = 2;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x84, 0x30)) {
            struct O *po = PloReachGrip__FP5ACTORi(p->x0, p->x84);
            if (po) {
                p->x8C = po;
                p->x90 = 2;
            }
        }
        if (p->x90 == 2)
            p->x80 = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p->x0, p->x38, 5, 7, 3, VecXfValue__FP2XFP7MATRIX4(p->x38, p->x38));
        p->x1C = p->x8 = 0.5f;
        RecalcBlend__FP6ASEGBL(p->x30);
        PostDeferredCall__FPvUi15PFNDEFERREDCALLi(g_sw, p->x0, D_002A77C8, p);
        break;
    case -1:
        DeleteCtrl__FPP4CTRL(&p->x80);
        p->x90 = n;
        p->x84 = 0;
        p->x88 = 0;
        p->x8C = 0;
        break;
    }
}
