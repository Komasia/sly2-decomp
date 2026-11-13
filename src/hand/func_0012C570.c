typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct KEY { float a, b; } KEY;
typedef struct T { int pad; int c; float *at; KEY *ak[3]; int pad2[2]; int v[4]; } T;
void ReadVector__18CBinaryInputStreamP6VECTOR(void *pbis, void *pv);
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
int U8Read(void *pbis) asm("U8Read__18CBinaryInputStream");
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(AREQ *preq);
void func_0012C570(T *t, void *pbis)
{
    AREQ req;
    int i, j, mask, grf;
    int c;
    ReadVector__18CBinaryInputStreamP6VECTOR(pbis, t->v);
    c = U16Read(pbis);
    req.cb = c * 4;
    req.cbAlign = 0x10;
    t->c = c;
    t->at = PvAllocSwImpl__Fi(&req);
    for (i = 0; i < t->c; i++)
        t->at[i] = U16Read(pbis) * 0.016666668f;
    grf = U8Read(pbis);
    for (j = 0, mask = 1; j < 3; j++, mask <<= 1) {
        if (mask & grf) {
            KEY *ak;
            req.cb = t->c * 8;
            req.cbAlign = 0x10;
            ak = PvAllocSwImpl__Fi(&req);
            t->ak[j] = ak;
            for (i = 0; i < t->c; i++) {
                ak[i].a = F32Read(pbis);
                ak[i].b = F32Read(pbis);
            }
        }
    }
}
