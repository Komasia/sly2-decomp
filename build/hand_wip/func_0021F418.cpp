// Update the controller target and consume state/animation transitions.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct RANGE {float lo,hi;};
struct O;
struct S;
struct ASEG;
struct VE {short delta,pad;union {void (*plain)(void *);void (*integer)(void *,int);void (*vector)(void *,qword);void (*evaluate)(void *,int,V *,float,float);} f;};
struct TRACK {VE *vt;};
struct TRACKREF {int tag;TRACK *track;};
struct ASEGA {char pad[0x14];ASEG *definition;char pad18[4];float time;char pad20[0x20];float scale;};
struct CONTROL {char pad[0x18];float heading,speed;};
struct O {char pad[0xC];VE *vt;int id;char pad14[0x13C];CONTROL *control;int field154,sentinel,actorId;char pad160[0x30];V target;char pad1A0[4];int movement;char pad1A8[0x38];V direction;char pad1F0[0xE40];ASEGA *animation;char pad1034[0x39C];int mode;};
struct EFFECT {char pad[0xC];VE *vt;};
struct S {O *owner;int state;float time;O *peer,*selected;float idleThreshold,activeThreshold;RANGE bounds;float radius,scale;char pad2C[0x14];float blend0;char pad44[8];float blend1;char pad50[8];ASEG *animation0,*animation1,*animation2,*animation3;char pad68[0x30];ASEG *animation4,*animation5,*animation6;char padA4[0x18];ASEG *animation7;V targetLocal,secondary,targetWorld,velocity,transitionBegin,transitionEnd;float transitionStart,transitionDuration;int transitioning;EFFECT *effect;float distance;};
struct CLOCK {float t,dt;};
union SCRATCH {V vector;RANGE range;};
struct WORK {SCRATCH scratch;V delta;float angle,radius;V ownerPosition,speed,vector,playerPosition;};
extern O *D_002DD5BC;
extern CLOCK D_002DDED0;
extern float D_002C40E0;
extern V D_002A2DC0,D_002A2DA0,D_002A2DD0;
extern "C" {
qword func_001A62E8(O *);
int func_001DAEA8(int);
qword func_0011E1A0(float,float,float);
void func_0011EF08(qword,float *,float *,float *);
float func_0011D948(RANGE *,float);
void func_0021FB70(S *,int);
float func_002458F0(float,float);
float func_00204740(O *);
float func_0011CF60(float);
void func_002206C8(S *,int);
void func_001384C0(ASEG *);
int func_00131968(ASEGA *);
int func_00132B10(O *,int);
int func_001C46C0(CONTROL *,int,float);
void func_00136530(O *,int);
TRACKREF *func_0012FF10(ASEG *,O *,void *,int);
}
static inline void IntCall(O *o,int slot,int value){VE *v=o->vt;v[slot].f.integer((char *)o+v[slot].delta,value);}
static inline void VectorCall(O *o,int slot,qword value){VE *v=o->vt;v[slot].f.vector((char *)o+v[slot].delta,value);}
static inline void EffectCall(EFFECT *o,int slot){VE *v=o->vt;v[slot].f.plain((char *)o+v[slot].delta);}
static inline void Evaluate(TRACK *o,int optional,V *result,float time,float scale){VE *v=o->vt;v[3].f.evaluate((char *)o+v[3].delta,optional,result,time,scale);}
static inline qword ToVF(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword CPUFloat(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword LoadVF(const V &v){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword LoadUp(){qword q;__asm__("lqc2 %0,0(%1)":"=j"(q):"r"(&D_002A2DC0),"m"(D_002A2DC0));return q;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword DotV(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));return d;}
static inline qword LengthV(qword v){qword d=DotV(v,v);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline qword Scale(qword v,qword k){__asm__("vmulx.xyzw %0,%1,%0x":"+j"(k):"j"(v));return k;}
static inline qword NormalizeLength(qword v,qword length){__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,Q":"+j"(v):"j"(length));return v;}
static inline qword Launch(qword direction,qword speed,qword up,qword height){__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%0,%3x":"+j"(up):"j"(direction),"j"(speed),"j"(height));return up;}
static inline qword Lerp(qword a,qword b,qword wa,qword wb){__asm__("vmulax.xyzw ACC,%0,%2x\n\tvmaddx.xyzw %0,%1,%3x":"+j"(a):"j"(b),"j"(wa),"j"(wb));return a;}
extern "C" void func_0021F418(S *s){
 WORK w;
 CONTROL *control=s->owner->control;
 w.ownerPosition.q=func_001A62E8(s->owner);
 if(s->state<7){
 if(s->state>=4){
  if(s->transitioning){
   float begin=s->transitionStart,end=begin+s->transitionDuration,time=D_002DDED0.t;
   if(end<=time){s->transitioning=0;s->targetWorld.q=s->transitionEnd.q;}
   else{
    float alpha=(time-begin)/(end-begin);
    qword toward=Scalar(alpha),from=Scalar(1.0f-alpha);
    w.scratch.vector.q=from;
    s->targetWorld.q=Lerp(s->transitionBegin.q,s->transitionEnd.q,from,toward);
    w.scratch.vector.q=toward;
   }
  }
  else{
   w.scratch.range=s->bounds;
   if(func_001DAEA8(0x24))w.scratch.range.hi*=D_002C40E0;
   w.delta.q=Sub(s->targetWorld.q,w.ownerPosition.q);w.delta.f[2]=0.0f;
   float elevation=w.delta.f[2];
   float dt=D_002DDED0.dt,speed=control->speed*dt,scale=s->scale;
   qword delta=LoadVF(w.delta);
   w.vector.q=delta;
   qword movement=func_0011E1A0(control->heading,speed*scale,elevation);
   w.delta.q=Add(LoadVF(w.vector),ToVF(movement));
   func_0011EF08(w.delta.q,&w.angle,&w.radius,0);
   w.radius=func_0011D948(&w.scratch.range,w.radius);
   w.delta.q=ToVF(func_0011E1A0(w.angle,w.radius,elevation));
   s->targetWorld.q=Add(w.ownerPosition.q,w.delta.q);
  }
  func_0021FB70(s,1);
 }
 }
 for(;;){
  int previous=s->state;
  ASEGA *animation=s->owner->animation;
  switch(previous){
  case 0:{
   w.scratch.vector.q=Sub(ToVF(func_001A62E8(s->selected)),w.ownerPosition.q);
   float heading=func_002458F0(w.scratch.vector.f[1],w.scratch.vector.f[0]);
   float angle=func_0011CF60(heading-func_00204740(s->owner));
   float threshold=s->idleThreshold;
   if(threshold<angle)func_002206C8(s,2);
   else if(angle<-threshold)func_002206C8(s,1);
   else{s->blend1=angle/threshold*0.5f+0.5f;s->blend0=1.0f-s->blend1;func_001384C0(s->animation0);}
   break;
  }
  case 1:case 2:
   if(!animation||func_00131968(animation))func_002206C8(s,0);
   break;
  case 3:
   if(!animation||func_00131968(animation)){if(D_002DD5BC->mode==8)func_002206C8(s,4);else func_002206C8(s,0);}
   break;
  case 4:case 5:case 6:{
   if(func_00132B10(s->selected,0x64)&&s->selected->sentinel!=-1){IntCall(s->owner,88,0);break;}
   float margin=0.1f;
   if(func_001C46C0(control,0xC0,margin)){func_002206C8(s,7);break;}
   if(func_001C46C0(control,0x30,margin)){
    if(s->animation0)func_002206C8(s,0);else IntCall(s->owner,88,0);
    if(s->selected==D_002DD5BC&&s->selected->mode==8){
     qword speed=CPUFloat(400.0f);w.scratch.vector.q=speed;w.speed.q=speed;
     w.playerPosition.q=ToVF(func_001A62E8(s->selected));
     qword position=func_001A62E8(s->owner);qword current=ToVF(position);qword direction=Sub(LoadVF(w.playerPosition),current);
     qword up=LoadUp();direction=Sub(direction,Scale(up,DotV(direction,up)));
     qword fallback=D_002A2DA0.q; qword length=LengthV(direction);
     if(X(length)<0.0001f)direction=fallback;else direction=NormalizeLength(direction,length);
     qword height=Scalar(600.0f);
     w.vector.q=Launch(direction,LoadVF(w.speed),LoadUp(),height);w.scratch.vector.q=height;
     func_00136530(D_002DD5BC,1);VectorCall(D_002DD5BC,35,LoadVF(w.vector));
    }
    if(s->effect)EffectCall(s->effect,9);
    return;
   }
   if(!animation||func_00131968(animation))func_002206C8(s,4);
   else if(s->state==4){
    w.scratch.vector.q=Sub(s->targetWorld.q,w.ownerPosition.q);
    float heading=func_002458F0(w.scratch.vector.f[1],w.scratch.vector.f[0]);
    float angle=func_0011CF60(heading-func_00204740(s->owner));
    float threshold=s->activeThreshold;
    if(threshold<angle)func_002206C8(s,6);else if(angle<-threshold)func_002206C8(s,5);
   }
   break;
  }
  case 7:
   if(!animation||func_00131968(animation)){if(s->animation0)func_002206C8(s,0);else IntCall(s->owner,88,0);}
   break;
  }
  if(s->state==previous||s->state==-1)break;
 }
 O *owner=s->owner;
 if(owner->movement!=1)return;
 ASEGA *animation=owner->animation;
 TRACKREF *reference=animation?func_0012FF10(animation->definition,owner,(void *)6,1):0;
 if(reference){
  Evaluate(reference->track,0,&w.scratch.vector,animation->time,animation->scale);
  V *direction=&s->owner->direction;float height=w.scratch.vector.f[2];direction->f[0]=0.0f;direction->f[2]=height;direction->f[1]=0.0f;
 }
 else s->owner->direction.q=D_002A2DD0.q;
}
