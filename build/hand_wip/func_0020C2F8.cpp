typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct ALO;
struct VENTRY {short delta,pad;void (*fn)(void *,qword);};
struct SPACE {char pad0[0x70];U position;char pad80[0x20];SPACE *parent;};
struct ALO {char pad0[0xC];VENTRY *vt;char pad10[0x48];SPACE *space;char pad5C[0xEC];unsigned long flags;char pad150[0x348];void *control;};
struct ASEG;
struct ASEGA {char pad0[0x40];float playbackRate;};
struct TUNING {int unused0;ASEG *animation;int unused8;float afterStart,afterEnd,flightTime,minimumTime;int unused1C;U acceleration;};
struct P {char pad0[0x10];int state;float stateTime;char pad18[8];U previousVelocity;TUNING *tuning;ALO *subject;ASEGA *job;int index;U target;float arrival,end;ALO *related;int kind;int ballistic,steep;void *constraint;};
struct CLOCK {float time,dt;};
struct GAME;
extern CLOCK D_002DDED0;
extern GAME D_003DD490;
void ApplyAsegCur(ASEG *,ALO *,float,float,int,ASEGA **);
extern "C" {
void func_001333C0(ASEGA *,P *);
qword func_001F5860(ALO *);
int func_00132B10(ALO *,int);
void func_0020B210(ALO *);
void func_0020D178(void *);
float func_00196928(qword,qword,float,float,float,float);
qword func_0022FC48(SPACE *,SPACE *,qword);
qword func_0022FCC8(SPACE *,SPACE *,qword);
void *func_0012DE58(ALO *,SPACE *,int,qword,qword,float);
void func_00134320(GAME *,ALO *);
void func_001F5880(ALO *,qword);
void func_00130D30(ASEGA *,int,float,float);
void func_0020B2A8(ALO *,ALO *,int);
void func_0020C760(P *);
void func_0020D1A0(void *);
}
static inline qword Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword Scale(qword v,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Combine(qword a,qword x,qword b,qword y){qword r;__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(x),"j"(b),"j"(y));return r;}
static inline qword AddScaled(qword a,qword b,qword x){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(x));return r;}
static inline qword Load(const U *p){qword r;__asm__("lq %0,%1":"=r"(r):"m"(*p));return r;}
static inline float Max(float a,float b){return a<b?b:a;}
extern "C" void func_0020C2F8(P *p,int state)
{
    U scalar,delta,acceleration,velocity,finalVelocity;
    if(state==p->state)return;
    p->state=state;
    p->stateTime=D_002DDED0.time;
    switch(state){
    case 0:
        ApplyAsegCur(p->tuning->animation,p->subject,0.0f,1.0f,p->index,&p->job);
        func_001333C0(p->job,p);
        p->previousVelocity.q=func_001F5860(p->subject);
        break;
    case 1:{
        if(func_00132B10(p->subject,0x38)){
            ALO *subject=p->subject;
            func_0020B210(subject);
            func_0020D178(subject->control);
        }
        float playbackRate=p->job->playbackRate;
        qword position=p->subject->space->position.q;
        qword accelerationInput=p->tuning->acceleration.q;
        scalar.q=Scalar(playbackRate*playbackRate);
        acceleration.q=Scale(accelerationInput,scalar.q);
        delta.q=Subtract(p->target.q,position);
        float time;
        if(p->ballistic){
            float low,high,slopeLow,slopeHigh;
            if(p->related&&(func_00132B10(p->related,0x13)||func_00132B10(p->related,0xB))){
                low=1250.0f;slopeLow=1.1f;high=0.0f;slopeHigh=50.0f;
            }else if(p->steep){
                low=1500.0f;slopeLow=1.33f;high=-1500.0f;slopeHigh=-1.33f;
            }else{
                low=1250.0f;slopeLow=1.1f;high=-1250.0f;slopeHigh=-1.1f;
            }
            time=func_00196928(delta.q,acceleration.q,low,high,slopeLow,slopeHigh);
        }else time=p->tuning->flightTime/playbackRate;
        time=Max(p->tuning->minimumTime/playbackRate,time);
        ALO *subject=p->subject;
        VENTRY &entry=subject->vt[35];
        short adjustment=entry.delta;
        void (*applyVelocity)(void *,qword)=entry.fn;
        scalar.q=Scalar(1.0f/time);
        qword halfTime=Scalar(-0.5f*time);
        velocity.q=Combine(delta.q,scalar.q,acceleration.q,halfTime);
        scalar.q=halfTime;
        applyVelocity((char *)subject+adjustment,Load(&velocity));
        p->arrival=D_002DDED0.time+time;
        p->end=p->arrival-p->tuning->minimumTime/playbackRate;
        if(p->ballistic){
            scalar.q=Scalar(time);
            finalVelocity.q=AddScaled(velocity.q,acceleration.q,scalar.q);
            qword position=func_0022FC48(0,p->subject->space->parent,p->target.q);
            qword speed=func_0022FCC8(0,p->subject->space->parent,finalVelocity.q);
            p->constraint=func_0012DE58(p->subject,p->subject->space,5,position,speed,p->arrival);
            p->subject->flags|=0x04000000ul;
            func_00134320(&D_003DD490,p->subject);
        }
        func_001F5880(p->subject,acceleration.q);
        break;
    }
    case 2:func_00130D30(p->job,0,p->tuning->afterStart,1.0f);break;
    case 3:
        func_00130D30(p->job,0,p->tuning->afterEnd,1.0f);
        if(p->related)func_0020B2A8(p->subject,p->related,p->kind);
        break;
    case 4:
        if(p->ballistic)func_0020C760(p);
        func_001F5880(p->subject,p->previousVelocity.q);
        if(func_00132B10(p->subject,0x38))func_0020D1A0(p->subject->control);
        break;
    }
}
