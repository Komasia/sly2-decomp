/* PostStepLoad (0x203A38): STEP vt slot 15: the ALO post-load, its own path object (cid 0x0A oid 713), the position
 * and rotation records in mode 1, the custom entry made from the oidMesh entry (which is then turned off), and the
 * behaviour stack's post-load (0x1EEC70). */
#include "step.h"

void func_001F36A8(STEP *pstep);                    /* ALO post-load */
struct LO *func_001E94B0(int oid, int c);           /* makes a path object */
void SetXfMode__FP3ALOP2XFi(STEP *pstep, XF *pxf, int mode);
void *func_001F6030(STEP *pstep, int oid);          /* the entry with that tag */
void MakeStepCustomEntry__FP3ALOP3SOE(STEP *pstep, void *psoe);
void SetSoeOff__FP3ALOP3SOE(STEP *pstep, void *psoe);
void func_001EEC70(void *pbhvstk);

#define OID_STEP_PATH 0x2C9

void PostStepLoad__FP4STEP(STEP *pstep)
{
    func_001F36A8(pstep);
    pstep->ploPath = func_001E94B0(OID_STEP_PATH, 0x10);
    SetXfMode__FP3ALOP2XFi(pstep, pstep->po.so.pxfUnk58, 1);
    SetXfMode__FP3ALOP2XFi(pstep, pstep->po.so.pxfUnk5c, 1);
    if (pstep->oidMesh != -1) {
        pstep->psoeSource = func_001F6030(pstep, pstep->oidMesh);
        if (pstep->psoeSource) {
            MakeStepCustomEntry__FP3ALOP3SOE(pstep, pstep->psoeSource);
            SetSoeOff__FP3ALOP3SOE(pstep, pstep->psoeSource);
        }
    }
    func_001EEC70(pstep->bhvstk);
}
