class X;
typedef void (X::*PMF)(void *);
struct D { int id; PMF pmf; };
extern "C" char g_sw[];
extern "C" void *PloFindSwNearest(void *, int, int, X *) asm("PloFindSwNearest__FP2LO3OIDii");
extern "C" void func_0013E5E0(X *p, D *pd)
{
    void *pv = PloFindSwNearest(g_sw, 4, pd->id, p);
    (p->*(pd->pmf))(pv);
}
