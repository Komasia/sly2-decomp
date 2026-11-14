/* func_00116B30 (0x116B30): g++ static initialisation of its translation unit (__static_initialization_and_destruction_0,
 * called by the unit's global-constructor entry 0x116C80 with __initialize_p = 1, __priority = 0xFFFF): the world
 * heap g_heapSw (vtable 0x2CA578, kind -1: see 0x116A58) and the CStructTypeFactory<T>::s_slotheap slot heaps, each
 * guarded by its g++ sentry counter (the same six as 0x128A00). */
#include "slotheap.h"
#include "so.h"

typedef struct HEAPSW {
    /* 0x0 */ VTE *pvt;
    /* 0x4 */ int nKind;
} HEAPSW;

extern HEAPSW g_heapSw;
extern VTE D_002CA578[];   /* g_heapSw's vtable */
extern int D_002DD2E0;
extern int D_002DD2E4;
extern int D_002DD2E8;
extern int D_002DD2EC;
extern int D_002DD2F0;
extern int D_002DD2F4;
extern SLOTHEAP D_004520A8;
extern SLOTHEAP D_004520D0;
extern SLOTHEAP D_004520F8;
extern SLOTHEAP D_00452120;
extern SLOTHEAP D_00452148;
extern SLOTHEAP D_00452170;

void func_00116B30(int fInitialize, int nPriority)
{
    if (nPriority == 0xFFFF && fInitialize) {
        g_heapSw.pvt = D_002CA578;
        g_heapSw.nKind = -1;
        if (++D_002DD2E0 == 1)
            func_0011CCA8(&D_004520A8, 0x14, 0x2000, 0x10);
        if (++D_002DD2E4 == 1)
            func_0011CCA8(&D_004520D0, 0x18, 0x800, 0x10);
        if (++D_002DD2E8 == 1)
            func_0011CCA8(&D_004520F8, 0x28, 0x200, 0x10);
        if (++D_002DD2EC == 1)
            func_0011CCA8(&D_00452120, 0x1C, 0x800, 0x10);
        if (++D_002DD2F0 == 1)
            func_0011CCA8(&D_00452148, 0xC, 0xC8, 0x10);
        if (++D_002DD2F4 == 1)
            func_0011CCA8(&D_00452170, 0x14, 0x100, 0x10);
    }
}
