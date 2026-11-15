/* SetBentleyHold: the mine's phase (+0x16B0: 0 the summon, 1 held, 2 falling; SafeHouse gang.h) and its animation
 * (the ASEG of the phase applied over the current one, flags 1 / 9), the velocity cleared at the summon; vt slot 90. */
#include "vtbl.h"
struct ASEG;
struct BENTLEY { int pad[3]; VTENT *vt; char pad1[0x190 - 0x10]; float vel[3]; char pad2[0x1030 - 0x19c]; void *pasega1030; int psma1034;
    char pad3[0x14e4 - 0x1038]; struct ASEG *paseg14E4; struct ASEG *paseg14E8; char pad4[0x15d4 - 0x14ec]; struct ASEG *paseg15D4;
    char pad5[0x15f0 - 0x15d8]; struct ASEG *paseg15F0; char pad6[0x16b0 - 0x15f4]; int n16B0; };
void ClearSmaHandle__FPP3SMA(void *);
void ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA(struct ASEG *, struct BENTLEY *, float, float, int, void **);
// name: SafeHouse port (SetBentleyHold)
void SetBentleyHold__FP7BENTLEYi(struct BENTLEY *pbentley, int n) {
    struct ASEG *paseg;
    int grfapl;
    if (n == pbentley->n16B0) return;
    pbentley->n16B0 = n;
    paseg = 0;
    grfapl = 1;
    switch (n) {
    case 0:
        paseg = pbentley->paseg14E4;
        {
            float *pvel = pbentley->vel;
            pvel[2] = 0.0f;
            pvel[1] = 0.0f;
            pvel[0] = 0.0f;
        }
        break;
    case 1:
        paseg = pbentley->paseg15F0;
        grfapl = 9;
        break;
    case 2:
        paseg = pbentley->paseg14E8;
        if (!paseg) paseg = pbentley->paseg15D4;
        grfapl = 9;
        break;
    }
    ClearSmaHandle__FPP3SMA(&pbentley->psma1034);
    ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA(paseg, pbentley, 0.0f, 1.0f, grfapl, &pbentley->pasega1030);
    ((void (*)(void *))pbentley->vt[90].pfn)(VT_THIS(pbentley, &pbentley->vt[90]));
}
