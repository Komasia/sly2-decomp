#include "vtbl.h"
struct VT { VTENT a[55]; };
struct X { char pad[0xC]; struct VT *pvt; };
struct N { void *pv0; struct N *next; int *pn8; struct X *px; };
struct E { char pad[0x60]; struct X *p60; struct N *pn; void *p68; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0xEC - 0x10]; struct E *pe; };
struct G;
extern struct G g_sw;
void MarkAloDirty__FP3ALO(struct P *);
void FreeSwXpList(struct G *, void *) asm("FreeSwXpList__FP2SWP2XP");
#define VF(q, n, a) ((void (*)(void *, void *))(q)->pvt->a[n].pfn)(VT_THIS((q), &(q)->pvt->a[n]), a)
// name: SafeHouse port (DetachAloContacts)
void DetachAloContacts__FP3ALO(struct P *p)
{
    struct N *pn;
    if (!p->pe) return;
    MarkAloDirty__FP3ALO(p);
    for (pn = p->pe->pn; pn; pn = pn->next) {
        struct X *q = p->pe->p60;
        ((void (*)(void *, void *))q->pvt->a[54].pfn)(VT_THIS(q, &q->pvt->a[54]), pn->px);
        ((void (*)(void *, void *))pn->px->pvt->a[54].pfn)(VT_THIS(pn->px, &pn->px->pvt->a[54]), p->pe->p60);
        FreeSwXpList(&g_sw, pn->pv0);
        *pn->pn8 = 0;
        pn->pv0 = 0;
    }
    ((void (*)(void *, void *))p->pvt->a[54].pfn)(VT_THIS(p, &p->pvt->a[54]), 0);
    FreeSwXpList(&g_sw, p->pe->p68);
    p->pe->p68 = 0;
}
