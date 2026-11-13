/* class: MESHZONE (cid 0x11, vt slot 7 = InitLo): the transform's init, then +0x110 -1, its list +0x118 (entries
 * linked at +0x60) and +0x124 -1. */
#include "so.h"
struct MESHZONE {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char pade0[0x110 - 0xe0];
    /* 0x110 */ int n110;
    /* 0x114 */ int pad114;
    /* 0x118 */ DL dl;
    /* 0x124 */ int n124;
};
void InitXfm__FP3XFM(struct MESHZONE *pxfm);
void InitDl__FP2DLi(DL *pdl, int ibDle);

void func_001C0378(struct MESHZONE *pzone)
{
    InitXfm__FP3XFM(pzone);
    pzone->n110 = -1;
    InitDl__FP2DLi(&pzone->dl, 0x60);
    pzone->n124 = -1;
}
