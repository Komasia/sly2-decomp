/* UpdateTask: a task's update: an available task with a time limit checks it (func_00165118: message 0x17); its shown
 * object is present (vtable entry 8, AddLo) while it is available and no job is current, else removed (entry 9). */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; };
struct TASK { char pad[0x54]; int nState; float tState; char pad2[0x78 - 0x5C]; float dtLimit; char pad3[4]; struct LO *ploShown; };
#include "clock.h"
extern int D_003E0F9C;   /* the current job */
void UpdateLo__FP2LO(struct TASK *ptask);
void func_00165118(struct TASK *ptask, int n);
// name: SafeHouse port (UpdateTask)
void UpdateTask__FP2LO(struct TASK *ptask)
{
    struct LO *ploShown;
    UpdateLo__FP2LO(ptask);
    if (ptask->nState == 1 && ptask->dtLimit > 0.0f) {
        float dt = g_clock.t - ptask->tState;
        if (dt < ptask->dtLimit && ptask->dtLimit + g_clock.dt <= dt)
            func_00165118(ptask, 0);
    }
    ploShown = ptask->ploShown;
    if (ploShown) {
        int fShow = ptask->nState == 1; if (D_003E0F9C) fShow = 0;
        if (fShow) {
            VTENT *pvte = &ploShown->vt[8];
            ((void (*)(void *))pvte->pfn)(VT_THIS(ploShown, pvte));
        } else {
            VTENT *pvte = &ploShown->vt[9];
            ((void (*)(void *))pvte->pfn)(VT_THIS(ploShown, pvte));
        }
    }
}
