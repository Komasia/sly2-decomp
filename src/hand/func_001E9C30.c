/* func_001E9C30: a path's AI record (PATHREC, 0x9C bytes at +0x180), made on first use (func_001E9C88)
 * (SafeHouse ai.h / spawner.cpp). Layout: crv.h CRV, h3_rope.h PATHREC. */
#include "h3_rope.h"

struct ALLOC { int cb; int cbAlign; };
void *PvAllocSwClearImpl__Fi(struct ALLOC *palloc);
void func_001E9C88(PATHREC *ppathrec, CRV *ppath);
void func_001E9C30(CRV *ppath)
{
    struct ALLOC alloc;
    if (!ppath->ppathrec) {
        alloc.cb = sizeof(PATHREC);
        alloc.cbAlign = 0x10;
        ppath->ppathrec = PvAllocSwClearImpl__Fi(&alloc);
        func_001E9C88(ppath->ppathrec, ppath);
    }
}
