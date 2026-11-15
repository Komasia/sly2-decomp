/* RecalcCrv: recompute a curve's distances for its world matrix (vt slot 31, cached in amat): a linear curve's
 * from the transformed points, a cubic one's from each segment's cached length (CacheSegCrv); then the rope's rest
 * distances follow (CopyRopeDistances). Layout: crv.h CRV, as this file declares it (sSeg = asSub[10], the cached
 * segment's length). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct M { qword a,b,c,d; };
struct CRV {
 char pad[0xC]; VTENT *pvt; char pad10[0xE0-0x10];
 int crvk; char padE4[4]; int cpoint; char padEC[4];
 float *as; qword *apos; char padF8[8]; struct M amat;
 char pad140[0x174-0x140]; float sSeg; int pad178; void *prope;
};
void RefreshCrv__FP3CRV(struct CRV*);
void CacheSegCrv__FP3CRVi(struct CRV*,int);
void CopyRopeDistances__FP4ROPE(void*);
static inline qword Point(struct M *m,qword a) {
 qword r;
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));
 return r;
}
static inline qword Move(qword a) { qword r; __asm__("vmove.xyzw %0,%1":"=j"(r):"j"(a));return r; }
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r; }
static inline qword LenVec(qword a) {
 qword d,one;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(a));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
 return d;
}
// name: SafeHouse port (RecalcCrv)
void RecalcCrv__FP3CRV(struct CRV *pcrv)
{
 int i;
 RefreshCrv__FP3CRV(pcrv);
 pcrv->amat=*((struct M*(*)(void*))pcrv->pvt[31].pfn)(VT_THIS(pcrv, &pcrv->pvt[31]));
 if (pcrv->crvk==0) {
  float *as0=pcrv->as; float sTotal=0.0f;
  qword prev;
  prev=Point(&pcrv->amat,pcrv->apos[0]);
  as0[0]=sTotal;
  for(i=1;i<pcrv->cpoint;i++) {
   qword cur=Point(&pcrv->amat,pcrv->apos[i]);
   qword lenv=LenVec(Sub(prev,cur));
   float len;
   prev=Move(cur);
   __asm__("mtc1 %1,%0":"=f"(len):"r"(lenv));
   sTotal+=len;
   pcrv->as[i]=sTotal;
  }
 } else {
  int j;
  pcrv->as[0]=0;
  for(j=0;j<pcrv->cpoint-1;j++) {
   CacheSegCrv__FP3CRVi(pcrv,j);
   pcrv->as[j+1]=pcrv->as[j]+pcrv->sSeg;
  }
 }
 if(pcrv->prope)CopyRopeDistances__FP4ROPE(pcrv->prope);
}
