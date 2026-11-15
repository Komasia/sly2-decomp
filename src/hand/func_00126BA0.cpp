/* RefEvalCase: (case key (datums body...) ... [(else body...)]) - evaluates the body of the first clause
 * with a datum eqv? to key; void when none matches. */
#include "splice_tagk.h"
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct NODE { int x0, x4; CRef ref; NODE *pnext; };
struct P { char pad[0xC]; struct { char pad[0x10]; NODE *pargs; } *pv; };
extern "C" {
CRef RefEval(NODE *p, void *penv) asm("RefEval__FP5CPairP6CFrame");
CRef RefOpEqv(int carg, CRef *aref, void *penv) asm("RefOpEqv__FiP4CRefP6CFrame");
CRef RefEvalCase(P *p, void *penv) asm("RefEvalCase__FP5CPairP6CFrame");
}
// name: SafeHouse port (RefEvalCase)
CRef RefEvalCase(P *p, void *penv)
{
    CRef ref;
    CRef arefT[2];
    CRef test;
    NODE *pkey;
    NODE *pcl;
    ref.Decref();
    ref.InitTag(TAGK_Void);
    pkey = p->pv->pargs;
    arefT[0] = RefEval(pkey, penv);
    pcl = pkey->pnext;
    while (pcl) {
        NODE *pc = (NODE *)pcl->ref.u.pv;
        int f;
        if (pc->ref.m_tagk == TAGK_Else) {
            f = 1;
        } else {
            NODE *pk;
            f = 0;
            pk = (NODE *)pc->ref.u.pv;
            while (pk) {
                arefT[1] = pk->ref;
                test = RefOpEqv(2, arefT, penv);
                if (test.m_tagk == TAGK_Bool && test.u.n) {
                    f = 1;
                    pk = 0;
                } else {
                    pk = pk->pnext;
                }
            }
        }
        if (f) {
            for (pc = pc->pnext; pc; pc = pc->pnext)
                ref = RefEval(pc, penv);
            pcl = 0;
        } else {
            pcl = pcl->pnext;
        }
    }
    return ref;
}
