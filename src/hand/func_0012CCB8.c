typedef struct KEY { float t; float g; float dgIn; float dgOut; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
typedef struct AREQ { int cb; int cbAlign; } AREQ;
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
KEY *PvAllocSwClearImpl__Fi(AREQ *preq);
// name: SafeHouse port (TRKGK::Load)
void Load__5TRKGKP18CBinaryInputStream(T *t, void *pbis)
{
    int i;
    int c = U16Read(pbis);
    AREQ req;
    req.cb = c << 4;
    req.cbAlign = 0x10;
    t->c = c;
    t->a = PvAllocSwClearImpl__Fi(&req);
    for (i = 0; i < t->c; i++) {
        KEY *pkey = &t->a[i];
        pkey->t = U16Read(pbis) * (1.0f / 60.0f);
        pkey->g = F32Read(pbis);
        pkey->dgIn = F32Read(pbis);
        pkey->dgOut = F32Read(pbis);
    }
}
