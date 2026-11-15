/* Splice objects collected by the CGc start with an 8-byte header; bit 31 of its second word is the mark bit
 * (the rest are pool links, see 0x1286E0). Layouts are Sly 1's splice classes (frame.h, pair.h, proc.h, gc.h)
 * after that header. */
typedef struct GCHDR { int x0; unsigned nLinks : 31; unsigned fMark : 1; } GCHDR;
typedef struct CRef { int m_tagk; GCHDR *pobj; } CRef;
typedef struct CVarb { int x0; unsigned nLinks : 31; unsigned fMark : 1; int symid; CRef ref; struct CVarb *pvarbNext; } CVarb;   /* a binding */
typedef struct CFrame { int x0; unsigned nLinks : 31; unsigned fMark : 1; int cpframeParent; struct CFrame *apframeParent[4]; CVarb *pvarbFirst; } CFrame;
typedef struct CPair { int x0; unsigned nLinks : 31; unsigned fMark : 1; CRef ref; struct CPair *ppairNext; } CPair;
/* 0x14: a pair list whose cells are only marked, not traced (Sly 1 has crefReq / fVarArg there); 0x18: the body */
typedef struct CProc { int x0; unsigned nLinks : 31; unsigned fMark : 1; CFrame *pframe; int xC; int x10; CPair *ppairMarked; CPair *ppairCodeExpr; } CProc;
/* the collector's work stacks (Sly 1 CGc m_cpframeStack .. m_approcStack, here as pointers to stack arrays) */
typedef struct CGc { int f; int cpframeStack; CFrame **apframeStack; int cppairStack; CPair **appairStack; int cpprocStack; CProc **approcStack; } CGc;
extern unsigned int D_002DD598[1];   /* the current mark value (flips each collection) */

static inline void PushPair(CGc *pgc, CPair *ppair) { pgc->appairStack[pgc->cppairStack++] = ppair; }
static inline void PushProc(CGc *pgc, CProc *pproc) { pgc->approcStack[pgc->cpprocStack++] = pproc; }
static inline void PushFrame(CGc *pgc, CFrame *pframe) { pgc->apframeStack[pgc->cpframeStack++] = pframe; }

static inline void MarkRef(CGc *pgc, CRef *pref)
{
    switch (pref->m_tagk) {
    case 0x1F: /* TAGK_Pair */ {
        CPair *ppair = (CPair *)pref->pobj;
        if (ppair->fMark != D_002DD598[0]) {
            ppair->fMark = D_002DD598[0];
            PushPair(pgc, ppair);
        }
        break;
    }
    case 0x20: /* TAGK_Proc */ {
        CProc *pproc = (CProc *)pref->pobj;
        if (pproc->fMark != D_002DD598[0]) {
            pproc->fMark = D_002DD598[0];
            PushProc(pgc, pproc);
        }
        break;
    }
    case 0x22: /* TAGK_Method */
        pref->pobj->fMark = D_002DD598[0];
        break;
    }
}

/* GC: marks the object a reference points to (pair, closure or method), pushing an unmarked pair or closure for
 * MarkLiveObjects to trace. */
void func_001285D8(CGc *pgc, CRef *pref)
{
    MarkRef(pgc, pref);
}
