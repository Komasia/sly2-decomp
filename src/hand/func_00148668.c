/* RunTriggerAsegList: a trigger state's animation list resolved after the load: each entry's oid becomes the ASEG
 * nearest the owner with that oid (or null), and each ASEG found is taken out of the world (vt slot 9, RemoveLo)
 * until the list runs it. Layout: SafeHouse port (trigger.cpp). */
#include "vtbl.h"
struct ASEG { char pad[0xC]; VTENT *vt; };
struct TRIGASEG { union { int oid; struct ASEG *paseg; } u; int n; };   /* the oid, once resolved the ASEG */
struct TRIGASEGLIST { int c; struct TRIGASEG a[8]; };
#define VTS_RemoveLo 9
extern char g_sw[];
struct ASEG *PloFindSwNearest__FP2LO3OIDii(void *psw, int grffso, int oid, void *ploNear);
// name: SafeHouse port (RunTriggerAsegList)
void RunTriggerAsegList__FP2LOPv(struct TRIGASEGLIST *plist, void *ploOwner)
{
    int i;
    for (i = 0; i < plist->c; i++) {
        struct ASEG *paseg = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, plist->a[i].u.oid, ploOwner);
        if (paseg) {
            VTENT *pvte;
            plist->a[i].u.paseg = paseg;
            pvte = &paseg->vt[VTS_RemoveLo];
            ((void (*)(void *))pvte->pfn)(VT_THIS(paseg, pvte));
        } else {
            plist->a[i].u.paseg = 0;
        }
    }
}
