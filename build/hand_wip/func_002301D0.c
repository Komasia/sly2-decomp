typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct N { char pad[0xC]; int k; struct N *next; int x14; VT *vt; } N;
typedef struct S { char pad[0x90]; N *first; } S;
void func_0022C840(void *, S *);

#define VCALL(o, k) ((void (*)(void *))(o)->vt[k].pfn)((char *)(o) + (o)->vt[k].d)

static inline void Insert(S *s, N *n)
{
    N **pp = &s->first;
    N *e;
    for (e = s->first; e && e->k > n->k; e = e->next)
        pp = &e->next;
    n->next = *pp;
    *pp = n;
}

void func_002301D0(void *ctx, S *s)
{
    N *a[16];
    int c = 0;
    N *e;
    N *head;
    for (e = s->first; e; e = e->next)
        a[c++] = e;
    head = s->first;
    s->first = 0;
    {
        int i;
        for (i = c - 1; i >= 0; i--)
            Insert(s, a[i]);
    }
    if (s->first != head) {
        func_0022C840(ctx, s);
        if (head)
            VCALL(head, 2);
        if (s->first)
            VCALL(s->first, 1);
    } else if (head) {
        VCALL(head, 3);
    }
}
