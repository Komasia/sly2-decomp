typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
/* Sly 1 geom.h GEOM / SURF (Sly 2: no radius first) */
struct SURF { qword normal; char pad[0xC]; int ipos; };   /* the plane (normal, gDot), a point on it */
struct GEOM { int cpos; qword *apos; int csurf; struct SURF *asurf; int cedge, aedge; };
struct REQ { int cb,nKind; };
void *PvAllocSwCopyImpl__FiPv(struct REQ *r,void *src);
void PlaneFromNormalPos__FP6VECTORG9VU_VECTORT1(struct SURF *psurf,qword normal,qword pos);
static inline qword Transform(const struct M4 *m,qword p) {
 qword r;
 __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
 :"=j"(r):"j"(m->r[0]),"j"(m->r[1]),"j"(m->r[2]),"j"(m->r[3]),"j"(p));return r;
}
static inline qword Rotate(const struct M4 *m,qword p) {
 register qword a0 __asm__("vf6")=m->r[0];
 register qword a1 __asm__("vf5")=m->r[1];
 register qword a2 __asm__("vf4")=m->r[2];
 __asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
 :"+j"(p):"j"(a0),"j"(a1),"j"(a2));return p;
}
static inline qword Normalize(qword v) {
 qword t,r; register qword l __asm__("vf2");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(l),"=&j"(t):"j"(v));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(l):"0"(l));
 __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(l),"j"(v));return r;
}
/* CopyTransformGeom: copy a geometry (its points and surfaces in new storage, the edges shared), transformed by
 * pmat when given: the points transformed, each surface's plane rebuilt from its rotated normal and a point. */
// name: SafeHouse port (CopyTransformGeom)
void CopyTransformGeom__FP4GEOMP7MATRIX4T0(struct GEOM *pgeomSrc,const struct M4 *pmat,struct GEOM *pgeomDst)
{
 struct REQ req;
 struct M4 m;
 int i,j;
 pgeomDst->cpos=pgeomSrc->cpos;
 req.cb=pgeomSrc->cpos*16;req.nKind=16;
 pgeomDst->apos=PvAllocSwCopyImpl__FiPv(&req,pgeomSrc->apos);
 pgeomDst->csurf=pgeomSrc->csurf;
 req.cb=pgeomSrc->csurf*32;req.nKind=16;
 pgeomDst->asurf=PvAllocSwCopyImpl__FiPv(&req,pgeomSrc->asurf);
 pgeomDst->cedge=pgeomSrc->cedge;pgeomDst->aedge=pgeomSrc->aedge;
 if(pmat) {
  m=*pmat;
  for(i=0;i<pgeomDst->cpos;i++){ qword *ppos=(qword *)((int)pgeomDst->apos+(i<<4)); *ppos=Transform(&m,*ppos); }
  for(j=0;j<pgeomDst->csurf;j++) {
   struct SURF *psurf=&pgeomDst->asurf[j];
   register const struct M4 *pm __asm__("$17")=&m;
   PlaneFromNormalPos__FP6VECTORG9VU_VECTORT1(psurf,Normalize(Rotate(pm,psurf->normal)),pgeomDst->apos[psurf->ipos]);
  }
 }
}
