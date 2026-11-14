typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3(){} M3(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;} };
struct LO { M3 matrix; U position; M3 rotation; char pad[0x24]; int kind; short state; char pad9A[6]; LO *parent; int stamp; char padA8[8]; U velocity; };
struct VTE { short delta,pad; qword (*fn)(void *); };
struct P { char pad[0xC]; VTE *vt; char pad10[0x4C]; LO *object; };
extern "C" M3 InverseMatrix3(const M3 *) asm("InverseMatrix3__FP7MATRIX3");
extern "C" void NormalizeRotateMatrix3__FP7MATRIX3(M3 *);
extern "C" void *s1_memset(void *,int,int) asm("memset");
extern "C" void HoldXfMode(P *,LO *);
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
extern "C" int FXfmMoving(int);
extern "C" void SetXfMode(P *,LO *,int) asm("SetXfMode__FP3ALOP2XFi");
extern "C" qword VecConvertXfs(LO *,LO *,qword) asm("VecConvertXfs__FP2XFT0G9VU_VECTOR");
extern "C" void MarkAloDirty(P *) asm("MarkAloDirty__FP3ALO");
extern "C" void WakeAlo(P *) asm("WakeAlo__FP3ALO");
extern "C" void SetAloIced(P *,long) asm("SetAloIced__FP3ALOl");
static inline qword Sub(qword a,const qword *pb) { qword r,b; __asm__("lqc2 %1,%3\n\tvsub.xyzw %0,%2,%1":"=j"(r),"=&j"(b):"j"(a),"m"(*pb));return r; }
static inline qword Transform(const M3 &m,qword v) { qword r;
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;
}
static inline void Clear(U *v) { v->i[2]=0;v->i[1]=0;v->i[0]=0; }
// name: SafeHouse port (SetAloAngVelocityToLoad)
extern "C" void SetAloAngVelocityToLoad__FP3ALOG9VU_VECTOR(P *p,qword position)
{
    LO *object=p->object;
    if(!object || object->kind!=6)return;
    if(!FXfmMoving(object->state))SetXfMode(p,object,1);
    const M3 *rotation=&object->rotation;
    Clear(&object->velocity);
    M3 normalized;
    qword origin=p->vt[34].fn((char *)p+p->vt[34].delta);
    normalized=*rotation;
    NormalizeRotateMatrix3__FP7MATRIX3(&normalized);
    M3 relative=Mul(*rotation,InverseMatrix3(&normalized));
    object->velocity.q=VecConvertXfs(0,object->parent,Transform(relative,Sub(position,&origin)));
    HoldXfMode(p,object);
    MarkAloDirty(p);
    WakeAlo(p);
    SetAloIced(p,0);
}
