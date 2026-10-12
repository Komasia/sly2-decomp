typedef struct N { int x0; unsigned prev : 13; unsigned prevpg : 2; unsigned p1 : 1; unsigned next : 13; unsigned nextpg : 2; unsigned p2 : 1; } N;
extern char *D_004520C0[4];
extern N *D_002DD290, *D_002DD298, *D_002DD29C;

static inline N *Ptr(unsigned idx, unsigned pg)
{
    if (idx == 0 && pg == 0)
        return 0;
    return (N *)(D_004520C0[pg] + idx * 24);
}

void func_00255438(N *p)
{
    N *prev = Ptr(p->prev, p->prevpg);
    N *next = Ptr(p->next, p->nextpg);
    if (p == D_002DD298)
        D_002DD298 = next;
    if (prev) {
        prev->next = p->next;
        prev->nextpg = p->nextpg;
    } else if (p == D_002DD290) {
        D_002DD290 = next;
    } else if (p == D_002DD29C) {
        D_002DD29C = next;
    }
    if (next) {
        next->prev = p->prev;
        next->prevpg = p->prevpg;
    }
}
