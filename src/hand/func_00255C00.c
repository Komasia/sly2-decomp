typedef struct N { int x0; unsigned prev : 13; unsigned prevpg : 2; unsigned p1 : 1; unsigned next : 13; unsigned nextpg : 2; unsigned p2 : 1; char pad[0xC - 8]; } N;
extern N *D_00452138[4];
extern unsigned int D_002DD2C4;

static inline void Handle(N *p, int *pidx, int *ppg)
{
    unsigned int i;
    for (i = 0; i < D_002DD2C4; i++) {
        if (p >= D_00452138[i] && p < D_00452138[i] + 0xC8) {
            *pidx = p - D_00452138[i];
            *ppg = i;
            return;
        }
    }
    *pidx = 0;
    *ppg = 0;
}

void func_00255C00(N *p, N **phead)
{
    int idx0, pg0, idx1, pg1;
    N *head;
    Handle(p, &idx0, &pg0);
    head = *phead;
    if (head) {
        head->prev = idx0;
        head->prevpg = pg0;
    }
    Handle(*phead, &idx1, &pg1);
    p->next = idx1;
    p->nextpg = pg1;
    *phead = p;
}
