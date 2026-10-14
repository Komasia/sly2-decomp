typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U rows[3];};
struct M4 {M3 basis;U position;};
struct FRAME {M4 matrix,world;};
struct VENTRY {short delta,pad;void (*fn)();};
struct REF {char pad0[0x70];U position;char pad80[0x20];FRAME *parent;};
struct POLY {float a,b,c;};
struct LIMITS {float low,high;};
struct P;
struct ATTACH {char pad0[0x10];P *owner;int index,id;void *object;void *binding;char pad24[8];int meshId;REF *mesh;void *meshBinding;int anchorId;P *anchor;LIMITS angleLimits,speedLimits;POLY flightTime;int unused5C;LIMITS flightLimits;float gravity;int stateIndex,state;float angle,speed;char pad7C[0x24];int active;char padA4[0xC];};
struct ENTRY {int id;REF *reference;int unknown;float steering;char pad10[4];float tilt;char pad18[0x48];};
struct SIDE {int id;REF *reference;void *binding;LIMITS angleLimits;};
struct SOUND {char pad0[0x4E];short references;};
struct P {char pad0[0xC];VENTRY *vt;char pad10[0x50];FRAME *space;char pad64[0x11C];int mode;char pad184[0xC];int count;char pad194[0xC];ENTRY entries[8];float width;int sideCount;SIDE sides[4];int attachCount;ATTACH *attachments[8];char pad51C[0x24];float heading,goalHeading,steering,wheelAngle,drive,turn,acceleration;char pad55C[0x3C];SOUND *sound;int unused59C;float soundRate;P *target;char pad5A8[0x18];float lastCorrection;};
struct CLOCK {float time,dt;};
extern CLOCK D_002DDED0;
extern const qword D_002A2DC0;
extern POLY D_002C2040,D_002C2060,D_002C2080;
extern LIMITS D_002C2050,D_002C2070,D_002C2090;
extern float D_002C2030,D_002C20A4;
extern char D_002C2098[],D_002C20A8[];
extern "C" {
void func_001F36E0(P *);
float func_002458F0(float,float);
int func_001D4E08(ATTACH *);
void func_001F0660(void *,int);
void func_001D2150(P *);
void func_001D2610(P *);
float func_0011CF60(float);
qword func_0011E1A0(float,float,float);
qword func_0022FCC8(FRAME *,FRAME *,qword);
float func_0011D948(const LIMITS *,float);
void func_0012D108(void *,qword);
float func_0011D2D0(float,float,float,void *,float *);
qword func_001A62E8(P *);
int func_0011D4D0(float,float,float);
float func_0011D018(float,float,float,void *,float *);
void func_001FB1F8(SOUND *,float);
void func_001FB2C0(SOUND *,float);
void func_001FB060(SOUND *);
void func_001F5078(P *);
}
static inline qword Vector(qword q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){qword r;__asm__("prot3w %0,%1":"=r"(r):"r"(q));return X(r);}
static inline float Z(qword q){qword r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(q));return X(r);}
static inline qword Pack(float x,float y,float z){qword a,b;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(a),"=&r"(b):"f"(x),"f"(y),"f"(z));return a;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline float Length(qword a){qword r=Dot(a,a);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return X(r);}
static inline float LengthXY(qword a){qword r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return X(r);}
static inline qword Combine(qword a,qword b,qword x,qword up,qword z){qword r;__asm__("vadda.xyzw ACC,$vf0,%1\n\tvmaddax.xyzw ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(a),"j"(b),"j"(x),"j"(up),"j"(z));return r;}
static inline float Evaluate(const POLY &p,float t){return p.a+t*(p.b+t*p.c);}
static inline float Clamp(float v,float low,float high){if(v<low)return low;else if(high<v)return high;else return v;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline void ResetDrive(P *p){
 register float zero __asm__("$f1"),heading __asm__("$f0");
 __asm__("mtc1 $zero,%0\n\t"
         "lwc1 %1,%2"
         : "=f"(zero),"=f"(heading)
         : "m"(p->heading));
 p->turn=zero;
 p->drive=zero;
 p->goalHeading=heading;
}
static inline M4 *GetMatrix(P *p){VENTRY &e=p->vt[31];return ((M4 *(*)(void *))e.fn)((char *)p+e.delta);}
static inline qword GetVelocity(P *p){VENTRY &e=p->vt[33];return ((qword (*)(void *))e.fn)((char *)p+e.delta);}
extern "C" void func_001D19A8(P *p)
{
    U scalar,position,targetPosition,targetVelocity,shot;
    int i=0;
    func_001F36E0(p);
    p->heading=func_002458F0(p->space->world.basis.rows[0].f[1],p->space->world.basis.rows[0].f[0]);
    if(p->attachCount>0){
        ATTACH **current=p->attachments;
        do {
            ATTACH *attach=*current;
            if(!func_001D4E08(attach))func_001F0660(attach->binding,0x65);
            ++i;++current;
        }while(i<p->attachCount);
    }
    switch(p->mode){
    case 0:case 3:ResetDrive(p);break;
    case 1:func_001D2150(p);break;
    case 2:func_001D2610(p);break;
    }
    register float angle __asm__("$f0")=func_0011CF60(p->goalHeading-p->heading);
    p->steering=Clamp(Evaluate(D_002C2040,angle),D_002C2050.low,D_002C2050.high);
    angle=Abs(func_0011CF60(p->goalHeading-p->heading));
    p->acceleration=Clamp(Evaluate(D_002C2060,angle),D_002C2070.low,D_002C2070.high);
    angle=Abs(func_0011CF60(p->goalHeading-p->heading));
    float turnFactor=Clamp(Evaluate(D_002C2080,angle),D_002C2090.low,D_002C2090.high);
    p->turn=turnFactor*Min(D_002C2030,p->drive)*p->steering/p->width;
    if(GetMatrix(p)->basis.rows[2].f[2]>0.5f)p->lastCorrection=D_002DDED0.time;
    for(int j=0;j<p->sideCount;j++){
        SIDE *side=&p->sides[j];
        qword direction=func_0022FCC8(0,side->reference->parent,func_0011E1A0(p->wheelAngle,1.0f,0.0f));
        float orientation=func_002458F0(Y(direction),X(direction));
        scalar.q=Pack(0.0f,0.0f,func_0011D948(&side->angleLimits,orientation));
        func_0012D108(side->binding,scalar.q);
    }
    for(int k=0;k<p->count;k++){
        ENTRY *entry=&p->entries[k];
        float desired;
        if(p->drive!=0.0f)desired=entry->steering*p->steering;else desired=0.0f;
        entry->tilt=func_0011D2D0(entry->tilt,desired,D_002DDED0.dt,D_002C2098,0);
    }
    position.q=func_001A62E8(p);
    targetPosition.q=func_001A62E8(p->target);
    qword targetSpeed=GetVelocity(p->target);
    if(p->attachCount>0){
        targetVelocity.q=targetSpeed;
        float distance=LengthXY(Subtract(targetPosition.q,position.q));
        const qword *up=&D_002A2DC0;
        for(int n=0;n<p->attachCount;n++){
            ATTACH *attach=p->attachments[n];
            if(!attach->mesh)continue;
            if(p->drive!=0.0f || !func_001D4E08(attach)){
                attach->active=0;attach->speed=attach->speedLimits.low;attach->angle=0.0f;
            }else{
                float time=Clamp(Evaluate(attach->flightTime,distance),attach->flightLimits.low,attach->flightLimits.high);
                qword origin;
                if(attach->anchor)origin=Vector(func_001A62E8(attach->anchor));else origin=attach->mesh->position.q;
                qword delta=Subtract(targetPosition.q,origin);
                qword horizontal=Subtract(targetVelocity.q,Scale(*up,Dot(targetVelocity.q,*up)));
                scalar.q=Scalar(1.0f/time);
                qword inverse=scalar.q;
                scalar.q=Scalar(attach->gravity*(time*-0.5f));
                shot.q=Combine(horizontal,delta,inverse,*up,scalar.q);
                float pitch=func_002458F0(Z(shot.q),LengthXY(shot.q));
                float speed=Length(shot.q);
                attach->angle=func_0011D948(&attach->angleLimits,pitch);
                attach->speed=func_0011D948(&attach->speedLimits,speed);
                int active=func_0011D4D0(attach->angle,pitch,0.01f) && func_0011D4D0(attach->speed,speed,0.01f);
                attach->active=active;
                if(!active){attach->angle=0.0f;attach->speed=attach->speedLimits.low;}
            }
            scalar.q=Pack(0.0f,-attach->angle,0.0f);
            func_0012D108(attach->meshBinding,scalar.q);
        }
    }
    if(p->sound){
        p->soundRate=func_0011D018(p->soundRate,p->drive/D_002C20A4,D_002DDED0.dt,D_002C20A8,0);
        float rate=Clamp(p->soundRate,0.2f,1.0f);
        func_001FB1F8(p->sound,rate);
        func_001FB2C0(p->sound,rate*0.2f);
        if(p->sound->references>0)func_001FB060(p->sound);
    }
    if(p->drive!=0.0f || p->turn!=0.0f)func_001F5078(p);
}
