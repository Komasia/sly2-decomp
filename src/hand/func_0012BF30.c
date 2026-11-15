/* TRKPA::Load (track kind 3: per-axis keys {g, dgIn, dgOut}): the constant vector v, U16 key count, the key times
 * (U16 frames, 1/60 s), then a U8 mask of the axes that have keys and, for each such axis, c keys of 3 F32s.
 * Layout: SafeHouse port (aseg.h TRKPA). */
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct KEYA3 { float g, dgIn, dgOut; } KEYA3;   /* field: SafeHouse port */
typedef struct TRKPA {
    /* 0x00 */ int pvtbl;
    /* 0x04 */ int ckey;
    /* 0x08 */ float *at;         /* field: SafeHouse port - the key times */
    /* 0x0c */ KEYA3 *aakey[3];   /* field: SafeHouse port (aag) - per axis, null: no keys */
    /* 0x18 */ int pad18[2];
    /* 0x20 */ int v[4];          /* field: SafeHouse port - the value of the axes without keys */
} TRKPA;
void ReadVector__18CBinaryInputStreamP6VECTOR(void *pbis, void *pv);
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
int U8Read(void *pbis) asm("U8Read__18CBinaryInputStream");
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(AREQ *preq);
// name: SafeHouse port (TRKPA::Load)
void Load__5TRKPAP18CBinaryInputStream(TRKPA *ptrk, void *pbis)
{
    AREQ req;
    int ikey, iaxis, mask, grfAxes;
    int ckey;
    ReadVector__18CBinaryInputStreamP6VECTOR(pbis, ptrk->v);
    ckey = U16Read(pbis);
    req.cb = ckey * 4;
    req.cbAlign = 0x10;
    ptrk->ckey = ckey;
    ptrk->at = PvAllocSwImpl__Fi(&req);
    for (ikey = 0; ikey < ptrk->ckey; ikey++)
        ptrk->at[ikey] = U16Read(pbis) * 0.016666668f;   /* frames -> seconds */
    grfAxes = U8Read(pbis);
    for (iaxis = 0, mask = 1; iaxis < 3; iaxis++, mask <<= 1) {
        if (mask & grfAxes) {
            KEYA3 *akey;
            req.cb = ptrk->ckey * 12;
            req.cbAlign = 0x10;
            akey = PvAllocSwImpl__Fi(&req);
            ptrk->aakey[iaxis] = akey;
            for (ikey = 0; ikey < ptrk->ckey; ikey++) {
                akey[ikey].g = F32Read(pbis);
                akey[ikey].dgIn = F32Read(pbis);
                akey[ikey].dgOut = F32Read(pbis);
            }
        }
    }
}
