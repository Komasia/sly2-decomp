/* g++ 2.95 (no vtable thunks) virtual function table entry: the this adjustment, the virtual base index, the
 * function. A virtual call through entry e of object p is pfn((char *)p + e->delta, args...). */
#ifndef VTBL_H
#define VTBL_H

typedef struct VTENT {
    /* 0x0 */ short delta;
    /* 0x2 */ short index;
    /* 0x4 */ void *pfn;
} VTENT;

/* the object p adjusted for entry pvte (the call's this) */
#define VT_THIS(p, pvte) ((void *)((char *)(p) + (pvte)->delta))

#endif
