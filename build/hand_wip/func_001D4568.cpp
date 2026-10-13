typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
union FN {qword (*get)(void *);void (*set)(void *,qword);};
struct VENTRY {short delta,pad;FN fn;};
struct P {char pad0[0xC];VENTRY *vt;char pad10[0x550];int remaining;};
struct EVENT {P *sender;char pad4[8];int kind,change;char pad14[0x30];int enabled;};
extern const qword D_002A2DA0,D_002A2DC0;
extern float D_002C21D0[2],D_002C21D8[2],D_002C21E0[2],D_002C21E8[2],D_002C21F0[2],D_002C21F8[2],D_002C2200[2];
extern "C" {
int func_001F7588(P *,EVENT *);
void func_001D4C88(P *);
void func_001D4940(P *,int);
float func_0011D448(float,float);
qword func_0011E1A0(float,float,float);
qword func_001A62E8(P *);
}
static inline void StoreCPU(U *p,qword q){__asm__("sq %1,%0":"=m"(*p):"r"(q));}
static inline qword Vector(qword q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword CPUScalar(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Zero(){qword r;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Dot(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a),"j"(b));return d;}
static inline qword Length(qword v){qword d=Dot(v,v);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;}
static inline float FloatWord(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Normal(qword v,qword fallback){qword length=Length(v);if(FloatWord(length)<0.0001f)return fallback;qword r;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(length),"j"(v));return r;}
static inline qword Combine(qword a,qword x,qword b,qword y){qword r;__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(x),"j"(b),"j"(y));return r;}
static inline float Random(const float *range){return func_0011D448(range[0],range[1]);}
static inline void AddVelocity(P *p,int getter,int setter,const U &delta){
    VENTRY *vt=p->vt;
    VENTRY *write=&vt[setter];
    void *receiver=(char *)p+write->delta;
    qword original=vt[getter].fn.get((char *)p+vt[getter].delta);
    write->fn.set(receiver,Add(Vector(original),delta.q));
}
extern "C" int func_001D4568(P *p,EVENT *event)
{
    U scalar,linear,angular;
    if(!func_001F7588(p,event))return 0;
    int remaining=p->remaining+event->change;
    if(remaining<0)remaining=0;
    p->remaining=remaining;
    func_001D4C88(p);
    if(!p->remaining)func_001D4940(p,3);
    linear.q=Zero();
    StoreCPU(&angular,linear.q);
    switch(event->kind){
    case 0x100:{
        float angle=func_0011D448(-3.14159274f,3.14159274f);
        float horizontal=Random(D_002C21D0);
        float vertical=Random(D_002C21D8);
        linear.q=func_0011E1A0(angle,horizontal,vertical);
        scalar.q=Scalar(Random(D_002C21E0));
        angular.q=Scale(Normal(Cross(D_002A2DC0,linear.q),D_002A2DA0),scalar.q);
        break;
    }
    case 0x1000:{
        U direction,first,second,side,position;
        position.q=Vector(func_001A62E8(p));
        qword other=func_001A62E8(event->sender);
        qword delta=Subtract(position.q,Vector(other));
        const qword *up=&D_002A2DC0;
        direction.q=Normal(Subtract(delta,Scale(*up,Dot(delta,*up))),D_002A2DA0);
        first.q=CPUScalar(Random(D_002C21E8));
        scalar.q=Scalar(Random(D_002C21F0));
        linear.q=Combine(direction.q,first.q,*up,scalar.q);
        second.q=CPUScalar(Random(D_002C21F8));
        side.q=Cross(*up,direction.q);
        scalar.q=Scalar(Random(D_002C2200));
        angular.q=Combine(side.q,second.q,*up,scalar.q);
        break;
    }
    }
    AddVelocity(p,33,35,linear);
    AddVelocity(p,34,36,angular);
    return 1;
}
