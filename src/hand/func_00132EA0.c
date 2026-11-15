/* class: BASIC (so.h; cls.h): the object's class id - its descriptor from virtual slot 5 (vtable entry 6), then
 * CLS::cid. */
#include "so.h"
#include "cls.h"

int func_00132EA0(BASIC *pbasic)
{
    VTENT *pvt = pbasic->pvt;
    CLS *pcls = ((CLS *(*)(void *))pvt[6].pfn)(VT_THIS(pbasic, &pvt[6]));
    return pcls->cid;
}
