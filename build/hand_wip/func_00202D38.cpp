typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct LINK {char pad0[0x54];int state;};
struct ACTOR {char pad0[0xE4];float headOffset,threshold;LINK *link;char padF0[0x18];int state,mode;void *choice;};
struct DISPLAY {char pad0[0x110];void *actorChoice,*risingChoice,*fallingChoice,*nearChoice,*emptyChoice;};
struct MODEL {void *object;char pad4[0x1C];int state;};
struct P {int state;char pad4[0xC];U origin;char pad20[0x10];int count;ACTOR *items[1];char pad38[0x54];ACTOR *actor;float proximity,sizeGain;int rising;float choiceTime;int savedFlags;void *resource;MODEL *model;DISPLAY *primary,*secondary;int refreshPending,visible;void *selected,*pending;};
struct CAMERA {char pad0[0x70];U up;};
struct CLOCK {float time,dt;};
struct PLAYER {char pad0[0x150];void *control;};
extern CAMERA D_002DDF40;
extern CLOCK D_002DDED0;
extern PLAYER *D_002E1E40;
extern "C" {
void func_0019CCE8(MODEL *);
void func_00213928(DISPLAY *,int);
void func_00202540(P *);
void func_002020C8(P *);
int func_002022D8(P *);
void func_00202768(P *,int);
qword func_001A62E8(ACTOR *);
qword func_0014F308(CAMERA *,qword);
void func_00212E40(DISPLAY *,int,float);
int func_002121E8(DISPLAY *,int);
void func_00213B00(DISPLAY *,int);
int func_00203758(ACTOR *);
int func_0014FD50(void *);
int func_001C46C0(void *,unsigned int,float);
}
static inline qword Scalar(const float *p){qword r,b;__asm__("lw %0,%1":"=r"(b):"m"(*p));__asm__("qmtc2 %1,%0":"=j"(r):"r"(b));return r;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float FloatWord(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Rotate(qword q){qword r;__asm__("prot3w %0,%1":"=r"(r):"r"(q));return r;}
static inline qword Upper(qword q){qword r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(q));return r;}
static inline qword Pack(float x,float y,float z){qword r;__asm__("pextlw %0,%1,%2":"=r"(r):"r"(y),"r"(x));__asm__("pcpyld %0,%1,%2":"=r"(r):"r"(z),"r"(r));return r;}
static inline qword Screen(qword q){return Pack(FloatWord(q)*320.0f+320.0f,FloatWord(Rotate(q))*(-246.40000915527344f)+246.40000915527344f,FloatWord(Upper(q)));}
static inline float LengthXY(qword a){__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(a));return FloatWord(a);}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a<b?b:a;}
extern "C" void func_00202D38(P *p)
{
    U scalar,head;
    if(!p->primary)return;
    if(!p->secondary)return;
    if(p->refreshPending){p->refreshPending=0;func_0019CCE8(p->model);}
    if(p->choiceTime+5.0f<D_002DDED0.time)func_00213928(p->primary,0x35B);
    if(p->state<8){if(p->state>=2){
        func_00202540(p);
        func_002020C8(p);
        if(!func_002022D8(p))func_00202768(p,1);
    }
    }
    if(p->actor){
        qword world=func_001A62E8(p->actor);
        CAMERA *camera=&D_002DDF40;
        scalar.q=Scalar(&p->actor->headOffset);
        head.q=Add(world,Scale(camera->up.q,scalar.q));
        qword base=func_0014F308(camera,world);
        qword top=func_0014F308(camera,head.q);
        qword first=Screen(base);
        qword second=Screen(top);
        float proximity=1.0f-(LengthXY(Subtract(first,p->origin.q))-128.0f)*0.0078125f;
        float size=LengthXY(Subtract(first,second))*0.008333333767950535f;
        p->rising=1;
        p->proximity=Max(0.0f,Min(1.0f,proximity));
        p->sizeGain=size;
        if(size>1.0f){p->rising=0;p->sizeGain=2.0f-size;}
        p->sizeGain=Max(p->sizeGain,0.0f);
    }
    switch(p->state){
    case -1:break;
    case 2:
        if(p->actor&&p->actor->state!=2)func_00202768(p,2);
        break;
    case 4:
        if(!p->actor)func_00202768(p,2);
        else if(p->actor->state==3)func_00202768(p,3);
        else if(p->proximity>=1.0f){
            if(p->rising)func_00202768(p,5);
            else func_00202768(p,6);
        }
        break;
    case 3:
        if(!p->actor)func_00202768(p,2);
        else if(p->actor->state!=3)func_00202768(p,4);
        break;
    case 5:
        if(!p->actor)func_00202768(p,2);
        else if(p->proximity<1.0f)func_00202768(p,4);
        else if(p->sizeGain>=1.0f-p->actor->threshold)func_00202768(p,7);
        else func_00212E40(p->secondary,0x35A,p->sizeGain);
        break;
    case 6:
        if(!p->actor)func_00202768(p,2);
        else if(p->proximity<1.0f)func_00202768(p,4);
        else if(p->sizeGain>=1.0f-p->actor->threshold)func_00202768(p,7);
        else func_00212E40(p->secondary,0x35A,p->sizeGain);
        break;
    case 7:
        if(!p->actor)func_00202768(p,2);
        else if(p->proximity<1.0f||p->sizeGain<1.0f-p->actor->threshold){
            if(p->rising)func_00202768(p,5);
            else func_00202768(p,6);
        }
        break;
    case 8:
        if(!func_002121E8(p->primary,0x358)){
            int changed=0;
            if(p->actor&&p->actor->state==1&&p->proximity>=1.0f&&p->sizeGain>=1.0f-p->actor->threshold){
                if(!p->actor->mode)func_00202768(p,9);
                else{p->pending=p->actor->choice;func_00202768(p,7);changed=1;}
            }else if(p->actor&&p->actor->state!=1){
                p->pending=p->primary->actorChoice;func_00202768(p,3);changed=1;
            }else if(p->proximity>=1.0f&&p->rising){
                p->pending=p->primary->risingChoice;func_00202768(p,5);changed=1;
            }else if(p->proximity>=1.0f&&!p->rising){
                p->pending=p->primary->fallingChoice;func_00202768(p,6);changed=1;
            }else if(p->actor){
                p->pending=p->primary->nearChoice;func_00202768(p,4);changed=1;
            }else{
                p->pending=p->primary->emptyChoice;func_00202768(p,2);changed=1;
            }
            if(changed){func_00213B00(p->primary,0x35B);p->choiceTime=D_002DDED0.time;}
        }
        break;
    case 9:
        if(!func_002121E8(p->primary,0x35C)){
            func_00202768(p,2);
            int ready=1;
            for(int i=0;i<p->count;i++){
                ACTOR *actor=p->items[i];
                int done=func_00203758(actor);
                int active=actor->link&&actor->link->state==1;
                if(!done&&active){ready=0;break;}
            }
            if(ready)p->refreshPending=1;
        }
        break;
    case 10:
        if(!func_002121E8(p->primary,0x314))func_00202768(p,-1);
        break;
    case 0:
        if(func_002121E8(p->primary,0x314))func_00202768(p,1);
        break;
    case 1:
        func_002020C8(p);
        if(func_002022D8(p))func_00202768(p,2);
        break;
    }
    if(p->model->state!=1){
        if(p->state>=2){
            if(p->state<7){
                if(!func_0014FD50((char *)&D_002DDF40+0x3A0)&&func_001C46C0(D_002E1E40->control,10,0.0f))func_00202768(p,8);
            }else if(p->state==7){
                if(!func_0014FD50((char *)&D_002DDF40+0x3A0)&&func_001C46C0(D_002E1E40->control,250,0.0f))func_00202768(p,8);
            }
        }
    }
}
