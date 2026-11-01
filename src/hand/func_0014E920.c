/* func_0014E920: resets the camera's adjustment / focus offsets: dposAdjust from func_0014E698, vAdjust and
 * vFocus zeroed. */
#include "cm.h"

qword func_0014E698(void);

void func_0014E920(CM *pcm)
{
    float *pvAdjust;
    float *pvFocus;

    pcm->dposAdjust = func_0014E698();
    pvFocus = pcm->vFocus;
    pvAdjust = pcm->vAdjust;
    pvAdjust[2] = 0;
    pvAdjust[1] = 0;
    pcm->vAdjust[0] = 0;
    pvFocus[2] = 0;
    pvFocus[1] = 0;
    pcm->vFocus[0] = 0;
}
