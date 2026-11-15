struct ALLOCREQ { int cb; int nKind; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
// func_00165C98: the world's tasks in graph order: every task (cid 0x85) unvisited, then VisitTask from each task
// without prerequisites; the list (on the stack) and its count go to the caller.
struct TASK { char pad[0x94]; int cptaskPrereq; char pad2[0xFC - 0x98]; int cVisit; };
struct SW { char pad[0x3AFC]; int ctask; };
extern SW g_sw;
extern "C" void *PvAllocStackClearImpl(ALLOCREQ *preq) asm("PvAllocStackClearImpl__Fi");
extern "C" int CFindObjectsByClass(SW *psw, int grf, int cid, int ploCtx, int c, void **aplo) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
extern "C" void VisitTask(TASK *px, int *pctask, void *pv, int a, int b) asm("VisitTask__FP4TASKPiPvii");
extern "C" void func_00165C98(int *pctask, void **paptask)
{
    ALLOCREQ req;
    SW *psw = &g_sw;
    *pctask = 0;
    req.cb = psw->ctask * 4;
    req.nKind = 0x10;
    *paptask = PvAllocStackClearImpl(&req);
    FRAME fr;
    req.cb = psw->ctask * 4;
    req.nKind = 0x10;
    TASK **aptask = (TASK **)PvAllocStackClearImpl(&req);
    int c = CFindObjectsByClass(psw, 5, 0x85, 0, psw->ctask, (void **)aptask);
    int i;
    for (i = 0; i < c; i++)
        aptask[i]->cVisit = 0;
    for (int j = 0; j < c; j++) {
        if (!aptask[j]->cptaskPrereq)
            VisitTask(aptask[j], pctask, *paptask, 0, 0);
    }
}
