#include "mat.h"
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x1C0]; int n1C0; char pad2[0x54]; float g218; int pad3; qword q220; };
extern "C" {
extern qword g_normalZ, D_002A2DD0;
extern char D_002BE800[], D_002BE810[];
MATRIX3 BuildRotateMatrixAxis(qword q, float g) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
void BrakeAloRotation(S *p, MATRIX3 *pm, void *pv) asm("BrakeAloRotation__FP3ALOP7MATRIX3Pf");
void AccelAloTowardPosition(S *p, qword a, int b, qword c, void *pv) asm("AccelAloTowardPosition__FP3ALOG9VU_VECTORP3CLQT1T2");
void MoveShip(S *p) asm("MoveShip__FP3ALO");
}
// name: SafeHouse port (MoveShip)
void MoveShip(S *p) {
    if (p->n1C0 == 3) return;
    MATRIX3 m; m = BuildRotateMatrixAxis(g_normalZ, p->g218);
    BrakeAloRotation(p, &m, D_002BE800);
    AccelAloTowardPosition(p, D_002A2DD0, 0, p->q220, D_002BE810);
}
