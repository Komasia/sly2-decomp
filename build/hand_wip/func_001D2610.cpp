typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U rows[3];};
struct M4 {M3 basis;U position;};
struct LIMITS {float low,high;};
struct CLOCK {float time,dt;};
struct REF {char pad0[0x70];U position;};
struct BINDING {char pad0[0x28];float pitch;};
struct P;
struct ATTACH {char pad0[0x10];P *owner;int index,id;void *object;void *binding;char pad24[8];int meshId;REF *mesh;BINDING *meshBinding;int anchorId;P *anchor;char pad40[0x2C];int stateIndex,state;float angle,speed,radius;int tactic;void *constraint;LIMITS enterRange,exitRange,fireInterval;int active;char padA4[0xC];};
struct PATH {char pad0[0xE8];int count;int unknownEC,unknownF0;U *points;};
struct P {char pad0[0x180];int mode,unknown184,state;float stateTime;char pad190[0x368];int attachCount;ATTACH *attachments[8];float slip;char pad520[0x20];float heading,goalHeading,steering,wheelAngle,drive;char pad554[0x50];P *target;void *navigator;PATH *path;float pathCursor,nextAttack;P *selectedObject;ATTACH *selectedAttach;};
struct HIT {U start,end,startNormal,endNormal;float startFraction,endFraction;int kind;void *object;char pad50[0x10];};
union WORK {struct {U scalar;M3 positive;} approach;M3 basis;};
extern CLOCK D_002DDED0;
extern qword D_002A2DA0,D_002A2DC0;
extern float D_002C20E8,D_002C20EC,D_002C20F0,D_002C20F4,D_002C20F8;
extern "C" {
qword func_001A62E8(P *);
ATTACH *func_001D2240(P *);
P *func_001D22D0(P *);
int func_0011D910(const LIMITS *,float);
void func_001D4B28(P *,int);
float func_002456F0(float);
M3 *func_0011B500(M3 *,qword,float);
int func_001C0960(void *,qword,qword,int,HIT *,int);
void func_001E6180(PATH *);
void func_001D2420(P *);
int func_001C02D0(void *,qword,qword,PATH *);
float func_002458F0(float,float);
M4 *func_001A6318(P *);
qword func_0022CA18(REF *,REF *);
float func_0011CF60(float);
void func_001F0660(void *,int);
float func_0011D448(float,float);
void func_001D2490(P *);
int func_001D4E08(ATTACH *);
int func_00227C90(void *,qword);
}
static inline qword Vector(qword q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){qword r;__asm__("prot3w %0,%1":"=r"(r):"r"(q));return X(r);}
static inline float Z(qword q){qword r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(q));return X(r);}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline float LengthXY(qword a){qword r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return X(r);}
static inline qword Rotate(const M3 &m,qword a){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q),"j"(a));return r;}
static inline void StoreCPU(U &out,qword value){__asm__("sq %1,%0":"=m"(out):"r"(value));}
static inline qword LoadVF(const U &value){qword out;__asm__("lqc2 %0,%1":"=j"(out):"m"(value));return out;}
union FLOATWORD {float value;int word;};
static inline qword ScalarBits(const float &f){FLOATWORD view;view.value=f;qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(view.word));return r;}
static inline qword NormalizeRadius(qword a,const float &radius,U &scalar){
    qword length=Dot(a,a);
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(length));
    scalar.q=ScalarBits(radius);
    qword direction;
    if(X(length)<0.0001f)direction=Vector(D_002A2DA0);
    else __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(direction):"j"(length),"j"(a));
    return Scale(direction,scalar.q);
}
extern "C" void func_001D2610(P *p)
{
    WORK work;
    HIT query[4];
    U position,targetPosition,delta,goal,offset;
    StoreCPU(position,func_001A62E8(p));
    StoreCPU(targetPosition,func_001A62E8(p->target));
    delta.q=Subtract(targetPosition.q,position.q);
    float distance=LengthXY(delta.q);
    p->selectedAttach=func_001D2240(p);
    if(!p->selectedAttach)p->selectedObject=func_001D22D0(p);else p->selectedObject=0;
    int previous;
    do {
        previous=p->state;
        switch(previous){
        case 0:if(p->selectedAttach){if(func_0011D910(&p->selectedAttach->enterRange,distance))func_001D4B28(p,1);}else if(p->selectedObject)func_001D4B28(p,2);else func_001D4B28(p,3);break;
        case 1:if(!p->selectedAttach || !func_0011D910(&p->selectedAttach->exitRange,distance))func_001D4B28(p,0);break;
        case 2:if(!p->selectedObject)func_001D4B28(p,0);break;
        case 3:if(p->selectedAttach || p->selectedObject)func_001D4B28(p,0);break;
        }
    }while(previous!=p->state);
    switch(p->state){
    case 0:{
        float radius=p->selectedAttach->radius;
        float angle=func_002456F0(radius/Max(radius*D_002C20E8,distance));
        offset.q=NormalizeRadius(Subtract(position.q,targetPosition.q),p->selectedAttach->radius,work.approach.scalar);
        switch(p->selectedAttach->tactic){
        case 0:case 1:goal.q=targetPosition.q;break;
        case 2:func_0011B500(&work.approach.positive,D_002A2DC0,angle);goal.q=Add(targetPosition.q,Rotate(work.approach.positive,offset.q));break;
        case 3:func_0011B500(&work.basis,D_002A2DC0,-angle);goal.q=Add(targetPosition.q,Rotate(work.basis,offset.q));break;
        case 4:break;
        }
        if(func_001C0960(p->navigator,position.q,goal.q,4,query,2)==1 && query[0].startFraction==0.0f && query[0].endFraction==1.0f){
            p->path->points[0].q=position.q;
            p->path->points[1].q=goal.q;
            p->path->count=2;
            func_001E6180(p->path);
            func_001D2420(p);
        }else if(p->path->count<2 || 50.0f<LengthXY(Subtract(p->path->points[p->path->count-1].q,targetPosition.q))){
            func_001C02D0(p->navigator,position.q,targetPosition.q,p->path);
            func_001D2420(p);
        }
        func_001D2490(p);
        p->wheelAngle=p->heading;
        break;
    }
    case 1:{
        p->drive=0.0f;
        p->goalHeading=p->heading;
        p->wheelAngle=func_002458F0(Y(delta.q),X(delta.q));
        if(p->nextAttack<D_002DDED0.time){
            ATTACH *attach=func_001D2240(p);
            if(attach){
                if(attach->mesh){
                    work.basis=func_001A6318(attach->anchor)->basis;
                    float aim=func_002458F0(work.basis.rows[0].f[1],work.basis.rows[0].f[0]);
                    qword packed=func_0022CA18(attach->mesh,attach->mesh);
                    float error=Abs(func_0011CF60(aim-p->wheelAngle));
                    float pitchError=Z(packed)-attach->meshBinding->pitch;
                    if(error<D_002C20EC){
                        if(Abs(pitchError)<D_002C20F0)goto attackNow;
                    }
                    break;
                }
                attackNow:
                func_001F0660(attach->binding,0x68);
                float time=D_002DDED0.time;
                p->nextAttack=time+func_0011D448(1.0f,1.5f);
            }
        }
        break;
    }
    case 2:{
        qword objectPosition=Vector(func_001A62E8(p->selectedObject));
        if(p->path->count<2 || 50.0f<LengthXY(Subtract(p->path->points[p->path->count-1].q,objectPosition))){
            func_001C02D0(p->navigator,position.q,objectPosition,p->path);
            func_001D2420(p);
        }
        func_001D2490(p);
        p->wheelAngle=p->heading;
        break;
    }
    case 3:
        p->goalHeading=func_002458F0(-Y(delta.q),-X(delta.q));
        p->wheelAngle=p->heading;
        p->drive=p->slip*0.85f;
        break;
    }
    if(p->nextAttack<D_002DDED0.time){
        for(int i=0;i<p->attachCount;i++){
            ATTACH *attach=p->attachments[i];
            if(!func_001D4E08(attach))continue;
            if(attach->constraint && !func_00227C90(attach->constraint,targetPosition.q))continue;
            if(0.0f<attach->enterRange.high && p->state!=1)continue;
            if(attach->mesh){
                work.basis=func_001A6318(attach->anchor)->basis;
                float aim=func_002458F0(work.basis.rows[0].f[1],work.basis.rows[0].f[0]);
                qword packed=func_0022CA18(attach->mesh,attach->mesh);
                float error=Abs(func_0011CF60(aim-p->wheelAngle));
                float pitchError=Z(packed)-attach->meshBinding->pitch;
                if(D_002C20F4<error)continue;
                if(D_002C20F8<Abs(pitchError))continue;
            }
            func_001F0660(attach->binding,0x68);
            float time=D_002DDED0.time;
            p->nextAttack=time+func_0011D448(attach->fireInterval.low,attach->fireInterval.high);
        }
    }
}
