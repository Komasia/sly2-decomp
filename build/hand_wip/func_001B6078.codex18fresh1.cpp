typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct VE{short delta,pad;void(*fn)();};
struct OBJ{char pad[12];VE*vt;};
struct ASEG{char pad[0x74];float duration;};
struct ASEGA{char pad[0x14];ASEG*clip;char pad18[4];float time;char pad20[0x40-0x20];float rate;};
struct COMPONENT;
struct ENTRY{float value;int kind,key,pad;};
struct P{char pad0[12];VE* vt;char pad10[72];void* first;void* second;char pad60[304];U velocity;float phase;char pad1a4[804];int submode;char pad4cc[2908];void* template0;void* template16;ASEGA* asega;COMPONENT* component;char pad1038[84];int retain;char pad1090[660];ASEG* clip1;char pad1328[168];int state;float time;char pad13d8[8];ASEG* clip3;char pad13e4[4];int alternate3;char pad13ec[32];ASEG* clip7;char pad1410[16];U goal;char pad1430[8];ASEG* clip8;int alternate8;ASEG* clip4a;ASEG* clip4b;char pad1448[4];int clipKind;char pad1450[208];void* template6;char pad1524[12];int marker;char pad1534[16];ASEG* clip10;char pad1548[980];OBJ* object15;int stamp15;char pad1924[300];OBJ* firstCleanup;OBJ* secondCleanup;char pad1a58[136];ASEG* extra7;ASEG* extra8;ASEG* extra3;ASEG* clip21;};
extern "C"{
 struct CLOCK{float t,dt;};extern CLOCK D_002DDED0;
 extern U D_002A2DD0;
 extern int D_002DD5BC;
 void func_002303A0(P*,void*,int);
 void func_00142880(P*);
 void func_001B6DA8(P*,int);
 void func_0015C150(OBJ*);
 void func_00195FB8(void*,int,int);
 void func_00192BD8(void*,int);
 void func_001A0B40(void*,int);
 void func_001B86B0(P*,int);
 void func_001B8D30(P*,int);
 void func_001B93E8(P*,int);
 void func_001B5658(P*,int);
 void func_001B5D30(P*,int);
 void func_002206C8(void*,int);
 void func_001F5720(P*,int);
 void func_0019EAB0(void*,int);
 int func_001F0400(void*,int);
 int func_001430C8(P*);
 void func_00142868(P*,int);
 void func_0020BD68(void*);
 void func_0019CD38(void*,int);
 int func_001DAEA8(int);
 void func_001B5E98(P*);
 qword func_001A62E8(P*);
 void func_002046B0(P*,qword);
 void func_00130658(ASEGA**);
 void func_001F15B8(COMPONENT**);
 void func_001305B8(ASEG*,P*,float,float,int,ASEGA**);
 void func_001F14F8(void*,P*,int,int,int,COMPONENT**);
 ENTRY*func_0012F938(ASEG*,int);
 void func_00131A90(ASEGA*,float);
}
static inline void*Block(P*p,int offset){return (void*)((char*)p+offset);}
static inline void Call(OBJ*p,int index){VE&v=p->vt[index];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetVelocity(P*p,qword q){VE&v=p->vt[35];((void(*)(void*,qword))v.fn)((char*)p+v.delta,q);}
static inline qword ReadZero(){register qword q __asm__("$3");__asm__("lq %0,%1":"=r"(q):"m"(D_002A2DD0.q));return q;}
static inline float Zero(){float f;__asm__("mtc1 $zero,%0":"=f"(f));return f;}

#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char ENTRY_Size[sizeof(ENTRY)==16?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_first_Offset[FIELD_OFFSET(P,first)==88?1:-1];
typedef char P_second_Offset[FIELD_OFFSET(P,second)==92?1:-1];
typedef char P_velocity_Offset[FIELD_OFFSET(P,velocity)==400?1:-1];
typedef char P_phase_Offset[FIELD_OFFSET(P,phase)==416?1:-1];
typedef char P_submode_Offset[FIELD_OFFSET(P,submode)==1224?1:-1];
typedef char P_template0_Offset[FIELD_OFFSET(P,template0)==4136?1:-1];
typedef char P_template16_Offset[FIELD_OFFSET(P,template16)==4140?1:-1];
typedef char P_asega_Offset[FIELD_OFFSET(P,asega)==4144?1:-1];
typedef char P_component_Offset[FIELD_OFFSET(P,component)==4148?1:-1];
typedef char P_retain_Offset[FIELD_OFFSET(P,retain)==4236?1:-1];
typedef char P_clip1_Offset[FIELD_OFFSET(P,clip1)==4900?1:-1];
typedef char P_state_Offset[FIELD_OFFSET(P,state)==5072?1:-1];
typedef char P_time_Offset[FIELD_OFFSET(P,time)==5076?1:-1];
typedef char P_clip3_Offset[FIELD_OFFSET(P,clip3)==5088?1:-1];
typedef char P_alternate3_Offset[FIELD_OFFSET(P,alternate3)==5096?1:-1];
typedef char P_clip7_Offset[FIELD_OFFSET(P,clip7)==5132?1:-1];
typedef char P_goal_Offset[FIELD_OFFSET(P,goal)==5152?1:-1];
typedef char P_clip8_Offset[FIELD_OFFSET(P,clip8)==5176?1:-1];
typedef char P_alternate8_Offset[FIELD_OFFSET(P,alternate8)==5180?1:-1];
typedef char P_clip4a_Offset[FIELD_OFFSET(P,clip4a)==5184?1:-1];
typedef char P_clip4b_Offset[FIELD_OFFSET(P,clip4b)==5188?1:-1];
typedef char P_clipKind_Offset[FIELD_OFFSET(P,clipKind)==5196?1:-1];
typedef char P_template6_Offset[FIELD_OFFSET(P,template6)==5408?1:-1];
typedef char P_marker_Offset[FIELD_OFFSET(P,marker)==5424?1:-1];
typedef char P_clip10_Offset[FIELD_OFFSET(P,clip10)==5444?1:-1];
typedef char P_object15_Offset[FIELD_OFFSET(P,object15)==6428?1:-1];
typedef char P_stamp15_Offset[FIELD_OFFSET(P,stamp15)==6432?1:-1];
typedef char P_firstCleanup_Offset[FIELD_OFFSET(P,firstCleanup)==6736?1:-1];
typedef char P_secondCleanup_Offset[FIELD_OFFSET(P,secondCleanup)==6740?1:-1];
typedef char P_extra7_Offset[FIELD_OFFSET(P,extra7)==6880?1:-1];
typedef char P_extra8_Offset[FIELD_OFFSET(P,extra8)==6884?1:-1];
typedef char P_extra3_Offset[FIELD_OFFSET(P,extra3)==6888?1:-1];
typedef char P_clip21_Offset[FIELD_OFFSET(P,clip21)==6892?1:-1];
typedef char ASEGA_clip_Offset[FIELD_OFFSET(ASEGA,clip)==20?1:-1];
typedef char ASEGA_time_Offset[FIELD_OFFSET(ASEGA,time)==28?1:-1];
typedef char ASEGA_rate_Offset[FIELD_OFFSET(ASEGA,rate)==64?1:-1];
typedef char ASEG_duration_Offset[FIELD_OFFSET(ASEG,duration)==116?1:-1];
typedef char OBJ_vt_Offset[FIELD_OFFSET(OBJ,vt)==12?1:-1];
typedef char VE_delta_Offset[FIELD_OFFSET(VE,delta)==0?1:-1];
typedef char VE_fn_Offset[FIELD_OFFSET(VE,fn)==4?1:-1];
typedef char ENTRY_value_Offset[FIELD_OFFSET(ENTRY,value)==0?1:-1];
typedef char ENTRY_kind_Offset[FIELD_OFFSET(ENTRY,kind)==4?1:-1];
typedef char ENTRY_key_Offset[FIELD_OFFSET(ENTRY,key)==8?1:-1];
typedef char CLOCK_t_Offset[FIELD_OFFSET(CLOCK,t)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char float_Size[sizeof(float)==4?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char unsigned_Size[sizeof(unsigned)==4?1:-1];
typedef char pointer_Size[sizeof(void*)==4?1:-1];
typedef char short_Size[sizeof(short)==2?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char P_Prefix_Size[sizeof(P)==0x1AF0?1:-1];
typedef char OBJ_Prefix_Size[sizeof(OBJ)==16?1:-1];
typedef char ASEG_Prefix_Size[sizeof(ASEG)==0x78?1:-1];
typedef char ASEGA_Prefix_Size[sizeof(ASEGA)==0x44?1:-1];
extern "C" void func_001B6078(P*p,int next){
 if(next==p->state)return;
 switch(p->state){
 case 0:
  func_002303A0(p,p->first,2);func_002303A0(p,p->second,2);func_00142880(p);break;
 case 16:case 17:case 18:
  func_002303A0(p,p->first,2);func_002303A0(p,p->second,2);break;
 case 3:func_001B6DA8(p,-1);break;
 case 2:{
  if(!p->retain){
   OBJ*object=0;
   switch(next){
   case 0:case 1:case 4:case 5:case 9:case 11:case 12:object=p->firstCleanup;break;
   case 2:case 3:case 6:case 7:case 8:case 10:break;
   case 13:{
    switch(p->submode){case 1:break;case 3:case 4:object=p->secondCleanup;break;default:object=p->firstCleanup;break;}
    break;
   }
   }
   if(object){Call(object,8);func_0015C150(object);Call(object,9);}
  }
  func_00195FB8(Block(p,0x2C0),-1,0);break;
 }
 case 13:func_00192BD8(Block(p,0x4C0),-1);break;
 case 14:func_001A0B40(Block(p,0xDF0),-1);break;
 case 11:func_001B86B0(p,-1);break;
 case 12:func_001B8D30(p,-1);break;
 case 4:func_001B93E8(p,-1);break;
 case 5:func_001B5658(p,-1);break;
 case 9:func_001B5D30(p,-1);break;
 case 15:Call(p->object15,9);func_002206C8(Block(p,0x1910),-1);func_001F5720(p,0);break;
 case 1:case 10:p->phase=p->asega->time/p->asega->clip->duration;break;
 case 6:p->marker=0;break;
 case 20:func_0019EAB0(Block(p,0xF50),-1);break;
 case 7:case 8:case 19:break;
 }
 int old=p->state;
 p->state=next;
 ASEG*clip=0;void*source=0;int flags=1,id=-1,mode=4;void*activation;
 float duration=Zero();
 p->time=D_002DDED0.t;
 switch(next){
 case 0:
  func_002303A0(p,p->first,1);func_002303A0(p,p->second,1);
  source=p->template0;p->velocity=D_002A2DD0;
  if(old!=2){register unsigned different __asm__("$3");__asm__("xori %0,%1,10":"=r"(different):"r"(old));id=different?0x175:0x176;}else id=0x178;
  if(func_001F0400(source,id)<0)id=-1;
  mode=func_001430C8(p);func_00142868(p,1);break;
 case 1:clip=p->clip1;activation=Block(p,0x1320);goto activate;
 case 14:func_0019CD38(Block(p,0xF00),-1);break;
 case 3:{func_001B6DA8(p,0);ASEG*a=p->extra3;if(a&&p->alternate3)clip=a;else clip=p->clip3;break;}
 case 5:func_001B5658(p,0);Call((OBJ*)p,90);return;
 case 6:source=p->template6;break;
 case 4:
  switch(p->clipKind){case 0:clip=p->clip4a;break;case 1:clip=p->clip4b;break;}
  p->velocity=D_002A2DD0;func_001B93E8(p,0);break;
 case 7:{
  ASEG*a=p->extra7;
  if(a&&func_001DAEA8(0x11))clip=p->extra7;else clip=p->clip7;
  p->velocity.q=ReadZero();func_001B5E98(p);
  U point=p->goal;qword current=func_001A62E8(p);
  register qword difference __asm__("vf1"),positionVector __asm__("vf2");register P*receiver __asm__("$4");
  __asm__("lqc2 %0,%3\n\tdaddu %2,%5,$zero\n\tqmtc2.ni %4,%1\n\tvsub.xyzw %0,%0,%1":"=&j"(difference),"=&j"(positionVector),"=&r"(receiver):"m"(point.q),"r"(current),"r"(p));
  func_002046B0(receiver,difference);break;
 }
 case 8:{ASEG*a=p->extra8;if(a&&p->alternate8)clip=a;else clip=p->clip8;goto clear_velocity;}
 case 9:func_001B5D30(p,0);Call((OBJ*)p,90);return;
 case 10:clip=p->clip10;activation=Block(p,0x1540);activate:flags=9;func_0020BD68(activation);break;
 case 15:
  Call(p->object15,8);p->stamp15=D_002DD5BC;func_002206C8(Block(p,0x1910),0);func_001F5720(p,1);SetVelocity(p,D_002A2DD0.q);return;
 case 16:source=p->template16;
 case 17:case 18:
  func_002303A0(p,p->first,1);func_002303A0(p,p->second,1);clear_velocity:p->velocity=D_002A2DD0;break;
 case 20:func_0019EAB0(Block(p,0xF50),0);return;
 case 21:{clip=p->clip21;register U*velocity __asm__("$2");__asm__("addiu %0,%1,%2":"=r"(velocity):"r"(p),"i"(FIELD_OFFSET(P,velocity)));velocity->i[2]=0;flags=9;velocity->i[1]=0;p->velocity.i[0]=0;break;}
 case 2:case 11:case 12:case 13:case 19:break;
 }
 {
  ASEGA**animation=&p->asega;COMPONENT**component=&p->component;float position=0.0f;
  func_00130658(animation);func_001F15B8(component);
  func_001305B8(clip,p,position,1.0f,flags,animation);
  func_001F14F8(source,p,id,flags,mode,component);
  if(clip||source){
   if(clip){if(duration==position){ENTRY*e=func_0012F938(clip,0x1AC);if(e)duration=e->value;}}
   if(duration!=0.0f)func_00131A90(p->asega,D_002DDED0.t+duration/p->asega->rate);
  }
 }
 Call((OBJ*)p,90);
}
