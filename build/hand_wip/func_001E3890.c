typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef struct ACTOR ACTOR;
typedef struct CONTROLLER CONTROLLER;
typedef struct P P;
typedef struct CTX CTX;
typedef struct VTE {short delta,pad;void *fn;} VTE;
typedef struct BASE {char padC[0xC];VTE *vt;} BASE;
typedef union VALUE {int id;float f;ACTOR *actor;void *ptr;} VALUE;
typedef struct OP {int kind;char pad4[0xC];VALUE a10,a14,a18,a1C,a20,a24;char pad28[0x18];int reset;int resetArg;} OP;
typedef struct RANGE {float low,high;} RANGE;
typedef union FIRST {RANGE limits;qword point;} FIRST;
typedef struct WORK {FIRST first;qword target;} WORK;
struct ACTOR {char padC[0xC];VTE *vt;char pad10[0x2CC];int stage;char pad2E0[0x1E8];int mode,active;char pad4D0[0xA90];float curveTime;char padF64[0xD0];void *thread;char pad1038[0x398];int state;char pad13D4[0x4F4];int state18C8;char pad18CC[0xC];int index18D8;char pad18DC[0x38];int kind1914;char pad1918[0xD8];qword oldPosition;char pad1A00[0x20];qword position;};
struct CONTROLLER {char pad7C[0x7C];ACTOR *actor;int word80;CONTROLLER *next;};
struct CTX {char pad40[0x40];uint taggedFlags;};
typedef struct ENTITY {char pad74[0x74];int live;} ENTITY;
typedef struct FLAG_OBJECT {char pad28[0x28];unsigned long flags;char pad30[0xFC];float progress;} FLAG_OBJECT;
typedef struct ITEM {char pad10[0x10];int id;} ITEM;
typedef struct MODE_OBJECT {char padF28[0xF28];int mode;} MODE_OBJECT;
struct P {char pad14[0x14];CTX *context;char pad18[0xC];ACTOR *subject;char pad28[0xC];float elapsed;char pad38[0xC];ACTOR *actor;int blocked;BASE *script;ENTITY *entity;void *pending,*fragment;int generation;FLAG_OBJECT *flagObject;void *target;ITEM *item;char pad6C[0x10];float previousCurve,time;char pad84[0x18];int group;MODE_OBJECT *modeObject;char padA4[0x34];ACTOR *commandActor;int command;};
extern float D_002DDF0C,D_002DDED0,D_002BD850,D_002C3620,D_002C3624,D_002C3628,D_002C362C;
extern char D_002DE460[],D_002DFC00[],D_003DA530[],D_003DD040[];
extern CONTROLLER *D_003E133C;
extern int D_004435F8;
P *func_001E0180(CTX*,int,P*);
int func_001E00E8(CTX*,int);
void func_001E0070(CTX*,int);
int func_00144038(void*),func_00131968(BASE*);
int func_001F0638(void*);
void func_001E5410(P*);
int func_002121C8(void*);
void func_001E5468(P*);
void func_0019E110(void*,RANGE*);
float func_0011D948(RANGE*,float);
int func_00132B10(ACTOR*,int);
int func_001423A0(ACTOR*),func_001424C0(ACTOR*),func_001424D0(ACTOR*),func_00142530(ACTOR*);
ACTOR *func_001E1DB8(P*,int);
void func_001E4D40(P*,ACTOR*,qword*,float*);
qword func_001A62E8(ACTOR*);
void func_001448F0(void*,qword);
void func_00143FF8(ACTOR*);
void *func_00205458(ACTOR*,int);
int func_00178D00(void*),func_00144EE8(void*);
void func_001EECD0(void*);
void func_001E5A98(P*,int);
int func_00150F58(void*),func_00151018(void*),func_001510D8(void*);
int func_00187D80(void*,int);
int func_001A6290(ACTOR*,int),func_001C4700(CONTROLLER*,int);
void func_00187DE0(void*,int);
int func_001D9880(void*);
int func_001FE848(void*,int);
float func_001FE888(void*),func_001FE3F8(void*);
int func_001F07E8(void*);
int func_00171DA8(ACTOR*,int);
int func_0011D4D0(float,float,float);
static inline float Clock(P *p){uint value=p->context->taggedFlags;if((value^1)&1)value=*(uint*)value;return value&0x100?D_002DDF0C:D_002DDED0;}
static inline float Remaining(P *p){return Clock(p)-p->elapsed;}
static inline void Call2(BASE *p){VTE *e=&p->vt[2];((void(*)(void*))e->fn)((char*)p+e->delta);}
static inline void Call88(ACTOR *p){VTE *e=&p->vt[88];((void(*)(void*,int))e->fn)((char*)p+e->delta,0);}
static inline int Call89(ACTOR *p){VTE *e=&p->vt[89];return ((int(*)(void*))e->fn)((char*)p+e->delta);}
static inline qword ToVU(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float LengthXY(qword a){qword r;float f;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(r));__asm__("mtc1 %1,%0":"=f"(f):"r"(r));return f;}
static inline float X(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Y(qword a){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(a));return f;}
static inline float Z(qword a){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(a));return f;}
int func_001E3890(P *p,OP *instruction){
 register OP *op __asm__("$19")=instruction;
 WORK work;int result;
 switch(op->kind){
 case 3:{int i;int *id=(int*)((char*)op+0x14);result=1;for(i=0;i<op->a10.id;i++,id++){if(func_001E0180(p->context,*id,p)){result=0;break;}}break;}
 case 4:result=func_001E00E8(p->context,op->a10.id);if(result&&op->a14.id)func_001E0070(p->context,op->a10.id);break;
 case 0xA:
  if(p->pending){result=0;if(func_00144038(p->pending))break;p->pending=0;result=1;break;}
  if(p->script&&func_00131968(p->script)){Call2(p->script);p->script=0;}
  result=p->script==0;break;
 case 0xB:
  if(p->entity&&!p->entity->live)p->entity=0;
  result=p->entity==0;break;
 case 0xD:
  if(p->fragment&&!func_001F0638(p->fragment)&&p->generation)func_001E5410(p);
  result=p->fragment==0;break;
 case 0xE:
  if(p->target&&func_002121C8(p->target))func_001E5468(p);
  result=p->target==0;break;
 case 0x1A:{
  float previous;result=1;if(!p->actor)break;
  func_0019E110((char*)p->actor+0xF50,&work.first.limits);
  previous=func_0011D948(&work.first.limits,p->previousCurve);
  result=__builtin_fabsf(p->actor->curveTime-previous)<op->a14.f;break;
 }
 case 0x1B:{
  ACTOR *a;result=1;if(!p->subject||!func_00132B10(p->subject,0x34))break;
  a=p->subject;if(a->stage>=0xB&&a->stage<0xE){result=0;break;}
  if(a->active!=-1&&(a->mode==0||a->mode==0xD))Call88(a);
  break;
 }
 case 0x1C:
  result=1;if(!p->subject||!func_00132B10(p->subject,0x35))break;
  switch(op->a14.id){case 2:result=p->subject->index18D8==-1;break;case 4:result=p->subject->state18C8!=2;break;case 8:result=p->subject->state18C8!=9;break;}
  break;
 case 0x1D:case 0x21:result=1;if(p->actor)result=func_001423A0(p->actor);break;
 case 0x1E:result=1;if(p->actor)result=func_001424C0(p->actor);break;
 case 0x1F:result=1;if(p->actor)result=func_001424D0(p->actor);break;
 case 0x22:result=1;if(p->actor)result=func_00142530(p->actor);break;
 case 0x23:result=op->a10.f<Remaining(p);break;
 case 0x24:{
  ACTOR *a=p->actor,*target;result=1;if(!a)break;
  target=func_001E1DB8(p,op->a10.id);
  if(target){
   func_001E4D40(p,target,&work.target,0);
   result=LengthXY(Sub(ToVU(func_001A62E8(a)),work.target))<op->a18.f;
   func_001448F0((char*)a+0xFD0,work.target);
  }
  if(result&&op->a20.id!=-1)func_00143FF8(a);break;
 }
 case 0x27:{
  ACTOR *a;void *item;result=1;if(!p->subject||!func_00132B10(p->subject,0x34))break;
  a=p->subject;result=0;item=func_00205458(a,0xA8);
  if(!item||func_00178D00(item))result=1;
  if(result){func_001EECD0((char*)a+0x26C);if(op->a24.id!=-1)func_00143FF8(a);}break;
 }
 case 0x28:{
  ACTOR *a;void *item;result=1;if(!p->subject||!func_00132B10(p->subject,0x34))break;
  a=p->subject;result=0;item=func_00205458(a,0xC1);
  if(!item||func_00144EE8(item))result=1;
  if(result){func_001EECD0((char*)a+0x26C);if(op->a24.id!=-1)func_00143FF8(a);}break;
 }
 case 0x29:{
  ACTOR *a=p->actor,*target;result=1;if(!a||a->active==-1||a->mode!=8)break;
  target=func_001E1DB8(p,op->a10.id);if(!target)break;
  func_001E4D40(p,target,&work.first.point,0);
  result=LengthXY(Sub(ToVU(func_001A62E8(a)),work.first.point))<op->a18.f;break;
 }
 case 0x2A:result=1;if(p->actor)result=p->actor->stage==-1;break;
 case 0x2B:result=1;if(p->subject&&func_00132B10(p->subject,0x34))result=p->subject->stage==-1;break;
 case 0x2C:case 0x2D:{
  FLAG_OBJECT *f=p->flagObject;
  if(f){
   unsigned long flags=f->flags;
   if(op->kind==0x2C){if((flags>>60)&1){if(f->progress==1.0f)p->flagObject=0;}}
   else if(!((flags>>60)&1))p->flagObject=0;
  }
  result=p->flagObject==0;break;
 }
 case 0x32:result=D_002BD850<Remaining(p);break;
 case 0x33:result=op->a10.f<Remaining(p);break;
 case 0x39:
  result=p->time<=D_002DDED0;
  if(result){if(op->reset)func_001E5A98(p,op->resetArg);else p->group=0;}break;
 case 0x3B:result=1;if(p->modeObject)result=p->modeObject->mode==1;break;
 case 0x3C:result=1;if(p->modeObject)result=p->modeObject->mode==-1;break;
 case 0x3D:result=func_00150F58(D_002DE460);break;
 case 0x3E:result=func_00151018(D_002DE460);break;
 case 0x40:result=func_001510D8(D_002DE460);break;
 case 0x42:
  if(op->a14.id==-1)result=func_00187D80(D_002DFC00,op->a10.id);
  else {
   CONTROLLER *c=D_003E133C;
   while(c&&!func_001A6290(c->actor,op->a14.id))c=c->next;
   result=1;if(c){result=0;if(func_001C4700(c,op->a10.id))result=1;}
   if(result)func_00187DE0(D_002DFC00,op->a10.id);
  }
  if(result)D_004435F8=0;break;
 case 0x43:result=1;if(p->subject&&func_00132B10(p->subject,0x34))result=Call89(p->subject)==op->a10.id;break;
 case 0x44:result=func_001D9880(D_003DA530)==0;break;
 case 0x45:result=func_001FE848(D_003DD040,op->a10.id)==0;break;
 case 0x52:{
  int id=p->item?p->item->id:-1;void *manager=D_003DD040;
  result=1;if(!func_001FE848(manager,id))break;
  result=0;if(op->a10.f<0.0f)break;
  result=0.0f<=func_001FE888(manager)-op->a10.f;break;
 }
 case 0x4A:result=op->a10.f<=func_001FE3F8(D_003DD040);break;
 case 0x4E:result=op->a10.f<=func_001FE3F8(D_003DD040);break;
 case 0x4F:
  result=0;if(!func_00132B10(p->subject,0x36))break;
  if(p->subject->state!=6){result=1;break;}
  if(op->a1C.id!=-1)result=func_001F07E8(p->subject->thread)==op->a1C.id;break;
 case 0x50:result=p->actor&&p->actor->state==6;break;
 case 0x51:result=p->actor&&p->actor->state!=6;break;
 case 0x53:result=op->a14.f<Remaining(p);break;
 case 0x55:
  if(p->command&&!func_00171DA8(p->commandActor,p->command)){p->commandActor=0;p->command=0;}
  result=p->command==0;break;
 case 0x58:{
  ACTOR *target;result=1;if(!p->actor)break;
  target=func_001E1DB8(p,op->a10.id);
  if(D_002C3620<Remaining(p))break;
  result=target->kind1914>=4&&target->kind1914<7;break;
 }
 case 0x59:{
  qword oldPosition,position;float tolerance;result=1;if(!p->actor)break;
  if(D_002C3624<Remaining(p))break;
  oldPosition=p->actor->oldPosition;tolerance=D_002C3628;position=p->actor->position;
  result=0;if(func_0011D4D0(X(position),X(oldPosition),tolerance)&&func_0011D4D0(Y(position),Y(oldPosition),tolerance)&&func_0011D4D0(Z(position),Z(oldPosition),tolerance))result=1;break;
 }
 case 0x5A:{
  ACTOR *a=p->actor;int state;result=1;if(!a)break;
  if(D_002C362C<Remaining(p))break;
  state=a->kind1914;result=0;if(state!=-1&&state!=0)break;
  if(state==0)Call88(a);
  result=op->a18.actor->stage==-1;break;
 }
 default:result=1;break;
 }
 return result;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char evaluator_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(unsigned long)==8 && sizeof(VALUE)==4 && sizeof(VTE)==8 && sizeof(RANGE)==8 && sizeof(FIRST)==16 && sizeof(WORK)==32 && OFF(VTE,delta)==0x0 && OFF(VTE,fn)==0x4 && OFF(BASE,vt)==0xC && OFF(RANGE,low)==0x0 && OFF(RANGE,high)==0x4 && OFF(WORK,first)==0x0 && OFF(WORK,target)==0x10 && OFF(OP,kind)==0x0 && OFF(OP,a10)==0x10 && OFF(OP,a14)==0x14 && OFF(OP,a18)==0x18 && OFF(OP,a1C)==0x1C && OFF(OP,a20)==0x20 && OFF(OP,a24)==0x24 && OFF(OP,reset)==0x40 && OFF(OP,resetArg)==0x44 && OFF(ACTOR,vt)==0xC && OFF(ACTOR,stage)==0x2DC && OFF(ACTOR,mode)==0x4C8 && OFF(ACTOR,active)==0x4CC && OFF(ACTOR,curveTime)==0xF60 && OFF(ACTOR,thread)==0x1034 && OFF(ACTOR,state)==0x13D0 && OFF(ACTOR,state18C8)==0x18C8 && OFF(ACTOR,index18D8)==0x18D8 && OFF(ACTOR,kind1914)==0x1914 && OFF(ACTOR,oldPosition)==0x19F0 && OFF(ACTOR,position)==0x1A20 && OFF(CONTROLLER,actor)==0x7C && OFF(CONTROLLER,next)==0x84 && OFF(CTX,taggedFlags)==0x40 && OFF(ENTITY,live)==0x74 && OFF(FLAG_OBJECT,flags)==0x28 && OFF(FLAG_OBJECT,progress)==0x12C && OFF(ITEM,id)==0x10 && OFF(MODE_OBJECT,mode)==0xF28 && OFF(P,context)==0x14 && OFF(P,subject)==0x24 && OFF(P,elapsed)==0x34 && OFF(P,actor)==0x44 && OFF(P,blocked)==0x48 && OFF(P,script)==0x4C && OFF(P,entity)==0x50 && OFF(P,pending)==0x54 && OFF(P,fragment)==0x58 && OFF(P,generation)==0x5C && OFF(P,flagObject)==0x60 && OFF(P,target)==0x64 && OFF(P,item)==0x68 && OFF(P,previousCurve)==0x7C && OFF(P,time)==0x80 && OFF(P,group)==0x9C && OFF(P,modeObject)==0xA0 && OFF(P,commandActor)==0xD8 && OFF(P,command)==0xDC)?1:-1];
