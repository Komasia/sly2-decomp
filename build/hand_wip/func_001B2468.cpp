/* WIP 121/151: compare/copy scheduling and VU allocation remain. */
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct V {float x,y,z,w;}__attribute__((aligned(16)));
struct VT {short delta,pad;void*fn;};
struct P {char pad[0xC];VT*vt;char pad10[0x1E8-0x10];int disabled;char pad1EC[0x278-0x1EC];float deadline;int pad27C;qword targetVelocity;};
struct CLOCK {float t,dt;};
extern "C" {
extern CLOCK D_002DDED0;
extern qword D_002A2DD0;
V func_001B2398(P*,float);
qword func_001A62E8(P*);
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,qword*);
void func_001FAC30(P*,qword);
}
int FFloatsNear(float,float,float)__asm__("FFloatsNear__Ffff");
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){qword b;float f;__asm__("prot3w %0,%1":"=r"(b):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(b));return f;}
static inline float Z(qword q){qword b;float f;__asm__("pextuw %0,$zero,%1":"=r"(b):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(b));return f;}
static inline int Equal(qword a,qword b){return FFloatsNear(X(a),X(b),0.0001f)&&FFloatsNear(Y(a),Y(b),0.0001f)&&FFloatsNear(Z(a),Z(b),0.0001f);}
static inline qword Velocity(P*p){VT*vt=p->vt;return ((qword(*)(void*))vt[33].fn)((char*)p+vt[33].delta);}
static inline float Max(float a,float b){return a>b?a:b;}
static inline float Min(float a,float b){return a<b?a:b;}
static inline qword Scalar(float f){qword b;__asm__("mfc1 %0,%1":"=r"(b):"f"(f));return b;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Combination(qword a,qword b,qword sa,qword sb){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(sa),"j"(sb));return r;}
static inline qword ScalarBits(int b){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(b));return r;}
static inline qword Divide(qword a,qword s){qword r;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(s),"j"(a));return r;}
extern "C" void func_001B2468(P*p){
    if(p->disabled)return;
    float remaining=Max(0.0f,p->deadline-D_002DDED0.t)+D_002DDED0.dt;
    V output=func_001B2398(p,Min(remaining,0.5f));
    U integrated,step;
    V destination=output;
    U scale,delta,negative,copy;
    int stationary=Equal(D_002A2DD0,p->targetVelocity);
    if(stationary){
        scale.q=Scalar(1.5f/remaining);
        integrated=scale;
        delta.q=Sub(*(qword*)&destination,func_001A62E8(p));
        negative.q=Scalar(-0.5f);
        integrated=negative;
        *(qword*)&output=Combination(delta.q,Velocity(p),scale.q,negative.q);
    }else *(qword*)&output=p->targetVelocity;
    float frameDt=D_002DDED0.dt;
    qword position=func_001A62E8(p);
    qword velocity=Velocity(p);
    func_00117120(remaining,frameDt,1.0f,position,velocity,*(qword*)&destination,*(qword*)&output,0,&integrated.q,0);
    copy=integrated;
    qword current=Velocity(p);
    qword dt=ScalarBits(*(int*)&D_002DDED0.dt);
    qword difference=Sub(copy.q,current);
    step.q=dt;
    func_001FAC30(p,Divide(difference,dt));
}
