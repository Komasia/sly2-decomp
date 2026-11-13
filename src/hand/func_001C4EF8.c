/* class: CID_5A family (cids 0x5B..0x5F, vt slot 14 = LoadFromBrx; SafeHouse loaders.cpp): the SO's load, its 0x12
 * child's +0xF0 = 1 (0x1F7B98), both transforms +0x58 / +0x5C in mode 0x15, then its parts bound (D_002C0D40). */
#include "so.h"
struct CBinaryInputStream;
struct CHILD12 {
    /* 0x00 */ char pad0[0xf0];
    /* 0xf0 */ int nF0;
};
extern char D_002C0D40[];   /* the parts' table */
void LoadSoFromBrx__FP2SOP18CBinaryInputStream(SO *pso, struct CBinaryInputStream *pbis);
struct CHILD12 *func_001F7B98(SO *pso);
void SetXfMode__FP3ALOP2XFi(SO *palo, XF *pxf, int mode);
void BindLoParts__FP3ALOiPv(SO *palo, int c, void *pv);

void func_001C4EF8(SO *pso, struct CBinaryInputStream *pbis)
{
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(pso, pbis);
    func_001F7B98(pso)->nF0 = 1;
    SetXfMode__FP3ALOP2XFi(pso, pso->pxfUnk58, 0x15);
    SetXfMode__FP3ALOP2XFi(pso, pso->pxfUnk5c, 0x15);
    BindLoParts__FP3ALOiPv(pso, 1, D_002C0D40);
}
