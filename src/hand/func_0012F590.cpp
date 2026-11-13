extern "C" {
typedef struct BIS BIS;
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct L0 { int n; int a, b, c; float x, y, z; } L0;
typedef struct L20 { int a, b; float g; } L20;
typedef struct ENT { float g0; int kind; union { int n; float g; void *pv; int *pn; } u8; union { int n; float g; } uC; } ENT;
float F32Read(BIS *pbis) asm("F32Read__18CBinaryInputStream");
int S16Read(BIS *pbis) asm("S16Read__18CBinaryInputStream");
int S32Read(BIS *pbis) asm("S32Read__18CBinaryInputStream");
int S8Read(BIS *pbis) asm("S8Read__18CBinaryInputStream");
int U8Read(BIS *pbis) asm("U8Read__18CBinaryInputStream");
void *PvAllocSwImpl(AREQ *preq) asm("PvAllocSwImpl__Fi");
void *PvAllocSwClearImpl(AREQ *preq) asm("PvAllocSwClearImpl__Fi");
void *PvAllocSwCopyImpl(AREQ *preq, void *pv) asm("PvAllocSwCopyImpl__FiPv");
void ReadCb8(BIS *pbis, void *pv) asm("ReadCb8__18CBinaryInputStreamPv");
void func_0012F590(void *px, BIS *pbis, int fTime, int *pc, struct ENT **pa);
}
static __inline__ void *PvAlloc(int cb) { AREQ req; req.cb = cb; req.cbAlign = 0x10; return PvAllocSwClearImpl(&req); }
void func_0012F590(void *px, BIS *pbis, int fTime, int *pc, ENT **pa) { int i; int c; ENT *aent;
 c = U8Read(pbis);
 *pc = c;
 aent = (ENT *)PvAlloc(c * 16);
 *pa = aent;
 for (i = 0; i < c; i++) {
   ENT *pe = &aent[i];
   pe->kind = S8Read(pbis);
   if (fTime) pe->g0 = S16Read(pbis) * (1.0f / 60.0f);
   switch (pe->kind) {
   case 0: { AREQ req; L0 l; l.n = S16Read(pbis); l.a = S32Read(pbis); l.b = S32Read(pbis); l.c = S32Read(pbis);
       l.z = F32Read(pbis); l.x = F32Read(pbis); l.y = F32Read(pbis);
       req.cb = 0x1C; req.cbAlign = 0x10; pe->u8.pv = PvAllocSwCopyImpl(&req, &l); break; }
   case 3: pe->uC.g = S16Read(pbis) * (1.0f / 60.0f); pe->u8.n = S16Read(pbis); break;
   case 5: pe->u8.g = S16Read(pbis) * (1.0f / 60.0f); pe->uC.g = F32Read(pbis); break;
   case 7: case 8: pe->u8.n = S32Read(pbis); pe->uC.g = F32Read(pbis); break;
   case 13: case 14: case 15: case 16: pe->u8.n = S32Read(pbis); pe->uC.n = S32Read(pbis); break;
   case 17: { pe->u8.pv = PvAlloc(0x10);
       pe->u8.pn[0] = S32Read(pbis); pe->u8.pn[1] = S32Read(pbis); pe->u8.pn[2] = S32Read(pbis); ((float *)pe->u8.pn)[3] = F32Read(pbis); break; }
   case 20: { L20 t; AREQ req; AREQ *preq; t.a = S32Read(pbis); t.b = S32Read(pbis); t.g = F32Read(pbis);
       preq = &req; req.cb = 0xC; preq->cbAlign = 0x10; pe->u8.pv = PvAllocSwCopyImpl(preq, &t); break; }
   case 1: case 2: case 21: pe->u8.n = S16Read(pbis); break;
   case 4: case 11: case 12: case 22: pe->u8.n = S32Read(pbis); break;
   case 24: { AREQ req; char *p; req.cb = 0x18; req.cbAlign = 0x10; p = (char *)PvAllocSwImpl(&req);
       ReadCb8(pbis, p); ReadCb8(pbis, p + 8); ReadCb8(pbis, p + 0x10); pe->u8.pv = p; break; }
   }
 } }
