/* TRKPA::Load for track kind 4 (per-axis keys {g, dg}): like 0x12BF30 with 2 F32s per key.
 * Layout: SafeHouse port (aseg.h TRKPA). */
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct KEYA2 { float g, dg; } KEYA2;
typedef struct TRKPA { int pvtbl; int ckey; float *at; KEYA2 *aakey[3]; int pad18[2]; int v[4]; } TRKPA;
void ReadVector__18CBinaryInputStreamP6VECTOR(void *pbis, void *pv);
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
int U8Read(void *pbis) asm("U8Read__18CBinaryInputStream");
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(AREQ *preq);
void func_0012C570(TRKPA *ptrk, void *pbis)
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
            KEYA2 *akey;
            req.cb = ptrk->ckey * 8;
            req.cbAlign = 0x10;
            akey = PvAllocSwImpl__Fi(&req);
            ptrk->aakey[iaxis] = akey;
            for (ikey = 0; ikey < ptrk->ckey; ikey++) {
                akey[ikey].g = F32Read(pbis);
                akey[ikey].dg = F32Read(pbis);
            }
        }
    }
}
