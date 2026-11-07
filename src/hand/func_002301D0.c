/* (Claude agent, lane E13) Matched. c is reused as the insertion index (for (c--; ...)), and the sorted insert is
   an if + do-while instead of a for loop. */
typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct N { char pad[0xC]; int k; struct N *next; int x14; VT *vt; } N;
typedef struct S { char pad[0x90]; N *first; } S;
void InvalidateXfParams__FP3ALOP2XF(void *, S *);

#define VCALL(o, k) ((void (*)(void *))(o)->vt[k].pfn)((char *)(o) + (o)->vt[k].d)

// name: SafeHouse port (SortXfCtrls)
void SortXfCtrls__FP3ALOP2XF(void *ctx, S *s)
{
    N *a[16];
    int c = 0;
    N *e;
    N *head;
    {
        N *ee;
        for (ee = s->first; ee; ee = ee->next)
            a[c++] = ee;
    }
    head = s->first;
    s->first = 0;
    for (c--; c >= 0; c--) {
        N *n = a[c];
        N **pp = &s->first;
        e = s->first;
        if (e && e->k > n->k) {
            do {
                pp = &e->next;
                e = e->next;
            } while (e && e->k > n->k);
        }
        n->next = *pp;
        *pp = n;
    }
    if (s->first != head) {
        InvalidateXfParams__FP3ALOP2XF(ctx, s);
        if (head)
            VCALL(head, 2);
        if (s->first)
            VCALL(s->first, 1);
    } else if (head) {
        VCALL(head, 3);
    }
}
