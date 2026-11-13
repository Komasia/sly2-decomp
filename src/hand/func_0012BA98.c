typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef struct KEY { VECTOR3 pos; float t; VECTOR3 dpos; int pad; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
typedef struct AREQ { int cb; int cbAlign; } AREQ;
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
void ReadVector__18CBinaryInputStreamP6VECTOR(void *pbis, VECTOR3 *pv);
KEY *PvAllocSwClearImpl__Fi(AREQ *preq);
void func_0012BA98(T *t, void *pbis)
{
    int i;
    int c = U16Read(pbis);
    AREQ req;
    req.cb = c << 5;
    req.cbAlign = 0x10;
    t->c = c;
    t->a = PvAllocSwClearImpl__Fi(&req);
    for (i = 0; i < t->c; i++) {
        KEY *pkey = &t->a[i];
        pkey->t = U16Read(pbis) * (1.0f / 60.0f);
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pkey->pos);
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pkey->dpos);
    }
}
