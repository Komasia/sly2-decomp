/* TRKGC::Load: a constant scalar track reads its value. TRKGC: SafeHouse port (aseg.h). */
struct CBinaryInputStream;
struct TRKGC {
    /* 0x0 */ void *pvtbl;
    /* 0x4 */ float g;     /* field: SafeHouse port */
};
float F32Read(struct CBinaryInputStream *pbis) asm("F32Read__18CBinaryInputStream");

// name: SafeHouse port (TRKGC::Load)
void Load__5TRKGCP18CBinaryInputStream(struct TRKGC *ptrk, struct CBinaryInputStream *pbis)
{
    ptrk->g = F32Read(pbis);
}
