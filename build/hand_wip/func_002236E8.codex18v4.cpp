// Complete camera visibility probe WIP with the real empty frame and used query workspace.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct M3 {qword r[3];};
struct M4 {qword r[4];};
struct O {char pad[0x18C];int disabled;};
struct S {O *object;char pad4[0xC];O *source;char pad14[0x6C];float time;};
struct CAMERA {char pad40[0x40];float scaleX,scaleY;char pad48[4];float depth;char pad50[0x10];M4 world;char pada0[0x260];int blocked;};
struct CLOCK {float t,dt;};
struct WORLD;
struct SO;
extern CAMERA D_002DDF40;
extern CLOCK D_002DDED0;
extern int D_002DFBC4,D_002C4118;
extern float D_002C4110,D_002C4114;
extern qword D_002A2DC0,D_002A2DA0,D_002C4290[5];
extern WORLD D_003DD490;
struct MARK;
extern "C" {
qword func_001A62E8(void *);
int func_0014F030(void *,SO *);
void func_0020FAA0(WORLD *,qword,qword,int (*)(void *,SO *),void *,int *,SO ***);
qword func_0014F308(CAMERA *,qword);
qword func_0014F268(CAMERA *,qword);
int func_0014EA08(int,SO **,qword,qword,float *,float,float *);
void func_0014D8C0(CAMERA *);
MARK *func_001AE478(MARK *);
void func_001AE4A0(MARK *,int);
}
struct MARK {};
static inline qword ToVF(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword LoadVF(const qword &v){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(v));return r;}
static inline qword Sub(qword a,qword b){register qword r asm("vf2");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword CrossXYZ(qword destination,qword a,qword b){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(destination):"j"(a),"j"(b));return destination;}
static inline qword Length(qword v){register qword len __asm__("vf1");register qword one __asm__("vf2");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(len),"=&j"(one):"j"(v));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(len));return len;}
static inline float X(qword v){float r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(v));return r;}
static inline qword Divide(qword v,qword length){register qword r asm("vf2");__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(length));return r;}
static inline qword Rotate(M3 &m,qword v){qword r;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]),"0"(v));return r;}
static inline qword Min(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"0"(a),"j"(b));return r;}
static inline qword Max(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword FallbackGPR(){register qword value asm("$3");asm("lq %0,%1":"=r"(value):"m"(D_002A2DA0));return value;}
static inline qword CameraVF(){register qword value asm("vf1");asm("lqc2 %0,%1":"=j"(value):"m"(D_002DDF40.world.r[3]));return value;}
struct WORK {V minimum,maximum,projected;V points[5];M3 basis;MARK mark;int count;SO **objects;float contact;V up;};
static inline qword RightInputs(qword value,const qword &up,qword &fallbackValue,float &threshold,const qword &cameraPosition){
 register qword point asm("vf3")=value,normal asm("vf1"),delta asm("vf2"),fallback asm("$3");register float epsilon asm("$f1");
 asm("li.s %4,0.0001\n\tlqc2 %1,%5\n\tlui %3,%%hi(%7)\n\tvsub.xyzw %2,%0,%1\n\taddiu %3,%3,%%lo(%7)\n\tlqc2 %1,%6\n\tvopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1\n\tlq %3,0(%3)"
 :"+j"(point),"=&j"(normal),"=&j"(delta),"=&r"(fallback),"=f"(epsilon):"m"(cameraPosition),"m"(up),"i"(&D_002A2DA0):"$1","memory");
 fallbackValue=fallback;threshold=epsilon;return point;
}
static inline void ReadInitialSnapshots(qword &cameraValue,qword &upValue,O *object,O *&objectArgument,const qword &cameraPosition){
 register qword *address asm("$2");register qword camera asm("$3"),up asm("$2");register O *receiver asm("$4");
 asm("lui %0,%%hi(%3)\n\tlq %1,%2\n\taddiu %0,%0,%%lo(%3)":"=&r"(address),"=&r"(camera):"m"(cameraPosition),"i"(&D_002A2DC0));
 asm("daddu %0,%2,$zero\n\tlq %1,%3":"=&r"(receiver),"=r"(up):"r"(object),"m"(*address));cameraValue=camera;upValue=up;objectArgument=receiver;
}
static inline void PublishInitialSnapshots(qword camera,qword up,WORK &work){
 asm volatile("sq %3,%0\n\tsq %3,%1\n\tsq %4,%2":"=m"(work.minimum.q),"=m"(work.maximum.q),"=m"(work.up.q):"r"(camera),"r"(up));
}
extern "C" void func_002236E8(S *p){
    WORK work;
    unsigned int i;
    register O *object asm("$20")=p->object;
    if(D_002DFBC4&2){p->time=D_002DDED0.t;return;}
    if(p->source && p->source->disabled)return;
    if(D_002C4118)return;
    if(D_002DDED0.t-p->time<D_002C4110)return;
    {
    register CAMERA *initialCamera asm("$16");
    {
        register CAMERA *high asm("$3");
        asm("lui %0,%%hi(%2)\n\taddiu %1,%0,%%lo(%2)":"=r"(high),"=r"(initialCamera):"i"(&D_002DDF40));
    }
    if(initialCamera->blocked)return;
    qword cameraValue,upValue;O *objectArgument;ReadInitialSnapshots(cameraValue,upValue,object,objectArgument,initialCamera->world.r[3]);
    PublishInitialSnapshots(cameraValue,upValue,work);work.basis.r[2]=upValue;
    qword position=ToVF(func_001A62E8(objectArgument));
    qword fallback;float epsilon;qword right=RightInputs(position,work.up.q,fallback,epsilon,initialCamera->world.r[3]);
    qword length=Length(right);
    qword normalized;
    if(X(length)<epsilon)normalized=fallback;
    else normalized=Divide(right,length);
    qword upAxis=work.basis.r[2];
    work.basis.r[0]=CrossXYZ(upAxis,upAxis,normalized);
    work.basis.r[1]=normalized;
    }
    MARK *marker=&work.mark;int *countOutput=&work.count;SO ***objectOutput=&work.objects;float *contactOutput=&work.contact;
    V *dst=work.points;
    for(i=0;i<5;i++,dst++){
        qword origin=func_001A62E8(object);
        qword position=Add(origin,Rotate(work.basis,D_002C4290[i]));
        work.minimum.q=Min(work.minimum.q,position);
        work.maximum.q=Max(work.minimum.q,position);
        dst->q=position;
    }
    {
        dst=work.points;func_001AE478(marker);
        float unit;
        {
            register qword minimum asm("$5");register float one asm("$f20");
            asm("li.s %0,1.0\n\tlq %1,%2":"=f"(one),"=r"(minimum):"m"(work.minimum.q):"$1");
            unit=one;
            func_0020FAA0(&D_003DD490,minimum,work.maximum.q,func_0014F030,0,countOutput,objectOutput);
        }
        register CAMERA *camera asm("$18");
        {
            register CAMERA *high asm("$2");
            asm("lui %0,%%hi(%2)\n\taddiu %1,%0,%%lo(%2)":"=r"(high),"=r"(camera):"i"(&D_002DDF40));
        }
        for(i=0;i<5;i++,dst++){
            qword projected=func_0014F308(camera,dst->q);
            register float depth asm("$f0");register CAMERA *receiver asm("$4");
            asm("lwc1 %0,%3\n\tdaddu %1,%4,$zero\n\tsq %5,%2":"=f"(depth),"=&r"(receiver),"=m"(work.projected.q):"m"(camera->depth),"r"(camera),"r"(projected));
            work.projected.f[2]=depth;
            work.projected.q=func_0014F268(receiver,work.projected.q);
            if(func_0014EA08(work.count,work.objects,dst->q,work.projected.q,0,0.0f,contactOutput) && work.contact>=unit){
                p->time=D_002DDED0.t;break;
            }
        }
        if(D_002DDED0.t-p->time>D_002C4114)func_0014D8C0(&D_002DDF40);
        func_001AE4A0(marker,2);
    }
}
