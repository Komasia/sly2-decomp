/* class: CID_60, the birds (vt slot 14 = LoadFromBrx; SafeHouse bird.cpp / loaders.cpp): the SO's load, the transform
 * +0x58 put in mode 1 with its counters cleared, +0x1D4 from the +0x5C transform's kind, then its step segments bound. */
#include "so.h"
struct CBinaryInputStream;
struct BIRD {
    /* 0x000 */ SO so;
    /* 0x150 */ char pad150[0x1d4 - 0x150];
    /* 0x1d4 */ int n1D4;
};
void LoadSoFromBrx__FP2SOP18CBinaryInputStream(struct BIRD *pso, struct CBinaryInputStream *pbis);
void SetXfMode__FP3ALOP2XFi(struct BIRD *palo, XF *pxf, int mode);
void BindStepSegs__FP8STEPSEGS(struct BIRD *p);

void func_001B0CA8(struct BIRD *pbird, struct CBinaryInputStream *pbis)
{
    int *an;
    XF *pxf;
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(pbird, pbis);
    SetXfMode__FP3ALOP2XFi(pbird, pbird->so.pxfUnk58, 1);
    pxf = pbird->so.pxfUnk58;
    an = pxf->anUnkF0;
    an[2] = 0;
    an[1] = 0;
    pxf->anUnkF0[0] = 0;
    pbird->n1D4 = pbird->so.pxfUnk5c->nKindUnk98;
    BindStepSegs__FP8STEPSEGS(pbird);
}
