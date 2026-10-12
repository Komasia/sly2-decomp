struct PMF { short delta; short pad; int (*pfn)(void *); };
struct S { int x0; int x4; struct PMF pmf; int x10; };
extern char D_002E65E0[];
extern int D_004425D8[];
void func_00234A60(int);
void func_00234A40(int);
void func_00234860(void);
void *func_002333B4(void *, int, unsigned int);
void func_001AAF18(struct S *s)
{
    func_00234A60(s->x0);
    s->x10 = s->pmf.pfn(D_002E65E0 + s->pmf.delta);
    func_002333B4(&s->pmf, 0, sizeof(s->pmf));
    s->x4 = -1;
    D_004425D8[0] = -1;
    func_00234A40(s->x0);
    func_00234860();
}
