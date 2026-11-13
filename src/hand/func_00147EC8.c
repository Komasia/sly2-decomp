/* The world's queue of object roots to check (SafeHouse activate.cpp / activate.h QueueLoRoot 0x147E88: SW +0x20):
 * an object taken out of it. */
#include "so.h"
struct SW {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ DL dlQueued;   /* SafeHouse port: lsplo20 */
};
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);

void func_00147EC8(struct SW *psw, void *plo)
{
    RemoveDlEntry__FP2DLPv(&psw->dlQueued, plo);
}
