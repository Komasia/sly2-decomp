/* AkeyFromList: the integer / symbol elements of a list as an array of 16-bit keys (stack-allocated), the
 * path of a progress value. */
#include "splice.h"
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct NODE { int pad[2]; CRef ref; struct NODE *pnext; } NODE;
typedef struct ARR { int c; short *a; } ARR;
short *PvAllocStackImpl__Fi(AREQ *preq);
// name: SafeHouse port (AkeyFromList)
void AkeyFromList__FP4CRefP3ARR(NODE *pnode, ARR *parr)
{
    NODE *p;
    int i;
    parr->c = 0;
    parr->a = 0;
    for (p = pnode; p; p = p->pnext)
        parr->c++;
    if (parr->c) {
        AREQ req;
        req.cb = parr->c * 2;
        req.cbAlign = 0x10;
        parr->a = PvAllocStackImpl__Fi(&req);
        for (p = pnode, i = 0; p; p = p->pnext, i++) {
            if (p->ref.m_tagk == TAGK_S32 || p->ref.m_tagk == TAGK_Symid)
                { int n = p->ref.m_tag.m_n; parr->a[i] = n; }
        }
    }
}
