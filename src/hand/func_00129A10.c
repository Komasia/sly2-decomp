#include "vtbl.h"
typedef struct CRef { int m_tagk; void *m_p; } CRef;
typedef struct O { int pad[3]; VTENT *vt; } O;
void Decref__4CRef(CRef *pref);
// name: SafeHouse port (CRef::SetBasic)
CRef *SetBasic__4CRefP5BASIC(CRef *pref, O *p)
{
    if (p)
        ((void (*)(void *))p->vt[1].pfn)(VT_THIS(p, &p->vt[1]));
    Decref__4CRef(pref);
    pref->m_p = p;
    pref->m_tagk = 0x21;
    return pref;
}
