/* The sink takes the c new objects: each out of its parent, given the sink's value (0x13F990) and, when the sink has
 * an id (+0x8), its proxy id (vt slot 25 SetIdProxy, with its children). */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; };
struct LOSINK { int f0; int nSink; int idProxy; };   /* the loaders' object sink */
void ReparentBooty__FP3ALOii(struct LO *, int, int);
void func_0013F990(struct LO *, int);
void func_0013FA30(struct LOSINK *psink, int c, struct LO **aplo) {
    int i;
    for (i = 0; i < c; i++) {
        struct LO *plo = aplo[i];
        ReparentBooty__FP3ALOii(plo, 0, 0);
        func_0013F990(plo, psink->nSink);
        if (psink->idProxy != -1) ((void (*)(void *, int, int))plo->vt[25].pfn)(VT_THIS(plo, &plo->vt[25]), psink->idProxy, 1);
    }
}
