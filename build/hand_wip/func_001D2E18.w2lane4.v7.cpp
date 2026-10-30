typedef int qword __attribute__((mode(TI)));
struct VV {qword q;VV(){}VV(const qword &v){q=v;}operator qword() const {return q;}};
union U {qword q;float f[4];unsigned int bits[4];};
struct M3 {U rows[3];};
struct M4 {M3 basis;U position;};
struct MOTION {M4 local,world;char pad80[0x20];MOTION *space;char padA4[0xC];U velocity;char padC0[0x30];U acceleration;};
struct PHYSICS {char pad0[0x28];float inertia;char pad2C[0xA4];float mass;};
struct CONTACT {char pad0[0x10];U point;char pad20[0x24];MOTION *motion;char pad48[0x48];float depth;char pad94[0x18];CONTACT *next;};
struct ENTRY {int id;void *node;CONTACT *contacts;char padC[0x18];float minimum,maximum;char pad2C[0x34];};
struct POLY {float a,b,c;};
struct LIMITS {float low,high;};
struct P {char pad0[0x58];MOTION *primary,*secondary,*space;char pad64[0x84];PHYSICS *physics;char padEC[0xA4];int count;char pad194[0xC];ENTRY entries[8];float width;char pad4A4[0x78];float slip;POLY traction;int unused52C;LIMITS limits;float reverseLimit,contactScale;char pad540[0x10];float drive,turn,acceleration;char pad55C[0x64];float lastCorrection;};
struct CLOCK {float time,dt;};
union PHASE {M3 rotation;struct {U acceleration,world,limited;} impulse;};
struct CONTROL {U scalar,velocity,localVelocity,torque,worldTorque;M3 basis;U desired;PHASE phase;U dt;};
union WORK {M3 reset;CONTROL control;};
extern CLOCK D_002DDED0;
extern const qword D_002A2DC0,D_002A2DD0;
extern POLY D_002C2100,D_002C2120,D_002C2130;
extern float D_002C2110,D_002C2114,D_002C2140,D_002C2144,D_002C2148;
extern "C" {
void func_001F9B20(P *);
M3 *func_001A6318(P *);
void func_0011B938(const M3 *,M3 *,M3 *);
void func_001F5C30(P *,const M3 *,const POLY *,qword,const POLY *);
CONTACT *func_001D2DD0(P *,ENTRY *);
qword func_0022D348(MOTION *,MOTION *,qword);
void func_001FAB78(P *,qword,qword);
qword func_0022FCC8(MOTION *,MOTION *,qword);
float func_0011CFE0(float,float);
void func_001FAC98(P *,qword);
M3 *func_0011B500(M3 *,qword,float);
qword func_0011E9F8(float,qword);
void func_001FAC30(P *,qword);
}
static inline VV Vector(VV q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline VV ScalarBits(int b){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(b));return r;}
static inline VV TimeStep(const CLOCK &c){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(*(const int *)&c.dt));return r;}
static inline VV Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline VV Subtract(VV a,VV b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline VV Scale(VV a,VV b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline VV Offset(VV origin,VV axis,VV amount){qword r;__asm__("vadda.xyzw $ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(origin),"j"(axis),"j"(amount));return r;}
static inline float Dot(VV a,VV b){qword r,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));__asm__("mtc1 %1,%0":"=f"(f):"r"(r));return f;}
static inline VV Rotate(const M3 &m,VV v){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(v):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q));return v;}
static inline VV InverseRotate(const M3 &m,VV v){qword r=m.rows[0].q,one,d0,d1,d2;__asm__("vmul.xyzw %1,%4,%5\n\tvmaxw.xyzw %0,$vf0,$vf0w\n\tvmul.xyzw %2,%6,%5\n\tvmul.xyzw %3,%7,%5\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %4,%0,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %4,%0,%2z\n\tvaddax.z $ACC,%3,%3x\n\tvmaddy.z %4,%0,%3y":"=&j"(one),"=&j"(d0),"=&j"(d1),"=&j"(d2),"+j"(r):"j"(v),"j"(m.rows[1].q),"j"(m.rows[2].q));return r;}
static inline VV Divide(VV v,VV scalar){qword r;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(scalar),"j"(v));return r;}
static inline float Evaluate(const POLY &p,float t){return p.a+t*(p.b+t*p.c);}
static inline float Clamp(float v,float low,float high){if(v<low)return low;else if(high<v)return high;else return v;}
static inline float ClampTo(float v,const LIMITS &l){return Clamp(v,l.low,l.high);}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
extern "C" void func_001D2E18(P *p)
{
    WORK work;
    U normal,previous;
    func_001F9B20(p);
    if(D_002DDED0.time-p->lastCorrection>3.0f){
        func_0011B938(func_001A6318(p),0,&work.reset);
        func_001F5C30(p,&work.reset,&D_002C2100,D_002A2DD0,0);
    }
    M3 *rotation=&work.control.phase.rotation;
    int i=0;
    float total=0.0f;
    if(p->count>0){
    do {
        ENTRY *entry=&p->entries[i];
        CONTACT *hit=func_001D2DD0(p,entry);
        if(hit){
            qword point=hit->point.q;
            normal.q=func_001A6318(p)->rows[2].q;
            previous.q=func_0022D348(p->space,0,point);
            qword other=func_0022D348(hit->motion,0,point);
            float fraction=hit->depth/(entry->maximum-entry->minimum);
            fraction=Clamp(fraction,0.0f,1.0f);
            float velocityCurve=Evaluate(D_002C2120,fraction);
            float depthCurve=Evaluate(D_002C2130,fraction);
            float response=hit->depth*depthCurve*D_002C2114;
            response+=Dot(Subtract(Vector(other),previous.q),normal.q)*velocityCurve*D_002C2110;
            if(response<0.0f)goto contactDone;
            work.control.scalar.q=Scalar(response*p->physics->mass);
            qword force=Scale(normal.q,work.control.scalar.q);
            func_001FAB78(p,point,force);
            total+=Dot(force,normal.q);
        }
        contactDone:;
    }while(++i<p->count);
    }
    float budget=Min(D_002C2140,p->contactScale*total/p->physics->mass);
    CLOCK *clock=&D_002DDED0;
    work.control.velocity.q=ScalarBits(*(const int *)&clock->dt);
    work.control.scalar.q=Offset(p->primary->velocity.q,p->primary->acceleration.q,work.control.velocity.q);
    work.control.velocity.q=func_0022FCC8(p->primary->space,p->secondary,work.control.scalar.q);
    work.control.localVelocity.q=InverseRotate(p->secondary->local.basis,p->secondary->velocity.q);
    float acceleration=D_002C2144*p->physics->mass*p->width/p->physics->inertia;
    work.control.torque.f[0]=work.control.torque.f[1]=0.0f;
    float turnImpulse=func_0011CFE0((p->turn-work.control.localVelocity.f[2])/clock->dt,acceleration*budget);
    work.control.torque.f[2]=turnImpulse;
    work.control.worldTorque.q=Rotate(p->secondary->world.basis,work.control.torque.q);
    budget-=Abs(D_002C2148*turnImpulse/acceleration);
    func_001FAC98(p,work.control.worldTorque.q);
    float dt=clock->dt;
    func_0011B500(rotation,D_002A2DC0,(work.control.localVelocity.f[2]+work.control.torque.f[2]*(dt*0.5f))*dt);
    work.control.desired.f[0]=p->acceleration*p->drive;
    work.control.desired.f[1]=work.control.desired.f[2]=0.0f;
    work.control.basis=work.control.phase.rotation;
    work.control.desired.q=Rotate(work.control.basis,work.control.desired.q);
    float fraction=work.control.velocity.f[0]/p->slip;
    float minimum,maximum;
    if(0.0f<=p->drive){
        minimum=-p->reverseLimit;
        maximum=ClampTo(Evaluate(p->traction,Clamp(fraction,0.0f,1.0f)),p->limits);
    }else{
        minimum=-ClampTo(Evaluate(p->traction,Clamp(-fraction,0.0f,1.0f)),p->limits);
        maximum=p->reverseLimit;
    }
    work.control.dt.q=TimeStep(D_002DDED0);
    work.control.phase.impulse.acceleration.q=Divide(Subtract(work.control.desired.q,work.control.velocity.q),work.control.dt.q);
    work.control.phase.impulse.acceleration.bits[2]=0;
    work.control.phase.impulse.acceleration.f[0]=Clamp(work.control.phase.impulse.acceleration.f[0],minimum,maximum);
    work.control.phase.impulse.limited.q=func_0011E9F8(budget,work.control.phase.impulse.acceleration.q);
    work.control.phase.impulse.world.q=func_0022FCC8(p->secondary,0,work.control.phase.impulse.limited.q);
    func_001FAC30(p,work.control.phase.impulse.world.q);
}
