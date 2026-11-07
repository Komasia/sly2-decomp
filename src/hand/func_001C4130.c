/* func_001C4130 (0x1C4130): change the PO's camera tunnel. The old one is switched off (SetZoneForced__FP2LOi(.., 0));
 * the new one is reset and switched on right away if this PO is the one in focus. */
#include "po.h"

typedef struct TN {
    /* 0x000 */ char unk_0x000[0x128];
    /* 0x128 */ int nUnk128;
} TN;

void SetZoneForced__FP2LOi(TN *ptn, int fActive);
void ReparentBooty__FP3ALOii(TN *ptn, int n0, int n1);
PO *func_001C4A48(SW *psw);

void func_001C4130(PO *ppo, TN *ptn)
{
    TN *ptnOld = (TN *)ppo->ptnCam;

    if (ptn != ptnOld) {
        if (ptnOld != NULL)
            SetZoneForced__FP2LOi(ptnOld, 0);
        ppo->ptnCam = ptn;
        if (ptn != NULL) {
            ptn->nUnk128 = -1;
            ReparentBooty__FP3ALOii((TN *)ppo->ptnCam, 0, 0);
            if (func_001C4A48(&g_sw) == ppo)
                SetZoneForced__FP2LOi((TN *)ppo->ptnCam, 1);
        }
    }
}
