typedef int qword __attribute__((mode(TI)));
struct BIS;
struct AREQ { int cb; int cbAlign; };
struct EDGE { unsigned short ipos0, ipos1, iface, ifaceOther; EDGE *pedgeNext; EDGE *pedgeOther; };
struct FACE { qword plane; EDGE *pedgeFirst; EDGE *pedgeOther; int pad; int ipos; };
struct GEOM { int cpos; qword *apos; int cface; FACE *aface; int cedge; EDGE *aedge; };
extern "C" {
int U16Read(BIS *pbis) asm("U16Read__18CBinaryInputStream");
float F32Read(BIS *pbis) asm("F32Read__18CBinaryInputStream");
int U8Read(BIS *pbis) asm("U8Read__18CBinaryInputStream");
void ReadVector(BIS *pbis, qword *pv) asm("ReadVector__18CBinaryInputStreamP6VECTOR");
void *PvAllocSwImpl(AREQ *preq) asm("PvAllocSwImpl__Fi");
void *PvAllocSwClearImpl(AREQ *preq) asm("PvAllocSwClearImpl__Fi");
void PlaneFromPoints(FACE *pface, qword a, qword b, qword c) asm("PlaneFromPoints__FP6VECTORG9VU_VECTORN21");
void ReadGeom(BIS *pbis, GEOM *pg) asm("ReadGeom__18CBinaryInputStreamP4GEOM");
}
static inline void *PvAlloc1D0(int cb) { AREQ req; req.cbAlign = 0x10; req.cb = cb; return PvAllocSwImpl(&req); }
static inline void *PvAlloc2A0(int cb) { AREQ req; req.cbAlign = 0x10; req.cb = cb; return PvAllocSwClearImpl(&req); }
// name: SafeHouse port (CBinaryInputStream::ReadGeom 0x117FD0) + Sly 1 ReadGeom
void ReadGeom(BIS *pbis, GEOM *pg) { int i;
 pg->cpos = U16Read(pbis);
 pg->apos = (qword *)PvAlloc1D0(pg->cpos * 16);
 for (i = 0; i < pg->cpos; i++) ReadVector(pbis, &pg->apos[i]);
 pg->cface = U16Read(pbis);
 pg->aface = (FACE *)PvAlloc2A0(pg->cface * 32);
 pg->cedge = U16Read(pbis);
 pg->aedge = (EDGE *)PvAlloc2A0(pg->cedge * 16); EDGE *pedge = pg->aedge;
 for (int iface = 0; iface < pg->cface; iface++) {
   FACE *pf = &pg->aface[iface];
   int ai[3];
   ai[0] = U16Read(pbis); ai[1] = U16Read(pbis); ai[2] = U16Read(pbis);
   PlaneFromPoints(pf, pg->apos[ai[0]], pg->apos[ai[1]], pg->apos[ai[2]]);
   pf->ipos = ai[0];
   for (int j = 0; j < 4; j++) F32Read(pbis);
   int cedge = U8Read(pbis);
   for (int k = 0; k < cedge; k++) {
     EDGE *pe = pedge++;
     pe->ipos0 = U16Read(pbis); pe->ipos1 = U16Read(pbis); pe->iface = iface;
     pe->ifaceOther = U16Read(pbis);
     if (k == 0) pf->pedgeFirst = pe; else pe[-1].pedgeNext = pe;
     FACE *pfO = &pg->aface[pe->ifaceOther];
     pe->pedgeOther = pfO->pedgeOther;
     pfO->pedgeOther = pe;
   }
 } }
