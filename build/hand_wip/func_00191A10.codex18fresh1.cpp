
typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;
union U{qword q;float f[4];int i[4];};struct M3{U row[3];};struct VTE{short delta,pad;void*fn;};struct ACTOR;struct SOURCE;struct AUX;struct SETTING;struct SPACE;struct COMPONENT;struct OBJECT;
struct INPUT{char pad0[0x10];float x,y,heading,amount;};
struct CLIP{char pad0[0x74];float duration;};struct ANIMATION{char pad0[0x14];CLIP*clip;char pad18[4];float phase;char pad20[0x20];float rate;};
struct ENTRY{float weight;int active;char pad8[8];U direction;};
struct PROGRAM{ACTOR*actor;CLIP*clip;char pad8[0x18];float limit20;char pad24[0x3C];float limit60;char pad64[0x38];int active,count;};
struct SUB{char bytes[0xB0];};struct CACHE{void*table;int active;float radius;int padC;U desired,center,hit0,hit1,end;};
struct SOURCE{char pad0[0xE4];int cyclic;char padE8[0xA4];int enabled18C;char pad190[0x2C];uint flags;char pad1C0[8];SOURCE*other;};
struct AUX{ACTOR*owner;};
struct ACTOR{char pad0[0xC];VTE*vt;char pad10[0x140];INPUT*input;char pad154[0x3C];U velocity;char pad1A0[8];float heading;char pad1AC[4];M3 local;char pad1E0[0x38];U*attachedPosition;char pad21C[0xE08];void*focus;char pad1028[8];ANIMATION*animation;void*component;int side,pad103C,role;char pad1044[0x4DC];CACHE firstCache;char pad1580[0xA0];CACHE secondCache;char pad1680[0x354];COMPONENT*firstA,*secondA,*firstB,*secondB;char pad19E4[12];OBJECT*firstObject,*secondObject;char pad19F8[0x238];PROGRAM program;};
struct CONTEXT{ACTOR*actor;float stamp;int action,step;float time;SOURCE*focus;SETTING*setting;float parameter,value;int reversed,index,previous;char pad30[0x20];float maximum;char pad54[0x14];AUX*aux;char pad6C[4];ENTRY axes70[8];CLIP*clip170,*clip174,*clip178,*clip17C;PROGRAM program180;char pad224[12];void*script230;CLIP*clip234,*clip238;char pad23C[4];PROGRAM program240;char pad2E4[0x4C];ENTRY axes330[8];CLIP*clip430;char pad434[12];SUB sub;};
struct CLOCK{float time,dt;};struct SMP{float maximum,minimum,duration;};struct HEIGHT{float minimum,maximum;};struct TRACK{VTE*vt;};struct BINDING{int key;TRACK*track;};
union PHASE{U vector;SMP smp;};struct WORK{U position,initialVelocity,temp;PHASE phase;U velocity,direction;PHASE second;U scalar;float heading,minimum,maximum,limit;};
extern "C"{extern CLOCK D_002DDED0;extern ACTOR*D_002E1E40;extern U D_002A2DA0;extern float D_002BF5BC,D_002BF5C0,D_002BF5C4,D_002BF5C8,D_002BF5CC;extern HEIGHT D_002BF630;extern U D_002BF5D0[3],D_002BF600[3];
qword func_001A62E8(ACTOR*);void func_00182CD8(SETTING*,ACTOR*,float*,U*,float*);int func_00132B10(void*,int);qword func_0011F088(qword,qword,float,SMP*,U*);qword func_0011E1A0(float,float,float);float func_001E6620(SOURCE*),func_001E6648(SOURCE*),func_001E6610(SOURCE*),func_001E6630(SOURCE*);float func_0011D018(float,float,float,SMP*,float*);void func_001940B0(CONTEXT*,int);void func_00204660(ACTOR*,float);float func_00204740(ACTOR*);float func_0011CF60(float);void func_00192BD8(CONTEXT*,int);void func_0020BB58(PROGRAM*,float);void func_0020BC08(PROGRAM*);void func_001441E8(ACTOR*,float);void func_001E6ED8(SOURCE*,qword,SPACE*,U*,U*,float*,float*,float);void func_00195A00(void*,int,int,void*);float func_002458F0(float,float);void func_001E6F60(SOURCE*,qword,SPACE*,U*,U*,float*,float*);void func_001CC2E8(SUB*);void func_001A0450(ACTOR*,ENTRY*,CLIP*);void func_00205910(ACTOR*,HEIGHT*,int,U*);BINDING*func_0012FF10(CLIP*,ACTOR*,void*,int);void func_002046F0(ACTOR*,SOURCE*);void func_00204CA8(ACTOR*);void func_00189C40(ACTOR*,COMPONENT*,float,COMPONENT*,OBJECT*,CACHE*);void func_00193C98(ACTOR*,CACHE*,OBJECT*);}
static inline qword Read(U*p){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(*p));return q;}
static inline qword RawCopyValue(U*p){qword q;__asm__("lq %0,%1":"=r"(q):"m"(*p));return q;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Add(qword a,qword b){qword q;__asm__("vadd.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Scale(qword v,qword k){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(v),"j"(k));return q;}
static inline qword ZeroVector(){qword q;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(q));return q;}
static inline qword Square(qword a){qword d,k;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(k):"j"(a));return d;}
static inline qword Root(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float X(qword a){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline float Length(qword a){return X(Root(Square(a)));}
static inline qword SquareXY(qword a){qword q;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(q):"j"(a));return q;}
static inline float LengthXY(qword a){return X(Root(SquareXY(a)));}
static inline qword DotQ(qword a,qword b){qword d,k;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(k):"j"(a),"j"(b));return d;}
static inline float Dot(qword a,qword b){return X(DotQ(a,b));}
static inline void Normalize(U*object){qword v=Read(object),length=Root(Square(v));qword fallback=D_002A2DA0.q;if(X(length)<0.0001f)object->q=fallback;else{qword q;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(q):"j"(v),"j"(length));object->q=q;}}
static inline qword Transpose(M3*m,qword v){qword result=m->row[0].q,p0,p1,p2,k;__asm__("vmul.xyzw %1,%0,%5\n\tvmaxw.xyzw %4,$vf0,$vf0w\n\tvmul.xyzw %2,%6,%5\n\tvmul.xyzw %3,%7,%5\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %0,%4,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %0,%4,%2z\n\tvaddax.z $ACC,%3,%3x\n\tvmaddy.z %0,%4,%3y":"+j"(result),"=&j"(p0),"=&j"(p1),"=&j"(p2),"=&j"(k):"j"(v),"j"(m->row[1].q),"j"(m->row[2].q));return result;}
static inline float Min(float a,float b){float f;__asm__("min.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
static inline float Max(float a,float b){float f;__asm__("max.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
static inline float Sqrt(float f){float q;__asm__("sqrt.s %0,%1":"=f"(q):"f"(f));return q;}
static inline float Clamp(float f,float low,float high){if(f<low)f=low;else if(high<f)f=high;return f;}
static inline bool Less(int value,int limit){return value<limit;}
static inline qword Velocity(ACTOR*p){VTE&v=p->vt[33];return ((qword(*)(void*))v.fn)((char*)p+v.delta);}
static inline void Sample(BINDING*b,ANIMATION*a,U*out){TRACK*t=b->track;VTE&v=t->vt[3];((void(*)(void*,int,U*,float,float))v.fn)((char*)t+v.delta,0,out,a->phase,a->rate);}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char INPUT_Size[sizeof(INPUT)==32?1:-1];
typedef char CLIP_Size[sizeof(CLIP)==120?1:-1];
typedef char ANIMATION_Size[sizeof(ANIMATION)==68?1:-1];
typedef char ENTRY_Size[sizeof(ENTRY)==32?1:-1];
typedef char PROGRAM_Size[sizeof(PROGRAM)==164?1:-1];
typedef char SUB_Size[sizeof(SUB)==176?1:-1];
typedef char CACHE_Size[sizeof(CACHE)==96?1:-1];
typedef char SOURCE_Size[sizeof(SOURCE)==460?1:-1];
typedef char AUX_Size[sizeof(AUX)==4?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==7392?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==1264?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char SMP_Size[sizeof(SMP)==12?1:-1];
typedef char HEIGHT_Size[sizeof(HEIGHT)==8?1:-1];
typedef char TRACK_Size[sizeof(TRACK)==4?1:-1];
typedef char BINDING_Size[sizeof(BINDING)==8?1:-1];
typedef char PHASE_Size[sizeof(PHASE)==16?1:-1];
typedef char WORK_Size[sizeof(WORK)==144?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char U_f_Offset[FIELD_OFFSET(U,f)==0?1:-1];
typedef char U_i_Offset[FIELD_OFFSET(U,i)==0?1:-1];
typedef char M3_row_Offset[FIELD_OFFSET(M3,row)==0?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char INPUT_x_Offset[FIELD_OFFSET(INPUT,x)==16?1:-1];
typedef char INPUT_y_Offset[FIELD_OFFSET(INPUT,y)==20?1:-1];
typedef char INPUT_heading_Offset[FIELD_OFFSET(INPUT,heading)==24?1:-1];
typedef char INPUT_amount_Offset[FIELD_OFFSET(INPUT,amount)==28?1:-1];
typedef char CLIP_duration_Offset[FIELD_OFFSET(CLIP,duration)==116?1:-1];
typedef char ANIMATION_clip_Offset[FIELD_OFFSET(ANIMATION,clip)==20?1:-1];
typedef char ANIMATION_phase_Offset[FIELD_OFFSET(ANIMATION,phase)==28?1:-1];
typedef char ANIMATION_rate_Offset[FIELD_OFFSET(ANIMATION,rate)==64?1:-1];
typedef char ENTRY_weight_Offset[FIELD_OFFSET(ENTRY,weight)==0?1:-1];
typedef char ENTRY_active_Offset[FIELD_OFFSET(ENTRY,active)==4?1:-1];
typedef char ENTRY_direction_Offset[FIELD_OFFSET(ENTRY,direction)==16?1:-1];
typedef char PROGRAM_actor_Offset[FIELD_OFFSET(PROGRAM,actor)==0?1:-1];
typedef char PROGRAM_clip_Offset[FIELD_OFFSET(PROGRAM,clip)==4?1:-1];
typedef char PROGRAM_limit20_Offset[FIELD_OFFSET(PROGRAM,limit20)==32?1:-1];
typedef char PROGRAM_limit60_Offset[FIELD_OFFSET(PROGRAM,limit60)==96?1:-1];
typedef char PROGRAM_active_Offset[FIELD_OFFSET(PROGRAM,active)==156?1:-1];
typedef char PROGRAM_count_Offset[FIELD_OFFSET(PROGRAM,count)==160?1:-1];
typedef char CACHE_table_Offset[FIELD_OFFSET(CACHE,table)==0?1:-1];
typedef char CACHE_active_Offset[FIELD_OFFSET(CACHE,active)==4?1:-1];
typedef char CACHE_radius_Offset[FIELD_OFFSET(CACHE,radius)==8?1:-1];
typedef char CACHE_desired_Offset[FIELD_OFFSET(CACHE,desired)==16?1:-1];
typedef char CACHE_center_Offset[FIELD_OFFSET(CACHE,center)==32?1:-1];
typedef char CACHE_hit0_Offset[FIELD_OFFSET(CACHE,hit0)==48?1:-1];
typedef char CACHE_hit1_Offset[FIELD_OFFSET(CACHE,hit1)==64?1:-1];
typedef char CACHE_end_Offset[FIELD_OFFSET(CACHE,end)==80?1:-1];
typedef char SOURCE_cyclic_Offset[FIELD_OFFSET(SOURCE,cyclic)==228?1:-1];
typedef char SOURCE_enabled18C_Offset[FIELD_OFFSET(SOURCE,enabled18C)==396?1:-1];
typedef char SOURCE_flags_Offset[FIELD_OFFSET(SOURCE,flags)==444?1:-1];
typedef char SOURCE_other_Offset[FIELD_OFFSET(SOURCE,other)==456?1:-1];
typedef char AUX_owner_Offset[FIELD_OFFSET(AUX,owner)==0?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_input_Offset[FIELD_OFFSET(ACTOR,input)==336?1:-1];
typedef char ACTOR_velocity_Offset[FIELD_OFFSET(ACTOR,velocity)==400?1:-1];
typedef char ACTOR_heading_Offset[FIELD_OFFSET(ACTOR,heading)==424?1:-1];
typedef char ACTOR_local_Offset[FIELD_OFFSET(ACTOR,local)==432?1:-1];
typedef char ACTOR_attachedPosition_Offset[FIELD_OFFSET(ACTOR,attachedPosition)==536?1:-1];
typedef char ACTOR_focus_Offset[FIELD_OFFSET(ACTOR,focus)==4132?1:-1];
typedef char ACTOR_animation_Offset[FIELD_OFFSET(ACTOR,animation)==4144?1:-1];
typedef char ACTOR_component_Offset[FIELD_OFFSET(ACTOR,component)==4148?1:-1];
typedef char ACTOR_side_Offset[FIELD_OFFSET(ACTOR,side)==4152?1:-1];
typedef char ACTOR_role_Offset[FIELD_OFFSET(ACTOR,role)==4160?1:-1];
typedef char ACTOR_firstCache_Offset[FIELD_OFFSET(ACTOR,firstCache)==5408?1:-1];
typedef char ACTOR_secondCache_Offset[FIELD_OFFSET(ACTOR,secondCache)==5664?1:-1];
typedef char ACTOR_firstA_Offset[FIELD_OFFSET(ACTOR,firstA)==6612?1:-1];
typedef char ACTOR_secondA_Offset[FIELD_OFFSET(ACTOR,secondA)==6616?1:-1];
typedef char ACTOR_firstB_Offset[FIELD_OFFSET(ACTOR,firstB)==6620?1:-1];
typedef char ACTOR_secondB_Offset[FIELD_OFFSET(ACTOR,secondB)==6624?1:-1];
typedef char ACTOR_firstObject_Offset[FIELD_OFFSET(ACTOR,firstObject)==6640?1:-1];
typedef char ACTOR_secondObject_Offset[FIELD_OFFSET(ACTOR,secondObject)==6644?1:-1];
typedef char ACTOR_program_Offset[FIELD_OFFSET(ACTOR,program)==7216?1:-1];
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
typedef char CONTEXT_maximum_Offset[FIELD_OFFSET(CONTEXT,maximum)==80?1:-1];
typedef char CONTEXT_aux_Offset[FIELD_OFFSET(CONTEXT,aux)==104?1:-1];
typedef char CONTEXT_axes70_Offset[FIELD_OFFSET(CONTEXT,axes70)==112?1:-1];
typedef char CONTEXT_clip170_Offset[FIELD_OFFSET(CONTEXT,clip170)==368?1:-1];
typedef char CONTEXT_clip174_Offset[FIELD_OFFSET(CONTEXT,clip174)==372?1:-1];
typedef char CONTEXT_clip178_Offset[FIELD_OFFSET(CONTEXT,clip178)==376?1:-1];
typedef char CONTEXT_clip17C_Offset[FIELD_OFFSET(CONTEXT,clip17C)==380?1:-1];
typedef char CONTEXT_program180_Offset[FIELD_OFFSET(CONTEXT,program180)==384?1:-1];
typedef char CONTEXT_script230_Offset[FIELD_OFFSET(CONTEXT,script230)==560?1:-1];
typedef char CONTEXT_clip234_Offset[FIELD_OFFSET(CONTEXT,clip234)==564?1:-1];
typedef char CONTEXT_clip238_Offset[FIELD_OFFSET(CONTEXT,clip238)==568?1:-1];
typedef char CONTEXT_program240_Offset[FIELD_OFFSET(CONTEXT,program240)==576?1:-1];
typedef char CONTEXT_axes330_Offset[FIELD_OFFSET(CONTEXT,axes330)==816?1:-1];
typedef char CONTEXT_clip430_Offset[FIELD_OFFSET(CONTEXT,clip430)==1072?1:-1];
typedef char CONTEXT_sub_Offset[FIELD_OFFSET(CONTEXT,sub)==1088?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char SMP_maximum_Offset[FIELD_OFFSET(SMP,maximum)==0?1:-1];
typedef char SMP_minimum_Offset[FIELD_OFFSET(SMP,minimum)==4?1:-1];
typedef char SMP_duration_Offset[FIELD_OFFSET(SMP,duration)==8?1:-1];
typedef char HEIGHT_minimum_Offset[FIELD_OFFSET(HEIGHT,minimum)==0?1:-1];
typedef char HEIGHT_maximum_Offset[FIELD_OFFSET(HEIGHT,maximum)==4?1:-1];
typedef char TRACK_vt_Offset[FIELD_OFFSET(TRACK,vt)==0?1:-1];
typedef char BINDING_key_Offset[FIELD_OFFSET(BINDING,key)==0?1:-1];
typedef char BINDING_track_Offset[FIELD_OFFSET(BINDING,track)==4?1:-1];
typedef char PHASE_vector_Offset[FIELD_OFFSET(PHASE,vector)==0?1:-1];
typedef char PHASE_smp_Offset[FIELD_OFFSET(PHASE,smp)==0?1:-1];
typedef char WORK_position_Offset[FIELD_OFFSET(WORK,position)==0?1:-1];
typedef char WORK_initialVelocity_Offset[FIELD_OFFSET(WORK,initialVelocity)==16?1:-1];
typedef char WORK_temp_Offset[FIELD_OFFSET(WORK,temp)==32?1:-1];
typedef char WORK_phase_Offset[FIELD_OFFSET(WORK,phase)==48?1:-1];
typedef char WORK_velocity_Offset[FIELD_OFFSET(WORK,velocity)==64?1:-1];
typedef char WORK_direction_Offset[FIELD_OFFSET(WORK,direction)==80?1:-1];
typedef char WORK_second_Offset[FIELD_OFFSET(WORK,second)==96?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==112?1:-1];
typedef char WORK_heading_Offset[FIELD_OFFSET(WORK,heading)==128?1:-1];
typedef char WORK_minimum_Offset[FIELD_OFFSET(WORK,minimum)==132?1:-1];
typedef char WORK_maximum_Offset[FIELD_OFFSET(WORK,maximum)==136?1:-1];
typedef char WORK_limit_Offset[FIELD_OFFSET(WORK,limit)==140?1:-1];
// Native stores the initial VT33 result at SP+10 without a later read.
extern "C" void func_00191A10(CONTEXT*p){WORK w;w.position.q=func_001A62E8(p->actor);w.initialVelocity.q=Velocity(p->actor);INPUT*input=p->actor->input;
 switch(p->action){
 case 0:case 13:{
  func_00182CD8(p->setting,p->actor,&p->value,&w.temp,&w.heading);
  float maximum;if(p->actor->role==1)maximum=Length(p->axes70[2].direction.q)*p->actor->animation->rate;else maximum=Length(p->axes70[4].direction.q)*p->actor->animation->rate;
  w.temp.f[2]=w.position.f[2];w.phase.smp.maximum=maximum;w.phase.smp.minimum=0;w.phase.smp.duration=0.3f;
  (void)func_0011F088(w.position.q,w.temp.q,D_002DDED0.dt,&w.phase.smp,&w.velocity);
  float lateral;qword world;
  if(func_00132B10(p->focus,38)){world=ZeroVector();lateral=0;}
  else{
   float angle=p->actor->role==1?w.heading-1.5707963267948966f:w.heading+1.5707963267948966f;
   w.direction.q=func_0011E1A0(angle,1.0f,0.0f);
   qword direction=func_0011E1A0(input->heading,1.0f,0.0f);w.second.vector.q=direction;
   float demand=Clamp(D_002BF5BC*Dot(w.direction.q,direction),-1.0f,1.0f)*input->amount;
   if(__builtin_fabsf(demand)<0.2f)demand=0;
   lateral=Min(Sqrt(maximum*maximum-X(Square(w.velocity.q))),demand*maximum);
   float side=lateral;
   if(func_00132B10(p->focus,12)){SOURCE*source=p->focus;if(!source->cyclic){
    (void)func_0011D018(p->value,func_001E6620(source)+30.0f,D_002DDED0.dt,&w.phase.smp,&w.minimum);
    (void)func_0011D018(p->value,func_001E6648(source)-30.0f,D_002DDED0.dt,&w.phase.smp,&w.maximum);
    side=Clamp(lateral,w.minimum,w.maximum);
   }}
   w.scalar.q=Scalar(side);world=Scale(w.direction.q,w.scalar.q);
  }
  world=Add(w.velocity.q,world);ACTOR*actor=p->actor;w.direction.q=Scalar(-1.0f);actor->velocity.q=Scale(Transpose(&actor->local,world),w.direction.q);
  int step;
  if(25.0f<Length(p->actor->velocity.q)){
   step=1;if(p->action==0){if(45.0f<Length(w.velocity.q))func_001940B0(p,0);else if(20.0f<p->actor->velocity.f[1])func_001940B0(p,p->actor->role==1?1:2);else if(p->actor->velocity.f[1]<-20.0f)func_001940B0(p,p->actor->role==1?2:1);}
  }else{
   step=0;if(func_00132B10(p->focus,12)){SOURCE*source=p->focus;
    if(lateral<-25.0f&&(source->flags&1)){step=2;if(p->action==0&&p->actor->role==0)step=3;}
    else if(25.0f<lateral&&(source->flags&2)){step=3;if(p->action==0&&p->actor->role==0)step=2;}
   }if(p->action==0)func_001940B0(p,3);
  }
  func_00204660(p->actor,w.heading);
  if(p->step==5){float difference=func_0011CF60(func_00204740(p->actor)-w.heading);if(0.25f<__builtin_fabsf(difference))step=5;}
  func_00192BD8(p,step);break;
 }
 case 1:
  if(p->focus->enabled18C&&0.0f<input->amount&&p->program180.clip){func_00192BD8(p,4);func_0020BB58(&p->program180,input->amount);func_00204660(p->actor,p->actor->input->heading);func_0020BC08(&p->program180);}else func_00192BD8(p,0);break;
 case 2:
  func_001441E8(p->actor,D_002BF5C0);
  if((p->step==0?0.1f:0.0f)<input->amount){func_00192BD8(p,4);func_0020BB58(&p->actor->program,input->amount*D_002BF5C4);func_00204660(p->actor,input->heading);}else func_00192BD8(p,0);break;
 case 4:func_00204660(p->actor,input->heading);break;
 case 3:{SOURCE*source=p->focus;
  func_001E6ED8(source,p->actor->attachedPosition->q,0,&w.temp,&w.phase.vector,&p->parameter,&p->value,p->parameter);
  if(source->flags&&!source->cyclic){float edge=func_001E6610(source)+0.01f;if(p->parameter<edge){func_00195A00((char*)p->actor+0x2C0,0,0,0);break;}edge=func_001E6630(source)-0.01f;if(edge<p->parameter){func_00195A00((char*)p->actor+0x2C0,0,0,0);break;}}
  w.phase.vector.i[2]=0;Normalize(&w.phase.vector);float heading=func_002458F0(w.phase.vector.f[1],w.phase.vector.f[0]);
  w.direction.q=func_0011E1A0(input->heading,1.0f,0.0f);
  if(source->other)func_001E6F60(source->other,p->actor->attachedPosition->q,0,0,&w.velocity,0,0);else w.velocity=w.phase.vector;
  w.velocity.i[2]=0;Normalize(&w.velocity);register float amount asm("$f20")=Dot(w.direction.q,w.velocity.q);
  switch(p->index){
  case 0:if(input->amount<0.25f)p->index=-1;else if(amount<-0.7f)p->index=1;break;
  case 1:if(input->amount<0.25f)p->index=-1;else if(0.7f<amount)p->index=0;break;
  case -1:if(0.35f<input->amount)p->index=amount>=0.0f?0:1;break;
  }
  if(p->index==0)p->reversed=0;else if(p->index==1)p->reversed=1;
  if(!source->flags){
   w.second.smp.maximum=p->program240.limit60;w.second.smp.minimum=p->program240.limit20;w.second.smp.duration=D_002BF5C8;
   if(source->cyclic)w.limit=w.second.smp.maximum;
   else if(p->reversed){(void)func_0011D018(p->value,50.0f,D_002DDED0.dt,&w.second.smp,&w.limit);w.limit=-w.limit;}
   else (void)func_0011D018(p->value,func_001E6648(source)-50.0f,D_002DDED0.dt,&w.second.smp,&w.limit);
   float ratio=(w.limit-w.second.smp.minimum)/(w.second.smp.maximum-w.second.smp.minimum);
   float requested=input->amount;
   if(requested<0.0f)amount=0.0f;
   else{amount=requested;if(ratio<requested){__asm__("mov.s %0,%1":"=f"(amount):"f"(ratio));}}
  }
  if(p->reversed)heading=func_0011CF60(heading+3.14159265358979323846f);
  if(0.0f<amount){func_00192BD8(p,4);func_0020BB58(&p->program240,amount);func_00204660(p->actor,heading);func_0020BC08(&p->program240);}else{func_00192BD8(p,0);func_00204660(p->actor,heading);}break;
 }
 case 5:case 9:func_001CC2E8(&p->sub);break;
 case 8:
  if(Less(p->step,9)&&!Less(p->step,7))break;
  if(0.0f<input->amount){
   func_00192BD8(p,10);ENTRY*entry=&p->axes330[3];if(!entry->active)entry=&p->axes330[2];
   qword sx=SquareXY(entry->direction.q),sy=SquareXY(p->axes330[1].direction.q);
   float x=-input->y*X(Root(sx)),y=input->x*X(Root(sy));U*velocity=&p->actor->velocity;velocity->f[0]=x;velocity->f[2]=0.0f;velocity->f[1]=y;
   func_001A0450(p->actor,p->axes330,p->clip430);
   ACTOR*actor=p->actor;float turn=-actor->velocity.f[1]/D_002BF5CC;actor->velocity.q=Scale(D_002A2DA0.q,DotQ(actor->velocity.q,D_002A2DA0.q));
   func_00204660(p->actor,p->actor->heading+turn*D_002DDED0.dt);
  }else func_00192BD8(p,9);
  func_00205910(p->actor,&D_002BF630,3,p->actor==D_002E1E40?D_002BF5D0:D_002BF600);break;
 case 10:{
  // This path initializes XYZ only; W is uninitialized when no track writes it.
  w.temp.i[2]=w.temp.i[1]=w.temp.i[0]=0;ANIMATION*a=p->actor->animation;
  if(a){BINDING*b=func_0012FF10(a->clip,p->actor,(void*)1,1);if(b){Sample(b,a,&w.temp);w.phase.vector.q=Scalar(-1.0f);w.temp.q=Scale(Read(&w.temp),w.phase.vector.q);}}
  p->actor->velocity.q=RawCopyValue(&w.temp);break;
 }
 case 11:if(p->focus){func_002046F0(p->actor,p->focus);func_00204CA8(p->actor);}break;
 }
 int step=p->step;
 if(step==0)goto stationary;if(step!=1)return;{func_001A0450(p->actor,p->axes70,p->clip170);if(p->actor->focus==p->aux&&Less(p->previous,3)&&0<p->previous){float weight=p->previous==step?p->axes70[1].weight:p->axes70[0].weight;p->maximum=Max(p->maximum,weight);}}
 return;
 stationary:if(p->action==3){ACTOR*actor=p->actor;func_00189C40(actor,actor->secondA,5.0f,actor->secondB,actor->firstObject,&actor->firstCache);func_00189C40(actor,actor->firstA,5.0f,actor->firstB,actor->secondObject,&actor->secondCache);func_00193C98(actor,&actor->firstCache,actor->firstObject);func_00193C98(actor,&actor->secondCache,actor->secondObject);}
}
