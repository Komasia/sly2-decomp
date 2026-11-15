/* PloCloneLo: a new object of plo's class (vt slot 6: its descriptor) with its oid under paloParent, made a copy of plo
 * (vt slot 40). SafeHouse port. */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; int pad2[2]; int oid; };
struct CLS { int pclsSuper; int cid; };   /* cls.h */
struct LO *PloNew__F3CIDP2SW3OIDi(int, int, int, int);
// name: SafeHouse port (PloCloneLo)
struct LO *PloCloneLo__FP2LOi(struct LO *plo, int paloParent) {
    struct CLS *pcls;
    struct LO *ploNew;
    if (!plo) return 0;
    pcls = (struct CLS *)((void *(*)(void *))plo->vt[6].pfn)(VT_THIS(plo, &plo->vt[6]));
    ploNew = PloNew__F3CIDP2SW3OIDi(pcls->cid, paloParent, plo->oid, -1);
    ((void (*)(void *, struct LO *))ploNew->vt[40].pfn)(VT_THIS(ploNew, &ploNew->vt[40]), plo);
    return ploNew;
}
