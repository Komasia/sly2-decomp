/* Initializes a constraint system for at most cdzMax rows: the rows (0x28 bytes each, cleared), the four row
 * lists and the solver's matrices / vectors, all on the stack heap. */
#include "dzg.h"
typedef struct MSG { int cb; int nKind; } MSG;

void *PvAllocStackClearImpl__Fi(MSG *pmsg);
void *PvAllocStackImpl__Fi(MSG *pmsg);
void *s1_memset(void *pv, int b, unsigned int cb) asm("memset");
void InitDl__FP2DLi(DL *pdl, int ibDle);

// name: SafeHouse port (InitDzgRows)
DZG *InitDzgRows__FP3DZGi(DZG *pdzg, int cdzMax)
{
    MSG msg;

    pdzg->cdzMax = cdzMax;
    pdzg->cdzClamped = 0;
    pdzg->cdz = 0;
    msg.cb = cdzMax * sizeof(DZ);
    msg.nKind = 0x10;
    pdzg->adz = (DZ *)PvAllocStackClearImpl__Fi(&msg);
    s1_memset(&pdzg->dlClamped, 0, sizeof(DL));
    s1_memset(&pdzg->dlLower, 0, sizeof(DL));
    s1_memset(&pdzg->dlUpper, 0, sizeof(DL));
    s1_memset(&pdzg->dlOpen, 0, sizeof(DL));
    InitDl__FP2DLi(&pdzg->dlClamped, IB_DZ_DLE);
    InitDl__FP2DLi(&pdzg->dlLower, IB_DZ_DLE);
    InitDl__FP2DLi(&pdzg->dlUpper, IB_DZ_DLE);
    InitDl__FP2DLi(&pdzg->dlOpen, IB_DZ_DLE);
    msg.cb = cdzMax * cdzMax * sizeof(float);
    msg.nKind = 0x10;
    pdzg->agA = (float *)PvAllocStackImpl__Fi(&msg);
    msg.cb = cdzMax * cdzMax * sizeof(float);
    msg.nKind = 0x10;
    pdzg->agLu = (float *)PvAllocStackImpl__Fi(&msg);
    msg.cb = cdzMax * sizeof(float);
    msg.nKind = 0x10;
    pdzg->agB = (float *)PvAllocStackImpl__Fi(&msg);
    msg.cb = cdzMax * sizeof(float);
    msg.nKind = 0x10;
    pdzg->agX = (float *)PvAllocStackImpl__Fi(&msg);
    return pdzg;
}
