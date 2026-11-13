// Update zoom from target bounds or controller input.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct M3 {qword r[3];};
struct M4 {qword r[4];};
struct RANGE {float lo,hi;};
struct SMP {float a,b,c,d;};
struct SHAPE {char pad[0x30];float radius;};
struct O {char pad[0x60];void *component;char pad64[0x88];SHAPE *shape;};
struct CONTROL {char pad[0x24];float zoom;};
struct S {char pad[0x150];CONTROL *control;char pad154[0x2C];O *target;int aim,follow;char pad18c[0x20];RANGE range;float blend,velocity,strength;};
struct CLOCK {float t,dt;};
extern "C" {
qword PosOfLo(void *) asm("PosOfLo__FP2LO");
M3 *MatJtLo(void *) asm("MatJtLo__FP2LO");
void func_002309E8(void *,void *,M4 *,M4 *,float);
float atanf(float) asm("atanf");
float GLimitLm(void *,float) asm("GLimitLm__FP2LMf");
float GSmoothA(float,float,float,float,SMP *,float *) asm("GSmoothA__FffffP4SMPAPf");
extern CLOCK g_clock;
extern float D_002DDF7C;
extern char g_lmZeroOne[];
extern float D_002C4418[2],D_002C4420[3];
extern SMP D_002A97B0;
}
static inline qword LoadVF(const qword &q){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(q));return r;}
static inline qword ToVF(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword Difference(qword b,qword a){qword r;__asm__("vsub.xyzw %0,%2,%1":"=j"(r):"j"(b),"j"(a));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(qword d){qword r,one;float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(d));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));
    __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;}
static inline float OffsetLength(qword d){qword r,one;register int bits __asm__("$3");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(d));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));
    __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(r));union {int i;float f;} value;value.i=(int)bits;return value.f;}
static inline qword InverseRotate(const M3 &m,qword v){qword r=m.r[0],one,a,b,c;
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y":"+j"(r),"=&j"(one),"=&j"(a),"=&j"(b),"=&j"(c):"j"(m.r[1]),"j"(m.r[2]),"j"(v));return r;}
static inline float Max(float a,float b){return a>b?a:b;}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Abs(float x){return __builtin_fabsf(x);}
static inline float Fraction(RANGE *range,float f){if(range->lo==range->hi)return 0.0f;return (f-range->lo)/(range->hi-range->lo);}
static inline float Blend(RANGE *range,float u){return (1.0f-u)*range->lo+u*range->hi;}
// name: SafeHouse port (UpdateTurretZoom)
extern "C" void UpdateTurretZoom__FP3ALO(S *p){
    if(p->target && p->follow){
        M4 m;
        V future,offset,local,swapped;
        SMP spring;
        V saved;
        V scratch;
        float radius=p->target->shape?p->target->shape->radius:0.0f;
        scratch.q=ToVF(PosOfLo(p));
        float angle=atanf(radius/(Length(Sub(scratch.q,PosOfLo(p->target)))*0.5f));
        angle=angle+angle;
        CLOCK *clock=&g_clock;
        angle=Max(angle,p->range.lo);
        func_002309E8(p->target->component,0,&m,0,clock->dt);
        scratch.q=LoadVF(m.r[3]);future.q=scratch.q;
        offset.q=Sub(scratch.q,PosOfLo(p->target));
        float extent=radius+OffsetLength(offset.q);
        saved.q=future.q;
        local.q=Difference(PosOfLo(p),saved.q);
        local.q=InverseRotate(*MatJtLo(p),local.q);
        swapped.f[0]=-local.f[1];swapped.f[1]=local.f[2];swapped.f[2]=local.f[0];
        float desired;
        if(local.f[0]>0.0001f){
            float horizontal=atanf((Abs(swapped.f[0])+extent)/(swapped.f[2]*D_002DDF7C));
            horizontal=horizontal+horizontal;
            float vertical=atanf((Abs(swapped.f[1])+extent)/swapped.f[2]);
            vertical=vertical+vertical;
            desired=Min(Max(horizontal,vertical),p->range.hi);
        }else desired=p->range.hi;
        desired=Max(desired,angle);
        float target=GLimitLm(g_lmZeroOne,1.0f-Fraction(&p->range,desired));
        float delta=Abs(target-p->blend);
        spring=D_002A97B0;
        float rate=(1.0f-delta)*D_002C4418[0]+delta*D_002C4418[1];
        spring.d*=rate;spring.a*=rate;spring.b*=rate;
        p->blend=GSmoothA(p->blend,p->velocity,target,g_clock.dt,&spring,&p->velocity);
    }else {
        if(p->control){
            float blend=p->blend,zoom=p->control->zoom;
            p->velocity=(D_002C4420[0]+blend*(D_002C4420[1]+blend*D_002C4420[2]))*zoom*Abs(zoom);
            p->blend=GLimitLm(g_lmZeroOne,blend+p->velocity*g_clock.dt);
        }
    }
    p->strength=Blend(&p->range,1.0f-p->blend);
}
