/* InitRope: set up a path's rope simulation: room for the points / velocities / rest distances, the defaults
 * (force (0, 0, -1750), damping 3, bend 500, bend damping 5, the capacity the path's points, the trail's step 300),
 * the points in the world (the path's world matrix, vt slot 31), the ends in the world record at the path's ends,
 * the rest distances the path's (CopyRopeDistances). Layout: h3_rope.h ROPE (as this file declares it, with the
 * spring parameters), crv.h CRV. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct M4 {qword a,b,c,d;};
struct ALLOC {int cb,cbAlign;};
struct CRV {char pad[0xC];VTENT *pvt;char pad10[0xE8-0x10];int cpoint;int padEC;float *as;qword *apos;};
struct ROPE {
 int forceX,forceY;float forceZ;char padC[0x20-0xC];
 qword aposEnd[2];          /* the ends' points in their records */
 void *apxf[2];             /* the ends' records */
 struct CRV *ppath;int mode;int pad50;
 qword *apos54,*avel58;float *as5C;
 float damping;char pad64[8];float bend,bendDamping;char pad74[0x84-0x74];
 int cMax;float sStep;
};
extern char D_002C44F0[];   /* the world's record */
void *PvAllocSwClearImpl__Fi(struct ALLOC*);
void CopyRopeDistances__FP4ROPE(struct ROPE*);
static inline qword Point(struct M4 *m,qword a) {qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));return r;}
// name: SafeHouse port (InitRope)
struct ROPE *InitRope__FP4ROPEP2LO(struct ROPE *prope,struct CRV *ppath) {
 struct ALLOC alloc;struct M4 *pmat;int i;
 prope->ppath=ppath;prope->mode=-1;
 alloc.cb=ppath->cpoint*16;alloc.cbAlign=16;prope->apos54=PvAllocSwClearImpl__Fi(&alloc);
 alloc.cb=ppath->cpoint*16;alloc.cbAlign=16;prope->avel58=PvAllocSwClearImpl__Fi(&alloc);
 alloc.cb=ppath->cpoint*4;alloc.cbAlign=16;prope->as5C=PvAllocSwClearImpl__Fi(&alloc);
 prope->forceZ=-1750.0f;prope->damping=3.0f;prope->bend=500.0f;prope->bendDamping=5.0f;
 prope->forceX=0;prope->forceY=0;
 prope->cMax=prope->ppath->cpoint;prope->sStep=300.0f;
 pmat=((struct M4 * (*)(void*))prope->ppath->pvt[31].pfn)(VT_THIS(prope->ppath, &prope->ppath->pvt[31]));
 for(i=0;i<prope->ppath->cpoint;i++)prope->apos54[i]=Point(pmat,prope->ppath->apos[i]);
 prope->apxf[0]=prope->apxf[1]=D_002C44F0;
 if(prope->ppath->cpoint>0) {
  prope->aposEnd[0]=prope->apos54[0];prope->aposEnd[1]=prope->apos54[prope->ppath->cpoint-1];
 }
 CopyRopeDistances__FP4ROPE(prope);
 return prope;
}
