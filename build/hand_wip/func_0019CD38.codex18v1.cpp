#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
struct VE{short delta,pad;void(*fn)();};
union ZERO{struct{int a,b,c,d;};qword q;void Clear(){a=b=c=0;}};
struct ASEGA{char pad[12];VE*vt;};
struct P;
struct COMPONENT{char pad[0x30];ASEGA*child;};
struct P{char pad0[12];VE*vt;char pad10[0x190-0x10];ZERO zero;char pad1A0[0x1030-0x1A0];ASEGA*child;COMPONENT*component;};
struct C;
struct OBJECT{char pad[12];VE*vt;};
struct SUB{C*owner;int mode;OBJECT*first;OBJECT*defaultObject;OBJECT*second;void*effect;};
struct C{P*actor;int mode;float time;void*effect0;void*effect2;ASEGA*output;ASEGA*child;int pad1C;int type;SUB sub;float value;P*aux;OBJECT*setting;};
struct CAMERA{char pad0[12];VE*vt;float first;char pad14[0xA4-0x14];float second;};
struct MANAGER{char pad0[0x450];CAMERA first;char between[0xD0-0xA8];CAMERA second;};
struct CLOCK{float time,dt;};
extern "C"{
 extern MANAGER D_002DDF40;
 extern CLOCK D_002DDED0;
 extern char D_003DD040[],D_003DD490[];
 extern qword D_002A2DD0;
 void func_0014E4C8(MANAGER*,int,int,CAMERA*,P*,int);
 void func_0014E328(MANAGER*,int,CAMERA*,P*,int);
 void func_0014D8C0(MANAGER*);
 void func_001FEA60(void*,int,int,float);
 void func_001F5720(P*,int);
 void func_00204660(P*,float);
 void func_0019D660(SUB*,int);
 void func_0019DCA0(SUB*,OBJECT*);
 void func_0020F198(void*);
 void func_0020F0C0(void*);
 void func_0020F1A8(void*);
 void func_0020F0F0(void*);
 void func_00131A00(ASEGA*,float);
 void func_001305B8(void*,P*,float,float,int,ASEGA**);
}
static inline void Flag(P*p,int slot,int key,int value){VE*v=&p->vt[slot];((void(*)(P*,int,int))v->fn)((P*)((char*)p+v->delta),key,value);}
static inline void Toggle(P*p,int value){VE*v=&p->vt[87];((void(*)(P*,int))v->fn)((P*)((char*)p+v->delta),value);}
static inline void Invoke(ASEGA*p,int slot){VE*v=&p->vt[slot];((void(*)(ASEGA*))v->fn)((ASEGA*)((char*)p+v->delta));}
static inline int Enabled(P*p){VE*v=&p->vt[94];return ((int(*)(P*))v->fn)((P*)((char*)p+v->delta));}
static inline void SetVector(P*p,int slot,qword value){VE*v=&p->vt[slot];((void(*)(P*,qword))v->fn)((P*)((char*)p+v->delta),value);}
typedef char SUB_Size[sizeof(SUB)==24?1:-1];
typedef char CAMERA_ConsumedPrefix[sizeof(CAMERA)==168?1:-1];
typedef char ZERO_Size[sizeof(ZERO)==16?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==0?1:-1];
typedef char C_mode_Offset[FIELD_OFFSET(C,mode)==4?1:-1];
typedef char C_time_Offset[FIELD_OFFSET(C,time)==8?1:-1];
typedef char C_effect0_Offset[FIELD_OFFSET(C,effect0)==12?1:-1];
typedef char C_effect2_Offset[FIELD_OFFSET(C,effect2)==16?1:-1];
typedef char C_output_Offset[FIELD_OFFSET(C,output)==20?1:-1];
typedef char C_child_Offset[FIELD_OFFSET(C,child)==24?1:-1];
typedef char C_type_Offset[FIELD_OFFSET(C,type)==32?1:-1];
typedef char C_sub_Offset[FIELD_OFFSET(C,sub)==36?1:-1];
typedef char C_value_Offset[FIELD_OFFSET(C,value)==60?1:-1];
typedef char C_aux_Offset[FIELD_OFFSET(C,aux)==64?1:-1];
typedef char C_setting_Offset[FIELD_OFFSET(C,setting)==68?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_zero_Offset[FIELD_OFFSET(P,zero)==400?1:-1];
typedef char P_child_Offset[FIELD_OFFSET(P,child)==4144?1:-1];
typedef char P_component_Offset[FIELD_OFFSET(P,component)==4148?1:-1];
typedef char COMPONENT_child_Offset[FIELD_OFFSET(COMPONENT,child)==48?1:-1];
typedef char ASEGA_vt_Offset[FIELD_OFFSET(ASEGA,vt)==12?1:-1];
typedef char SUB_owner_Offset[FIELD_OFFSET(SUB,owner)==0?1:-1];
typedef char SUB_mode_Offset[FIELD_OFFSET(SUB,mode)==4?1:-1];
typedef char SUB_first_Offset[FIELD_OFFSET(SUB,first)==8?1:-1];
typedef char SUB_defaultObject_Offset[FIELD_OFFSET(SUB,defaultObject)==12?1:-1];
typedef char SUB_second_Offset[FIELD_OFFSET(SUB,second)==16?1:-1];
typedef char SUB_effect_Offset[FIELD_OFFSET(SUB,effect)==20?1:-1];
typedef char CAMERA_vt_Offset[FIELD_OFFSET(CAMERA,vt)==12?1:-1];
typedef char CAMERA_first_Offset[FIELD_OFFSET(CAMERA,first)==16?1:-1];
typedef char CAMERA_second_Offset[FIELD_OFFSET(CAMERA,second)==164?1:-1];
typedef char MANAGER_first_Offset[FIELD_OFFSET(MANAGER,first)==1104?1:-1];
typedef char MANAGER_second_Offset[FIELD_OFFSET(MANAGER,second)==1312?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
extern "C" void func_0019CD38(C*incomingP,int incomingNext){
 register C*p __asm__("$18");
 __asm__("daddu %0,%1,$zero":"=r"(p):"r"(incomingP));
 register int next __asm__("$17")=incomingNext;
 int oldMode=p->mode;
 if(next==oldMode)return;
 switch(oldMode){
 case 1:
  switch(p->type){
  case 0:func_0014E4C8(&D_002DDF40,15,7,&D_002DDF40.first,p->actor,0);break;
  case 1:{
   func_0014E4C8(&D_002DDF40,15,8,&D_002DDF40.second,p->actor,0);
   P*aux=p->aux;
   if(aux){Flag(aux,84,0x3F,1);func_001F5720(aux,0);}
   Flag(p->actor,84,0x3F,0);break;
  }
  case 2:func_0014E4C8(&D_002DDF40,15,7,&D_002DDF40.first,p->aux,0);break;
  }
  func_0014D8C0(&D_002DDF40);
  func_001FEA60(D_003DD040,0,3,1.0f);func_001FEA60(D_003DD040,1,3,1.0f);
  if(p->type!=2)Toggle(p->actor,0);
  break;
 case -1:
  if(p->type==1){func_0020F198(D_003DD490);func_0020F0C0(D_003DD490);}
  if(p->actor->child)p->child=p->actor->child;
  else if(p->actor->component)p->child=p->actor->component->child;
  if(p->child){Invoke(p->child,1);func_00131A00(p->child,0.0f);}
  break;
 }
 p->mode=next;p->time=D_002DDED0.time;
 register void*effect __asm__("$19")=0;
 switch(next){
 case 0:effect=p->effect0;break;
 case 1:
  switch(p->type){
  case 0:
   func_0014E328(&D_002DDF40,7,&D_002DDF40.first,p->actor,0);
   func_00204660(p->actor,D_002DDF40.first.first);func_0019D660(&p->sub,0);break;
  case 1:{
   func_0014E328(&D_002DDF40,8,&D_002DDF40.second,p->actor,0);
   func_00204660(p->actor,D_002DDF40.second.second);
   register P*aux __asm__("$17");
   __asm__("lw %0,0x40(%1)":"=r"(aux):"r"(p):"memory");
   if(aux){
    register int enabled __asm__("$6"),delta __asm__("$4");
    register VE*vtable __asm__("$3");register void(*flag)(P*,int,int) __asm__("$2");
    register qword*zero __asm__("$16")=&D_002A2DD0;
    __asm__("lw %0,0xc(%2)\n\tli %1,1":"=r"(vtable),"=r"(enabled):"r"(aux):"memory");
    __asm__("lh %0,0x298(%2)\n\tlw %1,0x29c(%2)":"=r"(delta),"=r"(flag):"r"(vtable):"memory");
    flag((P*)((char*)aux+delta),0x3f,enabled);
    func_001F5720(aux,1);aux->zero.Clear();
    {
     register VE*vt __asm__("$2");register qword value __asm__("$5");
     register void(*setVector)(P*,qword) __asm__("$3");
     __asm__("lw %0,0xc(%4)\n\tlq %1,0(%5)\n\tlh %2,0x118(%0)\n\tlw %3,0x11c(%0)":"=&r"(vt),"=r"(value),"=r"(delta),"=r"(setVector):"r"(aux),"r"(zero):"memory");
     setVector((P*)((char*)aux+delta),value);
     __asm__("lw %0,0xc(%4)\n\tlq %1,0(%5)\n\tlh %2,0x120(%0)\n\tlw %3,0x124(%0)":"=&r"(vt),"=r"(value),"=r"(delta),"=r"(setVector):"r"(aux),"r"(zero):"memory");
     setVector((P*)((char*)aux+delta),value);
    }
    register SUB*sub __asm__("$16");register OBJECT*setting __asm__("$5");
    __asm__("addiu %0,%2,0x24\n\tlw %1,0x44(%2)":"=r"(sub),"=r"(setting):"r"(p):"memory");
    func_0019DCA0(sub,setting);func_0019D660(sub,0);
   }
   Flag(p->actor,83,0x3F,0);break;
  }
  case 2:func_0014E328(&D_002DDF40,7,&D_002DDF40.first,p->aux,0);func_0019D660(&p->sub,0);break;
  }
  p->actor->zero.Clear();
  SetVector(p->actor,35,D_002A2DD0);SetVector(p->actor,36,D_002A2DD0);
  func_0014D8C0(&D_002DDF40);
  func_001FEA60(D_003DD040,0,3,0.6f);func_001FEA60(D_003DD040,1,3,0.6f);
  if(p->type!=2)Toggle(p->actor,1);break;
 case 2:func_0019D660(&p->sub,2);effect=p->effect2;break;
 case -1:
  switch(p->type){
  case 0:case 2:func_0019D660(&p->sub,-1);break;
  case 1:func_0019D660(&p->sub,-1);func_0020F1A8(D_003DD490);func_0020F0F0(D_003DD490);break;
  }
  if(p->child){func_00131A00(p->child,1.0f);Invoke(p->child,2);p->child=0;}
  p->type=-1;break;
 }
 if(effect&&!Enabled(p->actor))effect=0;
 func_001305B8(effect,p->actor,0.0f,1.0f,1,&p->output);
}
