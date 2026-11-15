/* An ASEGA's message (held by a reference for the scope): its object's vt slot 5 is told (when it has one), then
 * the ASEGA's listeners (0x133508). Layout: SafeHouse port (asega.h ASEGA palo +0x18). */
#include "vtbl.h"
struct ASEGA { int pad[3]; VTENT *vt; int pad2[2]; struct ASEGA *palo; };
struct ASEGAREF { struct ASEGA *pasega; };
void func_00133508(struct ASEGA *pasega, int msgk, int n);
void func_00131738(struct ASEGA *pasega, int msgk, int n)
{
    struct ASEGAREF volatile ref;
    ref.pasega = pasega;
    ((void (*)(void *))pasega->vt[1].pfn)(VT_THIS(pasega, &pasega->vt[1]));   /* AddRef */
    if (pasega->palo)
        ((void (*)(void *, int, int))pasega->palo->vt[5].pfn)(VT_THIS(pasega->palo, &pasega->palo->vt[5]), msgk, n);
    func_00133508(pasega, msgk, n);
    { struct ASEGA *po = ref.pasega; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }   /* Release */
}
