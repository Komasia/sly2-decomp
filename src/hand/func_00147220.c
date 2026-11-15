/* PostLoadAnimatedOverlay: the overlay's post-load: the base post-load (0x1F36A8), its two display parts bound (the
 * parts table D_002BD380), no state (-1), and the overlay taken out of the world (vt slot 9, RemoveLo) until it is
 * started. Layout: SafeHouse port (overlay.cpp). */
#include "vtbl.h"
struct OVERLAY {
    /* 0x000 */ char pad[0xC];
    /* 0x00c */ VTENT *vt;
    /* 0x010 */ char pad2[0x150 - 0x10];
    /* 0x150 */ int state;   /* field: SafeHouse port */
};
#define VTS_RemoveLo 9
extern char D_002BD380[];   /* the overlay's parts table (two display parts) */
void func_001F36A8(struct OVERLAY *poverlay);   /* the base (ALO) post-load */
void BindLoParts__FP3ALOiPv(struct OVERLAY *poverlay, int cpart, void *apart);
// name: SafeHouse port (PostLoadAnimatedOverlay)
void PostLoadAnimatedOverlay__FP2LO(struct OVERLAY *poverlay)
{
    VTENT *pvte;
    func_001F36A8(poverlay);
    BindLoParts__FP3ALOiPv(poverlay, 2, D_002BD380);
    pvte = &poverlay->vt[VTS_RemoveLo];
    poverlay->state = -1;
    ((void (*)(void *))pvte->pfn)(VT_THIS(poverlay, pvte));
}
