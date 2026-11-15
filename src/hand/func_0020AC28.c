typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
/* a guard action: the rotation record it aims */
struct ACTIONOBJ { char pad[0xA0]; int pxfAim; };
struct GUARD { char pad[0xF08]; struct ACTIONOBJ *paction; int pctrlAim; int pxfTarget; char pad2[0xC]; qword posTarget; };
void DeleteCtrl__FPP4CTRL(int *ppctrl);
int PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct GUARD *pguard, int pxf, int a, int b, int c, qword vec);
/* SetGuardActionAim (0x20AC28): the guard's aimed action (+0xF08): the old one's aim controller deleted; an action
 * with a rotation record to aim (+0xA0) gets a new controller on it, aimed at posTarget in pxfTarget's frame. */
// name: SafeHouse port (SetGuardActionAim)
void SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, struct ACTIONOBJ *paction, int pxfTarget, qword posTarget)
{
    if (pguard->paction) {
        DeleteCtrl__FPP4CTRL(&pguard->pctrlAim);
        pguard->pctrlAim = 0;
        pguard->paction = 0;
    }
    pguard->paction = paction;
    if (paction && paction->pxfAim) {
        pguard->pctrlAim = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(pguard, paction->pxfAim, 5, 8, 3, D_002A2DD0);
        pguard->pxfTarget = pxfTarget;
        pguard->posTarget = posTarget;
    }
}
