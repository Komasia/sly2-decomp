typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct LINK {char pad0[0x54];int state;};
struct ACTOR {char pad0[0xE4];float headOffset,threshold;LINK *link;char padF0[0x18];int state,mode,choice;};
struct DISPLAY {char pad0[0x110];int actorChoice,risingChoice,fallingChoice,nearChoice,emptyChoice;};
struct MODEL {void *object;char pad4[0x1C];int state;};
struct P {int state;char pad4[0xC];U origin;char pad20[0x10];int count;ACTOR *items[1];char pad38[0x54];ACTOR *actor;float proximity,sizeGain;int rising;float choiceTime;int savedFlags;void *resource;MODEL *model;DISPLAY *primary,*secondary;int refreshPending,visible,selected,pending;};
struct CAMERA_UP_VIEW {char pad0[0x10];U up;};
struct CAMERA {char pad0[0x60];CAMERA_UP_VIEW direction;};
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
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"0"(b));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float FloatWord(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Rotate(qword q){qword r;__asm__("prot3w %0,%1":"=r"(r):"r"(q));return r;}
static inline qword Upper(qword q){qword r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(q));return r;}
static inline qword Pack(float x,float y,float z){qword r;__asm__("pextlw %0,%1,%2":"=r"(r):"r"(y),"r"(x));__asm__("pcpyld %0,%1,%2":"=r"(r):"r"(z),"r"(r));return r;}
static inline qword Screen(qword q){return Pack(FloatWord(q)*320.0f+320.0f,FloatWord(Rotate(q))*(-246.40000915527344f)+246.40000915527344f,FloatWord(Upper(q)));}
static inline float LengthXY(qword a){__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(a));return FloatWord(a);}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline void ProjectionInputs(qword point,const P &owner,const U &up,qword &pointVU,qword &offsetVU,qword &upVU,qword &argument){
 register int bits asm("$3");
 asm("lw %0,%1":"=r"(bits):"m"(owner.actor));
 register qword world asm("vf2"),height asm("vf3"),direction asm("vf1"),input asm("$5");
 asm("qmtc2.ni %5,%0\n\tlw %4,0xE4(%4)\n\tqmfc2.ni %3,%0\n\tqmtc2.ni %4,%1\n\tlqc2 %2,%7"
     :"=j"(world),"=j"(height),"=j"(direction),"=&r"(input),"+r"(bits)
     :"r"(point),"m"(((ACTOR *)bits)->headOffset),"m"(up));
 pointVU=world;offsetVU=height;upVU=direction;argument=input;
}
static inline qword HeadArgument(const U &head){
 register qword value asm("vf1");
 asm("lqc2 %0,%1":"=j"(value):"m"(head.q));
 return value;
}
static inline qword ScreenVector(qword bits){
 register qword value asm("vf2");
 asm("qmtc2.ni %1,%0":"=j"(value):"r"(bits));
 return value;
}
static inline float SizeAndPublish(U &home,float length,qword screen){
 register float result asm("$f2")=length;
 asm("mul.s %0,%0,%2\n\tsqc2 %3,%1":"+f"(result),"=m"(home.q):"f"(0.008333333767950535f),"j"(screen));
 return result;
}
static inline float LimitAndPublish(U &home,float proximity,qword screen){
 register float result asm("$f0")=1.0f;
 asm("min.s %0,%0,%2\n\tsq %3,%1":"+f"(result),"=m"(home.q):"f"(proximity),"r"(screen));
 return result;
}
static inline float ReloadGain(const float &gain){
 register float value asm("$f0");
 asm("lwc1 %0,%1":"=f"(value):"m"(gain));
 return value;
}
static inline qword BaseScreen(qword a){
 register float y asm("$f0"),x asm("$f1"),z asm("$f5");
 register qword rotated asm("$3")=Rotate(a);
 asm("mtc1 %1,%0":"=f"(y):"r"(rotated));
 asm("mtc1 %1,%0":"=f"(x):"r"(a));
 register qword upper asm("$4")=Upper(a);
 asm("mtc1 %1,%0":"=f"(z):"r"(upper));
 x=x*320.0f+320.0f;
 y=y*(-246.40000915527344f)+246.40000915527344f;
 register qword packed asm("$4");
 asm("mfc1 %0,%1\n\tmfc1 $3,%2\n\tpextlw %0,$3,%0\n\tmfc1 $3,%3\n\tpcpyld %0,$3,%0"
     :"=r"(packed):"f"(x),"f"(y),"f"(z):"$3");
 return packed;
}
static inline qword TopScreen(qword a){
 register float x asm("$f3"),y asm("$f2"),z asm("$f0");
 register qword rotated asm("$3")=Rotate(a);
 asm("mtc1 %1,%0":"=f"(x):"r"(a));
 asm("mtc1 %1,%0":"=f"(y):"r"(rotated));
 x=x*320.0f+320.0f;
 y=y*(-246.40000915527344f)+246.40000915527344f;
 register qword upper asm("$3")=Upper(a);
 asm("mtc1 %1,%0":"=f"(z):"r"(upper));
 register qword packed asm("$3");
 asm("mfc1 %0,%1\n\tmfc1 $2,%2\n\tpextlw %0,$2,%0\n\tmfc1 $2,%3\n\tpcpyld %0,$2,%0"
     :"=r"(packed):"f"(x),"f"(y),"f"(z):"$2");
 return packed;
}
static inline void PrepareHeadProjection(const U &head,qword value,CAMERA *camera,qword &saved,qword &argument,CAMERA *&receiver){
 register qword loaded asm("vf1"),retained asm("$16");
 register CAMERA *callReceiver asm("$4");
 asm("lqc2 %0,%3\n\tpor %1,$zero,%4\n\tdaddu %2,%5,$zero"
     :"=j"(loaded),"=&r"(retained),"=r"(callReceiver)
     :"m"(head.q),"r"(value),"r"(camera));
 saved=retained;argument=loaded;receiver=callReceiver;
}
static inline void ScreenGeometry(qword base,qword top,const U &origin,qword &firstVU,qword &second,qword &topVU,float &length,float &offset){
 register float baseY asm("$f0"),baseX asm("$f1"),baseZ asm("$f5");
 register float topX asm("$f3"),topY asm("$f2");
 register float width asm("$f4"),inverseY asm("$f6"),offsetY asm("$f7");
 register qword topRotated asm("$3");
 register qword upperBase asm("$4");
 {
  register qword rotated asm("$3")=Rotate(base);
  asm("li.s %0,%F1":"=f"(width):"F"(320.0f));
  asm("mtc1 %1,%0":"=f"(baseY):"r"(rotated));
 }
 asm("mtc1 %1,%0":"=f"(baseX):"r"(base));
 asm("li.s %0,%F1":"=f"(inverseY):"F"(-246.40000915527344f));
 baseX*=width;
 asm("li.s %0,%F1":"=f"(offsetY):"F"(246.40000915527344f));
 topRotated=Rotate(top);
 baseY*=inverseY;
 upperBase=Upper(base);
 baseX+=width;
 asm("mtc1 %1,%0":"=f"(topX):"r"(top));
 asm("mtc1 %1,%0":"=f"(topY):"r"(topRotated));
 baseY+=offsetY;
 register qword originVector asm("vf1");
 asm("lqc2 %0,%1":"=j"(originVector):"m"(origin.q));
 asm("mtc1 %1,%0":"=f"(baseZ):"r"(upperBase));
 {
  register qword first asm("$4");
  asm("mfc1 %0,%1\n\tmfc1 $3,%2\n\tpextlw %0,$3,%0\n\tmfc1 $3,%3\n\tpcpyld %0,$3,%0"
       :"=r"(first):"f"(baseX),"f"(baseY),"f"(baseZ):"$3");
  topX*=width;
  firstVU=ScreenVector(first);
 }
 topY*=inverseY;
 register qword distance asm("vf1")=originVector;
 asm("vsub.xyzw %0,%1,%0":"+j"(distance):"j"(firstVU));
 register qword upperTop asm("$3")=Upper(top);
 asm("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(distance));
 topX+=width;topY+=offsetY;
 register float topZ asm("$f0");
 asm("mtc1 %1,%0":"=f"(topZ):"r"(upperTop));
 register int distanceWord asm("$4");
 asm("qmfc2.ni %0,%1":"=r"(distanceWord):"j"(distance));
 {
  register qword packed asm("$3");
  asm("mfc1 %0,%1\n\tmfc1 $2,%2\n\tpextlw %0,$2,%0\n\tmfc1 $2,%3\n\tpcpyld %0,$2,%0"
       :"=r"(packed):"f"(topX),"f"(topY),"f"(topZ):"$2");
  second=packed;
 }
 register float baseDistance asm("$f1"),radiusOffset asm("$f8");
 register qword topVector asm("vf3");
 asm("li.s %0,%F3\n\tmtc1 %4,%1\n\tqmtc2.ni %5,%2"
      :"=f"(radiusOffset),"=f"(baseDistance),"=j"(topVector)
      :"F"(128.0f),"r"(distanceWord),"r"(second));
 length=baseDistance;offset=radiusOffset;topVU=topVector;
}
static inline float SizeDistance(qword first,qword second){
 register qword distance asm("vf1");
 asm("vsub.xyzw %0,%1,%2":"=j"(distance):"j"(first),"j"(second));
 asm("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(distance));
 return FloatWord(distance);
}
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
        register CAMERA_UP_VIEW *direction asm("$17")=&D_002DDF40.direction;
        qword worldVU,offsetVU,upVU,argument;
        ProjectionInputs(world,*p,direction->up,worldVU,offsetVU,upVU,argument);
        scalar.q=offsetVU;
        head.q=Add(worldVU,Scale(upVU,scalar.q));
        register CAMERA *camera asm("$17")=(CAMERA *)((char*)direction-0x60);
        qword projectedBase=func_0014F308(camera,argument);
        qword base,headValue;
        CAMERA *headCamera;
        PrepareHeadProjection(head,projectedBase,camera,base,headValue,headCamera);
        qword top=func_0014F308(headCamera,headValue);
        qword firstVU;
        register qword second asm("$3");
        float baseDistance,radiusOffset;
        qword topVU;
        ScreenGeometry(base,top,p->origin,firstVU,second,topVU,baseDistance,radiusOffset);
        float proximity=1.0f-(baseDistance-radiusOffset)*0.0078125f;
        float size=SizeAndPublish(scalar,SizeDistance(firstVU,topVU),firstVU);
        p->rising=1;
        p->proximity=Max(0.0f,LimitAndPublish(scalar,proximity,second));
        p->sizeGain=size;
        if(size>1.0f){p->rising=0;p->sizeGain=2.0f-size;}
        p->sizeGain=Max(ReloadGain(p->sizeGain),0.0f);
    }
    switch(p->state){
    case -1:break;
    case 2:
        if(p->actor&&p->actor->state!=2)func_00202768(p,4);
        break;
    case 4:
        if(!p->actor)goto no_actor;
        else if(p->actor->state==3)func_00202768(p,3);
        else if(p->proximity>=1.0f){
            if(p->rising)func_00202768(p,5);
            else func_00202768(p,6);
        }
        break;
    case 3:
        if(!p->actor)goto no_actor;
        else if(p->actor->state!=3)func_00202768(p,4);
        break;
    case 5:
        if(!p->actor)goto no_actor;
        else if(p->proximity<1.0f)func_00202768(p,4);
        else if(p->sizeGain>=1.0f-p->actor->threshold)func_00202768(p,7);
        else func_00212E40(p->secondary,0x35A,p->sizeGain);
        break;
    case 6:
        if(!p->actor)goto no_actor;
        else if(p->proximity<1.0f)func_00202768(p,4);
        else if(p->sizeGain>=1.0f-p->actor->threshold)func_00202768(p,7);
        else func_00212E40(p->secondary,0x35A,p->sizeGain);
        break;
    case 7:
        if(p->actor){
            if(p->proximity<1.0f||p->sizeGain<1.0f-p->actor->threshold){
                if(p->rising)func_00202768(p,5);
                else func_00202768(p,6);
            }
            break;
        }
no_actor:
        func_00202768(p,2);
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
            long ready=1;
            for(int i=0;i<p->count;i++){
                ACTOR *actor=p->items[i];
                int returned=func_00203758(actor);
                int done;
                LINK *link;
                {
                    register int status asm("$3");
                    register LINK *current asm("$2");
                    asm("daddu %0,%2,$zero\n\tlw %1,%3"
                       :"=&r"(status),"=r"(current):"r"(returned),"m"(actor->link));
                    done=status;link=current;
                }
                long active=0;
                if(link){if(link->state==1)active=1;}
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
    if(p->model->state==1)goto finished;
    {
        int activeState=p->state;
        if(activeState<2)goto finished;
        if(activeState<7)goto ordinary_input;
        if(activeState==7)goto near_input;
        goto finished;
    }
ordinary_input:
    if(!func_0014FD50((char *)&D_002DDF40+0x3A0)&&func_001C46C0(D_002E1E40->control,10,0.0f))func_00202768(p,8);
    goto finished;
near_input:
    if(!func_0014FD50((char *)&D_002DDF40+0x3A0)&&func_001C46C0(D_002E1E40->control,250,0.0f))func_00202768(p,8);
finished:;
}
