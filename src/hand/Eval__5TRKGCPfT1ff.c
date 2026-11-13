/* TRKGC::Eval: a constant scalar track: its value (+0x4) and no rate of change. TRKGC: SafeHouse port (aseg.h). */
struct TRKGC {
    /* 0x0 */ void *pvtbl;
    /* 0x4 */ float g;     /* field: SafeHouse port */
};

// name: SafeHouse port (TRKGC::Eval)
void Eval__5TRKGCPfT1ff(struct TRKGC *ptrk, float *pg, float *pdg, float t, float dtScale)
{
    if (pg)
        *pg = ptrk->g;
    if (pdg)
        *pdg = 0.0f;
}
