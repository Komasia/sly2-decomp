typedef int qword __attribute__((mode(TI)));
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
static inline float LoadScalar(const float *p){float f;__asm__("lw %0,%1":"=r"(f):"m"(*p));return f;}
static inline qword Vector(qword q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Offset(qword origin,qword axis,qword amount){qword r;__asm__("vadda.xyzw ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(origin),"j"(axis),"j"(amount));return r;}
static inline float Dot(qword a,qword b){qword r,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));int bits;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(r));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline qword Rotate(const M3 &m,qword v){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q),"j"(v));return r;}
static inline qword InverseRotate(const M3 &m,qword v){qword r=m.rows[0].q,d0,d1,d2,one;__asm__("vmul.xyzw %1,%0,%5\n\tvmaxw.xyzw %4,$vf0,$vf0w\n\tvmul.xyzw %2,%6,%5\n\tvmul.xyzw %3,%7,%5\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %0,%4,%1z\n\tvaddax.y ACC,%2,%2x\n\tvmaddz.y %0,%4,%2z\n\tvaddax.z ACC,%3,%3x\n\tvmaddy.z %0,%4,%3y":"+j"(r),"=&j"(d0),"=&j"(d1),"=&j"(d2),"=&j"(one):"j"(v),"j"(m.rows[1].q),"j"(m.rows[2].q));return r;}
static inline qword Divide(qword v,qword scalar){qword r;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(scalar),"j"(v));return r;}
static inline float Evaluate(const POLY &p,float t){return p.a+t*(p.b+t*p.c);}
static inline float Clamp(float v,float low,float high){if(v<low)return low;else if(high<v)return high;else return v;}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline int EntryOffset(int index)
{
 register int stride __asm__("$2")=sizeof(ENTRY);
 int offset;
 __asm__("mult %0,%1,%2":"=r"(offset):"r"(index),"r"(stride):"hi","lo");
 return offset;
}
extern "C" void func_001D2E18(P *p)
{
    WORK work;
    U normal,previous,force;
    func_001F9B20(p);
    if(D_002DDED0.time-p->lastCorrection>3.0f){
        func_0011B938(func_001A6318(p),0,&work.reset);
        func_001F5C30(p,&work.reset,&D_002C2100,D_002A2DD0,0);
    }
    M3 *rotation=&work.control.phase.rotation;
    const LIMITS *limits=&p->limits;
    const POLY *traction=&p->traction;
    float total=0.0f;
    const POLY *velocityResponse=&D_002C2120;
    const POLY *depthResponse=&D_002C2130;
    for(int i=0;i<p->count;i++){
        ENTRY *entry=(ENTRY*)((char*)p->entries+EntryOffset(i));
        CONTACT *hit=func_001D2DD0(p,entry);
        if(hit){
            qword point=hit->point.q;
            normal.q=func_001A6318(p)->rows[2].q;
            previous.q=func_0022D348(p->space,0,point);
            qword other=func_0022D348(hit->motion,0,point);
            float fraction=Clamp(hit->depth/(entry->maximum-entry->minimum),0.0f,1.0f);
            float response=Dot(Subtract(Vector(other),previous.q),normal.q)*Evaluate(*velocityResponse,fraction)*D_002C2110;
            response+=hit->depth*Evaluate(*depthResponse,fraction)*D_002C2114;
            if(response<0.0f)goto contactDone;
            work.control.scalar.q=Scalar(response*p->physics->mass);
            force.q=Scale(normal.q,work.control.scalar.q);
            func_001FAB78(p,point,force.q);
            total+=Dot(force.q,normal.q);
        }
        contactDone:;
    }
    float budget=Min(D_002C2140,p->contactScale*total/p->physics->mass);
    work.control.velocity.q=Scalar(LoadScalar(&D_002DDED0.dt));
    MOTION *primary=p->primary;
    work.control.scalar.q=Offset(primary->velocity.q,primary->acceleration.q,work.control.velocity.q);
    work.control.velocity.q=func_0022FCC8(primary->space,p->secondary,work.control.scalar.q);
    MOTION *secondary=p->secondary;
    work.control.localVelocity.q=InverseRotate(secondary->local.basis,secondary->velocity.q);
    float acceleration=D_002C2144*p->physics->mass*p->width/p->physics->inertia;
    work.control.torque.f[0]=work.control.torque.f[1]=0.0f;
    float turnImpulse=func_0011CFE0((p->turn-work.control.localVelocity.f[2])/D_002DDED0.dt,acceleration*budget);
    work.control.torque.f[2]=turnImpulse;
    work.control.worldTorque.q=Rotate(secondary->world.basis,work.control.torque.q);
    budget-=Abs(D_002C2148*turnImpulse/acceleration);
    func_001FAC98(p,work.control.worldTorque.q);
    float dt=D_002DDED0.dt;
    func_0011B500(rotation,D_002A2DC0,(work.control.localVelocity.f[2]+work.control.torque.f[2]*(dt*0.5f))*dt);
    work.control.desired.f[0]=p->acceleration*p->drive;
    work.control.desired.f[1]=work.control.desired.f[2]=0.0f;
    work.control.basis=*rotation;
    work.control.desired.q=Rotate(work.control.basis,work.control.desired.q);
    float fraction=work.control.velocity.f[0]/p->slip;
    float minimum,maximum;
    if(0.0f<=p->drive){
        minimum=-p->reverseLimit;
        maximum=Clamp(Evaluate(*traction,Clamp(fraction,0.0f,1.0f)),limits->low,limits->high);
    }else{
        minimum=-Clamp(Evaluate(*traction,Clamp(-fraction,0.0f,1.0f)),limits->low,limits->high);
        maximum=p->reverseLimit;
    }
    work.control.dt.q=Scalar(LoadScalar(&D_002DDED0.dt));
    work.control.phase.impulse.acceleration.q=Divide(Subtract(work.control.desired.q,work.control.velocity.q),work.control.dt.q);
    work.control.phase.impulse.acceleration.bits[2]=0;
    work.control.phase.impulse.acceleration.f[0]=Clamp(work.control.phase.impulse.acceleration.f[0],minimum,maximum);
    work.control.phase.impulse.limited.q=func_0011E9F8(budget,work.control.phase.impulse.acceleration.q);
    work.control.phase.impulse.world.q=func_0022FCC8(p->secondary,0,work.control.phase.impulse.limited.q);
    func_001FAC30(p,work.control.phase.impulse.world.q);
}
