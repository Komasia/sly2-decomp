/* NewBlend: the blend of the BL entries abl (cbl of them, stride cbBl; ctable segment tables at aibAmrsg[i] in each,
 * acmrsg[i] segments) played on palo: a new ASEGBL (cid 0x6E) with the union of the BLs' channels (a blended position
 * track TRKPBL holding the record's current value, or a blended scalar track TRKGBL), the events of the first BL that
 * has some, the priority / speed / frame of the first BL; the first BL's weight 1, the others 0, then RecalcBlend; null
 * without ASEGs. Layout: SafeHouse port (blend.h ASEGBL / BLENDBL / TRKPBL). */
// NewBlend (Claude agent laneBE2, 2026-10-23): MATCH. Built from build/hand_wip/NewBlend.fresh14.cpp:
// the E3-loop "r"(0x10) asm removed, one allocation-only empty asm on the i*4 giv, one register pin (mF31 in s5),
// and the not-found slot written as `pentNew = &pbl->achn[pbl->cchn++];`.
#include "cid.h"
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; AREQ(int c) { cb = c; cbAlign = 0x10; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct OBJ;
struct ENT { unsigned oid : 20; unsigned isub : 10; unsigned fDisabled : 1; signed fScalar : 1; OBJ *ptrk; };   // ASEGCHN (SafeHouse aseg.h)
struct E3 { int ibAmrsg; int cmrsg; void *amrsg; };   // a segment table: its offset in each BL, its segment count, the blended segments
struct X;
struct OBJ { int x0; X *pbl; E3 *aamrsg; OBJ **atrk; qword v; };   // TRKPBL / TRKGBL (SafeHouse blend.h)
struct XB {
    int pframe; int pad4[2];
    virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
    virtual void f6(); virtual void f7(); virtual void f8(); virtual void Init();
};
struct X : XB {
    char pad[0x5C - 0x10]; int cchn; ENT *achn; char pad64[0x6C - 0x64]; int prio; int pad70[2]; float svt;
    char pad7C[0x98 - 0x7C]; int cevStart, aevStart, cevTimed; void *aevTimed; int cevEnd, aevEnd;
    char padB0[0xC0 - 0xB0]; int cbBl; int cbl; struct ELEM *abl; int ctable; E3 *aamrsg; int iblDominant; X *pasegSkel;   // field: SafeHouse port (blend.h ASEGBL)
};
struct XV { virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
            virtual void f6(); virtual void f7(); virtual void f8(); virtual void Init(); };
struct ELEM { float weight; X *paseg; };   // a BL entry (SafeHouse blend.h BLENDBL)
extern "C" {
X *PloNew(int a, void *p, int b, int c) asm("PloNew__F3CIDP2SW3OIDi");
void *PvAllocSwImpl(const AREQ &req) asm("PvAllocSwImpl__Fi");
void *PvAllocSwCopyImpl(const AREQ &req, void *pv) asm("PvAllocSwCopyImpl__FiPv");
void *PvAllocStackClearImpl(const AREQ &req) asm("PvAllocStackClearImpl__Fi");
void *PvAllocSwClearImpl(const AREQ &req) asm("PvAllocSwClearImpl__Fi");
OBJ *PtrkpNew(int id) asm("PtrkpNew__Fi");
OBJ *PtrkgNew(int id) asm("PtrkgNew__Fi");
void GetAsegChannelTarget(X *px, void *p, ENT *pent, int *pa, void **ppb) asm("GetAsegChannelTarget__FP4ASEGP3ALOP7ASEGCHNPP3ALOPP2XF");
qword VecXfValue(void *pa, void *pb) asm("VecXfValue__FP2XFP7MATRIX4");
void func_00256EE0(X *px, int n);
void RecalcBlend(X *px) asm("RecalcBlend__FP6ASEGBL");
void NewBlend(void *palo, int cbBl, int cbl, ELEM *abl, int ctable, int *aibAmrsg, int *acmrsg, X **ppbl) asm("NewBlend__FP3ALOiiP4ELEMiPiT5Pv");
}
#define PELEM(i) ((ELEM *)((char *)abl + (i) * cbBl))
// name: SafeHouse port (NewBlend)
void NewBlend(void *palo, int cbBl, int cbl, ELEM *abl, int ctable, int *aibAmrsg, int *acmrsg, X **ppbl)
{
    ELEM *pe;
    ELEM *pel;
    X *pasegFirst;
    X *pasegFrame;
    X *pasegEvents = 0;
    pasegFrame = 0;
    pasegFirst = 0;
    int j;
    int i;
    for (i = 0; i < cbl; i++) {
        pe = PELEM(i);
        if (pe->paseg) {
            if (!pasegFirst) pasegFirst = pe->paseg;
            if (!pasegEvents && (pe->paseg->cevStart || pe->paseg->cevEnd || pe->paseg->cevTimed)) pasegEvents = pe->paseg;
            if (!pasegFrame) pasegFrame = pe->paseg->pframe ? pe->paseg : 0;
        }
    }
    if (!pasegFirst) { *ppbl = 0; return; }
    {
        FRAME frame;
        X *pbl = PloNew(CID_ASEGBL, palo, -1, -1);
        pbl->Init();
        pbl->cbBl = cbBl;
        pbl->cbl = cbl;
        pbl->abl = abl;
        pbl->ctable = ctable;
        pbl->aamrsg = (E3 *)PvAllocSwImpl(AREQ(ctable * 12));
        for (int ie = 0; ie < ctable; ie++) {
            E3 *pe3 = &pbl->aamrsg[ie];
            pe3->ibAmrsg = aibAmrsg[ie];
            int b = acmrsg[ie];
            pe3->cmrsg = b;
            pe3->amrsg = PvAllocSwImpl(AREQ(b * 8));
        }
        
        if (pasegEvents) {
            pbl->pasegSkel = pasegEvents;
            pbl->cevStart = pasegEvents->cevStart;
            pbl->aevStart = pasegEvents->aevStart;
            pbl->cevTimed = pasegEvents->cevTimed;
            { void *pvOld = pasegEvents->aevTimed; pbl->aevTimed = PvAllocSwCopyImpl(AREQ(pasegEvents->cevTimed << 4), pvOld); }
            pbl->cevEnd = pasegEvents->cevEnd;
            pbl->aevEnd = pasegEvents->aevEnd;
        }
        {
            int cTotal = 0;
            for (i = 0; i < cbl; i++) {
                if (PELEM(i)->paseg) cTotal += PELEM(i)->paseg->cchn;
            }
            pbl->achn = (ENT *)PvAllocStackClearImpl(AREQ(cTotal * 8));
            pbl->cchn = 0;
        }
        for (i = 0; i < cbl; i++) {
            pel = PELEM(i);
            if (!pel->paseg) continue;
            for (j = 0; j < pel->paseg->cchn; j++) {
                ENT *pent = &pel->paseg->achn[j];
                ENT *pentNew;
                OBJ *pobj;
                int k;
                if (pent->fDisabled) continue;
                k = 0;
                ENT *aent = pbl->achn;
                for (; k < pbl->cchn; k++) {
                    pentNew = &pbl->achn[k];
                    if ((*(unsigned *)pent & 0x3FFFFFFF) == (*(unsigned *)&aent[k] & 0x3FFFFFFF))
                        goto found;
                }
                pentNew = &pbl->achn[pbl->cchn++];
                pentNew->oid = (*(unsigned *)pent << 12) >> 12;
                pentNew->isub = pent->isub;
            found:
                register unsigned mF31 asm("$21") = 0x80000000;  /* register pin: mF31 in s5 like the target (global alloc otherwise gives s5 to &req) */
                if (pent->fScalar >= 0) {
            if (!pentNew->ptrk) {
            int a; void *pv;
            pobj = PtrkpNew(5);
            GetAsegChannelTarget(pbl, palo, pentNew, &a, &pv);
            pobj->v = VecXfValue(pv, pv);
            pobj->pbl = pbl;
            pobj->aamrsg = pbl->aamrsg;
            pobj->atrk = (OBJ **)PvAllocSwClearImpl(AREQ(cbl * 4));
            pentNew->ptrk = pobj;
            } else pobj = pentNew->ptrk;
                } else {
            if (!pentNew->ptrk) {
            pobj = PtrkgNew(2);
            pobj->pbl = pbl;
            pobj->aamrsg = pbl->aamrsg;
            pobj->atrk = (OBJ **)PvAllocSwClearImpl(AREQ(cbl * 4));
            pentNew->ptrk = pobj;
            *(unsigned *)pentNew |= mF31;
            } else pobj = pentNew->ptrk;
                }
                pobj->atrk[i] = pent->ptrk;
                __asm__("" : : "r"(i * 4));  /* empty asm, allocation only: one more ref on the i*4 giv */
            }
        }
        { ENT *aentOld = pbl->achn; pbl->achn = (ENT *)PvAllocSwCopyImpl(AREQ(pbl->cchn * 8), aentOld); }
        pbl->prio = pasegFirst->prio;
        pbl->svt = pasegFirst->svt;
        pbl->iblDominant = -1;
        if (pasegFrame) func_00256EE0(pbl, pasegFrame->pframe);
        pe = abl;
        for (i = 0; i < cbl; i++) {
            pe->weight = (pe->paseg == pasegFirst) ? 1.0f : 0.0f;
            pe = (ELEM *)((char *)pe + cbBl);
        }
        RecalcBlend(pbl);
        *ppbl = pbl;
    }
}
