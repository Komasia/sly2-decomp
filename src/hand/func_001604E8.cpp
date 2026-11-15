typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { qword r[3]; };
struct M4 { U r[4]; };
/* the target (its world matrix at +0x40) and the linked object (its local matrix, its parent, its update stamp) */
struct XFTARGET { char pad[0x40]; M4 matWorld; };
struct XFLINKED { M4 matLocal; char pad[0xA0-0x40]; XFTARGET *paloParent; int nStamp; };
struct ALOLINK { XFTARGET *ploTarget; XFLINKED *plo; int fPosition, fRotation; };   /* SafeHouse lo.h ALOLINK */
struct SW { char pad[0x3D58]; int nStampXf; };
extern SW g_sw;
extern "C" M4 InverseAffineMatrix4(const M4 *m) asm("InverseAffineMatrix4__FP7MATRIX4");
extern "C" M3 InverseMatrix3(const M3 *m) asm("InverseMatrix3__FP7MATRIX3");
extern "C" void NormalizeRotateMatrix3(M3 *m) asm("NormalizeRotateMatrix3__FP7MATRIX3");
extern "C" qword *func_00256D18(qword *pv,qword v);   /* store a VECTOR */
static inline qword Transform(const M4 &m,qword p) {
 qword r;
 __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
 :"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(p));return r;
}
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
 qword a0=a.r[0],a1=a.r[1],a2=a.r[2];
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0]));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1]));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2]));
}
/* UpdateXfLink: transform mode 15: the linked object takes the target's world position and / or rotation,
 * expressed in its parent's frame, and gets a new update stamp. */
// name: SafeHouse port (UpdateXfLink)
extern "C" void UpdateXfLink__FP3ALOPv(void *,ALOLINK *palolink)
{
 M3 mat;
 if(palolink->fPosition) {
  M4 matInv=InverseAffineMatrix4(&palolink->plo->paloParent->matWorld);
  XFLINKED *plo=palolink->plo;
  func_00256D18(&plo->matLocal.r[3].q,Transform(matInv,palolink->ploTarget->matWorld.r[3].q));
  plo->matLocal.r[3].f[3]=1.0f;
 }
 if(palolink->fRotation) {
  mat=Mul(InverseMatrix3((M3 *)&palolink->plo->paloParent->matWorld),*(M3 *)&palolink->ploTarget->matWorld);
  NormalizeRotateMatrix3(&mat);
  XFLINKED *plo=palolink->plo;
  *(M3 *)&plo->matLocal=mat;
  plo->matLocal.r[0].i[3]=0;
  plo->matLocal.r[1].i[3]=0;
  plo->matLocal.r[2].i[3]=0;
 }
 int nStamp=++g_sw.nStampXf;
 palolink->plo->nStamp=nStamp;
}
