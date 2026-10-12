class X;
typedef void (X::*PMF)(void *);
struct D { int id; PMF pmf; };
extern "C" char D_003DD490[];
extern "C" void *func_0015E938(void *, int, int, X *);
extern "C" void func_0013E5E0(X *p, D *pd)
{
    void *pv = func_0015E938(D_003DD490, 4, pd->id, p);
    (p->*(pd->pmf))(pv);
}
