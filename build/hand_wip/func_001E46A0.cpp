typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U {qword q;float f[4];};
union ARG {int id;float gain;};
struct PATH {char padE4[0xE4];int cyclic;};
struct PARAM {int kind;char pad4[0xC];int target;ARG value;char pad18[0xC];int flag;};
struct ACTOR {char pad4C8[0x4C8];int mode,active;int word4D0;PATH *motion;int word4D8;float motionTime;char pad4E0[0xA7C];PATH *curve;float curveTime;char padF64[0xA8C];qword oldPosition;char pad1A00[0x20];qword position;};
struct P {char pad40[0x40];PARAM *param;ACTOR *actor;int blocked;char pad4C[0x2C];float previousMotion,previousCurve;};
struct OUTPUT {char pad10[0x10];float x,y,heading,speed;char pad20[0x10];uint flags;};
struct WORK {U from,to,normal;float heading;qword first,second;};
extern "C" {
extern qword D_002A2DA0;
extern float D_002C3630[3],D_002BBB60[2],D_002C3640;
float func_001E6728(PATH*,float);
void func_001E6F10(PATH*,qword*,qword*,float);
qword func_001C4768(OUTPUT*,qword);
float func_002458F0(float,float);
float func_001E6648(PATH*),func_001E6630(PATH*);
float func_0011CF60(float);
ACTOR *func_001E1DB8(P*,int);
void func_001E4D40(P*,ACTOR*,qword*,float*);
void func_00204660(ACTOR*,float);
void func_001E67B8(PATH*,float,qword*,qword*);
qword func_001A62E8(ACTOR*);
qword func_001A6FC0(void*,ACTOR*,qword);
void func_001C45A8(OUTPUT*);
int func_0011D4D0(float,float,float);
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ToVU(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline float X(qword a){float r;__asm__("mtc1 %1,%0":"=f"(r):"r"(a));return r;}
static inline float Y(qword a){float r;__asm__("prot3w %0,%1":"=r"(r):"r"(a));return r;}
static inline float Z(qword a){float r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(a));return r;}
static inline qword Square(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Root(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword ReadPacked(const qword &a){qword r;__asm__("lq %0,%1":"=r"(r):"m"(a));return r;}
static inline qword NormalizeOr(qword a,const qword &fallback){qword length=Root(Square(a)),alternative=ReadPacked(fallback);if(X(length)<0.0001f)return ToVU(alternative);return Divide(a,length);}
static inline qword Normalize(qword a){return Divide(a,Root(Square(a)));}
static inline float LengthXY(qword a){qword r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));return X(Root(r));}
static inline void WriteVector(U &out,qword a){__asm__("sqc2 %1,%0":"=m"(out.q):"j"(a));}
extern "C" void func_001E46A0(P *p,OUTPUT *out){
 WORK work;PARAM *param=p->param;ACTOR *actor=p->actor;
 switch(param->kind){
 case 0x1A:{
  int reverse=0;
  float t=func_001E6728(actor->curve,actor->curveTime+50.0f);
  func_001E6F10(actor->curve,&work.from.q,0,t);
  t=func_001E6728(actor->curve,actor->curveTime-50.0f);
  func_001E6F10(actor->curve,&work.to.q,0,t);
  qword direction=func_001C4768(out,Sub(work.from.q,work.to.q));
  float x=X(direction),y=Y(direction);
  out->heading=func_002458F0(y,x);out->x=x;out->y=y;
  if(actor->curve->cyclic){
   float forward,backward;
   if(p->previousCurve<actor->curveTime){forward=actor->curveTime-p->previousCurve;backward=func_001E6648(actor->curve)+p->previousCurve-actor->curveTime;}
   else {backward=p->previousCurve-actor->curveTime;forward=func_001E6648(actor->curve)+actor->curveTime-p->previousCurve;}
   if(forward<backward)reverse=1;
  }else if(p->previousCurve<actor->curveTime)reverse=1;
  if(reverse){out->heading=func_0011CF60(out->heading+3.1415927f);out->x=-out->x;out->y=-out->y;}
  out->speed=1.0f;break;
 }
 case 0x1D:case 0x1E:case 0x1F:case 0x20:case 0x21:case 0x22:
 stopped:
  out->speed=0.0f;if(actor->active!=-1)out->flags|=0x20;break;
 case 0x23:{
  ACTOR *target=func_001E1DB8(p,param->value.id);
  if(!target)goto stopped;
  func_001E4D40(p,target,0,&work.heading);
  func_00204660(actor,work.heading);out->heading=work.heading;
  goto stopped;
 }
 case 0x24:{
  out->speed=__builtin_fabsf(param->value.gain);
  if(param->flag)out->flags|=8;
  ACTOR *target=func_001E1DB8(p,param->target);
  if(!target)goto activityFlags;
  if(actor->active!=-1&&actor->mode==3){
   PATH *motion=actor->motion;
   func_001E67B8(motion,actor->motionTime,&work.from.q,&work.to.q);
   work.to.f[2]=0.0f;WriteVector(work.to,NormalizeOr(work.to.q,D_002A2DA0));
   int reverse=0;
   out->heading=func_002458F0(work.to.f[1],work.to.f[0]);
   if(motion->cyclic){
    float forward,backward;
    if(p->previousMotion<actor->motionTime){forward=actor->motionTime-p->previousMotion;backward=func_001E6630(motion)+p->previousMotion-actor->motionTime;}
    else {backward=p->previousMotion-actor->motionTime;forward=func_001E6630(motion)+actor->motionTime-p->previousMotion;}
    if(forward<backward)reverse=1;
   }else if(p->previousMotion<actor->motionTime)reverse=1;
   if(reverse)out->heading=func_0011CF60(out->heading+3.1415927f);
  }else{
   func_001E4D40(p,target,&work.from.q,0);
   work.first=work.from.q;
   work.to.q=Sub(work.first,ToVU(func_001A62E8(actor)));
   out->heading=func_002458F0(work.to.f[1],work.to.f[0]);
   float distance=LengthXY(work.to.q);
   float gain=D_002C3630[0]+distance*(D_002C3630[1]+distance*D_002C3630[2]);
   float low=D_002BBB60[0],high=D_002BBB60[1];
   if(gain<low)gain=low;else if(high<gain)gain=high;
   out->speed*=gain;
  }
 }
 activityFlags:
  if(actor->active!=-1&&(actor->mode==0||actor->mode==0xD))out->flags|=0x20;
  break;
 case 0x29:{
  out->speed=__builtin_fabsf(param->value.gain);
  ACTOR *target=func_001E1DB8(p,param->target);
  if(!target||actor->active==-1||actor->mode!=8)break;
  func_001E4D40(p,target,&work.from.q,0);
  work.second=work.from.q;
  work.to.q=Sub(work.second,ToVU(func_001A62E8(actor)));
  work.to.f[2]=0.0f;
  work.normal.q=Normalize(ToVU(func_001A6FC0(0,actor,work.to.q)));
  out->y=work.normal.f[0]*out->speed;out->x=-work.normal.f[1]*out->speed;
  break;
 }
 case 0x58:
  out->speed=0.0f;out->flags|=0x20;func_001C45A8(out);break;
 case 0x5A:{
  float tolerance=D_002C3640;
  qword oldPosition=actor->oldPosition,position=actor->position;
  int near=0;
  if(func_0011D4D0(X(position),X(oldPosition),tolerance)&&func_0011D4D0(Y(position),Y(oldPosition),tolerance)&&func_0011D4D0(Z(position),Z(oldPosition),tolerance))near=1;
  if(near)out->flags|=0x40;
  out->speed=0.0f;func_001C45A8(out);break;
 }
 case 0x2A:out->speed=0.0f;break;
 case 0x50:p->blocked=1;break;
 case 0x51:p->blocked=0;break;
 }
 if(p->blocked){out->flags|=0x10;if(param->kind==0x50)func_001C45A8(out);}
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char controller_action_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(ARG)==4 && sizeof(PARAM)==0x28 && sizeof(WORK)==0x60 && OFF(PARAM,kind)==0 && OFF(PARAM,target)==0x10 && OFF(PARAM,value)==0x14 && OFF(PARAM,flag)==0x24 && OFF(ACTOR,mode)==0x4C8 && OFF(ACTOR,active)==0x4CC && OFF(ACTOR,motion)==0x4D4 && OFF(ACTOR,motionTime)==0x4DC && OFF(ACTOR,curve)==0xF5C && OFF(ACTOR,curveTime)==0xF60 && OFF(ACTOR,oldPosition)==0x19F0 && OFF(ACTOR,position)==0x1A20 && OFF(PATH,cyclic)==0xE4 && OFF(P,param)==0x40 && OFF(P,actor)==0x44 && OFF(P,blocked)==0x48 && OFF(P,previousMotion)==0x78 && OFF(P,previousCurve)==0x7C && OFF(OUTPUT,x)==0x10 && OFF(OUTPUT,y)==0x14 && OFF(OUTPUT,heading)==0x18 && OFF(OUTPUT,speed)==0x1C && OFF(OUTPUT,flags)==0x30 && OFF(WORK,from)==0 && OFF(WORK,to)==0x10 && OFF(WORK,normal)==0x20 && OFF(WORK,heading)==0x30 && OFF(WORK,first)==0x40 && OFF(WORK,second)==0x50)?1:-1];
