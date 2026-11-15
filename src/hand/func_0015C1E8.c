/* LoadExplgFromBrx: load an explosion group: its transform, then its children; the children derived from EXPL
 * (cid 0x1E) are kept in the group's array, any other child is removed (vtable slot 8). */
#include "cid.h"
#include "vtbl.h"
typedef struct ALLOCREQ { int cb; int nKind; } ALLOCREQ;
void *PvAllocSwClearImpl__Fi(ALLOCREQ *preq);
static inline void *PvAllocSwClear(ALLOCREQ *preq, int cb, int nKind) { preq->cb = cb; preq->nKind = nKind; return PvAllocSwClearImpl__Fi(preq); }
struct STACKSCOPE { int a[4]; };
struct LO { int a[3]; VTENT *vt; int pad[6]; unsigned long grf; };
struct DA { int n0; int cMax; int c; struct LO **aplo; };   /* the loaded children */
struct EXPLG { char pad[0xE0]; int cpexpl; struct LO **apexpl; };
void __10STACKSCOPE(struct STACKSCOPE *);
void _$_10STACKSCOPE(struct STACKSCOPE *, int);
void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(struct EXPLG *pexplg, void *pbis);
void func_0013F888(struct DA *pda);
void LoadLoxChildrenFromBrx__FP3LOXP18CBinaryInputStreamPv(struct EXPLG *pexplg, void *pbis, struct DA *pda);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void LoadExplgFromBrx__FP5EXPLGP18CBinaryInputStream(struct EXPLG *pexplg, void *pbis)
{
    struct STACKSCOPE scope;
    struct DA da;
    ALLOCREQ req;
    int i;
    LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(pexplg, pbis);
    __10STACKSCOPE(&scope);
    func_0013F888(&da);
    LoadLoxChildrenFromBrx__FP3LOXP18CBinaryInputStreamPv(pexplg, pbis, &da);
    pexplg->apexpl = PvAllocSwClear(&req, da.c * 4, 0x10);
    for (i = 0; i < da.c; i++) {
        struct LO *plo = da.aplo[i];
        plo->grf |= 0x200000000000000L;   /* bit 57 */
        if (!FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_EXPL)) {
            VTENT *pvte = &plo->vt[9];
            ((void (*)())pvte->pfn)(VT_THIS(plo, pvte));
        } else {
            pexplg->apexpl[pexplg->cpexpl++] = plo;
        }
    }
    _$_10STACKSCOPE(&scope, 2);
}
