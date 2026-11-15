// LoadAsegFromBrx: an animation segment's data: its length, the channels (each {oid:20, isub:10} of the object /
// record it drives, a position track (kinds by PtrkpNew) or a scalar track (PtrkgNew; the second one read wins),
// fDisabled), the scalar channel list {kind, n, track}, the three event lists (start, timed, end), then the
// object's options. Layout: SafeHouse port (aseg.h ASEGD / ASEGCHN / ASEGCHG).
struct BIS;
struct AREQ { int cb; int cbAlign; };
struct TRK { virtual void Load(BIS *pbis); };   // TRKP / TRKG: vt slot 1 Load
struct ASEGCHN { unsigned oid : 20; unsigned isub : 10; unsigned fDisabled : 1; unsigned fScalar : 1; TRK *ptrk; };   // field: SafeHouse port
struct ASEGCHG { int kind; int n; TRK *ptrkg; };   // field: SafeHouse port
struct ASEG { char pad[0x5C]; int cchn; ASEGCHN *achn; int cchg; ASEGCHG *achg; char pad2[0x74 - 0x6C]; float tMax;
           char pad3[0x98 - 0x78]; int cevStart, aevStart, cevTimed, aevTimed, cevEnd, aevEnd; };   // field: SafeHouse port
extern "C" {
float F32Read(BIS *pbis) asm("F32Read__18CBinaryInputStream");
int S16Read(BIS *pbis) asm("S16Read__18CBinaryInputStream");
int S32Read(BIS *pbis) asm("S32Read__18CBinaryInputStream");
int S8Read(BIS *pbis) asm("S8Read__18CBinaryInputStream");
int U8Read(BIS *pbis) asm("U8Read__18CBinaryInputStream");
void *PvAllocSwImpl(AREQ *preq) asm("PvAllocSwImpl__Fi");
void *PvAllocSwClearImpl(AREQ *preq) asm("PvAllocSwClearImpl__Fi");
TRK *PtrkpNew(int kind) asm("PtrkpNew__Fi");
TRK *PtrkgNew(int kind) asm("PtrkgNew__Fi");
void func_0012F590(ASEG *paseg, BIS *pbis, int fTime, int *pcev, int *paev);   // LoadAsegEventsFromBrx (SafeHouse)
void LoadOptionsFromBrx(ASEG *paseg, BIS *pbis) asm("LoadOptionsFromBrx__FPvP18CBinaryInputStream");
void LoadAsegFromBrx(ASEG *paseg, BIS *pbis) asm("LoadAsegFromBrx__FP4ASEGP18CBinaryInputStream");
}
// name: SafeHouse port (LoadAsegFromBrx)
void LoadAsegFromBrx(ASEG *paseg, BIS *pbis)
{
    int i;
    AREQ req;
    paseg->tMax = F32Read(pbis);
    paseg->cchn = S16Read(pbis);
    req.cbAlign = 0x10; req.cb = paseg->cchn * 8;
    paseg->achn = (ASEGCHN *)PvAllocSwImpl(&req);
    for (i = 0; i < paseg->cchn; i++) {
        ASEGCHN *pchn = &paseg->achn[i];
        pchn->oid = S32Read(pbis);
        pchn->isub = S16Read(pbis);
        int kind = S8Read(pbis);
        if (kind != -1) { pchn->ptrk = PtrkpNew(kind); pchn->ptrk->Load(pbis); pchn->fScalar = 0; }
        kind = S8Read(pbis);
        if (kind != -1) { pchn->ptrk = PtrkgNew(kind); pchn->ptrk->Load(pbis); pchn->fScalar = 1; }
        pchn->fDisabled = U8Read(pbis) != 0;
    }
    paseg->cchg = U8Read(pbis);
    req.cbAlign = 0x10; req.cb = paseg->cchg * 12;
    paseg->achg = (ASEGCHG *)PvAllocSwClearImpl(&req);
    for (i = 0; i < paseg->cchg; i++) {
        ASEGCHG *pchg = &paseg->achg[i];
        pchg->kind = U8Read(pbis);
        pchg->n = S32Read(pbis);
        pchg->ptrkg = PtrkgNew(S8Read(pbis));
        pchg->ptrkg->Load(pbis);
    }
    func_0012F590(paseg, pbis, 0, &paseg->cevStart, &paseg->aevStart);
    func_0012F590(paseg, pbis, 1, &paseg->cevTimed, &paseg->aevTimed);
    func_0012F590(paseg, pbis, 0, &paseg->cevEnd, &paseg->aevEnd);
    LoadOptionsFromBrx(paseg, pbis);
}
