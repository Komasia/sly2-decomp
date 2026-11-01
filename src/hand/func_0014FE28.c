/* func_0014FE28: CPLOOK: drops the zoom (uZoom and its speed to 0) and puts the camera FOV back to radFovZoom. */
#include "cm.h"

void func_0014FE28(CPLOOK *pcplook)
{
    pcplook->uZoom = 0;
    pcplook->svuZoom = 0;
    SetCmFov__FP2CMf(&g_cm, pcplook->radFovZoom);
}
