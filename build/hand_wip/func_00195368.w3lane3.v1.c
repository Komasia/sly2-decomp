// w3lane3 v1: aligned 12, no pins, no allocation-only operands. Guard n--;if(n>=0){inits; do{}while(--n>=0);} + inline SampleSource wrapper (stops gcse PRE hoisting &work addresses). Left: produced/ageOut s3/s4 swap + inner-preheader schedule.
// w2lane2 v3: aligned 11 (all registers match; only the inner-loop preheader init order differs). Allocation-only operands (commented below) raise produced/ageOut/originOut/spec priorities.
typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];}U;
struct VT{short delta,pad;void*fn;};
struct SAMPLE{char pad[0x20];struct VT*vt;};
struct SOURCE{int reserved;struct SAMPLE*sample;int reserved8,id;int reserved10,reserved14;float parameter;char pad[0x30-0x1C];};
struct RANGE{float lo,hi;};
struct SPEC{struct RANGE scale;char pad8[0x3C-8];float life;char pad40[8];struct RANGE offset,age;};
struct REP{char pad[0x50];struct SPEC spec;};
struct EMITTER{char pad[0xE0];int dirty;struct REP*rep;char padE8[0xFC-0xE8];float rate;char pad100[0x150-0x100];void*instance;};
struct P{char pad[0x12F8];struct EMITTER*emitter;};
struct CONTEXT{void**instance;int reserved;struct EMITTER*emitter;};
union WORK{struct {U origin,rawVelocity,scaledVelocity,scalar;}sample;struct CONTEXT context;};
struct CLOCK{float t,dt;};
extern struct CLOCK D_002DDED0;
void OnEmitterValuesChanged(struct EMITTER*)__asm__("OnEmitterValuesChanged__FP7EMITTER");
float func_0011D448(float,float);
void*func_002333B4(void*,int,unsigned int);
void func_0015B428(struct REP*,struct CONTEXT*,int,U*,U*,float*,float*,void*,void*);
static inline int Bits(float f){union{float f;int i;}u;u.f=f;return u.i;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(Bits(f)));return r;}
static inline qword Scalar2(float f,void*p,void*q,void*s){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(Bits(f)),"r"(p),"r"(q),"r"(s));return r;}
static inline qword Scale(qword v,qword k){__asm__("vmulx.xyzw %0,%0,%1x":"+j"(v):"j"(k),"j"(v));return v;}
static inline qword AddScaled(qword a,qword b,qword k){__asm__("vadda.xyzw $ACC,%0,$vf0
	vmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(k),"j"(b));return a;}
static inline void LoadAcc(qword a){__asm__ volatile("vadda.xyzw $ACC,%0,$vf0"::"j"(a));}
static inline qword MaddScaled(qword b,qword k){qword r;__asm__ volatile("vmaddx.xyzw %0,%1,%2x":"=j"(r):"j"(b),"j"(k));return r;}
static inline void SampleSource(struct SOURCE*source,union WORK*pw){struct SAMPLE*sample=source->sample;struct VT*vt=sample->vt;((void(*)(void*,U*,U*,float))vt[5].fn)((char*)sample+vt[5].delta,&pw->sample.origin,&pw->sample.rawVelocity,source->parameter);}
void func_00195368(void*unused,struct P*p,int sourceCount,struct SOURCE*sources){
    U vectors[20];float ages[10],ends[10];
    struct EMITTER*emitter=p->emitter;
    struct SPEC*spec;
    int produced;
    int i;
    union WORK work;
    if(!emitter)return;
    if(emitter->dirty)OnEmitterValuesChanged(emitter);
    spec=&emitter->rep->spec;
    produced=0;
    for(i=0;i<sourceCount;i++){
        struct SOURCE*source=&sources[i];
        float amount,random;
        int n;
        if(source->id==-1)continue;
        amount=emitter->rate*D_002DDED0.dt;
        random=func_0011D448(0.0f,1.0f);
        n=(int)amount;
        amount-=(float)n;
        if(random<amount)n++;
        n--;
        if(n>=0){
        struct RANGE*ageRange=&spec->age;
        struct RANGE*offsetRange=&spec->offset;
        U*originOut=vectors+produced;
        float*ageOut=ages+produced;float*endOut=ends+produced;
        do{
            float age;
            qword k;
            SampleSource(source,&work);
            k=Scalar(func_0011D448(spec->scale.lo,spec->scale.hi));
            work.sample.scalar.q=k;
            work.sample.scaledVelocity.q=Scale(work.sample.rawVelocity.q,k);
            {float now=D_002DDED0.t;age=now-func_0011D448(spec->age.lo,ageRange->hi);}
            *ageOut=age;
            *endOut=age+spec->life;
            if(spec->offset.lo!=spec->offset.hi){
                qword point=work.sample.origin.q;
                k=Scalar(func_0011D448(spec->offset.lo,offsetRange->hi));
                work.sample.scalar.q=k;
                work.sample.origin.q=AddScaled(point,work.sample.scaledVelocity.q,k);
            }
            *originOut=work.sample.origin;
            originOut[10]=work.sample.scaledVelocity;
            produced++;originOut++;ageOut++;endOut++;
            if((unsigned int)produced>=10)goto submit;
        }while(--n>=0);
        }
    }
submit:
    if(produced>0){
        func_002333B4(&work.context,0,sizeof(work.context));
        work.context.instance=&emitter->instance;
        work.context.emitter=emitter;
        func_0015B428(emitter->rep,&work.context,produced,vectors,vectors+10,ages,ends,0,0);
    }
}
