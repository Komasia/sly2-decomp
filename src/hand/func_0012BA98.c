/* TRKPK::Load (one-tangent keys, track kind 2): U16 key count, then per key {U16 time in frames (1/60 s),
 * position, tangent}, into 0x20-byte keys. Layout: SafeHouse port (aseg.h). */
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef struct KEYP1 {
    VECTOR3 pos;    /* field: SafeHouse port */
    float t;        /* field: SafeHouse port */
    VECTOR3 v;      /* field: SafeHouse port - the tangent (in = out) */
    int pad;
} KEYP1;
typedef struct TRKPK { int pvtbl; int ckey; KEYP1 *akey; } TRKPK;
typedef struct AREQ { int cb; int cbAlign; } AREQ;
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
void ReadVector__18CBinaryInputStreamP6VECTOR(void *pbis, VECTOR3 *pv);
KEYP1 *PvAllocSwClearImpl__Fi(AREQ *preq);
void func_0012BA98(TRKPK *ptrk, void *pbis)
{
    int ikey;
    int ckey = U16Read(pbis);
    AREQ req;
    req.cb = ckey << 5;
    req.cbAlign = 0x10;
    ptrk->ckey = ckey;
    ptrk->akey = PvAllocSwClearImpl__Fi(&req);
    for (ikey = 0; ikey < ptrk->ckey; ikey++) {
        KEYP1 *pkey = &ptrk->akey[ikey];
        pkey->t = U16Read(pbis) * (1.0f / 60.0f);
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pkey->pos);
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pkey->v);
    }
}
