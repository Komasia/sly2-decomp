/* GC mark loop: pops frame / closure / node stacks of GC, marks children (mark bit31 @+4 vs D_002DD598), pushes unmarked.
   Diff: 258/265 (shifted) - ours hoists the D_002DD598 load out of loops, target reloads per object; reg alloc. */
typedef struct OBJ { int x0; unsigned n : 31; unsigned fMark : 1; } OBJ;
typedef struct CRef { int m_tagk; OBJ *pobj; } CRef;
typedef struct BIND { int x0; unsigned n : 31; unsigned fMark : 1; int x8; CRef ref; struct BIND *pbNext; } BIND;
typedef struct FRAME { int x0; unsigned n : 31; unsigned fMark : 1; int c; struct FRAME *apf[1]; } FRAME;
typedef struct FRAMEX { int x0; unsigned n : 31; unsigned fMark : 1; int c; int pad[4]; BIND *pbFirst; } FRAMEX;
typedef struct NODE { int x0; unsigned n : 31; unsigned fMark : 1; CRef car; struct NODE *pnNext; } NODE;
typedef struct LINK { int x0; unsigned n : 31; unsigned fMark : 1; int x8; int xC; struct LINK *plNext; } LINK;
typedef struct CLO { int x0; unsigned n : 31; unsigned fMark : 1; FRAME *pf; int xC; int x10; LINK *pl; NODE *pn; } CLO;
typedef struct GC { int f; int cFrame; FRAME **apFrame; int cNode; NODE **apNode; int cClo; CLO **apClo; } GC;
extern unsigned int D_002DD598;

static inline void PushNode(GC *pgc, NODE *pn) { pgc->apNode[pgc->cNode++] = pn; }
static inline void PushClo(GC *pgc, CLO *pc) { pgc->apClo[pgc->cClo++] = pc; }
static inline void PushFrame(GC *pgc, FRAME *pf) { pgc->apFrame[pgc->cFrame++] = pf; }

static inline void MarkRef(GC *pgc, CRef *pref)
{
    switch (pref->m_tagk) {
    case 0x1F: {
        NODE *pn = (NODE *)pref->pobj;
        if (pn->fMark != D_002DD598) {
            pn->fMark = D_002DD598;
            PushNode(pgc, pn);
        }
        break;
    }
    case 0x20: {
        CLO *pc = (CLO *)pref->pobj;
        if (pc->fMark != D_002DD598) {
            pc->fMark = D_002DD598;
            PushClo(pgc, pc);
        }
        break;
    }
    case 0x22:
        pref->pobj->fMark = D_002DD598;
        break;
    }
}

void func_001281B0(GC *pgc)
{
    for (;;) {
        FRAME *pf = (pgc->cFrame > 0) ? pgc->apFrame[--pgc->cFrame] : 0;
        if (pf) {
            BIND *pb;
            int i;
            for (pb = ((FRAMEX *)pf)->pbFirst; pb; pb = pb->pbNext) {
                pb->fMark = D_002DD598;
                MarkRef(pgc, &pb->ref);
            }
            for (i = 0; i < pf->c; i++) {
                FRAME *pfChild = pf->apf[i];
                if (pfChild->fMark != D_002DD598) {
                    pfChild->fMark = D_002DD598;
                    PushFrame(pgc, pfChild);
                }
            }
            continue;
        }
        {
            CLO *pc = (pgc->cClo > 0) ? pgc->apClo[--pgc->cClo] : 0;
            if (pc) {
                LINK *pl;
                NODE *pn;
                FRAME *pfc;
                for (pl = pc->pl; pl; pl = pl->plNext) {
                    if (pl->fMark != D_002DD598)
                        pl->fMark = D_002DD598;
                }
                pn = pc->pn;
                if (pn->fMark != D_002DD598) {
                    pn->fMark = D_002DD598;
                    PushNode(pgc, pn);
                }
                pfc = pc->pf;
                if (pfc->fMark != D_002DD598) {
                    pfc->fMark = D_002DD598;
                    PushFrame(pgc, pfc);
                }
                continue;
            }
        }
        {
            NODE *pn = (pgc->cNode > 0) ? pgc->apNode[--pgc->cNode] : 0;
            NODE *pnNext;
            if (!pn)
                return;
            MarkRef(pgc, &pn->car);
            pnNext = pn->pnNext;
            if (pnNext && pnNext->fMark != D_002DD598) {
                pnNext->fMark = D_002DD598;
                PushNode(pgc, pnNext);
            }
        }
    }
}
