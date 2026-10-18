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
static inline void StoreVU(U*p,qword q){__asm__("sqc2 %1,%0":"=m"(*p):"j"(q));}
static inline qword Scalar4(float f){register qword bits __asm__("$3"),r __asm__("vf4");__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2 %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword CPUScalar(float f){register qword r __asm__("$3");__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ScaleFirst(qword normal,qword scalar){register qword n __asm__("vf1")=normal,s __asm__("vf4")=scalar,result __asm__("vf2");__asm__("vmulx.xyzw %0,%1,%2x":"=j"(result):"j"(n),"j"(s));return result;}
static inline qword CrossFirst(qword a,qword b){register qword up __asm__("vf1")=a,velocity __asm__("vf2")=b,r __asm__("vf3");__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(up),"j"(velocity));return r;}
static inline qword CrossRight(qword a,qword b){register qword up __asm__("vf1")=a,dir __asm__("vf2")=b;__asm__("vopmula.xyz ACC,%1,%0\n\tvopmsub.xyz %0,%0,%1":"+j"(dir):"j"(up));return dir;}
static inline qword Length(qword v){register qword d __asm__("vf1");register qword one __asm__("vf2");__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;}

static inline float FloatWord(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Normal(qword v,qword fallback){register qword length __asm__("vf1")=Length(v);register qword result __asm__("vf1");if(FloatWord(length)<0.0001f)result=fallback;else __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(result):"j"(length),"j"(v));return result;}
static inline void NormalInto(U*home,qword v,qword fallback){register qword length __asm__("vf1")=Length(v);if(FloatWord(length)<0.0001f)home->q=fallback;else {register qword r __asm__("vf2");__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(length),"j"(v));StoreVU(home,r);}}
static inline float Random(const float *range){return func_0011D448(range[0],range[1]);}
static inline void AddLinear(P*p,const U&delta){
 VENTRY*vt=p->vt;
 VENTRY*write=&vt[35];
 void*receiver=(char*)p+write->delta;
 qword original=vt[33].fn.get((char*)p+vt[33].delta);
 register qword value __asm__("vf1"),change __asm__("vf2");
 register void*calleeReceiver __asm__("$4");register void(*set)(void*,qword) __asm__("$6");
 __asm__("lqc2 %0,%4\n\tdaddu %1,%5,$zero\n\tqmtc2.ni %6,%2\n\tlw %3,%7"
 :"=j"(change),"=&r"(calleeReceiver),"=j"(value),"=r"(set)
 :"m"(delta.q),"r"(receiver),"r"(original),"m"(write->fn.set));
 __asm__("vadd.xyzw %0,%0,%1":"+j"(value):"j"(change));
 set(calleeReceiver,value);
}
static inline void AddAngular(P*p,const U&delta){
 VENTRY*vt=p->vt;
 VENTRY*write=&vt[36];
 void*receiver=(char*)p+write->delta;
 qword original=vt[34].fn.get((char*)p+vt[34].delta);
 register qword value __asm__("vf3"),change __asm__("vf4");
 register void*calleeReceiver __asm__("$4");register void(*set)(void*,qword) __asm__("$3");
 __asm__("qmtc2.ni %4,%0\n\tlw %1,%5\n\tlqc2 %2,%6\n\tdaddu %3,%7,$zero"
 :"=j"(value),"=&r"(set),"=j"(change),"=r"(calleeReceiver)
 :"r"(original),"m"(write->fn.set),"m"(delta.q),"r"(receiver));
 __asm__("vadd.xyzw %0,%0,%1":"+j"(value):"j"(change));
 set(calleeReceiver,value);
}
static inline qword Scalar2(float f){register qword bits __asm__("$3"),r __asm__("vf2");__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword LinearResponse(const U&direction,const U&first,const qword*up,qword scalar){
 register qword axis __asm__("vf1")=*up,normal __asm__("vf4")=direction.q,weight __asm__("vf3")=first.q,vertical __asm__("vf2")=scalar,result __asm__("vf3");
 __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(result):"j"(normal),"j"(weight),"j"(axis),"j"(vertical));return result;
}
static inline qword AngularInputs(float f,const qword*up,qword&axisResult){
 register qword bits __asm__("$3"),axis __asm__("vf2"),scalar __asm__("vf1");
 __asm__("mfc1 %0,%3\n\tlqc2 %1,%4\n\tqmtc2.ni %0,%2":"=&r"(bits),"=j"(axis),"=j"(scalar):"f"(f),"m"(*up));axisResult=axis;return scalar;
}
static inline qword AngularResponse(const U&side,const U&second,qword up,qword scalar){
 register qword axis __asm__("vf2")=up,normal __asm__("vf4"),weight __asm__("vf3"),vertical __asm__("vf1")=scalar,result __asm__("vf3");
 __asm__("lqc2 %0,%2\n\tlqc2 %1,%3":"=j"(weight),"=j"(normal):"m"(second.q),"m"(side.q));
 __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(result):"j"(normal),"j"(weight),"j"(axis),"j"(vertical));return result;
}
struct UP_PAGE {char pad2DC0[0x2DC0];qword up;};
static inline qword Position3(qword value){register qword r __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));return r;}
static inline qword PositionDeltaAndUpPage(const U&home,qword other,const UP_PAGE*&page,const qword*&projectionUp){
 register const UP_PAGE*saved __asm__("$16");register const qword*address __asm__("$3");
 register qword b __asm__("vf4"),a __asm__("vf3");
 __asm__("lui %0,0x2a\n\tqmtc2.ni %4,%1\n\tdaddu %2,%0,$zero\n\tlqc2 %3,%5\n\taddiu %0,%0,0x2dc0\n\tvsub.xyzw %3,%3,%1"
 :"=&r"(address),"=j"(b),"=&r"(saved),"=j"(a):"r"(other),"m"(home.q));
 page=saved;projectionUp=address;return a;
}
static inline qword ReadUp1(const qword*address){register qword r __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(r):"m"(*address));return r;}
static inline qword Perpendicular3(qword value,qword up){
 register qword delta __asm__("vf3")=value,axis __asm__("vf1")=up,projection __asm__("vf2"),one __asm__("vf4");
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(projection),"=&j"(one):"j"(delta),"j"(axis));
 __asm__("vmulx.xyzw %0,%1,%0x":"+j"(projection):"j"(axis));
 __asm__("vsub.xyzw %0,%0,%1":"+j"(delta):"j"(projection));return delta;
}
static inline const qword*UpAfterNormal(const UP_PAGE*page){register const qword*up __asm__("$16");__asm__("addiu %0,%1,0x2dc0":"=r"(up):"r"(page));return up;}
static inline int InitializeResponses(U&linear,U&angular,const EVENT*event){
 register qword zero __asm__("vf1");register int kind __asm__("$3");
 __asm__("vsub.xyzw %0,$vf0,$vf0\n\tsqc2 %0,%2\n\tqmfc2.ni $2,%0\n\tlw %1,%4\n\tsq $2,%3"
 :"=j"(zero),"=&r"(kind),"=m"(linear.q),"=m"(angular.q):"m"(event->kind):"$2");return kind;
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
    int kind=InitializeResponses(linear,angular,event);
    switch(kind){
    case 0x100:{
        float angle=func_0011D448(-3.14159274f,3.14159274f);
        float horizontal=Random(D_002C21D0);
        float vertical=Random(D_002C21D8);
        linear.q=func_0011E1A0(angle,horizontal,vertical);
        scalar.q=Scalar4(Random(D_002C21E0));
        register qword strength __asm__("vf4")=scalar.q;
        angular.q=ScaleFirst(Normal(CrossFirst(D_002A2DC0,linear.q),D_002A2DA0),strength);
        break;
    }
    case 0x1000:{
        U direction,first,second,side,position;
        position.q=Position3(func_001A62E8(p));
        qword other=func_001A62E8(event->sender);
        const UP_PAGE*upPage;const qword*projectionUp;
        qword delta=PositionDeltaAndUpPage(position,other,upPage,projectionUp);
        NormalInto(&direction,Perpendicular3(delta,ReadUp1(projectionUp)),D_002A2DA0);
        const qword*up=UpAfterNormal(upPage);
        StoreCPU(&first,CPUScalar(Random(D_002C21E8)));scalar.q=first.q;
        qword verticalResponse=Scalar2(Random(D_002C21F0));
        linear.q=LinearResponse(direction,first,up,verticalResponse);
        scalar.q=verticalResponse;
        StoreCPU(&second,CPUScalar(Random(D_002C21F8)));scalar.q=second.q;
        side.q=CrossRight(*up,direction.q);
        qword angularAxis;
        scalar.q=AngularInputs(Random(D_002C2200),up,angularAxis);
        angular.q=AngularResponse(side,second,angularAxis,scalar.q);
        break;
    }
    }
    AddLinear(p,linear);
    AddAngular(p,angular);
    return 1;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char final_driver_layout[(OFF(P,vt)==0xC && OFF(P,remaining)==0x560 && OFF(EVENT,sender)==0 && OFF(EVENT,kind)==0xC && OFF(EVENT,change)==0x10 && OFF(EVENT,enabled)==0x44 && OFF(VENTRY,delta)==0 && OFF(VENTRY,fn)==4 && sizeof(U)==16 && sizeof(VENTRY)==8 && sizeof(FN)==4 && sizeof(qword)==16 && __alignof__(U)==16 && __alignof__(qword)==16 && sizeof(float)==4 && sizeof(int)==4 && sizeof(P*)==4 && sizeof(short)==2 && OFF(U,q)==0 && OFF(U,f)==0 && OFF(UP_PAGE,up)==0x2DC0 && sizeof(UP_PAGE)==0x2DD0 && __alignof__(UP_PAGE)==16 && sizeof(EVENT*)==4 && sizeof(UP_PAGE*)==4 && sizeof(void(*)(void*,qword))==4 && 33*sizeof(VENTRY)==0x108 && 34*sizeof(VENTRY)==0x110 && 35*sizeof(VENTRY)==0x118 && 36*sizeof(VENTRY)==0x120)?1:-1];
