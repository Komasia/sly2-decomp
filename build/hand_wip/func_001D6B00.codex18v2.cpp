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
static inline OBJ*InitialSource(U&start,U&origin,qword value,const PARAMS*params){
 OBJ *source;
 __asm__("sq %2,%0\n\tlw %1,%3":"=m"(start.q),"=&r"(source):"r"(value),"m"(params->source));
 origin.q=value;
 return source;
}
static inline qword ToCPU(qword value){qword result;__asm__("qmfc2.ni %0,%1":"=r"(result):"j"(value));return result;}
static inline qword ReadStored(const U&value){qword result;__asm__("lq %0,%1":"=r"(result):"m"(value.q));return result;}
static inline qword Vector(qword q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword Pack(float x,float y,float z){qword out,scratch;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(out),"=&r"(scratch):"f"(x),"f"(y),"f"(z));return out;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Offset(qword origin,qword axis,qword amount){qword r;__asm__("vadda.xyzw ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(origin),"j"(axis),"j"(amount));return r;}
static inline qword Point(const M4&m,const U&point){
 register qword row2 __asm__("vf3")=m.rows[2].q;
 register qword position __asm__("vf1")=m.rows[3].q;
 register qword target __asm__("vf5")=point.q;
 register qword result __asm__("vf2")=m.rows[0].q;
 register qword row1 __asm__("vf4")=m.rows[1].q;
 __asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%3,%4y\n\tvmaddaz.xyz ACC,%1,%4z\n\tvmaddw.xyz %0,%2,$vf0w":"+j"(result):"j"(row2),"j"(position),"j"(row1),"j"(target));
 return result;
}
static inline qword LengthVector(qword v){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;}
static inline float FloatWord(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Length(qword q){return FloatWord(LengthVector(q));}
static inline qword Normal(qword v,qword fallback){qword length=LengthVector(v);if(FloatWord(length)<0.0001f)return Vector(fallback);qword r;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(length),"j"(v));return r;}
static inline qword OffsetNormalized(const U&origin,qword value,qword fallback,float amount,U&scalar){
 register qword vector __asm__("vf3")=value;
 register qword length __asm__("vf1"),one __asm__("vf2");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(length),"=&j"(one):"j"(vector));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(length));
 register float threshold __asm__("$f1")=0.0001f;
 register float distance __asm__("$f0")=FloatWord(length);
 register qword scale __asm__("vf2")=Scalar(amount);
 scalar.q=scale;
 if(distance<threshold)length=fallback;
 else __asm__("vdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"+j"(length):"j"(vector));
 __asm__("lqc2 %0,%1":"=j"(vector):"m"(origin.q));
 __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(vector):"j"(length),"j"(scale));
 return vector;
}
static inline qword SpeedNormalized(const U&start,const U&end,const float&speed,const qword&fallback,U&scalar){
 register qword endValue __asm__("vf1")=end.q;
 register qword startValue __asm__("vf2")=start.q;
 register qword vector __asm__("vf3");
 __asm__("vsub.xyzw %0,%1,%2":"=j"(vector):"j"(endValue),"j"(startValue));
 register unsigned bits __asm__("$2");
 __asm__("lw %0,%1":"=r"(bits):"m"(speed));
 register qword length __asm__("vf1"),one __asm__("vf2");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(length),"=&j"(one):"j"(vector));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(length));
 register float threshold __asm__("$f1")=0.0001f;
 register qword scale __asm__("vf2");
 __asm__("qmtc2 %1,%0":"=j"(scale):"r"(bits));
 register qword fallbackWord __asm__("$2");
 __asm__("lq %0,%1":"=r"(fallbackWord):"m"(fallback));
 register float distance __asm__("$f0")=FloatWord(length);
 scalar.q=scale;
 if(distance<threshold)length=fallbackWord;
 else __asm__("vdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"+j"(length):"j"(vector));
 __asm__("vmulx.xyzw %0,%1,%2x":"=j"(vector):"j"(length),"j"(scale));
 return vector;
}
static inline qword AngularNormalized(qword packed,const qword&fallback,float magnitude,U&scalar){
 register qword vector __asm__("vf3")=Vector(packed);
 register float threshold __asm__("$f1")=0.0001f;
 register qword length __asm__("vf1"),one __asm__("vf2");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(length),"=&j"(one):"j"(vector));
 register qword fallbackWord __asm__("$2");
 __asm__("lq %0,%1":"=r"(fallbackWord):"m"(fallback));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tsq %2,%1":"+j"(length),"=m"(scalar.q):"r"(packed));
 register float distance __asm__("$f0")=FloatWord(length);
 register qword normal __asm__("vf2")=fallbackWord;
 if(distance<threshold)goto angularReady;
 __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(normal):"j"(length),"j"(vector));
 angularReady:;
 register qword scale __asm__("vf1")=Scalar(magnitude);
 scalar.q=scale;
 __asm__("vmulx.xyzw %0,%1,%2x":"=j"(vector):"j"(normal),"j"(scale));
 return vector;
}
static inline float Evaluate(const POLY &p,float d){return p.a+d*(p.b+d*p.c);}
static inline float Clamp(float value,float low,float high){if(value<low)return low;else if(high<value)return high;else return value;}
static inline void Identity(M4 *m){func_002333B4(m,0,sizeof(*m));m->rows[0].f[0]=m->rows[1].f[1]=m->rows[2].f[2]=m->rows[3].f[3]=1.0f;}
static inline void Reset(OBJ *p){VENTRY &e=p->vt[8];((void (*)(void *))e.fn)((char *)p+e.delta);}
static inline void SetVector(OBJ *p,int slot,qword value){VENTRY &e=p->vt[slot];((void (*)(void *,qword))e.fn)((char *)p+e.delta,value);}
static inline void SetAngularVelocity(OBJ*p,qword angular){
 register VENTRY*table __asm__("$3");
 __asm__("lw %0,%1":"=r"(table):"m"(p->vt));
 register int delta __asm__("$4");register void(*method)() __asm__("$2");register qword value __asm__("$5");
 __asm__("qmfc2.ni %2,%5
	lh %0,%3
	lw %1,%4":"=&r"(delta),"=&r"(method),"=&r"(value):"m"(table[36].delta),"m"(table[36].fn),"j"(angular));
 ((void(*)(void*,qword))method)((char*)p+delta,value);
}
static inline void SetStoredVelocity(OBJ*p,const U&home){
 register VENTRY*table __asm__("$3");
 __asm__("lw %0,%1":"=r"(table):"m"(p->vt));
 register int delta __asm__("$4");register void(*method)() __asm__("$2");register qword value __asm__("$5");
 __asm__("lh %0,%3
	lw %1,%4
	lq %2,%5":"=&r"(delta),"=&r"(method),"=&r"(value):"m"(table[35].delta),"m"(table[35].fn),"m"(home.q));
 ((void(*)(void*,qword))method)((char*)p+delta,value);
}
static inline void SetBasis(OBJ *p,const M3 *basis){
 register VENTRY*table __asm__("$2");
 __asm__("lw %0,%1":"=r"(table):"m"(p->vt));
 register int delta __asm__("$4");register void(*method)() __asm__("$3");
 __asm__("lh %0,%2
	lw %1,%3":"=&r"(delta),"=&r"(method):"m"(table[30].delta),"m"(table[30].fn));
 ((void(*)(void*,const M3*))method)((char*)p+delta,basis);
}
extern "C" void func_001D6B00(PARAMS *params,OBJ *p)
{
    M4 parent;
    WORK work;
    M4 predicted;
    U start,origin,destination,launch,velocity;
    OBJ *source=InitialSource(start,origin,func_001A62E8(p),params);
    FRAME *frame;
    if(source){
        VENTRY &entry=source->vt[32];
        frame=((FRAME *(*)(void *,M4 *))entry.fn)((char *)source+entry.delta,&parent);
    }else{
        frame=&D_002C44F0;
        Identity(&parent);
    }
    func_0011C168(&work.matrix,&frame->world,&parent);
    qword delta=Subtract(Point(work.matrix,params->target),start.q);
    float distance=Length(delta);
    float prediction=Clamp(Evaluate(params->prediction,distance),params->predictionLow,params->predictionHigh);
    if(prediction!=0.0f){
        func_002309E8(frame,0,&work.matrix,0,prediction);
        func_0011C168(&predicted,&work.matrix,&parent);
        delta=Subtract(Point(predicted,params->target),start.q);
    }
    distance=Length(delta);
    float displacement=Clamp(Evaluate(params->displacement,distance),params->displacementLow,params->displacementHigh);
    qword projected=OffsetNormalized(origin,delta,D_002A2DA0,displacement,work.scalar);
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
        velocity.q=SpeedNormalized(start,destination,p->speed,D_002A2DA0,work.scalar);
        SetStoredVelocity(p,velocity);
        func_0011B7E0(&work.basis,velocity.q);
        SetBasis(p,&work.basis);
    }else{
        qword acceleration=func_001F5860(p);
        SetVector(p,35,func_001D6848(params->pitch,start.q,launch.q,acceleration));
    }
    register float angularHigh __asm__("$f1")=params->angularHigh;
    if(angularHigh>0.0f){
        float magnitude=func_0011D448(params->angularLow,angularHigh);
        float x=func_0011D448(-1.0f,1.0f);
        float y=func_0011D448(-1.0f,1.0f);
        float z=func_0011D448(-1.0f,1.0f);
        register qword angularBits __asm__("$3")=Pack(x,y,z);
        SetAngularVelocity(p,AngularNormalized(angularBits,D_002A2DA0,magnitude,work.scalar));
    }
    if(func_00132B10(p,0x50)){
        work.scalar=params->target;
        VENTRY &entry=p->vt[78];
        ((void (*)(void *,OBJ *,const U *))entry.fn)((char *)p+entry.delta,params->source,&work.scalar);
    }
}

#define OFF(t,f) ((int)&((t*)0)->f)
typedef char verified_launch_initial_0[(OFF(OBJ,vt)==0xC)?1:-1];
typedef char verified_launch_initial_1[(OFF(OBJ,speed)==0x260)?1:-1];
typedef char verified_launch_initial_2[(OFF(PARAMS,target)==0x50)?1:-1];
typedef char verified_launch_initial_3[(OFF(PARAMS,source)==0x60)?1:-1];
typedef char verified_launch_initial_4[(OFF(PARAMS,prediction)==0x70)?1:-1];
typedef char verified_launch_initial_5[(OFF(PARAMS,predictionLow)==0x80)?1:-1];
typedef char verified_launch_initial_6[(OFF(PARAMS,predictionHigh)==0x84)?1:-1];
typedef char verified_launch_initial_7[(OFF(PARAMS,displacement)==0x90)?1:-1];
typedef char verified_launch_initial_8[(OFF(PARAMS,displacementLow)==0xA0)?1:-1];
typedef char verified_launch_initial_9[(OFF(PARAMS,displacementHigh)==0xA4)?1:-1];
typedef char verified_launch_initial_10[(OFF(PARAMS,angularLow)==0xA8)?1:-1];
typedef char verified_launch_initial_11[(OFF(PARAMS,angularHigh)==0xAC)?1:-1];
typedef char verified_launch_initial_12[(OFF(PARAMS,pitch)==0xB0)?1:-1];
typedef char verified_launch_initial_13[(OFF(FRAME,world)==0x40)?1:-1];
typedef char verified_launch_initial_14[(OFF(WORK,matrix)==0x0)?1:-1];
typedef char verified_launch_initial_15[(OFF(WORK,basis)==0x0)?1:-1];
typedef char verified_launch_initial_16[(OFF(WORK,scalar)==0x0)?1:-1];
typedef char verified_launch_initial_17[(OFF(VENTRY,delta)==0x0)?1:-1];
typedef char verified_launch_initial_18[(OFF(VENTRY,fn)==0x4)?1:-1];
typedef char verified_launch_initial_19[(OFF(POLY,b)==0x4)?1:-1];
typedef char verified_launch_initial_20[(OFF(POLY,c)==0x8)?1:-1];
typedef char verified_launch_initial_21[(sizeof(U)==0x10)?1:-1];
typedef char verified_launch_initial_22[(sizeof(VENTRY)==0x8)?1:-1];
typedef char verified_launch_initial_23[(sizeof(M4)==0x40)?1:-1];
typedef char verified_launch_initial_24[(sizeof(M3)==0x30)?1:-1];
typedef char verified_launch_initial_25[(sizeof(WORK)==0x40)?1:-1];
typedef char verified_launch_initial_26[(sizeof(FRAME)==0x80)?1:-1];
typedef char verified_launch_initial_27[(sizeof(qword)==16)?1:-1];
typedef char verified_launch_initial_28[(OFF(U,q)==0)?1:-1];
typedef char verified_launch_initial_29[(OFF(U,f)==0)?1:-1];
typedef char verified_launch_initial_30[(OFF(U,f[3])==0xC)?1:-1];
typedef char verified_launch_initial_31[(__alignof__(U)==16)?1:-1];
typedef char verified_launch_initial_32[(sizeof(OBJ*)==4)?1:-1];
typedef char verified_launch_initial_33[(sizeof(int)==4)?1:-1];
typedef char verified_launch_initial_34[(sizeof(float)==4)?1:-1];
typedef char verified_launch_initial_35[(sizeof(((PARAMS*)0)->source)==4)?1:-1];
typedef char verified_launch_initial_36[(sizeof(((U*)0)->q)==16)?1:-1];
