typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct VENTRY {short delta,pad;void *fn;};
struct P {char pad0[0xC];VENTRY *vt;char pad10[0x550];int remaining;};
struct EVENT {P *sender;char pad4[8];int kind,change;};
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
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Length(qword v){
 qword d,one,len;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(len):"j"(d));
 return len;
}
static inline qword Unit(qword v,qword len){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(len));return r;}
static inline qword Normalize(qword v,qword fallback){
 qword len=Length(v);
 if(X(len)<0.0001f)return fallback;
 return Unit(v,len);
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Zero(){qword r;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Scale(qword v,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
static inline qword Dot(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a),"j"(b));return d;}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Combine(qword a,qword x,qword b,qword y){qword r;__asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(x),"j"(b),"j"(y));return r;}
static inline qword ToVU(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword ToCPU(qword q){qword r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword CPUScalar(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline float Random(const float *range){return func_0011D448(range[0],range[1]);}
static inline void AddTo(P *p,int get,int set,const U &delta){
 VENTRY *vt=p->vt;
 VENTRY *write=&vt[set];
 void *receiver=(char*)p+write->delta;
 qword original=((qword(*)(void*))vt[get].fn)((char*)p+vt[get].delta);
 qword value=Add(ToVU(original),delta.q);
 ((void(*)(void*,qword))write->fn)(receiver,value);
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
    qword zero=Zero();
    linear.q=zero;
    angular.q=ToCPU(zero);
    switch(event->kind){
    case 0x100:{
        float angle=func_0011D448(-3.14159274f,3.14159274f);
        float horizontal=Random(D_002C21D0);
        float vertical=Random(D_002C21D8);
        linear.q=func_0011E1A0(angle,horizontal,vertical);
        qword k=Scalar(Random(D_002C21E0));
        scalar.q=k;
        angular.q=Scale(Normalize(Cross(D_002A2DC0,linear.q),D_002A2DA0),k);
        break;
    }
    case 0x1000:{
        U direction,first,second,side,position;
        position.q=ToVU(func_001A62E8(p));
        qword other=ToVU(func_001A62E8(event->sender));
        qword delta=Sub(position.q,other);
        direction.q=Normalize(Sub(delta,Scale(D_002A2DC0,Dot(delta,D_002A2DC0))),D_002A2DA0);
        first.q=CPUScalar(Random(D_002C21E8));
        qword k=Scalar(Random(D_002C21F0));
        scalar.q=k;
        linear.q=Combine(direction.q,first.q,D_002A2DC0,k);
        second.q=CPUScalar(Random(D_002C21F8));
        side.q=Cross(D_002A2DC0,direction.q);
        k=Scalar(Random(D_002C2200));
        scalar.q=k;
        angular.q=Combine(side.q,second.q,D_002A2DC0,k);
        break;
    }
    }
    AddTo(p,33,35,linear);
    AddTo(p,34,36,angular);
    return 1;
}
