struct PMF { short delta; short pad; int (*pfn)(void *); };
struct S { int x0; int x4; struct PMF pmf; int x10; };
extern char D_002E65E0[];
extern int D_004425D8[];
void WaitSema(int);
void SignalSema(int);
void ExitDeleteThread(void);
void *s1_memset(void *, int, unsigned int);
void func_001AAF18(struct S *s)
{
    WaitSema(s->x0);
    s->x10 = s->pmf.pfn(D_002E65E0 + s->pmf.delta);
    s1_memset(&s->pmf, 0, sizeof(s->pmf));
    s->x4 = -1;
    D_004425D8[0] = -1;
    SignalSema(s->x0);
    ExitDeleteThread();
}
