#include "vtbl.h"
typedef struct N { char pad[0xC]; int k; struct N *next; int x14; VTENT *vt; } N;
typedef struct S { char pad[0x90]; N *first; } S;
void InvalidateXfParams__FP3ALOP2XF(void *, S *);

#define VCALL(o, k) ((void (*)(void *))(o)->vt[k].pfn)(VT_THIS((o), &(o)->vt[k]))

// name: SafeHouse port (AddXfCtrl)
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *ctx, S *s, N *n)
{
    N **pp = &s->first;
    N *head = s->first;
    N *e;
    for (e = head; e && e->k > n->k; e = e->next)
        pp = &e->next;
    n->next = *pp;
    *pp = n;
    if (s->first != head) {
        InvalidateXfParams__FP3ALOP2XF(ctx, s);
        if (head)
            VCALL(head, 2);
        VCALL(s->first, 1);
    } else if (head) {
        VCALL(head, 3);
    }
}
