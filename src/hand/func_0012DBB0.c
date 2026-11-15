/* PctrlNewSource: a new source controller (kind 5, mode -1: it leaves the record's mode to its source) added to
 * the record. SafeHouse port (xf.h). */
#define CTRLK_Source 5
void *func_0012DB50(int kind, void *palo, void *pxf, void *prio, int mode);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *palo, void *pxf, void *pctrl);
// name: SafeHouse port (PctrlNewSource)
void *PctrlNewSource__FP3ALOP2XFPv(void *palo, void *pxf, void *prio)
{
    void *pctrl = func_0012DB50(CTRLK_Source, palo, pxf, prio, -1);
    AddXfCtrl__FP3ALOP2XFP4CTRL(palo, pxf, pctrl);
    return pctrl;
}
