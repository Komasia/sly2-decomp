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
extern "C" float fabsf(float);
static inline float Abs(float f){return fabsf(f);}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword LoadVF(const U &value){qword out;__asm__("lqc2 %0,%1":"=j"(out):"m"(value));return out;}
static inline float DifferenceLength(qword target,const U &position,U &difference){
 register qword current __asm__("vf1")=Vector(target);
 register qword first __asm__("vf2")=LoadVF(position);
 __asm__("vsub.xyzw %0,%0,%1":"+j"(current):"j"(first));
 __asm__("sqc2 %1,%0":"=m"(difference):"j"(current));
 register qword saved __asm__("vf3")=LoadVF(difference);
 __asm__("vmul.xy %0,%0,%1\n\tvaddy.x %0,%0,%0y":"+j"(current):"j"(saved));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(current));
 return X(current);
}
union FLOATWORD {float value;int word;};
static inline qword ScalarBits(const float &f){FLOATWORD view;view.value=f;qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(view.word));return r;}
static inline qword NormalizeRadius(qword a,const float &radius,U &scalar){
    register qword value __asm__("vf3")=a;
    register qword length __asm__("vf1");
    register qword one __asm__("vf2");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(length),"=&j"(one):"j"(value));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(length));
    scalar.q=ScalarBits(radius);
    register qword direction __asm__("vf1");
    qword fallback=D_002A2DA0;
    if(X(length)<0.0001f){direction=Vector(fallback);return Scale(direction,scalar.q);}
    __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(direction):"j"(length),"j"(value));
    return Scale(direction,scalar.q);
}
static inline qword OrbitGoal(const M3&m,const U&offset,const U&targetPosition){
 register qword row2 __asm__("vf2")=m.rows[2].q;
 register qword row0 __asm__("vf1")=m.rows[0].q;
 register qword row1 __asm__("vf3")=m.rows[1].q;
 register qword value __asm__("vf4"),target __asm__("vf2");
 __asm__("lqc2 %1,%5\n\tvmulax.xyz ACC,%2,%1x\n\tvmadday.xyz ACC,%3,%1y\n\tvmaddz.xyz %2,%4,%1z\n\tlqc2 %0,%6\n\tvadd.xyzw %0,%0,%2"
 :"=j"(target),"=&j"(value),"+j"(row0):"j"(row1),"j"(row2),"m"(offset),"m"(targetPosition));
 return target;
}
static inline void PathMeasureTarget(const U&last,qword packedTarget,float&outLength,float&outLimit){
 register qword target __asm__("vf2")=packedTarget;
 register qword root __asm__("vf1"),bits __asm__("$2");
 register float limit __asm__("$f1"),length __asm__("$f0");
 __asm__(".set noat\n\tlui $at,0x4248\n\tmtc1 $at,%0\n\t.set at\n\tlqc2 %2,%4\n\tvsub.xyzw %2,%2,%5\n\tvmul.xy %2,%2,%2\n\tvaddy.x %2,%2,%2y\n\tvsqrt Q,%2x\n\tvwaitq\n\tvaddq.x %2,$vf0,Q\n\tqmfc2.ni %3,%2\n\tmtc1 %3,%1"
 :"=f"(limit),"=f"(length),"=&j"(root),"=r"(bits):"m"(last),"j"(target):"$1");
 outLength=length;outLimit=limit;
}
static inline void PathMeasureSelected(const U&last,qword packedTarget,float&outLength,float&outLimit){
 register qword target __asm__("vf2")=packedTarget;
 register qword root __asm__("vf1"),bits __asm__("$3");
 register float limit __asm__("$f1"),length __asm__("$f0");
 __asm__(".set noat\n\tlui $at,0x4248\n\tmtc1 $at,%0\n\t.set at\n\tlqc2 %2,%4\n\tvsub.xyzw %2,%2,%5\n\tvmul.xy %2,%2,%2\n\tvaddy.x %2,%2,%2y\n\tvsqrt Q,%2x\n\tvwaitq\n\tvaddq.x %2,$vf0,Q\n\tqmfc2.ni %3,%2\n\tmtc1 %3,%1"
 :"=f"(limit),"=f"(length),"=&j"(root),"=r"(bits):"m"(last),"j"(target):"$1");
 outLength=length;outLimit=limit;
}
extern "C" void func_001D2610(P *p)
{
    WORK work;
    HIT query[4];
    U position,targetPosition,delta,goal,offset;
    position.q=func_001A62E8(p);
    qword target=func_001A62E8(p->target);
    targetPosition.q=target;
    float distance=DifferenceLength(target,position,delta);
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
        case 2:func_0011B500(&work.approach.positive,D_002A2DC0,angle);goal.q=OrbitGoal(work.approach.positive,offset,targetPosition);break;
        case 3:func_0011B500(&work.basis,D_002A2DC0,-angle);goal.q=OrbitGoal(work.basis,offset,targetPosition);break;
        case 4:break;
        }
        if(func_001C0960(p->navigator,position.q,goal.q,4,query,2)==1 && query[0].startFraction==0.0f && query[0].endFraction==1.0f){
            p->path->points[0].q=position.q;
            p->path->points[1].q=goal.q;
            p->path->count=2;
            func_001E6180(p->path);
            func_001D2420(p);
        }else {
            float length,limit;
            if(p->path->count<2)goto RebuildOrbit;
            PathMeasureTarget(p->path->points[p->path->count-1],LoadVF(targetPosition),length,limit);
            if(limit<length){
                RebuildOrbit:
                func_001C02D0(p->navigator,position.q,targetPosition.q,p->path);
                func_001D2420(p);
            }
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
        qword packedPosition=func_001A62E8(p->selectedObject);
        register qword objectPosition __asm__("vf2");
        __asm__("qmtc2.ni %1,%0":"=j"(objectPosition):"r"(packedPosition));
        float length,limit;
        if(p->path->count<2)goto RebuildObject;
        PathMeasureSelected(p->path->points[p->path->count-1],objectPosition,length,limit);
        if(limit<length){
            RebuildObject:
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

#define OFF(t,f) ((int)&((t*)0)->f)
typedef char verified_difference_layout[(OFF(P,mode)==0x180&&OFF(P,state)==0x188&&OFF(P,stateTime)==0x18c&&OFF(P,attachCount)==0x4f8&&OFF(P,attachments)==0x4fc&&OFF(P,slip)==0x51c&&OFF(P,heading)==0x540&&OFF(P,goalHeading)==0x544&&OFF(P,wheelAngle)==0x54c&&OFF(P,drive)==0x550&&OFF(P,target)==0x5a4&&OFF(P,navigator)==0x5a8&&OFF(P,path)==0x5ac&&OFF(P,pathCursor)==0x5b0&&OFF(P,nextAttack)==0x5b4&&OFF(P,selectedObject)==0x5b8&&OFF(P,selectedAttach)==0x5bc&&OFF(ATTACH,owner)==0x10&&OFF(ATTACH,binding)==0x20&&OFF(ATTACH,mesh)==0x30&&OFF(ATTACH,meshBinding)==0x34&&OFF(ATTACH,anchor)==0x3c&&OFF(ATTACH,stateIndex)==0x6c&&OFF(ATTACH,state)==0x70&&OFF(ATTACH,radius)==0x7c&&OFF(ATTACH,tactic)==0x80&&OFF(ATTACH,constraint)==0x84&&OFF(ATTACH,enterRange)==0x88&&OFF(ATTACH,exitRange)==0x90&&OFF(ATTACH,fireInterval)==0x98&&OFF(ATTACH,active)==0xa0&&OFF(BINDING,pitch)==0x28&&OFF(PATH,count)==0xe8&&OFF(PATH,points)==0xf4&&OFF(HIT,start)==0x0&&OFF(HIT,end)==0x10&&OFF(HIT,startNormal)==0x20&&OFF(HIT,endNormal)==0x30&&OFF(HIT,startFraction)==0x40&&OFF(HIT,endFraction)==0x44&&OFF(HIT,kind)==0x48&&OFF(HIT,object)==0x4c&&OFF(WORK,approach.scalar)==0x0&&OFF(WORK,approach.positive)==0x10&&OFF(WORK,basis)==0x0&&sizeof(U)==0x10&&sizeof(M3)==0x30&&sizeof(M4)==0x40&&sizeof(WORK)==0x40&&sizeof(HIT)==0x60&&sizeof(ATTACH)==0xb0&&sizeof(PATH)==0xf8&&sizeof(P)==0x5c0&&sizeof(LIMITS)==0x8&&sizeof(FLOATWORD)==4&&OFF(FLOATWORD,value)==0&&OFF(FLOATWORD,word)==0&&sizeof(qword)==16&&sizeof(int)==4&&__alignof__(U)==16&&sizeof(HIT[4])==0x180&&sizeof(void*)==4&&sizeof(float)==4&&__alignof__(qword)==16&&OFF(U,q)==0&&OFF(U,f)==0)?1:-1];
typedef char d2610_final_0[(__alignof__(M3)==16)?1:-1];
typedef char d2610_final_1[(__alignof__(M4)==16)?1:-1];
typedef char d2610_final_2[(__alignof__(WORK)==16)?1:-1];
typedef char d2610_final_3[(sizeof(CLOCK)==8)?1:-1];
typedef char d2610_final_4[(OFF(CLOCK,time)==0)?1:-1];
typedef char d2610_final_5[(OFF(CLOCK,dt)==4)?1:-1];
typedef char d2610_final_6[(OFF(M3,rows[0])==0)?1:-1];
typedef char d2610_final_7[(OFF(M3,rows[1])==0x10)?1:-1];
typedef char d2610_final_8[(OFF(M3,rows[2])==0x20)?1:-1];
typedef char d2610_final_9[(OFF(M4,basis)==0)?1:-1];
typedef char d2610_final_10[(OFF(M4,position)==0x30)?1:-1];
typedef char d2610_final_11[(sizeof(((M3*)0)->rows[0])==16)?1:-1];
typedef char d2610_final_12[(OFF(M3,rows[0].f[3])==0xC)?1:-1];
typedef char d2610_final_13[(OFF(P,attachments[7])==0x518)?1:-1];
typedef char d2610_final_14[(sizeof(WORK)+sizeof(HIT[4])+5*sizeof(U)==0x210)?1:-1];
