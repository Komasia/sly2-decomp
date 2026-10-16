// Complete movement-state draft; 36/243 differences, native243 words/frameE0.
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int bits[4];void Assign(const U&v){q=v.q;}};
union F{float value;int bits;};
struct VE{short delta,pad;void(*fn)();};
struct GROUP{char pad[0xA0];void*space;};
struct TUNE{char pad[0xD0];float speed;};
struct P{char pad0[12];VE*vt;char pad10[0x58-0x10];GROUP*first;GROUP*second;char pad60[0xE8-0x60];TUNE*tuning;char padEC[0x334-0xEC];int attention;char pad338[0x10DC-0x338];P*owner;};
struct ASEGA;
struct ENTRY{float value;int kind,key,pad;};
struct CONTROL{char pad0[4];void*curves;ASEGA*asega;};
struct DELTA;
struct REQUEST{int flag;float a,b;int pad;U point,direction;};
struct C{char pad0[0x10];P*actor;char pad14[0x40-0x14];CONTROL*control;char pad44[12];int mode;float time;int pad58;P*target;int owned;DELTA*delta;};
struct CLOCK{float time,dt;};
extern "C"{
 extern CLOCK D_002DDED0;
 extern float D_002BE6FC,D_002BE700,D_002BE704;
 extern F D_002BE708;
 extern U D_002A2DC0;
 extern char D_003DD490[],D_002DFC00[];
 void func_001F35C8(P*,float);
 void func_00130D30(ASEGA*,int,float,float);
 void func_0012E460(DELTA**);
 void func_002303A0(P*,GROUP*,int);
 void func_00134320(void*,P*);
 void func_001F4E28(P*);
 void func_001749C0(C*,int);
 void func_0017AA78(C*,REQUEST*,U*,U*);
 qword func_001A62E8(P*);
 qword func_0022FC48(void*,void*,qword);
 qword func_0022FCC8(void*,void*,qword);
 DELTA*func_0012DE58(P*,GROUP*,void*,float,qword,qword);
 P*func_001C4840(void*);
 void func_00187E28(void*,int,float);
 ENTRY*func_0012F938(void*,int);
}
static inline void Request(P*p,REQUEST*r,float duration){VE*v=&p->vt[96];((void(*)(P*,REQUEST*,float))v->fn)((P*)((char*)p+v->delta),r,duration);}
static inline void SetVector(P*p,qword value){VE*v=&p->vt[35];((void(*)(P*,qword))v->fn)((P*)((char*)p+v->delta),value);}
static inline qword Word(float value){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(value));return r;}
static inline qword Blend(U*desired,qword current,U*scale,U*scratch){
 register qword a __asm__("vf1"),b __asm__("vf2"),d __asm__("vf3"),lift __asm__("vf2"),axis __asm__("vf1"),k __asm__("vf4");
 __asm__("qmtc2.ni %1,%0":"=j"(b):"r"(current));
 __asm__("lqc2 %0,%1":"=j"(a):"m"(desired->q));
 __asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));
 __asm__("qmtc2.ni %1,%0":"=j"(lift):"r"(D_002BE708.bits));
 __asm__("lqc2 %0,%1":"=j"(axis):"m"(D_002A2DC0.q));
 __asm__("lqc2 %0,%1":"=j"(k):"m"(scale->q));
 scratch->q=lift;
 __asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(k):"j"(d),"j"(axis),"j"(scratch->q));
 return k;
}
typedef char REQUEST_Size[sizeof(REQUEST)==48?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char F_Size[sizeof(F)==4?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char ENTRY_Size[sizeof(ENTRY)==16?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==16?1:-1];
typedef char C_control_Offset[FIELD_OFFSET(C,control)==64?1:-1];
typedef char C_mode_Offset[FIELD_OFFSET(C,mode)==80?1:-1];
typedef char C_time_Offset[FIELD_OFFSET(C,time)==84?1:-1];
typedef char C_target_Offset[FIELD_OFFSET(C,target)==92?1:-1];
typedef char C_owned_Offset[FIELD_OFFSET(C,owned)==96?1:-1];
typedef char C_delta_Offset[FIELD_OFFSET(C,delta)==100?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_first_Offset[FIELD_OFFSET(P,first)==88?1:-1];
typedef char P_second_Offset[FIELD_OFFSET(P,second)==92?1:-1];
typedef char P_tuning_Offset[FIELD_OFFSET(P,tuning)==232?1:-1];
typedef char P_attention_Offset[FIELD_OFFSET(P,attention)==820?1:-1];
typedef char P_owner_Offset[FIELD_OFFSET(P,owner)==4316?1:-1];
typedef char GROUP_space_Offset[FIELD_OFFSET(GROUP,space)==160?1:-1];
typedef char TUNE_speed_Offset[FIELD_OFFSET(TUNE,speed)==208?1:-1];
typedef char CONTROL_curves_Offset[FIELD_OFFSET(CONTROL,curves)==4?1:-1];
typedef char CONTROL_asega_Offset[FIELD_OFFSET(CONTROL,asega)==8?1:-1];
typedef char REQUEST_flag_Offset[FIELD_OFFSET(REQUEST,flag)==0?1:-1];
typedef char REQUEST_a_Offset[FIELD_OFFSET(REQUEST,a)==4?1:-1];
typedef char REQUEST_b_Offset[FIELD_OFFSET(REQUEST,b)==8?1:-1];
typedef char REQUEST_point_Offset[FIELD_OFFSET(REQUEST,point)==16?1:-1];
typedef char REQUEST_direction_Offset[FIELD_OFFSET(REQUEST,direction)==32?1:-1];
typedef char ENTRY_value_Offset[FIELD_OFFSET(ENTRY,value)==0?1:-1];
typedef char ENTRY_kind_Offset[FIELD_OFFSET(ENTRY,kind)==4?1:-1];
typedef char ENTRY_key_Offset[FIELD_OFFSET(ENTRY,key)==8?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
static inline int Still(int m){int f=0;if(m==4||m==5||m==0)f=1;return f;}
extern "C" void func_0017B1A8(C*p,int next){
 REQUEST request;
 U point,direction,scratch,scale,cached;
 if(next==p->mode)return;
 switch(p->mode){
 case -1:func_001F35C8(p->actor,D_002BE6FC*p->actor->tuning->speed);break;
 case 3:if(next!=-1)func_00130D30(p->control->asega,0,0.0f,1.0f);break;
 }
 if((unsigned)p->mode<2&&(unsigned)next>=2){
  func_0012E460(&p->delta);func_002303A0(p->actor,p->actor->first,2);func_002303A0(p->actor,p->actor->second,2);
 }
 int was=Still(p->mode),now=Still(next);
 p->mode=next;
 if(was!=now){func_00134320(D_003DD490,p->actor);func_001F4E28(p->actor);}
 p->mode=next;p->time=D_002DDED0.time;
 switch(next){
 case -1:func_001F35C8(p->actor,p->actor->tuning->speed/D_002BE6FC);func_001749C0(p,1);break;
 case 0:{
  Request(p->target,&request,D_002BE700);
  func_0017AA78(p,&request,&point,&direction);
  cached.Assign(point);
  scratch.q=Word(D_002BE704/D_002BE700);scale=scratch;
  qword current=func_001A62E8(p->actor);
  SetVector(p->actor,Blend(&cached,current,&scale,&scratch));
  GROUP*first=p->actor->first;
  if(!p->delta){
   float end=D_002DDED0.time+D_002BE700;
   qword localPoint=func_0022FC48(0,first->space,point.q);
   qword localDirection=func_0022FCC8(0,first->space,direction.q);
   p->delta=func_0012DE58(p->actor,first,0,end,localPoint,localDirection);
  }
  int owned=0;if(request.flag)owned=p->target->owner==p->actor;p->owned=owned;
  if(p->actor->attention){P*focus=func_001C4840(D_003DD490);if(focus&&focus==p->target)func_00187E28(D_002DFC00,3,0.15f);}
  break;
 }
 case 3:{ENTRY*entry=func_0012F938(p->control->curves,0x3C);if(entry)func_00130D30(p->control->asega,0,entry->value,1.0f);break;}
 case 4:case 5:
  if(p->mode==4){ENTRY*entry=func_0012F938(p->control->curves,0x173);if(entry)func_00130D30(p->control->asega,0,entry->value,1.0f);}
  break;
 case 1:case 2:break;
 }
}
