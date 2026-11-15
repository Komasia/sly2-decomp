struct ALLOCREQ { int cb; int nKind; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
class CBinaryInputStream {
public:
    int U8Read();
    int S32Read();
};
/* TASK (include/h2_task.h): its prerequisite / next task oids and pointers, objects and state-machine goals */
struct TASK { char pad[0x90]; int *aoidPrereq; int cptaskPrereq; void *aptaskPrereq; int *aoidNext; int cptaskNext; void *aptaskNext; int cobje; void *aobje; int csme; void *asme; };
extern "C" void *PvAllocStackImpl(ALLOCREQ *preq) asm("PvAllocStackImpl__Fi");
extern "C" void *PvAllocSwCopyImpl(ALLOCREQ *preq, void *pv) asm("PvAllocSwCopyImpl__FiPv");
extern "C" void *PvAllocSwClearImpl(ALLOCREQ *preq) asm("PvAllocSwClearImpl__Fi");
extern "C" void *PvAllocSwImpl(ALLOCREQ *preq) asm("PvAllocSwImpl__Fi");
extern "C" void LoadLoFromBrx(TASK *p, CBinaryInputStream *pbis) asm("LoadLoFromBrx__FP2LOP18CBinaryInputStream");
extern "C" void ReadDebugString(CBinaryInputStream *pbis) asm("ReadDebugString__FP18CBinaryInputStream");
static inline void *PvAllocReq(ALLOCREQ *preq, int cb, int nKind)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return PvAllocStackImpl(preq);
}
static inline void *PvShrinkReq(ALLOCREQ *preq, int cb, int nKind, void *pv)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return PvAllocSwCopyImpl(preq, pv);
}
static inline void *PvAllocA(ALLOCREQ *preq, int cb, int nKind)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return PvAllocSwClearImpl(preq);
}
static inline void *PvAllocB(ALLOCREQ *preq, int cb, int nKind)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return PvAllocSwImpl(preq);
}
/* LoadTaskFromBrx: load a task: room for 32 objects / goals while the options fill them (then shrunk), then its
 * prerequisite and next task oids (StartTask resolves them). */
// name: SafeHouse port (LoadTaskFromBrx)
extern "C" void LoadTaskFromBrx__FP2LOP18CBinaryInputStream(TASK *p, CBinaryInputStream *pbis)
{
    int i = 0;
    FRAME fr;
    ALLOCREQ req;
    p->aobje = PvAllocReq(&req, 32 * 16, 0x10);
    p->asme = PvAllocReq(&req, 32 * 0x18, 0x10);
    LoadLoFromBrx(p, pbis);
    p->aobje = PvShrinkReq(&req, p->cobje * 16, 0x10, p->aobje);
    p->asme = PvShrinkReq(&req, p->csme * 0x18, 0x10, p->asme);
    p->cptaskPrereq = pbis->U8Read();
    p->aptaskPrereq = PvAllocA(&req, p->cptaskPrereq * 4, 0x10);
    p->aoidPrereq = (int *)PvAllocB(&req, p->cptaskPrereq * 4, 0x10);
    for (; i < p->cptaskPrereq; i++)
        p->aoidPrereq[i] = pbis->S32Read();
    p->cptaskNext = pbis->U8Read();
    p->aptaskNext = PvAllocA(&req, p->cptaskNext * 4, 0x10);
    p->aoidNext = (int *)PvAllocB(&req, p->cptaskNext * 4, 0x10);
    for (int j = 0; j < p->cptaskNext; j++)
        p->aoidNext[j] = pbis->S32Read();
    ReadDebugString(pbis);
}
