typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union U { qword q; float f; };
struct G { char pad[0x60]; M3 mat; };
struct SPIN { char pad[0x40]; qword axis; };
struct S {char pad[0x14];float start,duration;char pad1C[0x40-0x1C];M3 mat;char pad70[0xF0-0x70];SPIN *spin;char padF4[0x100-0xF4];qword pos;};
extern G g_cm;
extern struct CLOCK {float t,dt;} g_clock;
extern "C" {
qword ConvertCmScreenToWorld(G*,qword) asm("ConvertCmScreenToWorld__FP2CMG9VU_VECTOR");
M3 MulMat3TransposeA(const M3&,const M3&) asm("MulMat3TransposeA__FP7MATRIX3T0Pv");
void DecomposeRotateMatrixRad(M3*,float*,qword*) asm("DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR");
M3 BuildRotateMatrixAxis(qword,float) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
int CollectRipDraws(S*,qword,const M3&) asm("CollectRipDraws__FP2CMG9VU_VECTORPv");
void func_001D0630(S*);
}
static inline M3 Mul(const M3 &a,const M3 &b) return r {
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[1]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[2]));
}
void func_001D0630(S *p) {
 M3 camera,fade,spin,render;
 U axis;float angle;
 G *pg=&g_cm;
 qword view=ConvertCmScreenToWorld(pg,p->pos);
 camera=MulMat3TransposeA(p->mat,pg->mat);
 DecomposeRotateMatrixRad(&camera,&angle,&axis.q);
 float t=(g_clock.t-p->start)/p->duration;
 fade=BuildRotateMatrixAxis(axis.q,angle*t);
 spin=BuildRotateMatrixAxis(p->spin->axis,(t+t)*3.14159274f);
 render=Mul(Mul(fade,spin),p->mat);
 CollectRipDraws(p,view,render);
}
