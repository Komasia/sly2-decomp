/* SetCmPosMat__FP2CMP6VECTOR: sets the camera matrix (rotation and position) and rebuilds the derived matrices
 * (UpdateCmMat4__FP2CM, Lilly: UpdateCmMat4). */
#include "cm.h"

void UpdateCmMat4__FP2CM(CM *pcm);

// name: SafeHouse port (SetCmPosMat)
void SetCmPosMat__FP2CMP6VECTOR(CM *pcm, const qword *amat)
{
    pcm->amat[0] = amat[0];
    pcm->amat[1] = amat[1];
    pcm->amat[2] = amat[2];
    pcm->amat[3] = amat[3];
    UpdateCmMat4__FP2CM(pcm);
}
