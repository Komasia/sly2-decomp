// WIP: 54/202 instruction differences; complete camera visibility probe.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct M3 {qword r[3];};
struct O {char pad[0x18C];int disabled;};
struct S {O *object;char pad4[0xC];O *source;char pad14[0x6C];float time;};
struct CAMERA {char pad[0x4C];float depth;char pad50[0x40];qword position;char pada0[0x260];int blocked;};
struct CLOCK {float t,dt;};
struct WORLD;
extern CAMERA D_002DDF40;
extern CLOCK D_002DDED0;
extern int D_002DFBC4,D_002C4118;
extern float D_002C4110,D_002C4114;
extern qword D_002A2DC0,D_002A2DA0,D_002C4290[5];
extern WORLD D_003DD490;
extern "C" {
qword func_001A62E8(void *);
int func_0014F030(void *,O *);
void func_0020FAA0(WORLD *,qword,qword,int (*)(void *,O *),void *,int *,O ***);
qword func_0014F308(CAMERA *,qword);
qword func_0014F268(CAMERA *,qword);
int func_0014EA08(int,O **,qword,qword,float *,float,float *);
void func_0014D8C0(CAMERA *);
void *func_001AE478(void *);
void func_001AE4A0(void *,int);
}
struct MARK {int mark;MARK(){func_001AE478(this);}~MARK(){func_001AE4A0(this,2);}};
static inline qword ToVF(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword LoadVF(const qword &v){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(v));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword CrossXYZ(qword destination,qword a,qword b){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(destination):"j"(a),"j"(b));return destination;}
static inline qword Length(qword v){qword len,one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(len),"=&j"(one):"j"(v));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(len));return len;}
static inline float X(qword v){float r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(v));return r;}
static inline qword Divide(qword v,qword length){qword r;
    __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"0"(length));return r;}
static inline qword Rotate(M3 &m,qword v){qword r;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]),"0"(v));return r;}
static inline qword Min(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"0"(a),"j"(b));return r;}
static inline qword Max(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
extern "C" void func_002236E8(S *p){
    V minimum,maximum,projected;
    V points[5];
    M3 basis;
    int count;
    O **objects;
    float contact;
    V up;
    unsigned int i;
    O *object=p->object;
    if(D_002DFBC4&2){p->time=D_002DDED0.t;return;}
    if(p->source && p->source->disabled)return;
    if(D_002C4118)return;
    if(D_002DDED0.t-p->time<D_002C4110)return;
    if(D_002DDF40.blocked)return;
    minimum.q=maximum.q=D_002DDF40.position;
    up.q=D_002A2DC0;basis.r[2]=up.q;
    qword position=ToVF(func_001A62E8(object));
    qword separation=Sub(position,LoadVF(D_002DDF40.position));
    qword right=CrossXYZ(position,LoadVF(up.q),separation);
    qword fallback=D_002A2DA0;
    qword length=Length(right);
    qword normalized;
    if(X(length)<0.0001f)normalized=ToVF(fallback);
    else normalized=Divide(right,length);
    qword upAxis=LoadVF(basis.r[2]);
    basis.r[0]=CrossXYZ(upAxis,upAxis,normalized);
    basis.r[1]=normalized;
    V *dst=points;
    for(i=0;i<5;i++,dst++){
        qword origin=func_001A62E8(object);
        qword position=Add(origin,Rotate(basis,D_002C4290[i]));
        minimum.q=Min(minimum.q,position);
        maximum.q=Max(minimum.q,position);
        dst->q=position;
    }
    {
        MARK mark;
        func_0020FAA0(&D_003DD490,minimum.q,maximum.q,func_0014F030,0,&count,&objects);
        for(i=0;i<5;i++){
            projected.q=func_0014F308(&D_002DDF40,points[i].q);
            projected.f[2]=D_002DDF40.depth;
            projected.q=func_0014F268(&D_002DDF40,projected.q);
            if(func_0014EA08(count,objects,points[i].q,projected.q,0,0.0f,&contact) && contact>=1.0f){
                p->time=D_002DDED0.t;break;
            }
        }
        if(D_002DDED0.t-p->time>D_002C4114)func_0014D8C0(&D_002DDF40);
    }
}
