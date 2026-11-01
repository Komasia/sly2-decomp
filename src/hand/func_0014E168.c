/* func_0014E168: sets the camera matrix (rotation and position) and rebuilds the derived matrices
 * (func_0014DC58, Lilly: UpdateCmMat4). */
#include "cm.h"

void func_0014DC58(CM *pcm);

void func_0014E168(CM *pcm, const qword *amat)
{
    pcm->amat[0] = amat[0];
    pcm->amat[1] = amat[1];
    pcm->amat[2] = amat[2];
    pcm->amat[3] = amat[3];
    func_0014DC58(pcm);
}
