#include "vtbl.h"
struct GUARD { char pad[0xC]; VTENT *pvt; };
#define VT(pguard, n, T) ((T)(pguard)->pvt[n].pfn)
/* a one-argument splice message: the argument and a pointer to it */
struct REQUEST { int nArg; int *pnArg; };
/* func_00206820 (0x206820): a guard's full reset (its method 454): vt slot 27 (0), splice message 0xF, vt slot 26
 * (0), then splice message 0xE (the start), each message with the one argument 0. */
void func_00206820(struct GUARD *pguard)
{
    struct REQUEST arg;
    register VTENT *pvt __asm__("$3");
    arg.pnArg=&arg.nArg;
    pvt=pguard->pvt;
    arg.nArg=0;
    ((void (*)(void*,int))pvt[27].pfn)(VT_THIS(pguard, &pvt[27]),0);
    VT(pguard, 3, void (*)(void *, int, int, int, int **, int))(VT_THIS(pguard, &pguard->pvt[3]), 0xF, 0, 1, &arg.pnArg, 0);
    VT(pguard, 26, void (*)(void *, int))(VT_THIS(pguard, &pguard->pvt[26]), 0);
    VT(pguard, 3, void (*)(void *, int, int, int, int **, int))(VT_THIS(pguard, &pguard->pvt[3]), 0xE, 0, 1, &arg.pnArg, 0);
}
