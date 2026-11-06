typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct REC { int id; float v[2]; float g; } REC;
typedef struct T { char pad[0xE4]; int c; void *pad2; void **ap; int crec; REC *arec; } T;
typedef struct G { char pad[0x228]; void *p; } G;
extern G D_003DD040;
void PostLoLoad__FP2LO(T *t);
void **PvAllocSwClearImpl__Fi(AREQ *preq);
void *IvoiceFromTarget__FP8SOUNDMGRi(G *pg, int id);
void AddVoiceFalloff__9CSndVoiceiiPvf(float g, void *p, void *q, T *t, float *pv);
void func_0012EC50(T *t)
{
    AREQ req;
    void *p;
    PostLoLoad__FP2LO(t);
    req.cb = t->c * 4;
    req.cbAlign = 0x10;
    t->ap = PvAllocSwClearImpl__Fi(&req);
    p = D_003DD040.p;
    if (p) {
        int i;
        for (i = 0; i < t->crec; i++) {
            REC *prec = &t->arec[i];
            AddVoiceFalloff__9CSndVoiceiiPvf(prec->g, p, IvoiceFromTarget__FP8SOUNDMGRi(&D_003DD040, prec->id), t, prec->v);
        }
    }
}
