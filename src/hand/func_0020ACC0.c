typedef int qword __attribute__((mode(TI)));
typedef struct MATRIX3 { qword a[3]; } MATRIX3;
struct XFAIM { char pad[0x30]; qword pos; char pad2[0x60]; int pxfAim; };   /* the aimed record's object */
struct ACTIONOBJ { char pad[0x90]; qword dirAim; struct XFAIM *pxfaim; };
struct CTRLAIM { char pad[0x20]; qword eulGoal; };   /* the aim controller: its goal rotation */
struct GUARD { char pad[0xF08]; struct ACTIONOBJ *paction; struct CTRLAIM *pctrlAim; int pxfTarget; char pad2[0xC]; qword posTarget; };
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int pxfFrom, int pxfTo, qword pos);
void BuildRotateVectorsMatrix__FP7MATRIX3G9VU_VECTORT1(MATRIX3 *pmat, qword vecFrom, qword vecTo);
qword DecomposeEulerMatrix__FP7MATRIX3(MATRIX3 *pmat);
/* UpdateGuardActionAim (0x20ACC0): each frame of an aimed action: the target point in the aimed record's frame, the
 * rotation from the action's aim direction to it, as Euler angles into the aim controller's goal. */
// name: SafeHouse port (UpdateGuardActionAim)
void UpdateGuardActionAim__FP5GUARD(struct GUARD *pguard)
{
    MATRIX3 mat;
    qword posTarget, dir;
    posTarget = PosConvertXfs__FP2XFT0G9VU_VECTOR(pguard->pxfTarget, pguard->paction->pxfaim->pxfAim, pguard->posTarget);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(dir) : "j"(posTarget), "j"(pguard->paction->pxfaim->pos));
    BuildRotateVectorsMatrix__FP7MATRIX3G9VU_VECTORT1(&mat, pguard->paction->dirAim, dir);
    { struct CTRLAIM *pctrlAim = pguard->pctrlAim; pctrlAim->eulGoal = DecomposeEulerMatrix__FP7MATRIX3(&mat); }
}
