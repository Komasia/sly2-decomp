#include "vtbl.h"
typedef struct O { char pad[0xC]; VTENT *vt; } O;
typedef struct CRef { int m_tagk; union { int *pn; char *pb; O *po; } u; } CRef;
void Incref__4CRef(CRef *pref)
{
    switch (pref->m_tagk) {
    case 0x1B:
        (*(int *)(pref->u.pb + 0x40))++;
        break;
    case 0x1A:
    case 0x1C:
        (*(int *)(pref->u.pb + 0x10))++;
        break;
    case 0x1D:
        (*(int *)(pref->u.pb + 0x8))++;
        break;
    case 0x1E:
        (*(int *)(pref->u.pb + 0xC))++;
        break;
    case 0x21: {
        O *po = pref->u.po;
        if (po)
            ((void (*)(void *))po->vt[1].pfn)(VT_THIS(po, &po->vt[1]));
        break;
    }
    case 0x1F:
    case 0x20:
    case 0x22:
        (*pref->u.pn)++;
        break;
    }
}
