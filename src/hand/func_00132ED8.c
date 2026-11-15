/* The splice event form (symid object args...) of an object as a list (SafeHouse update.cpp / aijob.cpp: orig
 * 0x132ED8, evaluated by 0x133000): a pair whose car is the list (symid . (object . args)), the args list appended
 * when there is one; returned through the handle ret (the temporary handle released: the CPair freed to its slot heap
 * D_004520A8 when no reference is left). */
struct CRef { int m_tagk; void *pv; };
struct CPair;
struct SP { struct CPair *p; };   /* a CPair handle */
struct CPair { int cref; int x4; struct CRef refCar; struct SP spCdr; };   /* a list cell */
struct ARGS { int f; struct CPair *ppairArgs; };   /* the args CRef: tagk (0: the empty list), its pair */
extern char D_004520A8[];
struct CPair *PpairNew__Fv(void);
void func_00256C38(struct SP *psp, struct CPair *pn);
void func_00256C58(struct SP *psp, struct CPair *pn);
void func_00256D40(struct SP *psp, int n);
struct CRef *SetPair__4CRefP5CPair(struct CRef *pref, struct CPair *pn);
void SetSymid__4CRefUi(struct CRef *pref, int n);
void SetBasic__4CRefP5BASIC(struct CRef *pref, int n);
void Decref(struct CRef *pref) asm("Decref__4CRef");
void func_002550F8(void *pv);
void func_0011CD98(void *pool, void *pv);
struct SP *func_00132ED8(struct SP *ret, int pbasic, int symid, struct ARGS *pargs)
{
    struct SP sp;
    struct CPair *p;
    func_00256C38(&sp, PpairNew__Fv());
    {
        struct CRef *pref = &sp.p->refCar;
        SetPair__4CRefP5CPair(pref, PpairNew__Fv());
    }
    p = (struct CPair *)sp.p->refCar.pv;
    SetSymid__4CRefUi(&p->refCar, symid);
    {
        struct CPair *pn = PpairNew__Fv();
        func_00256C58(&p->spCdr, pn);
    }
    p = p->spCdr.p;
    SetBasic__4CRefP5BASIC(&p->refCar, pbasic);
    if (pargs && pargs->f)
        func_00256C58(&p->spCdr, pargs->ppairArgs);
    func_00256C38(ret, sp.p);
    {
        struct CPair *pt = sp.p;
        if (pt && --pt->cref == 0) {
            func_00256D40(&pt->spCdr, 2);
            Decref(&pt->refCar);
            func_002550F8(pt);
            func_0011CD98(D_004520A8, pt);
        }
    }
    return ret;
}
