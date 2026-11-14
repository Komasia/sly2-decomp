/* class: XFHANDLE (SafeHouse xfhandle.cpp: a script's handle to an ALO's transform record, class 0x95, 0x30 bytes
 * from the slot heap 0x3E15CC, vtable 0x2CA2C0; the same entry in 0x2CA280 / 0x2D9938): its Release (vtable entry 2) -
 * at the last reference its frame and sidebag references dropped (0x256EE0 / 0x2580A8), its reference nodes
 * (0x1334A8), and its slot freed. */
#include "slotheap.h"

typedef struct XFHANDLE {
    /* 0x00 */ void *pframe;
    /* 0x04 */ void *psidebag;
    /* 0x08 */ void *prefnodeFirst;
    /* 0x0c */ void *pvt;
    /* 0x10 */ int cref;
} XFHANDLE;

extern SLOTHEAP D_003E15CC;
void func_00256EE0(void *ppframe, void *pframe);
void func_002580A8(void *ppsidebag, void *psidebag);
void func_001334A8(XFHANDLE *pxfh);
void func_0011CD98(SLOTHEAP *pslotheap, void *pv);

void func_001F8740(XFHANDLE *pxfh)
{
    if (--pxfh->cref <= 0) {
        func_00256EE0(&pxfh->pframe, 0);
        func_002580A8(&pxfh->psidebag, 0);
        func_001334A8(pxfh);
        func_0011CD98(&D_003E15CC, pxfh);
    }
}
