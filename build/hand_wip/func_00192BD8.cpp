typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;
union U{qword q;float f[4];int i[4];};struct M3{U row[3];};struct VTE{short delta,pad;void*fn;};struct ACTOR;struct SOURCE;struct ANIMATION;struct EFFECT;struct CLIP{char pad0[0x74];float duration;};struct PROGRAM;struct CAMERA;struct MANAGER;struct SPACE;
struct INPUT{char pad0[0x1C];float amount;};
struct BASE{char pad0[12];VTE*vt;char pad10[0x30];uint flags;};struct COMPONENT{void*object;};struct PROGRAM_ITEM{ACTOR*actor;CLIP*clip;char pad8[0x94];int active,count;};
struct SUB{char pad0[0x30];CLIP*clip;ACTOR*actor;char pad38[0x4C];SOURCE*focus;char pad88[0x1C];};
struct SPARSE{char pad0[0x10];float x;char pad14[12];float y;char pad24[12];float z;};struct AUX{ACTOR*owner;char pad4[0x108];SOURCE*target;char pad110[4];SPARSE*data;char pad118[0x10];int mode,enabled;char pad130[0x10];int phase;char pad144[12];U position;float value;};
union LINK_FIELD{int mode;ACTOR*owner;};struct SOURCE{char pad0[12];VTE*vt;char pad10[0xD0];LINK_FIELD link;char padE4[0x28];float parameter;char pad110[4];SPARSE*data;char pad118[0x44];ACTOR*other;char pad160[0x30];ACTOR*actor;char pad194[0x28];int enabled;};
struct ACTOR{char pad0[12];VTE*vt;char pad10[0x30];uint flags;char pad44[0x10C];INPUT*input;char pad154[0x3C];U velocity;char pad1A0[0x10];char local[1];char pad1B1[0x5B];float stamp;char pad210[0x20];U position,offset;char pad250[0x6B0];char secondary[1];char pad901[0xBB];int tag9BC;char pad9C0[0x664];void*focus;char pad1028[8];ANIMATION*animation;COMPONENT component;int tag1038;char pad103C[12];float height;char pad104C[20];U motion;char pad1070[0x50];void*anchor;char pad10C4[0x248];void*field130C;char pad1310[8];int tag1318;char pad131C[0x5BC];int field18D8;char pad18DC[0xC4];BASE*first,*second;char pad19A8[0x148];CLIP*specialClip;char pad1AF4[0xD8];int flag1BCC;char pad1BD0[0x60];PROGRAM_ITEM program;char pad1CD4[0x374];EFFECT*effect;};
struct CONTEXT{ACTOR*actor;float stamp;int action,step;float time;SOURCE*focus;void*setting;float parameter,value;int reversed,index,previous;char pad30[4];int changed;char pad38[0x30];AUX*aux;char pad6C[0x104];CLIP*clip170,*clip174,*clip178,*clip17C;PROGRAM_ITEM program180;char pad224[12];PROGRAM*script230;CLIP*clip234,*clip238;char pad23C[4];PROGRAM_ITEM program240;char pad2E4[0x30];CLIP*overrideClip;float gain318,gain31C;CLIP*clip320,*clip324,*clip328;PROGRAM*script32C;char pad330[0x100];CLIP*clip430;char pad434[12];SUB sub;char pad4E4[12];CLIP*clip4F0,*clip4F4,*clip4F8;int tag,inhibited;char pad504[8];CLIP*clip50C,*clip510,*clip514;};
struct CLOCK{float time,dt;};struct WORK{U direction,tangent;M3 matrix;};
extern "C"{extern CLOCK D_002DDED0;extern ACTOR*D_002E1E40,*D_002F7900;extern MANAGER D_002DDF40;extern U D_002A2DA0,D_002A2DC0,D_002A2DD0,D_002BF650;extern float D_002BF63C,D_002BF640;
int func_00132B10(void*,int);qword func_001A62E8(void*);M3*func_001A6318(void*);void func_001E6F60(SOURCE*,qword,SPACE*,U*,U*,float*,float*);void func_00183B80(SOURCE*,int);void func_001333C0(SOURCE*,ACTOR*);void func_00133448(SOURCE*,ACTOR*);void func_00204F78(ACTOR*,void*,int);void func_001E67B8(SOURCE*,float,U*,U*);EFFECT*func_001FBB90(int);void func_001FB2F8(EFFECT*,SOURCE*);void func_00258040(EFFECT**,EFFECT*);void func_002046F0(ACTOR*,SOURCE*);void func_00204CA8(ACTOR*);void func_002046B0(ACTOR*,qword);void func_0014E328(MANAGER*,int,CAMERA*,ACTOR*,void*);void func_0014E4C8(MANAGER*,int,int,CAMERA*,ACTOR*,void*);void func_0018E540(ACTOR*,int);void func_001CCAC0(SUB*,int);void func_001CD2C0(void*);void func_001FB098(EFFECT*,float);void func_00140C88(ACTOR*,void*);void func_00194118(CONTEXT*);qword func_001A6F00(void*,void*,qword);void func_0020BD68(PROGRAM_ITEM*);void func_00130658(ANIMATION**);void func_001F15B8(COMPONENT*);void func_001305B8(CLIP*,ACTOR*,float,float,int,ANIMATION**);void func_001F1448(PROGRAM*,ACTOR*,int,int,COMPONENT*);void func_0018C120(ACTOR*,int);}
static inline bool Less(int x,int limit){return x<limit;}
static inline qword Read(U*p){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(*p));return q;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Subtract(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword AddScaled(qword a,qword b,qword k){qword q;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(a),"j"(b),"j"(k));return q;}
static inline qword Rotate(M3*m,qword v){qword q;__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(q):"j"(m->row[0].q),"j"(m->row[1].q),"j"(m->row[2].q),"j"(v));return q;}
static inline float Dot(qword a,qword b){qword d,k;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(k):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline void Normalize(U*object){qword v=Read(object),d,k;float length;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(k):"j"(v));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));qword fallback=D_002A2DA0.q;__asm__("qmfc2.ni %0,%1":"=r"(length):"j"(d));if(length<0.0001f)object->q=fallback;else{__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(d):"j"(d),"j"(v));object->q=d;}}
static inline void SourceState(SOURCE*p,int code){VTE&v=p->vt[3];((void(*)(void*,int,void*,void*,void*,void*))v.fn)((char*)p+v.delta,code,0,0,0,0);}
static inline void Notify(BASE*p,int slot){VTE&v=p->vt[slot];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetVector(ACTOR*p,int slot,qword value){VTE&v=p->vt[slot];((void(*)(void*,qword))v.fn)((char*)p+v.delta,value);}
static inline void SetLocal(ACTOR*p){VTE&v=p->vt[30];((void(*)(void*,void*))v.fn)((char*)p+v.delta,p->local);}
static inline void FlagOr(uint*field,uint bits){uint old=*field;if((old^1)&1)*((uint*)old)|=bits;else *field=old|bits;}
static inline float Zero(){float f;__asm__("mtc1 $zero,%0":"=f"(f));return f;}
static inline float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline void WriteX(float*destination,qword value){__asm__("sw %1,%0":"=m"(*destination):"r"(value));}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char INPUT_Size[sizeof(INPUT)==32?1:-1];
typedef char BASE_Size[sizeof(BASE)==68?1:-1];
typedef char COMPONENT_Size[sizeof(COMPONENT)==4?1:-1];
typedef char PROGRAM_ITEM_Size[sizeof(PROGRAM_ITEM)==164?1:-1];
typedef char CLIP_Size[sizeof(CLIP)==120?1:-1];
typedef char SUB_Size[sizeof(SUB)==164?1:-1];
typedef char SPARSE_Size[sizeof(SPARSE)==52?1:-1];
typedef char AUX_Size[sizeof(AUX)==368?1:-1];
typedef char LINK_FIELD_Size[sizeof(LINK_FIELD)==4?1:-1];
typedef char SOURCE_Size[sizeof(SOURCE)==448?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==8272?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==1304?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char WORK_Size[sizeof(WORK)==80?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char U_f_Offset[FIELD_OFFSET(U,f)==0?1:-1];
typedef char U_i_Offset[FIELD_OFFSET(U,i)==0?1:-1];
typedef char M3_row_Offset[FIELD_OFFSET(M3,row)==0?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char INPUT_amount_Offset[FIELD_OFFSET(INPUT,amount)==28?1:-1];
typedef char BASE_vt_Offset[FIELD_OFFSET(BASE,vt)==12?1:-1];
typedef char BASE_flags_Offset[FIELD_OFFSET(BASE,flags)==64?1:-1];
typedef char COMPONENT_object_Offset[FIELD_OFFSET(COMPONENT,object)==0?1:-1];
typedef char PROGRAM_ITEM_actor_Offset[FIELD_OFFSET(PROGRAM_ITEM,actor)==0?1:-1];
typedef char PROGRAM_ITEM_clip_Offset[FIELD_OFFSET(PROGRAM_ITEM,clip)==4?1:-1];
typedef char PROGRAM_ITEM_active_Offset[FIELD_OFFSET(PROGRAM_ITEM,active)==156?1:-1];
typedef char PROGRAM_ITEM_count_Offset[FIELD_OFFSET(PROGRAM_ITEM,count)==160?1:-1];
typedef char CLIP_duration_Offset[FIELD_OFFSET(CLIP,duration)==116?1:-1];
typedef char SUB_clip_Offset[FIELD_OFFSET(SUB,clip)==48?1:-1];
typedef char SUB_actor_Offset[FIELD_OFFSET(SUB,actor)==52?1:-1];
typedef char SUB_focus_Offset[FIELD_OFFSET(SUB,focus)==132?1:-1];
typedef char SPARSE_x_Offset[FIELD_OFFSET(SPARSE,x)==16?1:-1];
typedef char SPARSE_y_Offset[FIELD_OFFSET(SPARSE,y)==32?1:-1];
typedef char SPARSE_z_Offset[FIELD_OFFSET(SPARSE,z)==48?1:-1];
typedef char AUX_owner_Offset[FIELD_OFFSET(AUX,owner)==0?1:-1];
typedef char AUX_target_Offset[FIELD_OFFSET(AUX,target)==268?1:-1];
typedef char AUX_data_Offset[FIELD_OFFSET(AUX,data)==276?1:-1];
typedef char AUX_mode_Offset[FIELD_OFFSET(AUX,mode)==296?1:-1];
typedef char AUX_enabled_Offset[FIELD_OFFSET(AUX,enabled)==300?1:-1];
typedef char AUX_phase_Offset[FIELD_OFFSET(AUX,phase)==320?1:-1];
typedef char AUX_position_Offset[FIELD_OFFSET(AUX,position)==336?1:-1];
typedef char AUX_value_Offset[FIELD_OFFSET(AUX,value)==352?1:-1];
typedef char LINK_FIELD_mode_Offset[FIELD_OFFSET(LINK_FIELD,mode)==0?1:-1];
typedef char LINK_FIELD_owner_Offset[FIELD_OFFSET(LINK_FIELD,owner)==0?1:-1];
typedef char SOURCE_vt_Offset[FIELD_OFFSET(SOURCE,vt)==12?1:-1];
typedef char SOURCE_link_Offset[FIELD_OFFSET(SOURCE,link)==224?1:-1];
typedef char SOURCE_parameter_Offset[FIELD_OFFSET(SOURCE,parameter)==268?1:-1];
typedef char SOURCE_data_Offset[FIELD_OFFSET(SOURCE,data)==276?1:-1];
typedef char SOURCE_other_Offset[FIELD_OFFSET(SOURCE,other)==348?1:-1];
typedef char SOURCE_actor_Offset[FIELD_OFFSET(SOURCE,actor)==400?1:-1];
typedef char SOURCE_enabled_Offset[FIELD_OFFSET(SOURCE,enabled)==444?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_flags_Offset[FIELD_OFFSET(ACTOR,flags)==64?1:-1];
typedef char ACTOR_input_Offset[FIELD_OFFSET(ACTOR,input)==336?1:-1];
typedef char ACTOR_velocity_Offset[FIELD_OFFSET(ACTOR,velocity)==400?1:-1];
typedef char ACTOR_local_Offset[FIELD_OFFSET(ACTOR,local)==432?1:-1];
typedef char ACTOR_stamp_Offset[FIELD_OFFSET(ACTOR,stamp)==524?1:-1];
typedef char ACTOR_position_Offset[FIELD_OFFSET(ACTOR,position)==560?1:-1];
typedef char ACTOR_offset_Offset[FIELD_OFFSET(ACTOR,offset)==576?1:-1];
typedef char ACTOR_secondary_Offset[FIELD_OFFSET(ACTOR,secondary)==2304?1:-1];
typedef char ACTOR_tag9BC_Offset[FIELD_OFFSET(ACTOR,tag9BC)==2492?1:-1];
typedef char ACTOR_focus_Offset[FIELD_OFFSET(ACTOR,focus)==4132?1:-1];
typedef char ACTOR_animation_Offset[FIELD_OFFSET(ACTOR,animation)==4144?1:-1];
typedef char ACTOR_component_Offset[FIELD_OFFSET(ACTOR,component)==4148?1:-1];
typedef char ACTOR_tag1038_Offset[FIELD_OFFSET(ACTOR,tag1038)==4152?1:-1];
typedef char ACTOR_height_Offset[FIELD_OFFSET(ACTOR,height)==4168?1:-1];
typedef char ACTOR_motion_Offset[FIELD_OFFSET(ACTOR,motion)==4192?1:-1];
typedef char ACTOR_anchor_Offset[FIELD_OFFSET(ACTOR,anchor)==4288?1:-1];
typedef char ACTOR_field130C_Offset[FIELD_OFFSET(ACTOR,field130C)==4876?1:-1];
typedef char ACTOR_tag1318_Offset[FIELD_OFFSET(ACTOR,tag1318)==4888?1:-1];
typedef char ACTOR_field18D8_Offset[FIELD_OFFSET(ACTOR,field18D8)==6360?1:-1];
typedef char ACTOR_first_Offset[FIELD_OFFSET(ACTOR,first)==6560?1:-1];
typedef char ACTOR_second_Offset[FIELD_OFFSET(ACTOR,second)==6564?1:-1];
typedef char ACTOR_specialClip_Offset[FIELD_OFFSET(ACTOR,specialClip)==6896?1:-1];
typedef char ACTOR_flag1BCC_Offset[FIELD_OFFSET(ACTOR,flag1BCC)==7116?1:-1];
typedef char ACTOR_program_Offset[FIELD_OFFSET(ACTOR,program)==7216?1:-1];
typedef char ACTOR_effect_Offset[FIELD_OFFSET(ACTOR,effect)==8264?1:-1];
typedef char CONTEXT_actor_Offset[FIELD_OFFSET(CONTEXT,actor)==0?1:-1];
typedef char CONTEXT_stamp_Offset[FIELD_OFFSET(CONTEXT,stamp)==4?1:-1];
typedef char CONTEXT_action_Offset[FIELD_OFFSET(CONTEXT,action)==8?1:-1];
typedef char CONTEXT_step_Offset[FIELD_OFFSET(CONTEXT,step)==12?1:-1];
typedef char CONTEXT_time_Offset[FIELD_OFFSET(CONTEXT,time)==16?1:-1];
typedef char CONTEXT_focus_Offset[FIELD_OFFSET(CONTEXT,focus)==20?1:-1];
typedef char CONTEXT_setting_Offset[FIELD_OFFSET(CONTEXT,setting)==24?1:-1];
typedef char CONTEXT_parameter_Offset[FIELD_OFFSET(CONTEXT,parameter)==28?1:-1];
typedef char CONTEXT_value_Offset[FIELD_OFFSET(CONTEXT,value)==32?1:-1];
typedef char CONTEXT_reversed_Offset[FIELD_OFFSET(CONTEXT,reversed)==36?1:-1];
typedef char CONTEXT_index_Offset[FIELD_OFFSET(CONTEXT,index)==40?1:-1];
typedef char CONTEXT_previous_Offset[FIELD_OFFSET(CONTEXT,previous)==44?1:-1];
typedef char CONTEXT_changed_Offset[FIELD_OFFSET(CONTEXT,changed)==52?1:-1];
typedef char CONTEXT_aux_Offset[FIELD_OFFSET(CONTEXT,aux)==104?1:-1];
typedef char CONTEXT_clip170_Offset[FIELD_OFFSET(CONTEXT,clip170)==368?1:-1];
typedef char CONTEXT_clip174_Offset[FIELD_OFFSET(CONTEXT,clip174)==372?1:-1];
typedef char CONTEXT_clip178_Offset[FIELD_OFFSET(CONTEXT,clip178)==376?1:-1];
typedef char CONTEXT_clip17C_Offset[FIELD_OFFSET(CONTEXT,clip17C)==380?1:-1];
typedef char CONTEXT_program180_Offset[FIELD_OFFSET(CONTEXT,program180)==384?1:-1];
typedef char CONTEXT_script230_Offset[FIELD_OFFSET(CONTEXT,script230)==560?1:-1];
typedef char CONTEXT_clip234_Offset[FIELD_OFFSET(CONTEXT,clip234)==564?1:-1];
typedef char CONTEXT_clip238_Offset[FIELD_OFFSET(CONTEXT,clip238)==568?1:-1];
typedef char CONTEXT_program240_Offset[FIELD_OFFSET(CONTEXT,program240)==576?1:-1];
typedef char CONTEXT_overrideClip_Offset[FIELD_OFFSET(CONTEXT,overrideClip)==788?1:-1];
typedef char CONTEXT_gain318_Offset[FIELD_OFFSET(CONTEXT,gain318)==792?1:-1];
typedef char CONTEXT_gain31C_Offset[FIELD_OFFSET(CONTEXT,gain31C)==796?1:-1];
typedef char CONTEXT_clip320_Offset[FIELD_OFFSET(CONTEXT,clip320)==800?1:-1];
typedef char CONTEXT_clip324_Offset[FIELD_OFFSET(CONTEXT,clip324)==804?1:-1];
typedef char CONTEXT_clip328_Offset[FIELD_OFFSET(CONTEXT,clip328)==808?1:-1];
typedef char CONTEXT_script32C_Offset[FIELD_OFFSET(CONTEXT,script32C)==812?1:-1];
typedef char CONTEXT_clip430_Offset[FIELD_OFFSET(CONTEXT,clip430)==1072?1:-1];
typedef char CONTEXT_sub_Offset[FIELD_OFFSET(CONTEXT,sub)==1088?1:-1];
typedef char CONTEXT_clip4F0_Offset[FIELD_OFFSET(CONTEXT,clip4F0)==1264?1:-1];
typedef char CONTEXT_clip4F4_Offset[FIELD_OFFSET(CONTEXT,clip4F4)==1268?1:-1];
typedef char CONTEXT_clip4F8_Offset[FIELD_OFFSET(CONTEXT,clip4F8)==1272?1:-1];
typedef char CONTEXT_tag_Offset[FIELD_OFFSET(CONTEXT,tag)==1276?1:-1];
typedef char CONTEXT_inhibited_Offset[FIELD_OFFSET(CONTEXT,inhibited)==1280?1:-1];
typedef char CONTEXT_clip50C_Offset[FIELD_OFFSET(CONTEXT,clip50C)==1292?1:-1];
typedef char CONTEXT_clip510_Offset[FIELD_OFFSET(CONTEXT,clip510)==1296?1:-1];
typedef char CONTEXT_clip514_Offset[FIELD_OFFSET(CONTEXT,clip514)==1300?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char WORK_direction_Offset[FIELD_OFFSET(WORK,direction)==0?1:-1];
typedef char WORK_tangent_Offset[FIELD_OFFSET(WORK,tangent)==16?1:-1];
typedef char WORK_matrix_Offset[FIELD_OFFSET(WORK,matrix)==32?1:-1];
extern "C" void func_00192BD8(CONTEXT*p,int step){WORK w;if(step==p->step)return;
 switch(p->step){
 case 1:p->actor->tag1038=-1;break;
 case -1:
  if(p->focus&&func_00132B10(p->focus,10)){SOURCE*source=p->focus;qword position=func_001A62E8(p->actor);func_001E6F60(source,position,0,0,0,&p->parameter,&p->value);}
  switch(p->action){
  case 1:p->focus->actor=p->actor;func_00183B80(p->focus,2);if(p->actor==D_002E1E40)Notify(p->actor->first,9);break;
  case 4:{SOURCE*source=p->focus;SourceState(source,5);func_001333C0(source,p->actor);func_00204F78(p->actor,source,1);ACTOR*actor=p->actor;actor->position.q=func_001A62E8(source);break;}
  case 3:{SOURCE*source=p->focus;SourceState(source,5);func_001333C0(source,p->actor);func_00204F78(p->actor,source,1);p->index=-1;func_001E67B8(source,p->parameter,&p->actor->position,&w.tangent);// Native clears Z only; X, Y and W have no preceding initialization.
  w.direction.i[2]=0;Normalize(&w.direction);qword normal=Read(&w.direction);p->reversed=Dot(normal,func_001A6318(p->actor)->row[0].q)<D_002BF63C;break;}
  case 2:{EFFECT*effect=func_001FBB90(0x5C);func_001FB2F8(effect,0);func_00258040(&D_002E1E40->effect,effect);break;}
  case 11:if(p->focus)func_001333C0(p->focus,p->actor);break;
  case 12:if(p->focus)func_002046F0(p->actor,p->focus);func_00204CA8(p->actor);break;
  }
  p->previous=-1;p->actor->stamp=D_002DDED0.time;break;
 case 7:if(Less(step,11)&&!Less(step,9)){SOURCE*source=p->focus;if(source->other){qword position=func_001A62E8(source->other);SetVector(p->actor,29,Subtract(position,p->actor->offset.q));w.direction.q=Scalar(p->actor->height);p->actor->motion.q=AddScaled(position,D_002A2DC0.q,w.direction.q);func_002046B0(p->actor,func_001A6318(source->other)->row[0].q);SetLocal(p->actor);SetVector(p->actor,35,D_002A2DD0.q);SetVector(p->actor,36,D_002A2DD0.q);}func_0014E328(&D_002DDF40,10,(CAMERA*)((char*)&D_002DDF40+0x4C0),p->actor,p->actor->anchor);}break;
 case 9:case 10:if(!(Less(step,11)&&!Less(step,9)))func_0014E4C8(&D_002DDF40,2,10,(CAMERA*)((char*)&D_002DDF40+0x4C0),0,0);break;
 }
 CLIP*clip=0;PROGRAM*script=0;int flags=1,special=0;float blend=0.0f,speed=1.0f;
 switch(step){
 case -1:{p->inhibited=0;
  switch(p->action){
  case 1:func_00183B80(p->focus,0);if(p->actor==D_002E1E40)Notify(p->actor->first,8);break;
  case 3:case 4:{SOURCE*source=p->focus;SourceState(source,6);func_00133448(source,p->actor);func_00204F78(p->actor,source,0);break;}
  case 6:if(!p->actor->field18D8)func_0018E540(p->actor,-1);break;
  case 11:if(p->focus)func_00133448(p->focus,p->actor);p->actor->field130C=0;p->actor->tag9BC=-1;break;
  case 5:case 9:func_001CCAC0(&p->sub,-1);break;
  case 12:p->actor->tag1318=-1;func_001CD2C0(p->actor->secondary);if(p->actor==D_002E1E40)p->actor->flag1BCC=0;break;
  case 2:if(D_002E1E40->effect){func_001FB098(D_002E1E40->effect,0.0f);func_00258040(&D_002E1E40->effect,0);}break;
  }
  if(p->actor->focus){if(p->actor->focus==p->aux)func_00140C88(p->actor,0);else if(!p->setting){if(p->actor->focus==p->aux->owner)func_00140C88(p->actor,0);}}
  p->actor->tag1038=-1;float zero=Zero();p->parameter=zero;p->tag=-1;p->action=-1;p->step=-1;p->focus=0;p->setting=0;p->value=zero;p->changed=0;break;}
 case 0:case 5:
  switch(p->action){
  case 0:clip=p->clip174;flags=9;break;
  case 13:clip=step==0?p->clip510:p->clip174;flags=9;break;
  case 2:clip=p->clip514;flags=9;break;
  case 1:script=p->script230;flags=1;break;
  case 4:clip=p->clip234;flags=9;special=7;break;
  case 3:if(p->focus->enabled&&p->overrideClip){clip=p->overrideClip;float zero=Zero();p->gain318=zero;p->gain31C=zero;}else clip=p->clip238;flags=9;special=31;break;
  case 6:case 7:clip=p->clip320;flags=9;special=7;break;
  case 5:case 9:p->sub.focus=p->focus;func_001CCAC0(&p->sub,0);clip=p->sub.clip;blend=clip->duration*0.5f;speed=0.0f;break;
  case 10:clip=p->actor->input->amount>=D_002BF640?p->clip4F0:p->clip4F4;break;
  case 11:clip=p->clip4F8;if(p->tag==21&&D_002F7900->specialClip)clip=D_002F7900->specialClip;break;
  case 12:clip=p->clip50C;break;
  }
  p->actor->velocity.q=D_002A2DD0.q;break;
 case 1:if(p->action==0){clip=p->clip170;if(!p->actor->focus){
   if(func_00132B10(p->focus,12)){SOURCE*source=p->focus;if(source->actor)func_00140C88(p->actor,source->actor);else{func_00194118(p);p->aux->target=source;func_00140C88(p->actor,p->aux);}}
   else if(func_00132B10(p->focus,34)){SOURCE*source=p->focus;if(source->link.owner)func_00140C88(p->actor,source->link.owner);else{func_00194118(p);p->aux->enabled=1;AUX*aux=p->aux;qword position=func_001A62E8(source);aux->position.q=func_001A6F00(0,p->aux,position);p->aux->value=source->parameter;func_00140C88(p->actor,p->aux);}}
   else if(func_00132B10(p->focus,38)){SOURCE*source=p->focus;if(source->link.owner)func_00140C88(p->actor,source->link.owner);else{func_00194118(p);qword v=Rotate(func_001A6318(source),D_002BF650.q);WriteX(&p->aux->data->x,v);p->aux->data->y=Y(v);p->aux->data->z=Z(v);func_00140C88(p->actor,p->aux);}}
  }}else if(p->action==13)clip=p->clip170;flags=9;break;
 case 4:switch(p->action){case 1:clip=p->program180.clip;func_0020BD68(&p->program180);break;case 2:clip=p->actor->program.clip;func_0020BD68(&p->actor->program);break;case 3:clip=p->program240.clip;func_0020BD68(&p->program240);break;}flags=9;break;
 case 3:clip=p->clip17C;p->actor->velocity.q=D_002A2DD0.q;break;
 case 2:clip=p->clip178;p->actor->velocity.q=D_002A2DD0.q;break;
 case 7:{SOURCE*source=p->focus;clip=p->clip324;if(source->other){w.matrix=*func_001A6318(source->other);func_002046B0(p->actor,w.matrix.row[0].q);}p->actor->velocity.q=D_002A2DD0.q;SourceState(source,5);break;}
 case 8:clip=p->clip328;p->actor->velocity.q=D_002A2DD0.q;SourceState(p->focus,6);break;
 case 9:script=p->script32C;if(p->step==7){FlagOr(&p->actor->flags,16);if(p->actor==D_002E1E40){FlagOr(&p->actor->first->flags,16);FlagOr(&D_002E1E40->second->flags,16);}}p->actor->velocity.q=D_002A2DD0.q;break;
 case 10:clip=p->clip430;p->actor->tag1038=-1;p->actor->velocity.q=D_002A2DD0.q;flags=9;break;
 }
 p->step=step;p->time=D_002DDED0.time;
 if(step!=-1){func_00130658(&p->actor->animation);func_001F15B8(&p->actor->component);func_001305B8(clip,p->actor,blend,speed,flags,&p->actor->animation);func_001F1448(script,p->actor,-1,flags,&p->actor->component);Notify((BASE*)p->actor,90);if(func_00132B10(p->actor,53))func_0018C120(p->actor,special);}
}