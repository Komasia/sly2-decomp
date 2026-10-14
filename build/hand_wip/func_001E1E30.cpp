typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U { qword q; float f[4]; int i[4]; };
union WORD { int i; float f; void *p; };
struct VTE { short delta,pad; void *fn; };
struct BASE { char pad[12]; VTE *vt; };
struct ACTOR;
struct P;
union VALUE { int id; float f; void *ptr; ACTOR *actor; };
union ARGS { VALUE a[12]; qword vectors[3]; };
struct OP { int kind,wait; char pad8[8]; ARGS args; WORD reset,resetArg; char pad48[8]; };
struct CTX { char padC[12]; VTE *vt; char pad10[0x30]; uint flags; char pad44[0x24]; P *callback; ACTOR *defaultActor; };
struct ACTOR {
 char padC[12]; VTE *vt; char pad10[0x230]; U relative;
 char pad250[0x8C]; int stage; char pad2E0[8]; int mode2E8;
 char pad2EC[0x1D4]; char mode4C0[8]; int mode,active,word4D0; ACTOR *modePath;
 char pad4D8[0xA7C]; int curveId; int wordF58; ACTOR *curve;
 char padF60[0xE8]; WORD height; char pad104C[0x14]; U goal;
 char pad1070[0x284]; int locked; char pad12F8[0x5F8]; int mode18F0;
 char pad18F4[0x1C]; void *item; int itemKind;
};
struct COMPONENT {
 char padC[12]; VTE *vt; char pad10[0x20]; int flag30; float speed34;
 int kind38; float rate3C; int flag40; char pad44[0x88]; int kindCC; float rateD0;
};
struct CONTACT { char pad20[0x20]; VTE *vt; };
struct GRAB { ACTOR *target; CONTACT *contact; char pad8[8]; U position; };
struct FRAGMENT { int a,b,c,d; };
struct EVENT { float time; int id; char pad8[8]; U position; int state; char pad24[12]; };
struct M3 { U r[3]; };
union FIRST {
 struct { U point; M3 rotation,writer; } pose;
 GRAB grab;
 FRAGMENT fragment;
};
struct WORK { FIRST first; EVENT events[6]; VALUE *arguments; float angle; U look; };
struct P {
 char padC[12]; VTE *vt; int word10; CTX *context; void *scope;
 ACTOR *baseActor,*overrideActor,*subject;
 OP *start,*end,*current; float time; char pad38[12]; ACTOR *actor; int blocked;
 BASE *script; ACTOR *entity,*pending; void *fragment; int generation;
 ACTOR *flagObject,*target; OP *operation; char pad6C[12]; float progress,previousCurve,duration;
 char pad84[0x18]; int group; ACTOR *modeObject; char padA4[0x34];
 ACTOR *commandActor,*commandTarget; int command; char padE4[8]; COMPONENT *component;
};
struct CLOCK { float time,dt; char pad8[0x34]; float paused; };
struct CAMERA { char pad90[0x90]; U position; };
extern CLOCK D_002DDED0;
extern CAMERA D_002DDF40;
extern U D_002A2DC0,D_002A2DD0;
extern float D_002A7AD0;
extern char D_002DEB30[],D_002DE460[],D_002DFC00[];
extern char D_003DD490[],D_003DD040[],D_003DA530[],D_003DA0C0[],D_004435F0[];
extern void *D_002DE570;
extern int D_004435F8;
extern "C" {
 ACTOR *func_001E1DB8(P*,int);
 P *func_001E5AE0(CTX*,OP*,P*),*func_001E0180(CTX*,int,P*);
 void func_001E1C40(P*),func_001E5628(P*);
 int func_00132B10(void*,int);
 void func_001E0020(void*,void*),func_001DFEB8(void*),func_001DFD58(void*,ACTOR*);
 void func_00143EE0(ACTOR*,int,int,int);
 BASE *func_00130488(ACTOR*,ACTOR*,float,float,int);
 void func_0020FFF0(void*,FRAGMENT*,void*,int,P*,void**);
 int func_001F0638(void*),func_001F07E8(void*);
 void func_001E5410(P*);
 ACTOR *func_0015E938(void*,int,int,void*);
 void func_0014D1D0(CLOCK*,int,float);
 void func_00161F48(void*,int,VALUE*,void*);
 void func_001E50E0(P*,int,int);
 int func_00210B68(void);
 void func_00228170(ACTOR*);
 void func_001928F8(void*,int,ACTOR*,ACTOR*),func_00192BD8(void*,int);
 void func_001E4EB8(P*,OP*,ACTOR*),func_001E4D40(P*,ACTOR*,U*,float*);
 M3 *func_0011B500(M3*,qword,float);
 void func_00204660(ACTOR*,float),func_002046B0(ACTOR*,qword);
 void func_00195A00(void*,int,ACTOR*,ACTOR*),func_001F4E28(ACTOR*);
 void func_0014D8C0(CAMERA*);
 void func_001E4F20(P*,ACTOR*),func_001E5000(P*,ACTOR*);
 void func_001E6F60(ACTOR*,qword,U*,U*,float*,float*,float*);
 void func_0018E540(ACTOR*,int),func_0018C250(ACTOR*,int,int);
 void func_00142140(ACTOR*,ACTOR*),func_00142278(ACTOR*,ACTOR*,ACTOR*);
 void func_00142340(ACTOR*,ACTOR*),func_001421A0(ACTOR*,ACTOR*),func_001421F8(ACTOR*,ACTOR*);
 qword func_001A62E8(ACTOR*);
 void func_001424E0(ACTOR*,ACTOR*,ACTOR*,int),func_001938C0(void*,int,ACTOR*);
 COMPONENT *func_00205438(ACTOR*,int);
 void func_00178D90(COMPONENT*,ACTOR*,int),func_00144F48(COMPONENT*,qword);
 void *s1_memset(void*,int,int);
 CONTACT *func_00184670(ACTOR*);
 void func_00173610(U*,float,float,int,int);
 void func_0019F590(ACTOR*,GRAB*);
 void func_00141968(ACTOR*,qword,float,float);
 ACTOR *func_00210338(void*,int,int,void*,CTX*,float);
 void func_00210408(void*,int,int,int,int,void*,CTX*);
 void func_002104A0(void*,int,int,int,int,void*,CTX*);
 void func_0014F750(CAMERA*,int),func_00187E28(void*,int,float);
 void func_00210538(void*,int,int,int,void*,CTX*,float);
 void func_00210678(void*,int,int,void*,CTX*,float);
 void func_00210740(void*,int,int,int,int,int,void*,CTX*,COMPONENT**,float,float,float);
 void func_002108E8(void*,int,CTX*,COMPONENT**);
 float func_001E4530(P*,OP*);
 void func_001E57A0(P*,OP*,OP*,float),func_001E5A98(P*,int);
 void func_0019CC50(void*,int,ACTOR*,ACTOR*),func_001E54B0(P*);
 void func_00150E20(void*,ACTOR*),func_00150E60(void*,ACTOR*);
 void func_00150EA0(void*,qword,qword,float),func_00150EE8(void*,float),func_00150EF0(void*);
 void func_001DD820(void*);
 void func_001FE5F0(void*,int,int),func_00227788(void*);
 void func_001E51A0(P*,ACTOR*,int,int),func_001E5280(P*,ACTOR*,int,int);
 void func_001531A8(void*,int,int,EVENT*),func_001532D8(void*,ACTOR*,int,int,float);
 void func_001524A0(ACTOR*,ACTOR*,ACTOR*);
 void func_001FE150(void*,int),func_001FE310(void*,int);
 ACTOR *func_001F67E0(ACTOR*,int);
 void func_001B9C00(ACTOR*,ACTOR*,int,int,int);
 void func_001DA4B8(void*,int,float),func_001DA578(void*,int);
 void func_00171CF8(ACTOR*,ACTOR*),func_00171D58(ACTOR*,ACTOR*),func_001B9880(ACTOR*);
 void func_00220508(void**,ACTOR*);
 void func_001E1E30(P*);
}
static inline void V0(void *p,int index){
 BASE*b=(BASE*)p;VTE&e=b->vt[index];((void(*)(void*))e.fn)((char*)p+e.delta);
}
static inline void Vi(void*p,int index,int value){
 BASE*b=(BASE*)p;VTE&e=b->vt[index];((void(*)(void*,int))e.fn)((char*)p+e.delta,value);
}
static inline void Vq(ACTOR*p,int index,qword value){
 VTE&e=p->vt[index];((void(*)(void*,qword))e.fn)((char*)p+e.delta,value);
}
static inline void Vm(ACTOR*p,M3*m){
 VTE&e=p->vt[30];((void(*)(void*,M3*))e.fn)((char*)p+e.delta,m);
}
struct Reference {
 P *p;
 Reference(P*v):p(v){V0(p,1);}
 ~Reference(){V0(p,2);}
};
static inline qword ToVU(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword FromWord(int a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScaled(qword point,qword axis,qword scalar){
 __asm__("vadda.xyzw $ACC,$vf0,%0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(point):"j"(axis),"j"(scalar));return point;
}
static inline float Clock(P*p){
 register CTX*context __asm__("$2")=p->context;uint flags=context->flags;if((flags^1)&1)flags=*(uint*)flags;
 return flags&0x100?D_002DDED0.paused:D_002DDED0.time;
}
static inline void Flag(CTX*p,int on){
 uint value=p->flags;
 if((value^1)&1){uint*flags=(uint*)value;if(on)*flags|=0x100;else *flags&=~0x100;}
 else if(on)p->flags=value|0x100;else p->flags=value&~0x100;
}
static inline int SubjectId(OP*op){
 switch(op->kind){
 case 0x16:case 0x1A:case 0x1C:case 0x1E:case 0x23:return op->args.a[2].id;
 case 0x27:case 0x28:return op->args.a[4].id;
 case 0x22:case 0x24:case 0x29:case 0x2A:case 0x2B:case 0x4A:return op->args.a[3].id;
 case 0x1B:case 0x47:case 0x48:case 0x4F:case 0x50:case 0x51:case 0x57:return op->args.a[0].id;
 case 0x0B:case 0x18:case 0x19:case 0x1D:case 0x1F:case 0x20:case 0x21:case 0x43:case 0x4B:case 0x58:case 0x59:case 0x5A:return op->args.a[1].id;
 default:return -1;
 }
}
void func_001E1E30(P*p){
 p->current++;
 if((uint)p->end<(uint)p->current)return;
 Reference hold(p);
 WORK w;
 OP*op=p->current;
 int id=SubjectId(op);
 register ACTOR*selected __asm__("s0");
 if(id==-1){
  selected=p->overrideActor;
  if(!selected){selected=p->baseActor;if(!selected)selected=p->context->defaultActor;}
 }else selected=func_001E1DB8(p,id);
 p->subject=selected;
 switch(op->kind){
 case 0:{P*child=func_001E5AE0(p->context,op,p);p->current=child->end;func_001E1C40(child);break;}
 case 2:{P*thread;if(op->args.a[0].id==-1)thread=p;else thread=func_001E0180(p->context,op->args.a[0].id,0);if(thread)func_001E5628(thread);break;}
 case 5:{ACTOR*selected;
  void*alarm;
  if(op->args.a[1].id==-1)alarm=p->context;
  else{selected=func_001E1DB8(p,op->args.a[1].id);alarm=selected&&func_00132B10(selected,0x72)?selected:0;}
  if(alarm)func_001E0020(alarm,op->args.a[0].ptr);break;
 }
 case 6:{ACTOR*selected;
  void*alarm;
  if(op->args.a[0].id==-1)alarm=p->context;
  else{selected=func_001E1DB8(p,op->args.a[0].id);alarm=selected&&func_00132B10(selected,0x72)?selected:0;}
  if(alarm)func_001DFEB8(alarm);break;
 }
 case 7:{ACTOR*selected;selected=func_001E1DB8(p,op->args.a[0].id);if(selected&&func_00132B10(selected,0x32))Vi(selected,79,1);break;}
 case 8:p->overrideActor=func_001E1DB8(p,op->args.a[0].id);break;
 case 9:{
  p->context->callback=p;w.arguments=&op->args.a[0];
  CTX*c=p->context;VTE&e=c->vt[3];
  ((void(*)(void*,int,int,int,VALUE**,int))e.fn)((char*)c+e.delta,4,0,1,&w.arguments,0);
  p->context->callback=0;break;
 }
 case 0xA:{ACTOR*selected;
  ACTOR*owner=func_001E1DB8(p,op->args.a[1].id);
  if(owner&&func_00132B10(owner,0x34)){
   func_00143EE0(owner,op->args.a[0].id,op->args.a[2].id|1,5);
   if(!op->wait)p->pending=owner;break;
  }
  if(owner&&!func_00132B10(owner,0x30))owner=0;
  selected=func_001E1DB8(p,op->args.a[0].id);
  if(selected&&func_00132B10(selected,0x6D)){
   BASE*script=func_00130488(selected,owner,0.0f,1.0f,op->args.a[2].id);
   if(!op->wait){p->script=script;V0(script,1);}
  }break;
 }
 case 0xB:{
  ACTOR*alarm=func_001E1DB8(p,op->args.a[0].id);
  if(alarm&&func_00132B10(alarm,0x72)){func_001DFD58(alarm,selected);if(!op->wait)p->entity=alarm;}break;
 }
 case 0xC:p->scope=func_001E1DB8(p,op->args.a[0].id);if(!p->scope)p->scope=p->context;break;
 case 0xD:{
  w.first.fragment.a=op->args.a[0].id;w.first.fragment.b=op->args.a[1].id;
  w.first.fragment.c=op->args.a[2].id;w.first.fragment.d=-1;
  func_0020FFF0(D_003DD490,&w.first.fragment,p->scope,op->args.a[3].id?3:1,p,&p->fragment);
  if(op->wait){func_001E5410(p);break;}
  if(p->fragment&&!p->generation&&!func_001F0638(p->fragment)&&func_001F07E8(p->fragment)==op->args.a[2].id)p->generation=1;
  break;
 }
 case 0xE:case 0xF:{ACTOR*selected;
  selected=func_0015E938(D_003DD490,0x405,op->args.a[0].id,0);
  if(selected&&func_00132B10(selected,0x7E)){
   if(op->kind==0xE){Vi(selected,49,op->args.a[1].id);if(!op->wait)p->target=selected;}
   else V0(selected,50);
  }break;
 }
 case 0x10:func_0014D1D0(&D_002DDED0,6,op->args.a[0].f);Flag(p->context,op->args.a[0].f==0.0f);break;
 case 0x11:func_00161F48(D_002DEB30,1,&op->args.a[0],p->scope);break;
 case 0x12:func_001E50E0(p,op->args.a[0].id,op->args.a[1].id);break;
 case 0x14:case 0x15:{
  if(op->kind==0x15&&func_00210B68()!=op->args.a[1].id)break;
  OP*found=0;int depth=0;
  for(OP*scan=p->start+1;(uint)scan<(uint)p->end;scan++){
   switch(scan->kind){
   case 0:depth++;break;case 1:depth--;break;
   case 0x13:if(!depth&&scan->args.a[0].id==op->args.a[0].id){found=scan;scan=p->end;}break;
   }
  }
  if(found)p->current=found;break;
 }
 case 0x16:{ACTOR*selected;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  if(target&&func_00132B10(target,0x29)){func_00228170(target);break;}
  if(!p->subject)break;
  if(target&&func_00132B10(target,0x1B)){
   if(func_00132B10(p->subject,0x34)){
    selected=p->subject;func_001928F8(selected->mode4C0,8,target,0);
    func_00192BD8(selected->mode4C0,9);func_001E4EB8(p,0,0);
   }break;
  }
  func_001E4D40(p,target,&w.first.pose.point,&w.angle);
  if(func_00132B10(p->subject,0x33)){
   selected=p->subject;
   Vq(selected,29,Sub(w.first.pose.point.q,selected->relative.q));
   func_00204660(selected,w.angle);
  }else Vq(p->subject,29,w.first.pose.point.q);
  func_0011B500(&w.first.pose.writer,D_002A2DC0.q,w.angle);
  w.first.pose.rotation=w.first.pose.writer;Vm(p->subject,&w.first.pose.rotation);
  if(func_00132B10(p->subject,0x34)){
   selected=p->subject;
   w.first.pose.writer.r[0].q=FromWord(selected->height.i);
   selected->goal.q=AddScaled(w.first.pose.point.q,D_002A2DC0.q,w.first.pose.writer.r[0].q);
   if(!op->args.a[1].id&&!selected->locked){func_00195A00((char*)selected+0x2C0,0xB,0,0);func_001F4E28(selected);}
   func_001E4EB8(p,0,0);
  }
  Vq(p->subject,35,D_002A2DD0.q);Vq(p->subject,36,D_002A2DD0.q);break;
 }
 case 0x17:func_0014D8C0(&D_002DDF40);break;
 case 0x18:{ACTOR*selected;selected=func_001E1DB8(p,op->args.a[0].id);if(selected&&func_00132B10(selected,0xF))func_001E4F20(p,selected);break;}
 case 0x19:func_001E5000(p,func_001E1DB8(p,op->args.a[0].id));break;
 case 0x1A:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  if(selected->curveId==-1)break;
  func_001E4D40(p,func_001E1DB8(p,op->args.a[0].id),&w.first.pose.point,0);
  func_001E6F60(selected->curve,w.first.pose.point.q,0,0,0,0,&p->previousCurve);
  func_001E4EB8(p,op,selected);break;
 }
 case 0x1C:{
  if(!p->subject||!func_00132B10(p->subject,0x35))break;
  switch(op->args.a[1].id){
   case 2:func_0018E540(p->subject,3);break;
   case 4:func_0018C250(p->subject,0xD,-1);break;
   case 8:func_0018C250(p->subject,9,-1);break;
  }break;
 }
 case 0x1D:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  func_00142140(selected,target);func_001E4EB8(p,op,selected);break;
 }
 case 0x1E:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  ACTOR*a=func_001E1DB8(p,op->args.a[0].id),*b=func_001E1DB8(p,op->args.a[1].id);
  func_00142278(selected,a,b);func_001E4EB8(p,op,selected);break;
 }
 case 0x1F:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  func_00142340(selected,target);func_001E4EB8(p,op,selected);break;
 }
 case 0x20:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  func_001421A0(selected,target);break;
 }
 case 0x21:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  func_001421F8(selected,target);func_001E4EB8(p,op,selected);break;
 }
 case 0x22:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  ACTOR*clip=func_0015E938(D_003DD490,1,op->args.a[0].id,selected),*target;
  if(op->args.a[1].id==3){
   w.look=D_002DDF40.position;
   func_002046B0(selected,Sub(w.look.q,ToVU(func_001A62E8(selected))));target=0;
  }else target=func_001E1DB8(p,op->args.a[1].id);
  func_001424E0(selected,clip,target,op->args.a[2].id);func_001E4EB8(p,op,selected);break;
 }
 case 0x23:{
  ACTOR*target=func_001E1DB8(p,op->args.a[1].id);
  if(target&&p->subject&&func_00132B10(p->subject,0x34))func_001E4EB8(p,op,p->subject);break;
 }
 case 0x24:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;
  ACTOR*actor=p->subject;
  if(op->args.a[4].id!=-1)func_00143EE0(actor,op->args.a[4].id,9,6);
  selected=func_001E1DB8(p,op->args.a[0].id);
  if(selected){
   if(func_00132B10(selected,0x22)||func_00132B10(selected,0xC)||func_00132B10(selected,0x26)||
      func_00132B10(selected,0x58)||func_00132B10(selected,0xB)||func_00132B10(selected,0x13)){
    int mode=0xFFFF;
    if(!func_00132B10(actor,0x35))mode=func_00132B10(actor,0x37)?0xF8FE:0xF8FA;
    func_001938C0(actor->mode4C0,mode,selected);
   }
   if(actor->active!=-1&&actor->mode==3){
    ACTOR*path=actor->modePath;func_001E4D40(p,selected,&w.first.pose.point,0);
    func_001E6F60(path,w.first.pose.point.q,0,0,0,&p->progress,0);
   }
  }
  func_001E4EB8(p,op,actor);break;
 }
 case 0x25:p->command=1;break;case 0x26:p->command=0;break;
 case 0x27:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  if(!target||!func_00132B10(target,0xA))break;
  selected=p->subject;if(op->args.a[5].id!=-1)func_00143EE0(selected,op->args.a[5].id,9,6);
  COMPONENT*c=func_00205438(selected,0xA8);c->flag40=p->command;c->kindCC=op->args.a[2].id;c->rateD0=op->args.a[3].f;
  func_00178D90(c,target,op->args.a[1].id==0);V0(c,8);break;
 }
 case 0x28:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;selected=p->subject;
  func_001E4D40(p,func_001E1DB8(p,op->args.a[0].id),&w.first.pose.point,0);
  if(op->args.a[5].id!=-1)func_00143EE0(selected,op->args.a[5].id,9,6);
  COMPONENT*c=func_00205438(selected,0xC1);c->flag30=p->command;c->speed34=op->args.a[1].f;
  c->kind38=op->args.a[2].id;c->rate3C=op->args.a[3].f;
  func_00144F48(c,w.first.pose.point.q);V0(c,8);break;
 }
 case 0x29:{
  if(p->subject&&func_00132B10(p->subject,0x34)&&p->subject->active!=-1&&p->subject->mode==8)
   func_001E4EB8(p,op,p->subject);break;
 }
 case 0x2A:{
  if(!p->subject||!func_00132B10(p->subject,0x34))break;
  ACTOR*actor=p->subject,*target=func_001E1DB8(p,op->args.a[0].id);
  GRAB*g=&w.first.grab;s1_memset(g,0,0x20);
  if(!target)g->position.q=Add(ToVU(func_001A62E8(actor)),actor->relative.q);
  else{
   CONTACT*contact=func_00184670(target);g->contact=contact;
   if(contact){
    if(actor->curveId!=-1&&actor->curve==target)break;
    VTE&e=contact->vt[2];((void(*)(void*,ACTOR*,U*))e.fn)((char*)contact+e.delta,actor,&g->position);
    g->target=target;
   }else{
    func_001E4D40(p,target,&g->position,0);func_00173610(&g->position,100.0f,-150.0f,0,0);
   }
  }
  func_0019F590(actor,g);if(op->args.a[1].id==1)actor->mode2E8=1;
  if(func_00132B10(actor,0x35))actor->mode18F0=op->args.a[2].id;
  func_001E4EB8(p,op,actor);break;
 }
 case 0x2B:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x34))break;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);selected=p->subject;
  func_001E4D40(p,target,&w.first.pose.point,0);
  func_00141968(selected,w.first.pose.point.q,op->args.a[1].f,op->args.a[2].f);break;
 }
 case 0x2C:case 0x2D:{ACTOR*selected;
  selected=func_00210338(D_003DD490,op->kind==0x2C,op->args.a[0].id,p->scope,p->context,op->args.a[1].f);
  if(selected&&!op->wait&&func_00132B10(selected,0x30))p->flagObject=selected;break;
 }
 case 0x2E:case 0x2F:func_00210408(D_003DD490,op->kind==0x2E,op->args.a[0].id,op->args.a[1].id,0,p->scope,p->context);break;
 case 0x30:case 0x31:func_002104A0(D_003DD490,op->kind==0x30,op->args.a[0].id,op->args.a[1].id,0,p->scope,p->context);break;
 case 0x32:func_0014F750(&D_002DDF40,op->args.a[0].id);break;
 case 0x33:func_00187E28(D_002DFC00,op->args.a[1].id,op->args.a[0].f);break;
 case 0x34:func_00210538(D_003DD490,op->args.a[0].id,op->args.a[1].id,op->args.a[2].id,p->scope,p->context,op->args.a[3].f);break;
 case 0x35:func_00210678(D_003DD490,op->args.a[0].id,op->args.a[1].id,p->scope,p->context,op->args.a[2].f);break;
 case 0x36:func_00210740(D_003DD490,op->args.a[0].id,op->args.a[1].id,op->args.a[2].id,op->args.a[3].id,0,p->scope,p->context,&p->component,op->args.a[4].f,op->args.a[5].f,op->args.a[6].f);break;
 case 0x37:func_002108E8(D_003DD490,op->args.a[0].id,p->context,&p->component);break;
 case 0x38:{
  float duration=op->reset.f;int automatic=duration==0.0f,depth=0;OP*last=0;
  if(automatic)duration=0.0f;
  for(OP*scan=op+1;(uint)scan<(uint)p->end&&!last;scan++){
   switch(scan->kind){
   case 0:depth++;break;case 1:depth--;break;
   case 0x39:if(!depth)last=scan;break;
   default:if(!depth&&automatic)duration+=func_001E4530(p,scan);break;
   }
  }
  if(last)func_001E57A0(p,op,last,duration);break;
 }
 case 0x39:if(p->duration==D_002A7AD0){if(op->reset.i)func_001E5A98(p,op->resetArg.i);else p->group=0;}break;
 case 0x3A:func_001E5A98(p,op->args.a[0].id);break;
 case 0x3B:{ACTOR*selected;
  ACTOR*target=func_001E1DB8(p,op->args.a[1].id);if(target)func_00132B10(target,0x33);
  ACTOR*resource=func_0015E938(D_003DD490,0x405,op->args.a[2].id,0);
  selected=func_001E1DB8(p,op->args.a[0].id);
  if(selected&&func_00132B10(selected,0x34)){p->modeObject=selected;func_0019CC50((char*)selected+0xF00,1,target,resource);}break;
 }
 case 0x3C:func_001E54B0(p);break;
 case 0x3D:func_00150E20(D_002DE460,func_001E1DB8(p,op->args.a[0].id));break;
 case 0x3E:func_00150E60(D_002DE460,func_001E1DB8(p,op->args.a[0].id));break;
 case 0x3F:func_00150EA0(D_002DE460,op->args.vectors[0],op->args.vectors[1],op->args.a[8].f);break;
 case 0x40:func_00150EE8(D_002DE460,op->args.a[0].f);break;
 case 0x41:func_00150EF0(D_002DE460);break;
 case 0x42:D_004435F8=op->args.a[0].id&0xF0;break;
 case 0x44:func_001DD820(D_003DA530);break;
 case 0x45:func_001FE5F0(D_003DD040,op->args.a[0].id,op->args.a[1].id);p->operation=op;break;
 case 0x46:func_00227788(D_004435F0);break;
 case 0x47:if(selected)func_001E51A0(p,selected,op->args.a[1].id,op->args.a[2].id);break;
 case 0x48:if(selected)func_001E5280(p,selected,op->args.a[1].id,op->args.a[2].id);break;
 case 0x49:{
  if(!D_002DE570)break;
  int count=0,depth=0;EVENT*write=w.events;
  for(OP*scan=op+1;(uint)scan<(uint)p->end;scan++){
   switch(scan->kind){
   case 0:depth++;break;case 1:depth--;break;
   case 0x49:if(!depth)scan=p->end;break;
   case 0x4A:if(!depth&&(uint)count<6){write->time=scan->args.a[0].f;write->id=scan->args.a[1].id;write++;count++;}break;
   }
  }
  func_001531A8(D_002DE570,op->args.a[0].id,count,w.events);break;
 }
 case 0x4A:if(p->subject&&func_00132B10(p->subject,0x44)&&D_002DE570)func_001532D8(D_002DE570,p->subject,op->args.a[1].id,op->args.a[2].id,op->args.a[0].f);break;
 case 0x4B:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x44))break;selected=p->subject;
  ACTOR*target=op->args.a[0].id==-1?0:func_0015E938(D_003DD490,4,op->args.a[0].id,selected);
  func_001524A0(selected,target,0);break;
 }
 case 0x4C:func_001FE150(D_003DD040,op->args.a[0].id);break;
 case 0x4D:func_001FE310(D_003DD040,op->args.a[0].id);break;
 case 0x4F:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x36))break;selected=p->subject;
  ACTOR*target=func_001E1DB8(p,op->args.a[1].id);if(!target)break;
  ACTOR*resource=func_001F67E0(target,-1);
  if(resource)func_001B9C00(selected,resource,op->args.a[3].id,op->args.a[2].id,op->args.a[4].id);break;
 }
 case 0x50:case 0x51:if(p->subject&&func_00132B10(p->subject,0x37))func_001E4EB8(p,op,p->subject);break;
 case 0x53:func_001DA4B8(D_003DA0C0,op->args.a[0].id,op->args.a[1].f);break;
 case 0x54:func_001DA578(D_003DA0C0,op->args.a[0].id);break;
 case 0x55:{
  ACTOR*a=func_001E1DB8(p,op->args.a[0].id),*b=func_001E1DB8(p,op->args.a[1].id);
  func_00171CF8(a,b);if(!op->wait){p->commandActor=a;p->commandTarget=b;}break;
 }
 case 0x56:{
  ACTOR*a=func_001E1DB8(p,op->args.a[0].id),*b=func_001E1DB8(p,op->args.a[1].id);func_00171D58(a,b);break;
 }
 case 0x57:if(p->subject&&func_00132B10(p->subject,0x36))func_001B9880(p->subject);break;
 case 0x58:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x37))break;selected=p->subject;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  if(target&&func_00132B10(target,0x36)){
   func_00195A00((char*)selected+0x2C0,selected->stage==0x11?3:1,0,0);func_001E4EB8(p,op,selected);
  }break;
 }
 case 0x59:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x36))break;selected=p->subject;
  if(selected->itemKind<4||selected->itemKind>=7)break;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  if(target){func_00220508(&selected->item,target);}break;
 }
 case 0x5A:{ACTOR*selected;
  if(!p->subject||!func_00132B10(p->subject,0x36))break;selected=p->subject;
  if(selected->itemKind<4||selected->itemKind>=7)break;
  op->args.a[2].ptr=selected->item;
  ACTOR*target=func_001E1DB8(p,op->args.a[0].id);
  if(target){func_00220508(&selected->item,target);func_001E4EB8(p,op,selected);}break;
 }
 default:break;
 }
 p->time=Clock(p);
}

#define OFF(T,F) ((int)&((T*)0)->F)
typedef char command_layout_00[(sizeof(qword)==16)?1:-1];
typedef char command_layout_01[(sizeof(VTE)==8)?1:-1];
typedef char command_layout_02[(sizeof(VALUE)==4)?1:-1];
typedef char command_layout_03[(sizeof(OP)==0x50)?1:-1];
typedef char command_layout_04[(sizeof(EVENT)==0x30)?1:-1];
typedef char command_layout_05[(sizeof(M3)==0x30)?1:-1];
typedef char command_layout_06[(sizeof(WORK)==0x1B0)?1:-1];
typedef char command_layout_07[(sizeof(GRAB)==0x20)?1:-1];
typedef char command_layout_08[(OFF(OP,args)==0x10)?1:-1];
typedef char command_layout_09[(OFF(OP,reset)==0x40)?1:-1];
typedef char command_layout_10[(OFF(OP,resetArg)==0x44)?1:-1];
typedef char command_layout_11[(OFF(CTX,vt)==0xC)?1:-1];
typedef char command_layout_12[(OFF(CTX,flags)==0x40)?1:-1];
typedef char command_layout_13[(OFF(CTX,callback)==0x68)?1:-1];
typedef char command_layout_14[(OFF(CTX,defaultActor)==0x6C)?1:-1];
typedef char command_layout_15[(OFF(ACTOR,relative)==0x240)?1:-1];
typedef char command_layout_16[(OFF(ACTOR,stage)==0x2DC)?1:-1];
typedef char command_layout_17[(OFF(ACTOR,mode2E8)==0x2E8)?1:-1];
typedef char command_layout_18[(OFF(ACTOR,mode4C0)==0x4C0)?1:-1];
typedef char command_layout_19[(OFF(ACTOR,mode)==0x4C8)?1:-1];
typedef char command_layout_20[(OFF(ACTOR,active)==0x4CC)?1:-1];
typedef char command_layout_21[(OFF(ACTOR,modePath)==0x4D4)?1:-1];
typedef char command_layout_22[(OFF(ACTOR,curveId)==0xF54)?1:-1];
typedef char command_layout_23[(OFF(ACTOR,curve)==0xF5C)?1:-1];
typedef char command_layout_24[(OFF(ACTOR,height)==0x1048)?1:-1];
typedef char command_layout_25[(OFF(ACTOR,goal)==0x1060)?1:-1];
typedef char command_layout_26[(OFF(ACTOR,locked)==0x12F4)?1:-1];
typedef char command_layout_27[(OFF(ACTOR,mode18F0)==0x18F0)?1:-1];
typedef char command_layout_28[(OFF(ACTOR,item)==0x1910)?1:-1];
typedef char command_layout_29[(OFF(ACTOR,itemKind)==0x1914)?1:-1];
typedef char command_layout_30[(OFF(COMPONENT,flag30)==0x30)?1:-1];
typedef char command_layout_31[(OFF(COMPONENT,speed34)==0x34)?1:-1];
typedef char command_layout_32[(OFF(COMPONENT,kind38)==0x38)?1:-1];
typedef char command_layout_33[(OFF(COMPONENT,rate3C)==0x3C)?1:-1];
typedef char command_layout_34[(OFF(COMPONENT,flag40)==0x40)?1:-1];
typedef char command_layout_35[(OFF(COMPONENT,kindCC)==0xCC)?1:-1];
typedef char command_layout_36[(OFF(COMPONENT,rateD0)==0xD0)?1:-1];
typedef char command_layout_37[(OFF(CONTACT,vt)==0x20)?1:-1];
typedef char command_layout_38[(OFF(GRAB,contact)==4)?1:-1];
typedef char command_layout_39[(OFF(GRAB,position)==0x10)?1:-1];
typedef char command_layout_40[(OFF(WORK,events)==0x70)?1:-1];
typedef char command_layout_41[(OFF(WORK,arguments)==0x190)?1:-1];
typedef char command_layout_42[(OFF(WORK,angle)==0x194)?1:-1];
typedef char command_layout_43[(OFF(WORK,look)==0x1A0)?1:-1];
typedef char command_layout_44[(OFF(P,vt)==0xC)?1:-1];
typedef char command_layout_45[(OFF(P,context)==0x14)?1:-1];
typedef char command_layout_46[(OFF(P,scope)==0x18)?1:-1];
typedef char command_layout_47[(OFF(P,baseActor)==0x1C)?1:-1];
typedef char command_layout_48[(OFF(P,overrideActor)==0x20)?1:-1];
typedef char command_layout_49[(OFF(P,subject)==0x24)?1:-1];
typedef char command_layout_50[(OFF(P,start)==0x28)?1:-1];
typedef char command_layout_51[(OFF(P,end)==0x2C)?1:-1];
typedef char command_layout_52[(OFF(P,current)==0x30)?1:-1];
typedef char command_layout_53[(OFF(P,time)==0x34)?1:-1];
typedef char command_layout_54[(OFF(P,script)==0x4C)?1:-1];
typedef char command_layout_55[(OFF(P,entity)==0x50)?1:-1];
typedef char command_layout_56[(OFF(P,pending)==0x54)?1:-1];
typedef char command_layout_57[(OFF(P,fragment)==0x58)?1:-1];
typedef char command_layout_58[(OFF(P,generation)==0x5C)?1:-1];
typedef char command_layout_59[(OFF(P,flagObject)==0x60)?1:-1];
typedef char command_layout_60[(OFF(P,operation)==0x68)?1:-1];
typedef char command_layout_61[(OFF(P,progress)==0x78)?1:-1];
typedef char command_layout_62[(OFF(P,previousCurve)==0x7C)?1:-1];
typedef char command_layout_63[(OFF(P,duration)==0x80)?1:-1];
typedef char command_layout_64[(OFF(P,group)==0x9C)?1:-1];
typedef char command_layout_65[(OFF(P,modeObject)==0xA0)?1:-1];
typedef char command_layout_66[(OFF(P,commandActor)==0xD8)?1:-1];
typedef char command_layout_67[(OFF(P,commandTarget)==0xDC)?1:-1];
typedef char command_layout_68[(OFF(P,command)==0xE0)?1:-1];
typedef char command_layout_69[(OFF(P,component)==0xEC)?1:-1];
typedef char command_layout_70[(OFF(CLOCK,paused)==0x3C)?1:-1];
typedef char command_layout_71[(OFF(CAMERA,position)==0x90)?1:-1];



typedef char command_target_layout[OFF(P,target)==0x64?1:-1];
