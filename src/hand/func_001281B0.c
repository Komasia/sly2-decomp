/* CGc::MarkLiveObjects (Sly 1 gc.cpp; 0x1286E0 calls it after pushing the roots): drains the collector's frame,
 * closure and pair stacks, giving every reachable object the current mark and pushing the unmarked ones it reaches
 * (a frame's bindings and parents, a closure's frame and body, a pair's value and cdr).
 * Register keys (Claude agent, 2026-10-17): one function-level `pproc` for every closure pointer (the TAGK_Method
 * case marks through the stale pointer of an earlier TAGK_Proc case - original behaviour), one `pframe` for the
 * popped frame and the closure's frame, one `ppair` for the closure's marked-list walk, its body and the popped
 * pair. */
/* Splice objects collected by the GC start with an 8-byte header; bit 31 of its second word is the mark bit
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
extern unsigned int D_002DD598[1];   /* the current mark value; likely g_gc's first word (Collect 0x1286E0 flips pgc->f) */

static inline void PushPair(CGc *pgc, CPair *ppair) { pgc->appairStack[pgc->cppairStack++] = ppair; }
static inline void PushProc(CGc *pgc, CProc *pproc) { pgc->approcStack[pgc->cpprocStack++] = pproc; }
static inline void PushFrame(CGc *pgc, CFrame *pframe) { pgc->apframeStack[pgc->cpframeStack++] = pframe; }

#define MARKREF(pref, STMT_METHOD) \
    switch ((pref)->m_tagk) { \
    case 0x1F: /* TAGK_Pair */ { \
        CPair *ppairRef = (CPair *)(pref)->pobj; \
        if (ppairRef->fMark != D_002DD598[0]) { ppairRef->fMark = D_002DD598[0]; PushPair(pgc, ppairRef); } \
        break; } \
    case 0x20: /* TAGK_Proc */ \
        pproc = (CProc *)(pref)->pobj; \
        if (pproc->fMark != D_002DD598[0]) { pproc->fMark = D_002DD598[0]; PushProc(pgc, pproc); } \
        break; \
    case 0x22: /* TAGK_Method */ STMT_METHOD; break; \
    }

void func_001281B0(CGc *pgc)
{
    CProc *pproc;
    CPair *ppair;
    CFrame *pframe;
    for (;;) {
        pframe = (pgc->cpframeStack > 0) ? pgc->apframeStack[--pgc->cpframeStack] : 0;
        if (pframe) {
            CVarb *pvarb;
            int i;
            for (pvarb = pframe->pvarbFirst; pvarb; pvarb = pvarb->pvarbNext) {
                CRef *pref;
                pvarb->fMark = D_002DD598[0];
                pref = &pvarb->ref;
                MARKREF(pref, pproc->fMark = D_002DD598[0])
            }
            for (i = 0; i < pframe->cpframeParent; i++) {
                CFrame *pframeParent = pframe->apframeParent[i];
                if (pframeParent->fMark != D_002DD598[0]) {
                    pframeParent->fMark = D_002DD598[0];
                    PushFrame(pgc, pframeParent);
                }
            }
            continue;
        }
        {
            pproc = (pgc->cpprocStack > 0) ? pgc->approcStack[--pgc->cpprocStack] : 0;
            if (pproc) {
                for (ppair = pproc->ppairMarked; ppair; ppair = ppair->ppairNext) {
                    if (ppair->fMark != D_002DD598[0])
                        ppair->fMark = D_002DD598[0];
                }
                ppair = pproc->ppairCodeExpr;
                if (ppair->fMark != D_002DD598[0]) {
                    ppair->fMark = D_002DD598[0];
                    PushPair(pgc, ppair);
                }
                pframe = pproc->pframe;
                if (pframe->fMark != D_002DD598[0]) {
                    pframe->fMark = D_002DD598[0];
                    PushFrame(pgc, pframe);
                }
                continue;
            }
        }
        {
            CPair *ppairNext;
            ppair = (pgc->cppairStack > 0) ? pgc->appairStack[--pgc->cppairStack] : 0;
            if (!ppair)
                return;
            MARKREF(&ppair->ref, ppair->ref.pobj->fMark = D_002DD598[0])
            ppairNext = ppair->ppairNext;
            if (ppairNext && ppairNext->fMark != D_002DD598[0]) {
                ppairNext->fMark = D_002DD598[0];
                PushPair(pgc, ppairNext);
            }
        }
    }
}
