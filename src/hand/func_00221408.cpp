// Project a world point into a path basis and return the path direction.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct S { char pad[0x10C]; void *curve; char pad1[0x12C-0x110]; int arc; char pad2[0x140-0x130]; float time; char pad3[0x150-0x144]; qword origin; float radius; };
extern "C" {
void EvalCrvS(void *, float, qword *, qword *) asm("EvalCrvS__FP3CRVfP6VECTORT2");
M3 BuildLookAtMatrix(qword,qword) asm("BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1");
qword SetVectorCylind(float,float,float) asm("SetVectorCylind__Ffff");
M3 *MatJtLo(struct S *) asm("MatJtLo__FP2LO");
qword ConvertPos(void *,void *,qword) asm("ConvertPos__FP2LOT0G9VU_VECTOR");
}
extern qword g_normalZ;
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b));return r; }
static inline qword Add(qword a,qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b));return r; }
static inline qword Cross(qword a,qword b) { qword r; __asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "0"(a),"j"(b));return r; }
// The VU helper receives vf1 and reuses its length temporary for the result.
static inline qword Normalize(qword arg) { qword d,one,r;
    register qword v __asm__("vf1") = arg;
    qword len;

__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(len),"=&j"(one) : "j"(v));
__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(len) : "j"(len));
__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q" : "=j"(r) : "j"(v),"0"(len));
return r; }

static inline qword InverseRotate(const M3 &m, qword v) {
    qword one,a,b,c;
    __asm__("vmul.xyzw %2,%5,%0\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%0\n\tvmul.xyzw %4,%7,%0\n\tvadday.x ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y" : "+j"(v),"=&j"(one),"=&j"(a),"=&j"(b),"=&j"(c) : "j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]));
    return v;
}
// name: SafeHouse port (ConvertZonePos)
extern "C" void ConvertZonePos__FP6ZONECMG9VU_VECTORP6VECTORT2(S *p,qword v,qword *out,qword *normal) {
    U pos;
    M3 m;
    if(p->curve) {
        EvalCrvS(p->curve,p->time,&pos.q,normal);
        m=BuildLookAtMatrix(*normal,g_normalZ);
        *out=InverseRotate(m,Sub(v,pos.q));
    } else if(p->arc) {
        U a;
        a.q=SetVectorCylind(p->time/p->radius,p->radius,0.0f);
        pos.q=Add(p->origin,a.q);
        *normal=Normalize(Cross(g_normalZ,a.q));
        m=BuildLookAtMatrix(*normal,g_normalZ);
        *out=InverseRotate(m,Sub(v,pos.q));
    } else {
        *normal=Normalize(MatJtLo(p)->r[0]);
        *out=ConvertPos(0,p,v);
    }
}
