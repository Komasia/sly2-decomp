// Complete animation-state draft; 34/342 differences, native342 words/frameA0.
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int bits[4];void Clear(){bits[0]=bits[1]=bits[2]=0;}};
struct VE{short delta,pad;void(*fn)();};
struct ASEGA{char pad[12];VE*vt;};
struct ASEG;
struct COMPONENT;
struct CONTROL{char pad[0x18];float yaw;};
struct VALUE{char pad[0x20];U value;};
struct INNER{char pad[0x60];VALUE*value;};
struct RIG{char pad[0xA8];INNER*inner;};
struct P{char pad0[12];VE*vt;char pad10[0x150-0x10];CONTROL*control;char pad154[8];int frozen;char pad160[0x190-0x160];U zero;char pad1A0[8];float yaw;int pad1AC;U forward;char pad1C0[0x1030-0x1C0];ASEGA*asega;COMPONENT*component;char pad1038[0x19B8-0x1038];RIG*first;RIG*second;};
struct C{P*actor;int mode;float time;char padC[0x98-12];float changed;int pad9C;ASEG*clips[13];ASEG*Default(int next){ASEG**base=clips;int offset=next<8?0:0x20;return *(ASEG**)((char*)base+offset);}};
struct CLOCK{float time,dt;};
struct CM{char pad[0x90];U position;};
struct POLY{float a,b,c;};
struct LIMIT{float lo,hi;};
extern "C"{
 extern CLOCK D_002DDED0;
 extern CM D_002DDF40;
 extern U D_002BFA00,D_002BFA10,D_002A2DD0;
 extern POLY D_002BFA20;
 extern LIMIT D_002BBB60;
 extern float D_002A6720;
 int func_00132B10(P*,int);
 float func_002458F0(float,float);
 float func_0011CF60(float);
 void func_00204660(P*,float);
 void func_00204CA8(P*);
 void func_002046B0(P*,qword);
 qword func_001A62E8(P*);
 float func_00204740(P*);
 void func_001F4BF8(P*);
 void func_00130658(ASEGA**);
 void func_001F15B8(COMPONENT**);
 void func_001305B8(ASEG*,P*,float,float,int,ASEGA**);
 void func_001F1448(void*,P*,int,void*,COMPONENT**);
}
static inline qword Vector(P*p){VE*v=&p->vt[33];return ((qword(*)(P*))v->fn)((P*)((char*)p+v->delta));}
static inline void SetVector(P*p,qword q){VE*v=&p->vt[36];((void(*)(P*,qword))v->fn)((P*)((char*)p+v->delta),q);}
static inline void Invoke(P*p,int slot){VE*v=&p->vt[slot];((void(*)(P*))v->fn)((P*)((char*)p+v->delta));}
static inline qword Position(CM*manager){return manager->position.q;}
static inline qword From(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Load(U*u){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(u->q));return r;}
static inline float X(qword a){int word;float f;__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline float Dot(qword a,U*b){
 register qword v __asm__("vf4")=From(a),axis __asm__("vf1")=Load(b);
 register qword d __asm__("vf2"),one __asm__("vf3");
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v),"j"(axis));return X(d);
}
static inline float LengthXY(qword v){qword d;
 __asm__("vmul.xy %0,%1,%1":"=j"(d):"j"(v));
 __asm__("vaddy.x %0,%0,%0y":"+j"(d));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return X(d);
}
static inline qword Difference(U*a,qword b){register qword x __asm__("vf1")=Load(a),y __asm__("vf2")=From(b);__asm__("vsub.xyzw %0,%0,%1":"+j"(x):"j"(y));return x;}
static inline qword Difference1(U*a,qword b){register qword x __asm__("vf4")=Load(a),y __asm__("vf1")=From(b);__asm__("vsub.xyzw %0,%0,%1":"+j"(x):"j"(y));return x;}
static inline float Clamp(float value,LIMIT*range){
 float lo=range->lo,hi=range->hi;
 if(value<lo)return lo;
 if(hi<value)return hi;
 return value;
}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char POLY_Size[sizeof(POLY)==12?1:-1];
typedef char LIMIT_Size[sizeof(LIMIT)==8?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==0?1:-1];
typedef char C_mode_Offset[FIELD_OFFSET(C,mode)==4?1:-1];
typedef char C_time_Offset[FIELD_OFFSET(C,time)==8?1:-1];
typedef char C_changed_Offset[FIELD_OFFSET(C,changed)==152?1:-1];
typedef char C_clips_Offset[FIELD_OFFSET(C,clips)==160?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_control_Offset[FIELD_OFFSET(P,control)==336?1:-1];
typedef char P_frozen_Offset[FIELD_OFFSET(P,frozen)==348?1:-1];
typedef char P_zero_Offset[FIELD_OFFSET(P,zero)==400?1:-1];
typedef char P_yaw_Offset[FIELD_OFFSET(P,yaw)==424?1:-1];
typedef char P_forward_Offset[FIELD_OFFSET(P,forward)==432?1:-1];
typedef char P_asega_Offset[FIELD_OFFSET(P,asega)==4144?1:-1];
typedef char P_component_Offset[FIELD_OFFSET(P,component)==4148?1:-1];
typedef char P_first_Offset[FIELD_OFFSET(P,first)==6584?1:-1];
typedef char P_second_Offset[FIELD_OFFSET(P,second)==6588?1:-1];
typedef char CONTROL_yaw_Offset[FIELD_OFFSET(CONTROL,yaw)==24?1:-1];
typedef char RIG_inner_Offset[FIELD_OFFSET(RIG,inner)==168?1:-1];
typedef char INNER_value_Offset[FIELD_OFFSET(INNER,value)==96?1:-1];
typedef char VALUE_value_Offset[FIELD_OFFSET(VALUE,value)==32?1:-1];
typedef char CM_position_Offset[FIELD_OFFSET(CM,position)==144?1:-1];
typedef char POLY_a_Offset[FIELD_OFFSET(POLY,a)==0?1:-1];
typedef char POLY_b_Offset[FIELD_OFFSET(POLY,b)==4?1:-1];
typedef char POLY_c_Offset[FIELD_OFFSET(POLY,c)==8?1:-1];
typedef char LIMIT_lo_Offset[FIELD_OFFSET(LIMIT,lo)==0?1:-1];
typedef char LIMIT_hi_Offset[FIELD_OFFSET(LIMIT,hi)==4?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
extern "C" void func_001A0B40(C*p,int next){
 U velocity,camera0,camera1;
 if(next==p->mode)return;
 switch(p->mode){
 case -1:
  if(func_00132B10(p->actor,0x35)){
   P*actor=p->actor;actor->first->inner->value->value=D_002BFA00;
   actor->second->inner->value->value=D_002BFA00;
  }
  Invoke(p->actor,91);
  p->actor->zero.Clear();p->actor->frozen=0;p->changed=D_002A6720;
  break;
 case 3:case 10:
  if(func_00132B10(p->actor,0x35))p->actor->first->inner->value->value.Clear();
  break;
 }
 ASEG*clip=0;int flags=1;
 switch(next){
 case -1:
  if(func_00132B10(p->actor,0x35)){
   P*actor=p->actor;actor->first->inner->value->value.Clear();actor->second->inner->value->value.Clear();
  }
  p->actor->frozen=1;p->changed=D_002DDED0.time;break;
 case 8:
  {qword moving=Vector(p->actor);P*actor=p->actor;
  if(Dot(moving,&actor->forward)>-250.0f)next=9;
  else{
   qword v=From(Vector(actor));float speed=LengthXY(v);
   float c=D_002BFA20.c,b=D_002BFA20.b,a=D_002BFA20.a;
   c=speed*c;b=b+c;speed=speed*b;float fraction=a+speed;
   velocity.q=v;
   float blend=Clamp(fraction,&D_002BBB60);
   float angle=func_002458F0(velocity.f[1],velocity.f[0])+3.1415927f;
   angle=func_0011CF60(angle-p->actor->yaw);
   func_00204660(p->actor,p->actor->yaw+angle*blend);
   func_00204CA8(p->actor);
  }}
 case 9:clip=p->clips[next];flags=0x21;break;
 case 10:
  camera0.q=Position(&D_002DDF40);
  func_002046B0(p->actor,Difference(&camera0,func_001A62E8(p->actor)));
  flags=0x21;
 case 3:
  clip=p->clips[next];
  if(func_00132B10(p->actor,0x35))p->actor->first->inner->value->value=D_002BFA10;
  break;
 case 5:case 11:
  camera1.q=Position(&D_002DDF40);
  func_002046B0(p->actor,Difference1(&camera1,func_001A62E8(p->actor)));
  if(next==11)flags=0x21;
  clip=p->clips[next];break;
 case 0:case 6:case 7:clip=p->clips[next];break;
 case 4:case 12:
  SetVector(p->actor,D_002A2DD0.q);
  func_00204660(p->actor,func_00204740(p->actor));
  p->actor->control->yaw=p->actor->yaw;
  if(next==12)flags=0x21;
  clip=p->clips[next];break;
 case 1:case 2:
  flags=0;
  func_00204660(p->actor,func_00204740(p->actor));
  p->actor->control->yaw=p->actor->yaw;clip=p->clips[next];break;
 }
 func_001F4BF8(p->actor);
 p->mode=next;p->time=D_002DDED0.time;
 if(next!=-1){
  if(!clip)clip=p->Default(next);
  func_00130658(&p->actor->asega);func_001F15B8(&p->actor->component);
  func_001305B8(clip,p->actor,0.0f,1.0f,flags,&p->actor->asega);
  func_001F1448(0,p->actor,-1,0,&p->actor->component);
  Invoke(p->actor,90);
 }
}
