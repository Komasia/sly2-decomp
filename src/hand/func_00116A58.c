/* class: the world heap g_heapSw (a HEAP: vtable 0x2CA578 = {PvAlloc 0x116A30, PvRealloc 0x116A58, Free 0x116A90},
 * set up by the unit's static initialiser 0x116B30): its PvRealloc (vtable slot 2) - a fresh allocation through
 * its own PvAlloc (slot 1), with the heap's fixed kind unless that is -1 (then the caller's). The old block is
 * not copied or freed. */
#include "so.h"

typedef struct HEAPSW {
    /* 0x0 */ VTE *pvt;
    /* 0x4 */ int nKind;   /* -1: use the caller's */
} HEAPSW;

void *func_00116A58(HEAPSW *pheap, void *pv, int cb, int nKind)
{
    VTE *pvt = pheap->pvt;
    int nKindHeap = pheap->nKind;

    return ((void *(*)(void *, int, int))pvt[1].pfn)((char *)pheap + pvt[1].d, cb,
                                                     (nKindHeap == -1) ? nKind : nKindHeap);
}
