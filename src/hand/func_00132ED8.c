struct CRef { int m_tagk; void *pv; };
struct N;
struct SP { struct N *p; };
struct N { int cref; int x4; struct CRef ref; struct SP sp; };
struct X { int f; struct N *pn; };
extern char D_004520A8[];
struct N *PpairNew__Fv(void);
void func_00256C38(struct SP *psp, struct N *pn);
void func_00256C58(struct SP *psp, struct N *pn);
void func_00256D40(struct SP *psp, int n);
struct CRef *SetPair__4CRefP5CPair(struct CRef *pref, struct N *pn);
void SetSymid__4CRefUi(struct CRef *pref, int n);
void SetBasic__4CRefP5BASIC(struct CRef *pref, int n);
void Decref(struct CRef *pref) asm("Decref__4CRef");
void func_002550F8(void *pv);
void func_0011CD98(void *pool, void *pv);
struct SP *func_00132ED8(struct SP *ret, int a1, int a2, struct X *px)
{
    struct SP sp;
    struct N *p;
    func_00256C38(&sp, PpairNew__Fv());
    {
        struct CRef *pref = &sp.p->ref;
        SetPair__4CRefP5CPair(pref, PpairNew__Fv());
    }
    p = (struct N *)sp.p->ref.pv;
    SetSymid__4CRefUi(&p->ref, a2);
    {
        struct N *pn = PpairNew__Fv();
        func_00256C58(&p->sp, pn);
    }
    p = p->sp.p;
    SetBasic__4CRefP5BASIC(&p->ref, a1);
    if (px && px->f)
        func_00256C58(&p->sp, px->pn);
    func_00256C38(ret, sp.p);
    {
        struct N *pt = sp.p;
        if (pt && --pt->cref == 0) {
            func_00256D40(&pt->sp, 2);
            Decref(&pt->ref);
            func_002550F8(pt);
            func_0011CD98(D_004520A8, pt);
        }
    }
    return ret;
}
