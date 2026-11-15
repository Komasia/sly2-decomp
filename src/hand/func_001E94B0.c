/* func_001E94B0: a new linear path object oid with cpoint points (PloNew CID_PATH, no world): an identity local
 * matrix, parameters 0, 1, ..., cpoint - 1, room for the distances and the points (SafeHouse: e.g. 0x1E94B0(713, 16),
 * the POs' path; 0x1E94B0(0x62C, c), the AI chase curve). Layout: crv.h CRV. */
#include "cid.h"
#include "crv.h"

struct ALLOC { int cb; int cbAlign; };
CRV *PloNew__F3CIDP2SW3OIDi(int cid, void *psw, int oid, int n);
void s1_memset(void *pv, int b, int cb) asm("memset");
void *PvAllocSwImpl__Fi(struct ALLOC *palloc);
CRV *func_001E94B0(int oid, int cpoint)
{
    struct ALLOC alloc;
    int i;
    CRV *pcrv = PloNew__F3CIDP2SW3OIDi(CID_PATH, 0, oid, -1);
    float (*pmat)[4];
    pcrv->crvk = CRVK_Linear;
    pcrv->fClosed = 0;
    pmat = pcrv->matLocal;
    s1_memset(pmat, 0, 0x40);
    pmat[3][3] = 1.0f; pmat[2][2] = 1.0f; pmat[1][1] = 1.0f; pmat[0][0] = 1.0f;
    alloc.cb = cpoint * 4;
    alloc.cbAlign = 0x10;
    pcrv->ag = PvAllocSwImpl__Fi(&alloc);
    for (i = 0; i < cpoint; i++) pcrv->ag[i] = i;
    alloc.cb = cpoint * 4;
    alloc.cbAlign = 0x10;
    pcrv->as = PvAllocSwImpl__Fi(&alloc);
    alloc.cb = cpoint * 16;
    alloc.cbAlign = 0x10;
    pcrv->apos = PvAllocSwImpl__Fi(&alloc);
    return pcrv;
}
