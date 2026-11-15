struct ALLOCREQ { int cb; int nKind; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
/* TASK: its state and whether it counts toward the percentage */
struct TASK { char pad[0x54]; int nState; char pad2[0xA0 - 0x58]; int fCounts; };
struct SW { char pad[0x3AFC]; int ctask; };   /* the world's task count (TASK Init counts them) */
extern SW g_sw;
extern "C" void *PvAllocStackClearImpl(ALLOCREQ *preq) asm("PvAllocStackClearImpl__Fi");
extern "C" int CFindObjectsByClass(SW *psw, int grf, int cid, int ploCtx, int cMax, void **aplo) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
static inline void *PvAllocReq(ALLOCREQ *preq, int cb, int nKind)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return PvAllocStackClearImpl(preq);
}
static inline int Min(int a, int b) { return a > b ? b : a; }
/* NTasksPercentDone: the percentage of the world's counted tasks (cid 0x85) that are closed: 0 for none, 100 only
 * for all, else 1..99. */
// name: SafeHouse port (NTasksPercentDone)
extern "C" int NTasksPercentDone__Fv()
{
    int c = 0;
    int cDone = 0;
    FRAME fr;
    ALLOCREQ req;
    SW *psw = &g_sw;
    TASK **aptask = (TASK **)PvAllocReq(&req, psw->ctask * 4, 0x10);
    int ctask = CFindObjectsByClass(psw, 5, 0x85, 0, psw->ctask, (void **)aptask);
    for (int i = 0; i < ctask; i++) {
        TASK *ptask = aptask[i];
        if (ptask->fCounts) {
            c++;
            if (ptask->nState == 3)   /* TASKS_Closed */
                cDone++;
        }
    }
    if (!cDone)
        return 0;
    if (cDone == c)
        return 100;
    int nMax = 99; int pct = cDone * 100 / c; int nRet = 1; if (pct > 0) nRet = Min(pct, nMax); return nRet;
}
