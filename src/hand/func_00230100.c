#include "vtbl.h"
typedef struct N { char pad[0x10]; struct N *next; int x14; VTENT *vt; } N;
typedef struct S { char pad[0x90]; N *first; } S;
void InvalidateXfParams__FP3ALOP2XF(void *, S *);

#define VCALL(o, k) ((void (*)(void *))(o)->vt[k].pfn)(VT_THIS((o), &(o)->vt[k]))

// name: SafeHouse port (RemoveXfCtrl)
void RemoveXfCtrl__FP3ALOP2XFP4CTRL(void *ctx, S *s, N *n)
{
    N *head = s->first;
    N **pp = &s->first;
    N *e;
    for (e = head; e; e = e->next) {
        if (e == n) {
            *pp = e->next;
            if (s->first != head) {
                InvalidateXfParams__FP3ALOP2XF(ctx, s);
                VCALL(head, 2);
                if (s->first)
                    VCALL(s->first, 1);
            } else if (head) {
                VCALL(head, 3);
            }
            return;
        }
        pp = &e->next;
    }
}
