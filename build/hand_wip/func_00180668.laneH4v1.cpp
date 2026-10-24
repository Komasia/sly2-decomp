// func_00180668 laneH4v1: clean rewrite (no pins, VU helper asms + commented allocation-only operands), aligned 47. Structure from codex18v2.
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
typedef union U{qword q;float f[4];int i[4];}U;
struct VTE{short delta,pad;qword(*fn)(void*);};
struct FRAME{char pad0[0xA0];void*space;};
struct NODE{char pad0[12];VTE*vt;char pad10[0x18];ulong flags;char pad30[0x2C];FRAME*frame;char pad60[0x8C];void*group;};
struct LM{float low,high;};
struct RULE{int distanceEnabled,angleEnabled;LM enterDistance,stayDistance,enterAngle,stayAngle;};
struct POLY{float a,b,c;};
struct CLOCK{float t,dt;};
struct P{NODE node;char padF0[0xD0];int state;float stateTime;int cooldown,active;void*binding;NODE*target;void*curve;float progress;qword previousSelf,previousTarget;float stamp,heading;char pad208[8];qword output;char pad220[0x50];RULE rules[5];float scale;char pad33C[4];POLY remaining;char pad34C[4];POLY angle;char pad35C[4];POLY simpleAngle;char pad36C[4];LM simpleClamp;};
struct VU_FLOAT{qword qw;};
extern "C"{
extern qword D_002A2DD0,D_002A2DA0;
extern float D_002BE820,D_002BE824,D_002BE828;
extern POLY D_002BE830,D_002BE840,D_002BE860;
extern LM D_002BE850,D_002BBB60;
extern CLOCK D_002DDED0;
extern char D_002DE578[],D_003DD490[];
void func_001F36E0(P*);
int func_0017F550(P*);
void func_00181268(P*,int);
qword func_001A62E8(void*);
qword func_001A6FC0(void*,void*,qword);
qword func_0022FCC8(void*,void*,qword);
float func_002458F0(float,float);
float func_0011CF60(float);
int func_0011D910(LM*,float);
void func_001C02D0(void*,qword,qword,void*);
void func_001E7380(void*,qword,void*,qword*,float,qword*,float*,float*);
float func_001E6648(void*);
float func_00154C90(void*);
int func_0015E9C8(void*,int,int,void*,int,NODE**);
qword func_0011E9F8(qword,float);
}
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwDot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));return r;}
static inline qword QwSqrt(qword a){qword r;__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(a));return r;}
static inline qword QwDivide(qword v,qword len){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(len));return r;}
static inline qword QwAddScaled(qword base,qword v,VU_FLOAT g){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(v),"j"(g.qw));return r;}
static inline qword QwScaleX(qword v,VU_FLOAT g){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(g.qw));return r;}
static inline float GXOfQw(qword qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw));return x;}
static inline float GXOfVf(qword qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw),"j"(qw));return x;} /* allocation-only "j": the value stays in a VF register */
static inline float GYOfQw(qword qw){qword r;__asm__("prot3w %0,%1":"=r"(r):"r"(qw));return GXOfQw(r);}
static inline float Length(qword v){return GXOfQw(QwSqrt(QwDot(v,v)));}
static inline float Heading(qword v){return func_002458F0(GYOfQw(v),GXOfQw(v));}
static inline qword QwNormalizeSafe(qword v,qword fallback){
 qword len=QwSqrt(QwDot(v,v)),r;float x;
 __asm__("mtc1 %1,%0":"=f"(x):"r"(len),"r"(fallback)); /* allocation-only "r"(fallback): the fallback is held in a GPR */
 if(x<0.0001f)r=fallback;else r=QwDivide(v,len);
 return r;}
static inline qword NormalizeInPlace(U*pv,const qword*pfallback){qword v=pv->q;qword len=QwSqrt(QwDot(v,v));if(GXOfVf(len)<0.0001f)pv->q=*pfallback;else pv->q=QwDivide(v,len);return len;}
static inline ulong Alive(NODE*p){return (p->flags>>60)&1;}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
static inline float Limit(float f,LM*p){float low=p->low,high=p->high,r;if(f<low)r=low;else if(high<f)r=high;else r=f;return r;}
static inline float Clamp(float f,LM*p){float low=p->low,high=p->high;if(f<low)f=low;else if(high<f)f=high;return f;}

extern "C" void func_00180668(P*p){
 U nearest,direction,unit;
 func_001F36E0(p);
 if(p->state==2||p->state==4){if(func_0017F550(p))func_00181268(p,0);}
 if(p->state!=0&&p->state!=4){if(!p->target||!Alive(p->target))func_00181268(p,0);}
 if(!p->active&&p->target&&Alive(p->target)){
  RULE*rule=&p->rules[p->state];
  qword target=func_001A62E8(p->target);
  qword delta=QwSub(target,func_001A62E8(p));
  float distance=Length(delta);
  float heading=func_0011CF60(Heading(func_001A6FC0(0,p,delta)));
  int accept;
  if(!rule->distanceEnabled)accept=rule->angleEnabled;else accept=func_0011D910(&rule->stayDistance,distance);
  if(accept){
   if(!rule->angleEnabled)goto dispatch;
   if(func_0011D910(&rule->stayAngle,heading))goto dispatch;
  }
  {
   int state;
   for(state=4;state>0;state--){
    rule=&p->rules[state];
    if(!rule->distanceEnabled)accept=rule->angleEnabled;else accept=func_0011D910(&rule->enterDistance,distance);
    if(!accept)continue;
    if(!rule->angleEnabled)break;
    if(func_0011D910(&rule->enterAngle,heading))break;
   }
   func_00181268(p,state);
  }
 }
dispatch:
 switch(p->state){
 case 0:case 4:break;
 case 1:case 2:{
  if(p->cooldown)break;
  FRAME*frame=p->node.frame;
  qword target=func_001A62E8(p->target);
  qword self=func_001A62E8(p);
  float heading=func_0011CF60(Heading(func_0022FCC8(0,frame->space,QwSub(target,self))));
  p->heading=Clamp(Evaluate(&p->simpleAngle,heading),&p->simpleClamp);
  break;
 }
 case 3:{
  qword target=func_001A62E8(p->target);
  qword self=func_001A62E8(p);
  VTE*vte=&p->node.vt[33];
  vte->fn((char*)p+vte->delta);
  int refresh=0;
  if(D_002BE820<Length(QwSub(target,p->previousTarget)))refresh=1;
  else if(D_002BE820<Length(QwSub(self,p->previousSelf)))refresh=1;
  else if(D_002BE824<D_002DDED0.t-p->stamp)refresh=1;
  if(refresh){
   func_001C02D0(p->binding,self,target,p->curve);
   p->progress=0.0f;
   p->previousTarget=target;
   p->previousSelf=self;
   p->stamp=D_002DDED0.t;
  }
  func_001E7380(p->curve,self,0,&nearest.q,p->progress,&direction.q,0,&p->progress);
  {
   qword d=QwSub(QwAddScaled(nearest.q,direction.q,VuFloatFromMemWord(*(int*)&D_002BE828)),self);
   unit.q=QwNormalizeSafe(d,D_002A2DD0);
  }
  float remaining=func_001E6648(p->curve)-p->progress;
  float turn=Heading(func_001A6FC0(0,p,unit.q));
  float response=func_00154C90(D_002DE578);
  float speed=Limit(Evaluate(&p->remaining,remaining),&D_002BBB60)*Limit(Evaluate(&p->angle,turn),&D_002BBB60)*Limit(Evaluate(&D_002BE830,response),&D_002BBB60)*p->scale;
  qword force=QwScaleX(unit.q,VuFloat(speed));
  NODE*objects[64];
  NODE**buffer=objects;
  int n=func_0015E9C8(D_003DD490,0x105,0x49,0,64,buffer);
  if(n>0){
   NODE**cursor=buffer;int count=n;
   do{
    NODE*object=*cursor;
    if(object!=&p->node&&object->group!=p->node.group){
     U scalar;
     scalar.q=QwSub(self,func_001A62E8(object));
     scalar.f[2]=0.0f;
     qword len=NormalizeInPlace(&scalar,&D_002A2DA0);
     float weight=Limit(Evaluate(&D_002BE840,GXOfVf(len)),&D_002BE850);
     weight*=Limit(Evaluate(&D_002BE860,GXOfQw(QwDot(scalar.q,unit.q))),&D_002BBB60);
     force=QwAddScaled(force,scalar.q,VuFloat(weight));
    }
    cursor++;
   }while(--count);
  }
  p->output=func_0011E9F8(force,speed);
  p->heading=func_002458F0(unit.f[1],unit.f[0]);
  break;
 }
 }
}
