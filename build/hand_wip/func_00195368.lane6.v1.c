// WIP: emitter sampling; 111/168 instruction differences.
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
struct INPUT{int count;struct SOURCE*entries;int index;};
struct CLOCK{float t,dt;};
extern struct CLOCK D_002DDED0;
void OnEmitterValuesChanged(struct EMITTER*)__asm__("OnEmitterValuesChanged__FP7EMITTER");
float func_0011D448(float,float);
void*func_002333B4(void*,int,unsigned int);
void func_0015B428(struct REP*,struct CONTEXT*,int,U*,U*,float*,float*,void*,void*);
static inline int CurrentRound(float f){float word;int n;__asm__("cvt.w.s %1,%2
	mfc1 %0,%1":"=r"(n),"=&f"(word):"f"(f));return n;}

static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword Scale(qword v,qword k){__asm__("vmulx.xyzw %0,%0,%1x":"+j"(v):"j"(k));return v;}
static inline qword AddScaled(qword a,qword b,qword k){__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(k));return a;}
void func_00195368(void*unused,struct P*p,int sourceCount,struct SOURCE*sources){
    U vectors[20];float ages[10],ends[10];
    struct EMITTER*emitter=p->emitter;
    struct SPEC*spec;
    int produced;
    union WORK work;
    {
    struct INPUT input;input.count=sourceCount;input.entries=sources;
    if(!emitter)return;
    if(emitter->dirty)OnEmitterValuesChanged(emitter);
    spec=&emitter->rep->spec;
    input.index=0;
    for(produced=0;input.index<input.count;input.index++){
        struct SOURCE*source=&input.entries[input.index];
        float amount,random;
        int n;
        if(source->id==-1)continue;
        amount=emitter->rate*D_002DDED0.dt;
        random=func_0011D448(0.0f,1.0f);
        n=CurrentRound(amount);
        amount-=(float)n;
        if(random<amount)n++;
        {
        struct RANGE*offsetRange=&spec->offset;
        struct RANGE*ageRange=&spec->age;
        U*originOut=vectors+produced;
        float*ageOut=ages+produced;float*endOut=ends+produced;
        for(n--;n>=0;n--){
            struct SAMPLE*sample=source->sample;
            struct VT*vt=sample->vt;
            float age;
            qword k;
            ((void(*)(void*,U*,U*,float))vt[5].fn)((char*)sample+vt[5].delta,&work.sample.origin,&work.sample.rawVelocity,source->parameter);
            k=Scalar(func_0011D448(spec->scale.lo,spec->scale.hi));
            work.sample.scalar.q=k;
            work.sample.scaledVelocity.q=Scale(work.sample.rawVelocity.q,k);
            {float now=D_002DDED0.t;age=now-func_0011D448(spec->age.lo,ageRange->hi);}
            *ageOut=age;
            *endOut=age+spec->life;
            if(spec->offset.lo!=offsetRange->hi){
                qword point=work.sample.origin.q;
                k=Scalar(func_0011D448(spec->offset.lo,offsetRange->hi));
                work.sample.scalar.q=k;
                work.sample.origin.q=AddScaled(point,work.sample.scaledVelocity.q,k);
            }
            *originOut=work.sample.origin;
            originOut[10]=work.sample.scaledVelocity;
            produced++;originOut++;ageOut++;endOut++;
            if((unsigned int)produced>=10)goto submit;
        }
        }
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
