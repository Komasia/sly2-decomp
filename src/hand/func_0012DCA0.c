/* A new look-along-the-motion controller (kind 4, CTRLLOOKMOTION) with its two lead floats (+0x1C / +0x20), added
 * to the record (SafeHouse xfhandle.cpp: the script's xfh look, orig 0x12DCA0). */
typedef struct CTRLLOOKMOTION {
    int pad[7];
    float gLo;   /* field: SafeHouse port (job.gLo) */
    float gHi;   /* field: SafeHouse port (job.gHi) */
} CTRLLOOKMOTION;
#define CTRLK_LookMotion 4
CTRLLOOKMOTION *func_0012DB50(int kind, void *palo, void *pxf, void *prio, void *mode);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *palo, void *pxf, CTRLLOOKMOTION *pctrl);
CTRLLOOKMOTION *func_0012DCA0(void *palo, void *pxf, void *prio, void *mode, float gLo, float gHi)
{
    CTRLLOOKMOTION *pctrl = func_0012DB50(CTRLK_LookMotion, palo, pxf, prio, mode);
    pctrl->gLo = gLo;
    pctrl->gHi = gHi;
    AddXfCtrl__FP3ALOP2XFP4CTRL(palo, pxf, pctrl);
    return pctrl;
}
