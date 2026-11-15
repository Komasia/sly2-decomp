/* HandleLoSpliceEvent (SafeHouse update.cpp, orig 0x1331F8): when the object's splice frame binds the event symid,
 * its arguments (carg values at apv, typed by the event's OTYP list D_0027A10C[D_0027A1D8[symid]]) become a list,
 * the form (symid object args...) is built (0x132ED8) and either queued as a deferred call at the clock's time
 * (0x133040) or evaluated now (0x133000, the result into prefResult). */
struct CRef { int m_tagk; void *pv; };
struct CPair;
struct SP { struct CPair *p; };   /* a CPair handle */
struct CPair { int cref; int x4; struct CRef refCar; struct SP spCdr; };   /* a list cell */
struct LO { void *pframe; };   /* LO +0x0: its splice frame */
#include "clock.h"
extern char g_sw[];
extern char D_004520A8[];
extern int D_0027A1D8[];
extern int D_0027A10C[];
int PrefFindBinding(void *pframe, int symid, int n) asm("PrefFindBinding__6CFrameUii");
struct CRef *RefSetArgListFromPvs__FiP4OTYPPPv(struct CRef *ret, int carg, int *aotyp, int apv);
struct SP *func_00132ED8(struct SP *ret, struct LO *plo, int symid, struct CRef *pref);
void func_00133040(void *pg, struct LO *plo, struct CPair *pn, float t);
void func_00133000(struct LO *plo, struct CPair *ppairForm, void *pframe, int prefResult);
void func_00256D40(struct SP *psp, int n);
void Decref(struct CRef *pref) asm("Decref__4CRef");
void func_002550F8(void *pv);
void func_0011CD98(void *pool, void *pv);
void func_001331F8(struct LO *plo, int symid, int fDeferred, int carg, int apv, int prefResult)
{
    if (plo->pframe && PrefFindBinding(plo->pframe, symid, 1)) {
        struct CRef ref;
        struct SP sp;
        RefSetArgListFromPvs__FiP4OTYPPPv(&ref, carg, &D_0027A10C[D_0027A1D8[symid]], apv);
        func_00132ED8(&sp, plo, symid, &ref);
        if (fDeferred)
            func_00133040(g_sw, plo, sp.p, g_clock.t);
        else
            func_00133000(plo, sp.p, plo->pframe, prefResult);
        {
            struct CPair *pt = sp.p;
            if (pt && --pt->cref == 0) {
                func_00256D40(&pt->spCdr, 2);
                Decref(&pt->refCar);
                func_002550F8(pt);
                func_0011CD98(D_004520A8, pt);
            }
        }
        Decref(&ref);
    }
}
