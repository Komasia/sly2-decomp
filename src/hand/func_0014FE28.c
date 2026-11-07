/* ResetZoom__7CPRECON: CPLOOK: drops the zoom (uZoom and its speed to 0) and puts the camera FOV back to radFovZoom. */
#include "cm.h"

// name: SafeHouse port (CPRECON::ResetZoom)
void ResetZoom__7CPRECON(CPLOOK *pcplook)
{
    pcplook->uZoom = 0;
    pcplook->svuZoom = 0;
    SetCmFov__FP2CMf(&g_cm, pcplook->radFovZoom);
}
