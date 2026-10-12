typedef struct N { int x0; unsigned prev : 13; unsigned prevpg : 2; unsigned p1 : 1; unsigned next : 13; unsigned nextpg : 2; unsigned p2 : 1; } N;
extern char *D_004520E8[4];
extern N *D_002DD2A0, *D_002DD2A8, *D_002DD2AC;

static inline N *Ptr(unsigned idx, unsigned pg)
{
    if (idx == 0 && pg == 0)
        return 0;
    return (N *)(D_004520E8[pg] + idx * 40);
}

void func_00255770(N *p)
{
    N *prev = Ptr(p->prev, p->prevpg);
    N *next = Ptr(p->next, p->nextpg);
    if (p == D_002DD2A8)
        D_002DD2A8 = next;
    if (prev) {
        prev->next = p->next;
        prev->nextpg = p->nextpg;
    } else if (p == D_002DD2A0) {
        D_002DD2A0 = next;
    } else if (p == D_002DD2AC) {
        D_002DD2AC = next;
    }
    if (next) {
        next->prev = p->prev;
        next->prevpg = p->prevpg;
    }
}
