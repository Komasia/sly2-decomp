struct ALLOCREQ { int cb; int nKind; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
class CBinaryInputStream;
/* JOB (include/h2_task.h): its event lists (+0x54 / +0x5C), objects (+0x8C) and state-machine goals (+0x94) */
struct JOB { char pad[0x54]; int cnEndClose; void *anEndClose; int cnEnd; void *anEnd; char pad2[0x8C - 0x64]; int cobje; void *aobje; int csme; void *asme; };
extern "C" void *PvAllocStackImpl(ALLOCREQ *preq) asm("PvAllocStackImpl__Fi");
extern "C" void *PvAllocSwCopyImpl(ALLOCREQ *preq, void *pv) asm("PvAllocSwCopyImpl__FiPv");
extern "C" void LoadLoFromBrx(JOB *pjob, CBinaryInputStream *pbis) asm("LoadLoFromBrx__FP2LOP18CBinaryInputStream");
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
/* LoadMissionFromBrx: load a job: its four lists get room for 32 entries while the options fill them, then shrink to
 * their counts. */
// name: SafeHouse port (LoadMissionFromBrx)
extern "C" void LoadMissionFromBrx__FP2LOP18CBinaryInputStream(JOB *pjob, CBinaryInputStream *pbis)
{
    FRAME fr;
    ALLOCREQ req;
    pjob->aobje = PvAllocReq(&req, 32 * 16, 0x10);
    pjob->asme = PvAllocReq(&req, 32 * 0x18, 0x10);
    pjob->anEndClose = PvAllocReq(&req, 32 * 4, 0x10);
    pjob->anEnd = PvAllocReq(&req, 32 * 4, 0x10);
    LoadLoFromBrx(pjob, pbis);
    pjob->aobje = PvShrinkReq(&req, pjob->cobje * 16, 0x10, pjob->aobje);
    pjob->asme = PvShrinkReq(&req, pjob->csme * 0x18, 0x10, pjob->asme);
    pjob->anEndClose = PvShrinkReq(&req, pjob->cnEndClose * 4, 0x10, pjob->anEndClose);
    pjob->anEnd = PvShrinkReq(&req, pjob->cnEnd * 4, 0x10, pjob->anEnd);
    ReadDebugString(pbis);
}
