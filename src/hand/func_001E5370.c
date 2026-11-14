#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x4C]; struct O *po; int n50; void *pv; };
void RetractAsega__FP5ASEGA(struct O *po);
void EndActorScriptAnim__FP5ACTOR(void *pv);
void func_001E5370(struct S *p)
{
    if (p->po) {
        RetractAsega__FP5ASEGA(p->po);
        { struct O *po = p->po; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }
        p->po = 0;
    }
    if (p->pv) {
        EndActorScriptAnim__FP5ACTOR(p->pv);
        p->pv = 0;
    }
}
