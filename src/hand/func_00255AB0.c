typedef struct N { int x0; unsigned prev : 13; unsigned prevpg : 2; unsigned p1 : 1; unsigned next : 13; unsigned nextpg : 2; unsigned p2 : 1; } N;
extern char *D_00452110[4];
extern N *D_002DD2B0, *D_002DD2B8, *D_002DD2BC;

static inline N *Ptr(unsigned idx, unsigned pg)
{
    if (idx == 0 && pg == 0)
        return 0;
    return (N *)(D_00452110[pg] + idx * 28);
}

void func_00255AB0(N *p)
{
    N *prev = Ptr(p->prev, p->prevpg);
    N *next = Ptr(p->next, p->nextpg);
    if (p == D_002DD2B8)
        D_002DD2B8 = next;
    if (prev) {
        prev->next = p->next;
        prev->nextpg = p->nextpg;
    } else if (p == D_002DD2B0) {
        D_002DD2B0 = next;
    } else if (p == D_002DD2BC) {
        D_002DD2BC = next;
    }
    if (next) {
        next->prev = p->prev;
        next->prevpg = p->prevpg;
    }
}
