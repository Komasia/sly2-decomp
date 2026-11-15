/* TRKGK::Load: a keyed scalar track: U16 key count, then per key {U16 time in frames (1/60 s), g, dgIn, dgOut}.
 * Layout: SafeHouse port (aseg.h TRKGK / KEYG). */
typedef struct KEYG { float t; float g; float dgIn; float dgOut; } KEYG;   /* field: SafeHouse port */
typedef struct TRKGK { int pvtbl; int ckey; KEYG *akey; } TRKGK;
typedef struct AREQ { int cb; int cbAlign; } AREQ;
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
KEYG *PvAllocSwClearImpl__Fi(AREQ *preq);
// name: SafeHouse port (TRKGK::Load)
void Load__5TRKGKP18CBinaryInputStream(TRKGK *ptrk, void *pbis)
{
    int ikey;
    int ckey = U16Read(pbis);
    AREQ req;
    req.cb = ckey << 4;
    req.cbAlign = 0x10;
    ptrk->ckey = ckey;
    ptrk->akey = PvAllocSwClearImpl__Fi(&req);
    for (ikey = 0; ikey < ptrk->ckey; ikey++) {
        KEYG *pkey = &ptrk->akey[ikey];
        pkey->t = U16Read(pbis) * (1.0f / 60.0f);
        pkey->g = F32Read(pbis);
        pkey->dgIn = F32Read(pbis);
        pkey->dgOut = F32Read(pbis);
    }
}
