// An object-reference option with a setter: the object oid nearest to plo passed to the option's member function.
class X;
typedef void (X::*PMF)(void *);
struct D { int oid; PMF pmf; };   // an object option with a setter (a pointer to member)
extern "C" char g_sw[];
extern "C" void *PloFindSwNearest(void *, int, int, X *) asm("PloFindSwNearest__FP2LO3OIDii");
extern "C" void func_0013E5E0(X *plo, D *popt)
{
    void *pv = PloFindSwNearest(g_sw, 4, popt->oid, plo);
    (plo->*(popt->pmf))(pv);
}
