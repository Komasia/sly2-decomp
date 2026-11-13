struct BIS;
struct AREQ { int cb; int cbAlign; };
struct OBJ { virtual void Load(BIS *pbis); };
struct ENT { unsigned n : 20; unsigned k : 10; unsigned f30 : 1; unsigned f31 : 1; OBJ *pobj; };
struct ENT2 { int a; int b; OBJ *pobj; };
struct X { char pad[0x5C]; int c; ENT *aent; int c2; ENT2 *aent2; char pad2[0x74 - 0x6C]; float g74;
           char pad3[0x98 - 0x78]; int x98, x9C, xA0, xA4, xA8, xAC; };
extern "C" {
float F32Read(BIS *pbis) asm("F32Read__18CBinaryInputStream");
int S16Read(BIS *pbis) asm("S16Read__18CBinaryInputStream");
int S32Read(BIS *pbis) asm("S32Read__18CBinaryInputStream");
int S8Read(BIS *pbis) asm("S8Read__18CBinaryInputStream");
int U8Read(BIS *pbis) asm("U8Read__18CBinaryInputStream");
void *PvAllocSwImpl(AREQ *preq) asm("PvAllocSwImpl__Fi");
void *PvAllocSwClearImpl(AREQ *preq) asm("PvAllocSwClearImpl__Fi");
OBJ *PtrkpNew(int id) asm("PtrkpNew__Fi");
OBJ *PtrkgNew(int id) asm("PtrkgNew__Fi");
void func_0012F590(X *px, BIS *pbis, int n, int *pa, int *pb);
void LoadOptionsFromBrx(X *px, BIS *pbis) asm("LoadOptionsFromBrx__FPvP18CBinaryInputStream");
void LoadAsegFromBrx(X *px, BIS *pbis) asm("LoadAsegFromBrx__FP4ASEGP18CBinaryInputStream");
}
void LoadAsegFromBrx(X *px, BIS *pbis) { int i; AREQ req;
 px->g74 = F32Read(pbis);
 px->c = S16Read(pbis);
 req.cbAlign = 0x10; req.cb = px->c * 8;
 px->aent = (ENT *)PvAllocSwImpl(&req);
 for (i = 0; i < px->c; i++) {
   ENT *pe = &px->aent[i];
   pe->n = S32Read(pbis);
   pe->k = S16Read(pbis);
   int id = S8Read(pbis);
   if (id != -1) { pe->pobj = PtrkpNew(id); pe->pobj->Load(pbis); pe->f31 = 0; }
   id = S8Read(pbis);
   if (id != -1) { pe->pobj = PtrkgNew(id); pe->pobj->Load(pbis); pe->f31 = 1; }
   pe->f30 = U8Read(pbis) != 0;
 }
 px->c2 = U8Read(pbis);
 req.cbAlign = 0x10; req.cb = px->c2 * 12;
 px->aent2 = (ENT2 *)PvAllocSwClearImpl(&req);
 for (i = 0; i < px->c2; i++) {
   ENT2 *pe = &px->aent2[i];
   pe->a = U8Read(pbis);
   pe->b = S32Read(pbis);
   pe->pobj = PtrkgNew(S8Read(pbis));
   pe->pobj->Load(pbis);
 }
 func_0012F590(px, pbis, 0, &px->x98, &px->x9C);
 func_0012F590(px, pbis, 1, &px->xA0, &px->xA4);
 func_0012F590(px, pbis, 0, &px->xA8, &px->xAC);
 LoadOptionsFromBrx(px, pbis); }

// name: SafeHouse port (LoadAsegFromBrx)