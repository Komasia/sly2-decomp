// Transition controller states and select the corresponding animation.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct O;
struct S;
struct ASEG;
struct ASEGA;
struct WORLD;
struct VE {short delta,pad;union {void (*plain)(void *);void (*integer)(void *,int);void (*vector)(void *,qword);} f;};
struct CONTROL {char pad[0xA0];O *selected;};
struct HANDLE {O *object;};
struct O {char pad[0xC];VE *vt;int id;char pad14[0x148];int actorId;char pad160[0x30];V target;char pad1A0[4];int movement;char pad1A8[0x38];V direction;char pad1F0[0x710];CONTROL controller;char pad9A4[0x68C];ASEGA *animation;HANDLE extra;char pad1038[0x7C8];int playerState;};
struct EFFECT {char pad[0xC];VE *vt;char pad10[0x144];int active,count;void *records;int reset;};
struct S {O *owner;int state;float time;O *peer,*selected;char pad14[0x2C];float blend0;char pad44[8];float blend1;char pad50[8];ASEG *animation0,*animation1,*animation2,*animation3;char pad68[0x30];ASEG *animation4,*animation5,*animation6;char padA4[0x18];ASEG *animation7;V targetLocal,secondary,targetWorld,velocity;char pad100[0x28];int field128;EFFECT *effect;float distance;};
struct CLOCK {float t,dt;};
struct WORK {V scalar,saved,coefficient,velocity,point;};
extern O *D_002DD5BC;
extern WORLD D_003DD490;
extern CLOCK D_002DDED0;
extern V D_002A2DC0,D_002A2DA0,D_002A2DD0;
extern "C" {
void func_001CD098(CONTROL *,O *);
void func_001CD2C0(CONTROL *);
int func_00132B10(O *,int);
void func_00134320(WORLD *,O *);
float func_00204740(O *);
void func_00204660(O *,float);
qword func_001A62E8(O *);
void func_002046B0(O *,qword);
void func_00136530(O *,int);
void func_001A58D0(O *,int,int);
void func_001F7BF8(O *,float);
void func_001384C0(ASEG *);
qword func_001A6F00(O *,O *,qword);
void func_0021FB70(S *,int);
void func_00141CD0(O *,int);
void func_001F15B8(HANDLE *);
void func_001305B8(ASEG *,O *,float,float,int,ASEGA **);
}
static inline void IntCall(O *o,int slot,int value){VE *v=o->vt;v[slot].f.integer((char *)o+v[slot].delta,value);}
static inline void PlainCall(O *o,int slot){VE *v=o->vt;v[slot].f.plain((char *)o+v[slot].delta);}
static inline void EffectCall(EFFECT *o,int slot){VE *v=o->vt;v[slot].f.plain((char *)o+v[slot].delta);}
static inline void VectorCall(O *o,int slot,qword value){VE *v=o->vt;v[slot].f.vector((char *)o+v[slot].delta,value);}
static inline qword LoadUp(){register qword q __asm__("vf1");__asm__("lqc2 %0,0(%1)":"=j"(q):"r"(&D_002A2DC0),"m"(D_002A2DC0));return q;}
static inline qword PointVF(qword q){register qword r __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword RestorePoint(const V &v){register qword q __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword LaunchUp(){register qword q __asm__("vf2");__asm__("lqc2 %0,0(%1)":"=j"(q):"r"(&D_002A2DC0),"m"(D_002A2DC0));return q;}
static inline qword LaunchSpeed(const V &v){register qword q __asm__("vf4");__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword LaunchCurrent(qword position){register qword value asm("vf1");asm("qmtc2.ni %1,%0":"=j"(value):"r"(position));return value;}
static inline qword ToVF(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword CPUFloat(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Scalar(float f){register qword r __asm__("vf1");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword LoadVF(const V &v){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword DotV(qword a,qword b){register qword d __asm__("vf2"),one __asm__("vf4");__asm__("vmul.xyz %0,%1,%2":"=j"(d):"j"(a),"j"(b));__asm__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));return d;}
static inline qword LengthV(qword v){register qword d __asm__("vf1"),one __asm__("vf2");__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline qword Scale(qword v,qword k){__asm__("vmulx.xyzw %0,%1,%0x":"+j"(k):"j"(v));return k;}
static inline qword NormalizeLength(qword v,qword length){__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,Q":"+j"(v):"j"(length));return v;}
static inline qword Launch(qword direction,qword speed,qword up,qword height){__asm__("vmulax.xyzw ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(speed):"j"(direction),"j"(up),"j"(height));return speed;}
static inline qword LaunchOperands(float height,const V &coefficient,qword &speed,O *&receiver,int &flag){
 register qword scalar asm("vf1"),velocity asm("vf4");register O *player asm("$4");register int one asm("$5");
 asm("addiu %3,$zero,1\n\tmfc1 $3,%4\n\tqmtc2.ni $3,%0\n\tlqc2 %1,%5\n\tlw %2,%6":"=j"(scalar),"=j"(velocity),"=r"(player),"=&r"(one):"f"(height),"m"(coefficient.q),"m"(D_002DD5BC):"$3");speed=velocity;receiver=player;flag=one;return scalar;
}
static inline void ZeroXYZ(V &v){v.f[0]=v.f[1]=v.f[2]=0.0f;}
static inline qword RestoreTarget(O **receiver,const S *state,const V &saved){
 register O *owner asm("$4");qword target;
 asm("lw %0,%2\n\tlqc2 %1,%3":"=r"(owner),"=j"(target):"m"(state->owner),"m"(saved));
 *receiver=owner;return target;
}
extern "C" void func_002206C8(S *s,int state){
 WORK w;
 int old=s->state;
 if(state==old)return;
 switch(old){
 case -1:
  if(s->selected!=D_002DD5BC)func_001CD098(&s->owner->controller,s->selected);
  if(func_00132B10(s->selected,0x64))IntCall(s->selected,76,0);
  ZeroXYZ(s->owner->target);
  break;
 case 3:
  if(state!=4)IntCall(D_002DD5BC,79,1);
  break;
 }
 int previous=s->state;
 s->state=state;s->time=D_002DDED0.t;
 func_00134320(&D_003DD490,s->owner);
 switch(s->state){
 case -1:func_00204660(s->owner,func_00204740(s->owner));s->owner->movement=0;break;
 case 7:
  w.saved.q=s->targetWorld.q;
  {qword position=func_001A62E8(s->owner);qword current=ToVF(position);O *receiver;qword target=RestoreTarget(&receiver,s,w.saved);func_002046B0(receiver,Sub(target,current));}
  s->owner->movement=0;
  break;
 default:s->owner->direction.q=D_002A2DD0.q;s->owner->movement=1;break;
 }
 ASEG *animation=0;int flags=1;
 switch(s->state){
 case -1:
  if(s->selected==D_002DD5BC&&!s->selected->playerState){
    w.scalar.q=CPUFloat(400.0f);w.coefficient.q=w.scalar.q;
    w.point.q=PointVF(func_001A62E8(s->selected));
    qword position=func_001A62E8(s->owner);qword current=LaunchCurrent(position);qword direction=Sub(RestorePoint(w.point),current);
    qword up=LoadUp();
    direction=Sub(direction,Scale(up,DotV(direction,up)));
    qword fallback=D_002A2DA0.q;
    qword length=LengthV(direction);
    if(X(length)<0.0001f)direction=fallback;else direction=NormalizeLength(direction,length);
    qword liftUp=LaunchUp(),speed;O *receiver;int flag;qword height=LaunchOperands(600.0f,w.coefficient,speed,receiver,flag);
    qword velocity=Launch(direction,speed,liftUp,height);asm volatile("sqc2 %1,%0":"=m"(w.velocity.q):"j"(velocity));w.scalar.q=height;
    func_00136530(receiver,flag);
    VectorCall(D_002DD5BC,35,w.velocity.q);
  }
  else if(s->selected->id==s->peer->id){
   if(func_00132B10(s->selected,0x64))IntCall(s->selected,76,4);
   else{func_001A58D0(s->selected,0,0xF);func_001F7BF8(s->selected,0.25f);}
  }
  func_001CD2C0(&s->owner->controller);
  if(s->effect)EffectCall(s->effect,9);
  s->selected=0;
  return;
 case 0:
  if(previous!=1&&previous!=2){s->blend0=s->blend1=0.5f;func_001384C0(s->animation0);}
  animation=s->animation0;flags=9;break;
 case 1:animation=s->animation1;break;
 case 2:animation=s->animation2;break;
 case 3:animation=s->animation3;IntCall(s->owner,79,1);break;
 case 4:
  if(s->effect){s->effect->active=1;s->effect->reset=0;EffectCall(s->effect,8);}
  if(previous!=5&&previous!=6){s->distance=0.0f;s->targetWorld.q=func_001A6F00(s->owner,0,s->targetLocal.q);func_0021FB70(s,0);}
  animation=s->animation4;flags=9;s->field128=0;break;
 case 5:animation=s->animation5;break;
 case 6:animation=s->animation6;break;
 case 7:
  animation=s->animation7;
  if(func_00132B10(s->selected,0x64))func_00141CD0(s->owner,s->selected->actorId);
  break;
 }
 func_001F15B8(&s->owner->extra);
 func_001305B8(animation,s->owner,0.0f,1.0f,flags,&s->owner->animation);
 PlainCall(s->owner,90);
 func_00134320(&D_003DD490,s->owner);
}
