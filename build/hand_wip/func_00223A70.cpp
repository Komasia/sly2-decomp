// Complete camera segment avoidance WIP. FRAME has no instance members.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct O;
struct S {O *object;char pad[0x30];int state;};
struct CAMERA {char pad[0x48];float radius;};
struct WORLD;
extern CAMERA D_002DDF40;
extern WORLD D_003DD490;
extern float D_002A9700;
extern "C" {
void *func_001AE478(void *);
void func_001AE4A0(void *,int);
qword func_001A62E8(void *);
int func_0014F030(void *,O *);
void func_0020FAA0(WORLD *,qword,qword,int (*)(void *,O *),void *,int *,O ***);
qword func_0014EB70(int,O **,qword,float);
int func_0014EA08(int count,O **objects,qword origin,qword endpoint,float gap,float *low,float *high);
float func_00223A10(void *,qword,qword,void *);
qword func_0014EDA0(CAMERA *,int,O **,float (*)(void *,qword,qword,void *),qword,qword,float,float);
void func_0011EF08(qword,float *,float *,float *);
qword func_0011E1A0(float,float,float);
}
struct MARK {MARK(){(void)func_001AE478(this);}~MARK(){func_001AE4A0(this,2);}};
struct WORK {V minimum,maximum,origin,candidate;MARK mark;V offset,rayEnd,best,scalar;int count;O **objects;float low,high,phase,radius,height;};
static inline qword Min(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Max(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ToVF(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword Blend(qword a,qword b,qword left,qword right){__asm__("vmulax.xyzw ACC,%0,%2x\n\tvmaddx.xyzw %0,%1,%3x":"+j"(a):"j"(b),"j"(left),"j"(right));return a;}
static inline qword BlendToRight(qword a,qword b,qword left,qword right){__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%0,%3x":"+j"(b):"j"(a),"j"(left),"j"(right));return b;}
static inline void StoreVF(qword *p,qword q){__asm__("sqc2 %1,%0":"=m"(*p):"j"(q));}
static inline float Abs(float f){return __builtin_fabsf(f);}
extern "C" void func_00223A70(S *p,qword begin,qword end,qword *out){
    O *object=p->object;
    WORK w;
    qword final;
    float initialAngle=0.0f;
    float one=1.0f;
    w.minimum.q=Min(begin,Min(end,func_001A62E8(object)));
    w.maximum.q=Max(begin,Max(end,func_001A62E8(object)));
    func_0020FAA0(&D_003DD490,w.minimum.q,w.maximum.q,func_0014F030,0,&w.count,&w.objects);
    int count=w.count; O **objects=w.objects;
    w.origin.q=func_0014EB70(count,objects,func_001A62E8(object),500.0f);
    func_0014EA08(w.count,w.objects,w.origin.q,end,initialAngle,&w.low,&w.high);
    if(w.high<one){
        float angle=initialAngle;
        p->state=4;
        func_0011EF08(Sub(end,begin),&w.phase,&w.radius,&w.height);
        float bestCost=D_002A9700;
        float minGap=initialAngle;
        do{
            w.offset.q=ToVF(func_0011E1A0(w.phase+angle,w.radius,w.height));
            w.rayEnd.q=Add(begin,w.offset.q);
            func_0014EA08(w.count,w.objects,w.origin.q,w.rayEnd.q,minGap,&w.low,&w.high);
            float cost=(1.25f-w.high)*(Abs(angle)+0.47123894f);
            if(cost<bestCost){
                float left=1.0f-w.high;
                qword right=Scalar(w.high);
                bestCost=cost;
                qword a=Scalar(left);
                w.scalar.q=a;
                w.best.q=Blend(w.origin.q,w.rayEnd.q,a,right);
                w.scalar.q=right;
            }
            float next=-angle;
            if(angle<=minGap)next+=0.28559935f;
            angle=next;
            if(bestCost<(Abs(next)+0.47123894f)*0.25f)break;
        }while(angle<3.1415927f);
        w.candidate.q=w.best.q;
    }else w.candidate.q=end;
    final=ToVF(func_0014EDA0(&D_002DDF40,w.count,w.objects,func_00223A10,w.candidate.q,w.candidate.q,D_002DDF40.radius,D_002DDF40.radius));
    func_0014EA08(w.count,w.objects,w.candidate.q,final,0.0f,&w.low,&w.high);
    if(w.high!=1.0f){
        float u=(w.low+w.high)*0.5f;
        qword right=Scalar(u);
        qword left=Scalar(1.0f-u);
        w.offset.q=left;
        final=BlendToRight(w.candidate.q,final,left,right);
        w.offset.q=right;
    }
    StoreVF(out,final);
}
