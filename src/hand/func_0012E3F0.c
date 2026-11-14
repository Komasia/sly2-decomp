/* An actuator added again (SafeHouse so.cpp: "the actuators' owners re-add theirs: 0x12E3F0"): a new controller of
 * the kind *pn (0x12E238), its vt slot 6 (at +0x18) run with the arguments. */
#include "vtbl.h"
struct CTRL {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ VTENT *pvt;
};
struct CTRL *func_0012E238(int kind);

struct CTRL *func_0012E3F0(int *pkind, int n1, int n2)
{
    struct CTRL *pctrl = func_0012E238(*pkind);
    VTENT *pvte = &pctrl->pvt[6];
    ((void (*)(void *, int *, int, int))pvte->pfn)(VT_THIS(pctrl, pvte), pkind, n1, n2);
    return pctrl;
}
