/* The world's queue of object roots to check (SafeHouse activate.h QueueLoRoot, orig 0x00147E88: SW +0x20): the root
 * taken out, then put back before the queue's insertion point SW +0x39A4. */
#include "so.h"
struct LO;
struct SW {
    /* 0x0000 */ char pad0[0x20];
    /* 0x0020 */ DL dlQueued;          /* SafeHouse port: lsplo20 */
    /* 0x002c */ char pad2c[0x39a4 - 0x2c];
    /* 0x39a4 */ void *pvQueueBefore;
};
void DequeueLoRoot__FP2SWP2LO(struct SW *psw, struct LO *plo);
void InsertDlEntryBefore__FP2DLPvT1(DL *pdl, void *pvBefore, void *pv);

void func_00147E88(struct SW *psw, struct LO *ploRoot)
{
    DequeueLoRoot__FP2SWP2LO(psw, ploRoot);
    InsertDlEntryBefore__FP2DLPvT1(&psw->dlQueued, psw->pvQueueBefore, ploRoot);
}
