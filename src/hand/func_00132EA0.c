/* class: BASIC (so.h; cls.h): the object's class id - its descriptor from virtual slot 5 (vtable entry 6), then
 * CLS::cid. */
#include "so.h"
#include "cls.h"

int func_00132EA0(BASIC *pbasic)
{
    VTE *pvt = pbasic->pvt;
    CLS *pcls = ((CLS *(*)(void *))pvt[6].pfn)((char *)pbasic + pvt[6].d);
    return pcls->cid;
}
