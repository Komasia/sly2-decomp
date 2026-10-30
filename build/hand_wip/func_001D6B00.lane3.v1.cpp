// Launch an object toward a target: predict target position, set launch velocity/spin, apply.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword rows[3];};
struct M4 {U rows[4];};
struct FRAME {M4 local,world;};
union WORK {M4 matrix;M3 basis;U scalar;};
struct VENTRY {short delta,pad;void (*fn)();};
struct OBJ {char pad0[0xC];VENTRY *vt;char pad10[0x250];float speed;};
struct POLY {float a,b,c;};
struct PARAMS {char pad0[0x50];U target;OBJ *source;char pad64[0xC];POLY prediction;int unused7C;float predictionLow,predictionHigh;char pad88[8];POLY displacement;int unused9C;float displacementLow,displacementHigh;float angularLow,angularHigh,pitch;};
extern FRAME D_002C44F0;
extern const qword D_002A2DA0;
extern char D_003DD490[];
extern "C" {
qword func_001A62E8(OBJ *);
M4 *func_0011C168(M4 *,const M4 *,const M4 *);
void *func_002333B4(void *,int,int);
void func_002309E8(FRAME *,int,M4 *,M4 *,float);
int func_00132B10(OBJ *,int);
void func_0013BC60(OBJ *,PARAMS *);
void func_00134320(void *,OBJ *);
void func_001F5720(OBJ *,void *);
void func_001F57C0(OBJ *,void *);
void func_001A58D0(OBJ *,int,int);
void func_001F4898(OBJ *,qword);
qword func_001F5860(OBJ *);
qword func_001D6848(float,qword,qword,qword);
M3 *func_0011B7E0(M3 *,qword);
float func_0011D448(float,float);
}
static inline qword Pack(float x,float y,float z){qword out,t;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(out),"=&r"(t):"f"(x),"f"(y),"f"(z));return out;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Point(const M4&m,const U&p){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q),"j"(m.rows[3].q),"j"(p.q));return r;}
static inline qword LenVec(qword v){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));qword l;__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(l):"j"(d));return l;}
static inline qword ToCPU(qword v){qword r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(v));return r;}
static inline float Word(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarBits(const float &f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(*(const int *)&f));return r;}
static inline qword Unit(qword length,qword v){qword r;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(length),"j"(v));return r;}
static inline qword Mulx(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword AddMul(qword o,qword a,qword s){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(o),"j"(a),"j"(s));return r;}
static inline float Evaluate(const POLY &p,float d){return p.a+d*(p.b+d*p.c);}
static inline float Clamp(float value,float low,float high){if(value<low)return low;else if(high<value)return high;else return value;}
static inline void Identity(M4 *m){func_002333B4(m,0,sizeof(*m));m->rows[0].f[0]=m->rows[1].f[1]=m->rows[2].f[2]=m->rows[3].f[3]=1.0f;}
static inline void Reset(OBJ *p){VENTRY &e=p->vt[8];((void (*)(void *))e.fn)((char *)p+e.delta);}
static inline void SetVector(OBJ *p,int slot,qword value){VENTRY &e=p->vt[slot];((void (*)(void *,qword))e.fn)((char *)p+e.delta,value);}
static inline void SetBasis(OBJ *p,const M3 *basis){VENTRY &e=p->vt[30];((void (*)(void *,const M3 *))e.fn)((char *)p+e.delta,basis);}
extern "C" void func_001D6B00(PARAMS *params,OBJ *p)
{
    M4 parent;
    WORK work;
    M4 predicted;
    U start,origin,destination,launch,velocity;
    qword pos=func_001A62E8(p);
    start.q=pos;origin.q=pos;
    OBJ *source=params->source;
    FRAME *frame;
    if(source){
        VENTRY &entry=source->vt[32];
        frame=((FRAME *(*)(void *,M4 *))entry.fn)((char *)source+entry.delta,&parent);
    }else{
        frame=&D_002C44F0;
        Identity(&parent);
    }
    func_0011C168(&work.matrix,&frame->world,&parent);
    qword delta=Sub(Point(work.matrix,params->target),start.q);
    float distance=Word(LenVec(delta));
    float prediction=Clamp(Evaluate(params->prediction,distance),params->predictionLow,params->predictionHigh);
    if(prediction!=0.0f){
        func_002309E8(frame,0,&work.matrix,0,prediction);
        func_0011C168(&predicted,&work.matrix,&parent);
        delta=Sub(Point(predicted,params->target),start.q);
    }
    distance=Word(LenVec(delta));
    float displacement=Clamp(Evaluate(params->displacement,distance),params->displacementLow,params->displacementHigh);
    qword length=LenVec(delta);
    qword scale=Scalar(displacement);
    work.scalar.q=scale;
    qword fb=D_002A2DA0;
    if(Word(length)<0.0001f)length=fb;
    else length=Unit(length,delta);
    qword projected=AddMul(origin.q,length,scale);
    destination.q=ToCPU(projected);
    launch.q=projected;
    if(func_00132B10(p,0x4F)){
        func_0013BC60(p,params);
        func_00134320(D_003DD490,p);
    }
    Reset(p);
    func_001F5720(p,0);
    func_001F57C0(p,0);
    func_001A58D0(p,0,3);
    if(func_00132B10(p,0x52)){
        work.scalar.q=Pack(p->speed,0.0f,0.0f);
        func_001F4898(p,work.scalar.q);
    }else if(func_00132B10(p,0x51)){
        qword d=Sub(destination.q,start.q);
        qword l=LenVec(d);
        qword s=ScalarBits(p->speed);
        work.scalar.q=s;
        qword fb2=D_002A2DA0;
        if(Word(l)<0.0001f)l=fb2;
        else l=Unit(l,d);
        velocity.q=Mulx(l,s);
        SetVector(p,35,velocity.q);
        func_0011B7E0(&work.basis,velocity.q);
        SetBasis(p,&work.basis);
    }else{
        qword acceleration=func_001F5860(p);
        SetVector(p,35,func_001D6848(params->pitch,start.q,launch.q,acceleration));
    }
    if(params->angularHigh>0.0f){
        float magnitude=func_0011D448(params->angularLow,params->angularHigh);
        float x=func_0011D448(-1.0f,1.0f);
        float y=func_0011D448(-1.0f,1.0f);
        float z=func_0011D448(-1.0f,1.0f);
        qword packed=Pack(x,y,z);
        work.scalar.q=packed;
        qword l=LenVec(packed);
        qword s=Scalar(magnitude);
        work.scalar.q=s;
        qword n;
        qword fb3=D_002A2DA0;
        if(Word(l)<0.0001f)n=fb3;
        else n=Unit(l,packed);
        SetVector(p,36,Mulx(n,s));
    }
    if(func_00132B10(p,0x50)){
        work.scalar=params->target;
        VENTRY &entry=p->vt[78];
        ((void (*)(void *,OBJ *,const U *))entry.fn)((char *)p+entry.delta,params->source,&work.scalar);
    }
}
