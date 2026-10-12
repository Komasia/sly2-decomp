typedef struct N { int x0; unsigned prev : 13; unsigned prevpg : 2; unsigned p1 : 1; unsigned next : 13; unsigned nextpg : 2; unsigned p2 : 1; } N;
extern char *D_00452160[4];
extern N *D_002DD2D0, *D_002DD2D8, *D_002DD2DC;

static inline N *Ptr(unsigned idx, unsigned pg)
{
    if (idx == 0 && pg == 0)
        return 0;
    return (N *)(D_00452160[pg] + idx * 20);
}

void func_00256120(N *p)
{
    N *prev = Ptr(p->prev, p->prevpg);
    N *next = Ptr(p->next, p->nextpg);
    if (p == D_002DD2D8)
        D_002DD2D8 = next;
    if (prev) {
        prev->next = p->next;
        prev->nextpg = p->nextpg;
    } else if (p == D_002DD2D0) {
        D_002DD2D0 = next;
    } else if (p == D_002DD2DC) {
        D_002DD2DC = next;
    }
    if (next) {
        next->prev = p->prev;
        next->prevpg = p->prevpg;
    }
}
