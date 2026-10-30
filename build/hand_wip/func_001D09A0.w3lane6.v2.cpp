typedef int qword __attribute__((mode(TI)));
struct M3{qword r[3];};
struct P{char pad0[0x40];M3 matrix;char pad70[0x20];qword vel;char padA0[0x24];float drag;};
struct CLOCK{float time,dt;};
extern "C"{
extern CLOCK D_002DDED0;
extern float D_002C2010[3],D_002C2020[2],D_002C2028,D_002C202C;
extern qword D_002A2DA0;
M3 func_0011B500(qword,float);
float func_0011E290(qword,qword,qword*,qword*);
void func_001CF0A0(P*);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline float GClamp(float g, const float *lim)
{
    float gMin=lim[0],gMax=lim[1];
    if (g < gMin) return gMin;
    if (gMax < g) return gMax;
    return g;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline qword ToVF(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword Rot(const M3&m,qword v){qword r;__asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z":"=j"(r):"j"(v),"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]));return r;}
static inline M3 Multiply(const M3&a,const M3&b) return r {
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[1]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[2]));
}
static inline qword LengthVec(qword a){
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(l):"j"(d));
    return l;
}
static inline qword Normalize(qword a, qword l){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(l),"j"(l));return r;}
static inline float GetX(qword q){float g;__asm__("mtc1 %1, %0" : "=f"(g) : "r"(q));return g;}
static inline float FloatOf(qword q){int r;float g;__asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(q));__asm__("mtc1 %1, %0" : "=f"(g) : "r"(r));return g;}
static inline qword NormalizeE(qword a, qword l, float eps){qword r;__asm__("vdiv Q,$vf0w,%2x
	vwaitq
	vmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(l),"j"(l),"f"(eps));return r;}
static inline qword NormalizeSafe(qword*pv,const qword*pfallback){float eps=0.0001f;qword v=ToVF(*pv);qword len=LengthVec(v);if(GetX(len)<eps)*pv=*pfallback;else *pv=NormalizeE(v,len,eps);return len;}
extern "C" void func_001D09A0(P*p){
 qword row0=p->matrix.r[0];
 qword axis=p->matrix.r[1];
 float g=Dot(p->vel,row0);
 float t=GClamp(D_002C2010[0]+g*(D_002C2010[1]+g*D_002C2010[2]),D_002C2020);
 M3 rot=func_0011B500(axis,t*D_002DDED0.dt);
 p->vel=Rot(rot,p->vel);
 p->matrix=Multiply(rot,p->matrix);
 float drag=p->drag;
 p->drag=0.0f;
 struct{qword par,perp;}w;
 func_0011E290(p->vel,row0,&w.par,&w.perp);
 qword len=NormalizeSafe(&w.par,&D_002A2DA0);
 float dt=D_002DDED0.dt;
 g=GetX(len);
 float along=D_002C2028+(D_002C202C*dt+1.0f)*(g-D_002C2028);
 float across=drag*dt+1.0f;
 p->vel=VecCombo(VU_FLOAT(along),VU_VECTOR(w.par),VU_FLOAT(across),VU_VECTOR(w.perp));
 func_001CF0A0(p);
 p->drag=drag;
}
