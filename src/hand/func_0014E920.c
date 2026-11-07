/* ResetCmAdjust__FP2CM: resets the camera's adjustment / focus offsets: dposAdjust from CalcCmAdjust__FP2CMP6CPDEFI, vAdjust and
 * vFocus zeroed. */
#include "cm.h"

qword CalcCmAdjust__FP2CMP6CPDEFI(void);

// name: SafeHouse port (ResetCmAdjust)
void ResetCmAdjust__FP2CM(CM *pcm)
{
    float *pvAdjust;
    float *pvFocus;

    pcm->dposAdjust = CalcCmAdjust__FP2CMP6CPDEFI();
    pvFocus = pcm->vFocus;
    pvAdjust = pcm->vAdjust;
    pvAdjust[2] = 0;
    pvAdjust[1] = 0;
    pcm->vAdjust[0] = 0;
    pvFocus[2] = 0;
    pvFocus[1] = 0;
    pcm->vFocus[0] = 0;
}
