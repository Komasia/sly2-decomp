/* NotifyLo (vt slot 4, SafeHouse update.cpp / activate.cpp): the message msgk goes to the object's own slot 5, then
 * to each listener's slot 5. */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; };
struct LISTENER { struct LO *plo; int c; struct LISTENER *pnext; };   /* field: SafeHouse port (id = the listening object) */
struct BASIC { int pframe; int psidebag; struct LISTENER *plistenerFirst; VTENT *vt; };
void func_00133508(struct BASIC *pbasic, int msgk, void *pv) {
    struct LISTENER *plistener;
    ((void (*)(void *, int, void *))pbasic->vt[5].pfn)(VT_THIS(pbasic, &pbasic->vt[5]), msgk, pv);
    for (plistener = pbasic->plistenerFirst; plistener; ) {
        struct LO *ploListener = plistener->plo;
        plistener = plistener->pnext;
        ((void (*)(void *, int, void *))ploListener->vt[5].pfn)(VT_THIS(ploListener, &ploListener->vt[5]), msgk, pv);
    }
}
