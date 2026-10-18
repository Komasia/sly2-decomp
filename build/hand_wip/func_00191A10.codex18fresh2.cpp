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
static inline qword RawCopyValue(U*p){qword q;__asm__("lq %0,%1":"=r"(q):"m"(*p));return q;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword v,qword k){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(v),"j"(k));return q;}
static inline qword ZeroVector(){qword q;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(q));return q;}
static inline qword Square(qword a){qword d,k;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(k):"j"(a));return d;}
static inline qword Root(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float X(qword a){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline float Length(qword a){return X(Root(Square(a)));}
static inline qword DotQ(qword a,qword b){qword d,k;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(k):"j"(a),"j"(b));return d;}
static inline float Min(float a,float b){float f;__asm__("min.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
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
extern "C" void func_00191A10(CONTEXT*context){WORK w;w.position.q=func_001A62E8(context->actor);w.initialVelocity.q=Velocity(context->actor);register INPUT*input __asm__("$18")=context->actor->input;
 switch(context->action){
 case 0:case 13:{
  func_00182CD8(context->setting,context->actor,&context->value,&w.temp,&w.heading);
  register float maximum __asm__("$f22");
  register ACTOR*speedActor __asm__("$4")=context->actor;
  if(speedActor->role==1){
   register ANIMATION*animation __asm__("$2");
   __asm__("lw %0,%1":"=r"(animation):"m"(speedActor->animation));
   register int bits __asm__("$2");register float rate __asm__("$f1");
   __asm__("lqc2 $vf1,%2\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tlwc1 %0,%3\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tqmfc2.ni %1,$vf1"
    :"=f"(rate),"=r"(bits):"m"(context->axes70[2].direction.q),"m"(animation->rate):"vf1","vf2");
   register float length __asm__("$f0");
   __asm__("mtc1 %1,%0":"=f"(length):"r"(bits));
   maximum=length*rate;
  }else{
   register ANIMATION*animation __asm__("$2");__asm__("lw %0,0x1030(%1)":"=r"(animation):"r"(speedActor),"X"(speedActor->animation));
   register int bits __asm__("$3");register float rate __asm__("$f1");
   __asm__("lqc2 $vf1,%2\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tlwc1 %0,%3\n\tqmfc2.ni %1,$vf1"
    :"=f"(rate),"=r"(bits):"m"(context->axes70[4].direction.q),"m"(animation->rate):"vf1","vf2");
   __asm__("mtc1 %1,$f0\n\tmul.s %0,$f0,%2":"=f"(maximum):"r"(bits),"f"(rate):"$f0");
  }
  w.temp.f[2]=w.position.f[2];w.phase.smp.maximum=maximum;w.phase.smp.minimum=0;w.phase.smp.duration=0.3f;
  register SMP*profile __asm__("$19")=&w.phase.smp;
  (void)func_0011F088(w.position.q,w.temp.q,D_002DDED0.dt,profile,&w.velocity);
  register float lateral __asm__("$f21");register qword world __asm__("vf1");
  if(func_00132B10(context->focus,38)){world=ZeroVector();lateral=0;}
  else{
   float angle=context->actor->role==1?w.heading-1.5707963267948966f:w.heading+1.5707963267948966f;
   register float one __asm__("$f21")=1.0f,zero __asm__("$f20")=0.0f;
   w.direction.q=func_0011E1A0(angle,one,zero);
   qword directionReturn=func_0011E1A0(input->heading,one,zero);
   register qword direction __asm__("vf2");register float lower __asm__("$f2");register float*gainHigh __asm__("$2");
   __asm__("qmtc2.ni %3,%0\n\t.set noat\n\tlui $1,0xbf80\n\tmtc1 $1,%1\n\t.set at\n\tlui %2,%%hi(%4)":"=j"(direction),"=f"(lower),"=r"(gainHigh):"r"(directionReturn),"i"(&D_002BF5BC):"$1");
   register qword dotCarrier __asm__("vf1");register float projected __asm__("$f1"),dot __asm__("$f0");
   __asm__("lqc2 %0,%3\n\tvmul.xyz %0,%0,%2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf3,%0z\n\tlwc1 %1,%%lo(%5)(%4)":"=&j"(dotCarrier),"=f"(projected):"j"(direction),"m"(w.direction.q),"r"(gainHigh),"i"(&D_002BF5BC),"X"(*(float*)((char*)gainHigh-0xa44)):"vf3");
   __asm__("qmfc2.ni $2,%1\n\tmtc1 $2,%0":"=f"(dot):"j"(dotCarrier):"$2");
   __asm__("mul.s %0,%0,%1":"+f"(projected):"f"(dot));
   register float demand __asm__("$f3");
   if(projected<lower)demand=lower;else{demand=projected;if(one<projected)demand=one;}
   w.second.vector.q=direction;
   register float magnitude __asm__("$f1"),deadzone __asm__("$f2");
   __asm__("lwc1 $f0,%3\n\t.set noat\n\tlui $1,0x3e4c\n\tori $1,$1,0xcccd\n\tmtc1 $1,%2\n\t.set at\n\tmul.s %0,%0,$f0\n\tabs.s %1,%0":"+f"(demand),"=f"(magnitude),"=f"(deadzone):"m"(input->amount):"$1","$f0");
   if(magnitude<deadzone)demand=0.0f;
   register qword squared __asm__("vf1")=w.velocity.q;
   register float remaining __asm__("$f2")=maximum*maximum;
   __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf2,%0z":"+j"(squared): :"vf2");
   __asm__("mul.s %0,%1,%2":"=f"(lateral):"f"(demand),"f"(maximum));
   register float baseSquared __asm__("$f0");
   __asm__("qmfc2.ni $3,%1\n\tmtc1 $3,%0":"=f"(baseSquared):"j"(squared):"$3");
   __asm__("sub.s %0,%0,%1":"+f"(remaining):"f"(baseSquared));
   register float capacity __asm__("$f1");__asm__("sqrt.s %0,%1":"=f"(capacity):"f"(remaining));
   lateral=Min(capacity,lateral);
   register float side __asm__("$f0");
   if(func_00132B10(context->focus,12)){SOURCE*source=context->focus;if(!source->cyclic){
    (void)func_0011D018(context->value,func_001E6620(source)+30.0f,D_002DDED0.dt,profile,&w.minimum);
    (void)func_0011D018(context->value,func_001E6648(source)-30.0f,D_002DDED0.dt,profile,&w.maximum);
    side=w.minimum;register float upper __asm__("$f1")=w.maximum;
    if(lateral<side)goto lateral_side_ready;
    if(upper<lateral)side=upper;else side=lateral;
    lateral_side_ready:;
   }else side=lateral;}else side=lateral;
   w.scalar.q=Scalar(side);world=Scale(w.direction.q,w.scalar.q);
  }
  register ACTOR*actor __asm__("$3")=context->actor;
  register float negative __asm__("$f0")=-1.0f,threshold __asm__("$f1");
  __asm__("addiu $2,%5,0x1b0\n\tlqc2 $vf3,%4\n\tlqc2 $vf2,0x10($2)\n\tvadd.xyzw $vf3,$vf3,%0\n\tlqc2 $vf4,0x20($2)\n\tlqc2 %0,0x1b0(%5)\n\tmfc1 $2,%6\n\tvmul.xyzw $vf8,%0,$vf3\n\tvmaxw.xyzw $vf9,$vf0,$vf0w\n\tvmul.xyzw $vf7,$vf2,$vf3\n\tvmul.xyzw $vf6,$vf4,$vf3\n\tvadday.x ACC,$vf8,$vf8y\n\tvmaddz.x %0,$vf9,$vf8z\n\tvaddax.y ACC,$vf7,$vf7x\n\tvmaddz.y %0,$vf9,$vf7z\n\tvaddax.z ACC,$vf6,$vf6x\n\tvmaddy.z %0,$vf9,$vf6y\n\tqmtc2.ni $2,$vf5\n\t.set noat\n\tlui $1,0x41c8\n\tmtc1 $1,%1\n\t.set at\n\tsqc2 $vf5,%2\n\tvmulx.xyzw %0,%0,$vf5x"
   :"+j"(world),"=f"(threshold),"=m"(w.direction.q)
   :"X"(actor->local.row[0].q),"m"(w.velocity.q),"r"(actor),"f"(negative),"X"(actor->local.row[1].q),"X"(actor->local.row[2].q)
   :"$1","$2","vf2","vf3","vf4","vf5","vf6","vf7","vf8","vf9");
  actor->velocity.q=world;
  register ACTOR*speedResult __asm__("$3");__asm__("lw %0,%1":"=r"(speedResult):"m"(context->actor));
  int step;
  if(threshold<Length(speedResult->velocity.q)){
   step=1;if(context->action==0){if(45.0f<Length(w.velocity.q))func_001940B0(context,0);else{
    register ACTOR*turnActor __asm__("$2")=speedResult;
    register float vertical __asm__("$f1");__asm__("lwc1 %0,%1":"=f"(vertical):"m"(turnActor->velocity.f[1]));
    if(20.0f<vertical){if(turnActor->role==1)goto variant_one;else goto variant_two;}
    else if(vertical<-20.0f){if(speedResult->role==1)goto variant_two;else goto variant_one;}
    goto variant_done;
    variant_two:func_001940B0(context,2);goto variant_done;
    variant_one:func_001940B0(context,1);
    variant_done:;
   }}
  }else{
   step=0;if(func_00132B10(context->focus,12)){SOURCE*source=context->focus;
    if(lateral<-25.0f&&(source->flags&1)){step=2;if(context->action==0&&context->actor->role==0)step=3;}
    else if(25.0f<lateral&&(source->flags&2)){step=3;if(context->action==0&&context->actor->role==0)step=2;}
   }if(context->action==0)func_001940B0(context,3);
  }
  func_00204660(context->actor,w.heading);
  if(context->step==5){float difference=func_0011CF60(func_00204740(context->actor)-w.heading);if(0.25f<__builtin_fabsf(difference))step=5;}
  func_00192BD8(context,step);break;
 }
 case 1:
  if(context->focus->enabled18C&&0.0f<input->amount&&context->program180.clip){func_00192BD8(context,4);func_0020BB58(&context->program180,input->amount);func_00204660(context->actor,context->actor->input->heading);func_0020BC08(&context->program180);}else func_00192BD8(context,0);break;
 case 2:
  func_001441E8(context->actor,D_002BF5C0);
  if((context->step==0?0.1f:0.0f)<input->amount){func_00192BD8(context,4);func_0020BB58(&context->actor->program,input->amount*D_002BF5C4);func_00204660(context->actor,input->heading);}else func_00192BD8(context,0);break;
 case 4:func_00204660(context->actor,input->heading);break;
 case 3:{SOURCE*source=context->focus;
  func_001E6ED8(source,context->actor->attachedPosition->q,0,&w.temp,&w.phase.vector,&context->parameter,&context->value,context->parameter);
  if(source->flags&&!source->cyclic){float edge=func_001E6610(source)+0.01f;if(context->parameter<edge){func_00195A00((char*)context->actor+0x2C0,0,0,0);break;}edge=func_001E6630(source)-0.01f;if(edge<context->parameter){func_00195A00((char*)context->actor+0x2C0,0,0,0);break;}}
  w.phase.vector.i[2]=0;
  register U*axisHigh __asm__("$19");
  {
   register qword vector __asm__("vf3"),length __asm__("vf1"),fallback __asm__("$2");
   register float epsilon __asm__("$f1");register U*high __asm__("$2");
   __asm__("lui %0,%%hi(%1)":"=r"(high):"i"(&D_002A2DA0));
   __asm__(".set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%3\n\t.set at\n\tdaddu %4,%7,$zero\n\tlqc2 %0,%5\n\taddiu %2,%7,%%lo(%6)\n\tvmul.xyz %1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\tlq %2,0(%2)\n\tvsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q"
    :"=j"(vector),"=j"(length),"=r"(fallback),"=f"(epsilon),"=r"(axisHigh)
    :"m"(w.phase.vector.q),"i"(&D_002A2DA0),"r"(high),"X"(*(U*)((char*)high+0x2da0)):"$1","vf2");
   register float magnitude __asm__("$f0");
   __asm__("qmfc2.ni $3,%1\n\tmtc1 $3,%0":"=f"(magnitude):"j"(length):"$3");
   if(magnitude<epsilon)length=fallback;
   else __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(length):"j"(vector));
   w.phase.vector.q=length;
  }
  float heading=func_002458F0(w.phase.vector.f[1],w.phase.vector.f[0]);
  w.direction.q=func_0011E1A0(input->heading,1.0f,0.0f);
  if(source->other)func_001E6F60(source->other,context->actor->attachedPosition->q,0,0,&w.velocity,0,0);else w.velocity=w.phase.vector;
  w.velocity.i[2]=0;
  register qword normalized __asm__("vf3");
  {
   register qword length __asm__("vf1"),fallback __asm__("$2");
   register float epsilon __asm__("$f1");
   __asm__("addiu %2,%4,%%lo(%6)\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%3\n\t.set at\n\tlqc2 %0,%5\n\tvmul.xyz %1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\tlq %2,0(%2)\n\tvsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q"
    :"=j"(normalized),"=j"(length),"=&r"(fallback),"=f"(epsilon)
    :"r"(axisHigh),"m"(w.velocity.q),"i"(&D_002A2DA0),"X"(*(U*)((char*)axisHigh+0x2da0)):"$1","vf2");
   register float magnitude __asm__("$f0");
   __asm__("qmfc2.ni $3,%1\n\tmtc1 $3,%0":"=f"(magnitude):"j"(length):"$3");
   if(magnitude<epsilon)normalized=fallback;
   else __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,$Q":"+j"(normalized):"j"(length));
  }
  register float amount __asm__("$f20");register int index __asm__("$3");
  __asm__("lqc2 $vf1,%3\n\tvmul.xyz $vf1,$vf1,%2\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tlw %1,%4\n\tqmfc2.ni $2,$vf1\n\tmtc1 $2,%0"
   :"=f"(amount),"=r"(index):"j"(normalized),"m"(w.direction.q),"m"(context->index):"$2","vf1","vf2");
  w.velocity.q=normalized;
  switch(index){
  case 0:if(input->amount<0.25f)context->index=-1;else if(amount<-0.7f)context->index=1;break;
  case 1:if(input->amount<0.25f)context->index=-1;else if(0.7f<amount)context->index=0;break;
  case -1:if(0.35f<input->amount){if(0.0f<=amount)context->index=0;else context->index=1;}break;
  }
  if(context->index!=0){if(context->index==1)context->reversed=context->index;}else context->reversed=0;
  if(!source->flags){
   __asm__("lwc1 $f0,%3\n\tlwc1 $f2,%4\n\tlwc1 $f1,%5\n\tswc1 $f0,%0\n\tswc1 $f1,%1\n\tswc1 $f2,%2"
    :"=m"(w.second.smp.minimum),"=m"(w.second.smp.duration),"=m"(w.second.smp.maximum)
    :"m"(context->program240.limit20),"m"(context->program240.limit60),"m"(D_002BF5C8):"$f0","$f1","$f2");
   if(source->cyclic)w.limit=w.second.smp.maximum;
   else if(context->reversed){(void)func_0011D018(context->value,50.0f,D_002DDED0.dt,&w.second.smp,&w.limit);w.limit=-w.limit;}
   else (void)func_0011D018(context->value,func_001E6648(source)-50.0f,D_002DDED0.dt,&w.second.smp,&w.limit);
   register float numerator __asm__("$f1"),span __asm__("$f0"),requested __asm__("$f12"),zero __asm__("$f3");
   __asm__("lwc1 $f2,%4\n\tlwc1 %0,%5\n\tlwc1 %1,%6\n\tlwc1 %2,%7\n\tsub.s %0,%0,$f2\n\tmtc1 $zero,%3\n\tsub.s %1,%1,$f2"
    :"=f"(numerator),"=f"(span),"=f"(requested),"=f"(zero)
    :"m"(w.second.smp.minimum),"m"(w.limit),"m"(w.second.smp.maximum),"m"(input->amount):"$f2");
   register float ratio __asm__("$f1")=numerator/span;
   if(requested<zero)amount=0.0f;
   else{amount=requested;if(ratio<requested){__asm__("mov.s %0,%1":"=f"(amount):"f"(ratio));}}
  }
  if(context->reversed)heading=func_0011CF60(heading+3.14159265358979323846f);
  if(0.0f<amount){func_00192BD8(context,4);func_0020BB58(&context->program240,amount);func_00204660(context->actor,heading);func_0020BC08(&context->program240);}else{func_00192BD8(context,0);func_00204660(context->actor,heading);}break;
 }
 case 5:case 9:func_001CC2E8(&context->sub);break;
 case 8:
  if(Less(context->step,9)&&!Less(context->step,7))break;
  if(0.0f<input->amount){
   func_00192BD8(context,10);ENTRY*entry=&context->axes330[3];if(!entry->active)entry=&context->axes330[2];
   {
    register float x __asm__("$f2")=input->y,lengthX __asm__("$f1"),inputX __asm__("$f3");
    register int bitsY __asm__("$2");
    __asm__("lqc2 $vf2,%4\n\tlqc2 $vf1,%5\n\tneg.s %0,%0\n\tvmul.xy $vf1,$vf1,$vf1\n\tvaddy.x $vf1,$vf1,$vf1y\n\tvmul.xy $vf2,$vf2,$vf2\n\tvaddy.x $vf2,$vf2,$vf2y\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tvsqrt $Q,$vf2x\n\tvwaitq\n\tvaddq.x $vf2,$vf0,$Q\n\tqmfc2.ni $3,$vf1\n\tlwc1 %2,%6\n\tmtc1 $3,%1\n\tqmfc2.ni %3,$vf2"
     :"+f"(x),"=f"(lengthX),"=f"(inputX),"=r"(bitsY)
     :"m"(context->axes330[1].direction.q),"m"(entry->direction.q),"m"(input->x):"$3","vf1","vf2");
    register float lengthY __asm__("$f0");__asm__("mtc1 %1,%0":"=f"(lengthY):"r"(bitsY));
    x=x*lengthX;register ACTOR*actor __asm__("$2")=context->actor;
    inputX=inputX*lengthY;actor->velocity.f[0]=x;
    U*velocity=&actor->velocity;velocity->f[2]=0.0f;velocity->f[1]=inputX;
   }
   func_001A0450(context->actor,context->axes330,context->clip430);
   ACTOR*actor=context->actor;float turn=-actor->velocity.f[1]/D_002BF5CC;qword projected=DotQ(actor->velocity.q,D_002A2DA0.q);__asm__("vmulx.xyzw %0,%1,%0x":"+j"(projected):"j"(D_002A2DA0.q));actor->velocity.q=projected;
   func_00204660(context->actor,context->actor->heading+turn*D_002DDED0.dt);
  }else func_00192BD8(context,9);
  {register ACTOR*terrainActor __asm__("$4")=context->actor;U*points=terrainActor==D_002E1E40?D_002BF5D0:D_002BF600;func_00205910(terrainActor,&D_002BF630,3,points);}break;
 case 10:{
  // This path initializes XYZ only; W is uninitialized when no track writes it.
  w.temp.i[2]=w.temp.i[1]=w.temp.i[0]=0;ANIMATION*a=context->actor->animation;
  if(a){BINDING*b=func_0012FF10(a->clip,context->actor,(void*)1,1);if(b){Sample(b,a,&w.temp);register float negative __asm__("$f0")=-1.0f;
    __asm__("lqc2 $vf1,%0\n\tmfc1 $3,%2\n\tqmtc2.ni $3,$vf2\n\tvmulx.xyzw $vf1,$vf1,$vf2x\n\tsqc2 $vf2,%1\n\tsqc2 $vf1,%0":"+m"(w.temp.q),"=m"(w.phase.vector.q):"f"(negative):"$3","vf1","vf2");}}
  context->actor->velocity.q=RawCopyValue(&w.temp);break;
 }
 case 11:if(context->focus){func_002046F0(context->actor,context->focus);func_00204CA8(context->actor);}break;
 }
 int step=context->step;
 if(step==0)goto stationary;if(step!=1)return;{func_001A0450(context->actor,context->axes70,context->clip170);if(context->actor->focus==context->aux&&Less(context->previous,3)&&0<context->previous){register float maximum __asm__("$f0")=context->maximum,weight __asm__("$f1");if(context->previous==step)weight=context->axes70[1].weight;else weight=context->axes70[0].weight;__asm__("max.s %0,%0,%1":"+f"(maximum):"f"(weight));context->maximum=maximum;}}
 return;
 stationary:if(context->action==3){ACTOR*actor=context->actor;func_00189C40(actor,actor->secondA,5.0f,actor->secondB,actor->firstObject,&actor->firstCache);func_00189C40(actor,actor->firstA,5.0f,actor->firstB,actor->secondObject,&actor->secondCache);func_00193C98(actor,&actor->firstCache,actor->firstObject);func_00193C98(actor,&actor->secondCache,actor->secondObject);}
}

typedef char uint_Width[sizeof(uint)==4?1:-1];
typedef char int_Width[sizeof(int)==4?1:-1];
typedef char float_Width[sizeof(float)==4?1:-1];
typedef char pointer_Width[sizeof(void*)==4?1:-1];
typedef char qword_Alignment[__alignof__(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char M3_Alignment[__alignof__(M3)==16?1:-1];
