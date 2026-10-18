typedef int qword __attribute__((mode(TI)));typedef unsigned long ulong;
union U{qword q;float f[4];int i[4];};struct VTE{short delta,pad;void*fn;};struct ACTOR;struct ANIMATION;struct PROVIDER;struct REFERENCE;struct OBJECT;struct PROPERTIES;struct CAMERA;struct COLLISION;struct CLIP;
struct SOURCE{char pad0[0x28];ulong flags;char pad30[0x14C];int state;};struct INPUT{char pad0[0x1C];float amount;char pad20[16];unsigned int flags;};struct SUPPORT{char pad0[0x88];float normalZ;};struct BODY{char pad0[0x70];U position;char pad80[0x20];void*frame;char padA4[4];float actionTime;char padAC[12];float motionZ;};
struct COMPANION{ACTOR*actor;int mode;};struct ACTOR{char pad0[12];VTE*vt;char pad10[0x48];BODY*body;char pad5C[0x90];COLLISION*collision;char padF0[0x60];INPUT*input;char pad154[0xB4];SUPPORT*support;char pad20C[0x2B4];char control[1];char pad4C1[0xA3F];char camera[1];char padF01[0x10F];U offset;char pad1020[0x10];ANIMATION*animation;char pad1034[0x2E8];float stamp;char pad1320[0x5D0];int transition;char pad18F4[0x1C];COMPANION companion;char pad1918[0x5C];PROPERTIES*properties;};
struct LINK{void*space;ACTOR*owner;};struct QUERY{OBJECT*object;PROVIDER*provider;REFERENCE*reference;int tag;U point;};struct EVENT{char pad0[0x1C];float deadline;U point,velocity;};
struct ENDPOINT{LINK*shape;void*space,*extra;ACTOR*owner;U point,local;char pad30[16];};struct CONTACT{ENDPOINT endpoint[2];U normal;float distance,x94,x98;int kind;void*first,*second;int xA8;CONTACT*next;};
struct CONTEXT{ACTOR*actor;int state,variant;SOURCE*source;char pad10[8];float stamp;int mode;float time;int flags24,flags28,flags2C,actionFlag;char pad34[12];int combo;char pad44[0x84];LINK*link;char padCC[4];U relative,direction,offset;int contactKind;void*contactInfo;char pad108[0x2C];CLIP*alternateClip;char pad138[0x98];QUERY query;EVENT*event;};
struct CLOCK{float time,dt;};struct SMP{float maximum,minimum,duration;};struct WORK{U position,velocity,temp,scalar;int side;};
extern "C"{extern CLOCK D_002DDED0;extern ACTOR*D_002E1E40,*D_002F7900;extern float D_002BF818,D_002BF81C,D_002BF82C,D_002BF830;extern SMP D_002BF820;extern U D_002A2DD0;
qword func_001A62E8(ACTOR*);void func_0019C828(CONTEXT*);int func_001C4660(INPUT*,int,float);int func_00143D20(ACTOR*,float);void func_001C4738(INPUT*,int);void func_00195A00(CONTEXT*,int,int,SOURCE*);void func_0019B110(CONTEXT*,void*);int func_001DAEA8(int);void func_00141CD0(ACTOR*,int);void func_00195FB8(CONTEXT*,int,SOURCE*);void func_00197370(CONTEXT*);float func_0012F990(PROPERTIES*,int);void func_002206C8(COMPANION*,int);void func_0019C688(CONTEXT*);void func_001928F8(CAMERA*,int,void*,void*);CONTACT*func_00199D48(CONTEXT*,int*,U*);qword func_0022FC48(void*,void*,qword);int func_0019A098(ACTOR*,float*,float);void func_0019F590(ACTOR*,QUERY*);int func_001C46C0(INPUT*,int,float);qword func_0011F088(qword,qword,float,SMP*,float*);int func_001999D0(CONTEXT*,LINK*,qword,int,void*,U*);void func_002046B0(ACTOR*,qword);void func_0019CC50(CAMERA*,int,ACTOR*,void*);int func_001974C8(COLLISION*);int func_00141EA8(ACTOR*,int);int func_00131968(ANIMATION*);int func_00132B10(void*,int);void func_001305B8(CLIP*,ACTOR*,float,float,int,ANIMATION**);qword func_0019A750(CONTEXT*,int);qword func_0019F3F8(ACTOR*,QUERY*,float);void func_0012E0F0(EVENT*,qword,qword);int func_001441A0(ACTOR*);}
static inline ulong Alive(ulong flags){return (flags>>60)&1;}
static inline bool Less(int x,int limit){return x<limit;}
static inline qword Velocity(ACTOR*p){VTE&v=p->vt[33];return ((qword(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetVelocity(ACTOR*p,qword q){VTE&v=p->vt[35];((void(*)(void*,qword))v.fn)((char*)p+v.delta,q);}
static inline int Test(ACTOR*p,int slot,int value){VTE&v=p->vt[slot];return ((int(*)(void*,int))v.fn)((char*)p+v.delta,value);}
static inline void SetState(ACTOR*p,int slot,int value){VTE&v=p->vt[slot];((void(*)(void*,int))v.fn)((char*)p+v.delta,value);}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword a,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k));return r;}
static inline float Minimum(float a,float b){return a<b?a:b;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char ulong_Size[sizeof(ulong)==8?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char SOURCE_Size[sizeof(SOURCE)==384?1:-1];
typedef char INPUT_Size[sizeof(INPUT)==52?1:-1];
typedef char SUPPORT_Size[sizeof(SUPPORT)==140?1:-1];
typedef char BODY_Size[sizeof(BODY)==192?1:-1];
typedef char COMPANION_Size[sizeof(COMPANION)==8?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==6528?1:-1];
typedef char LINK_Size[sizeof(LINK)==8?1:-1];
typedef char QUERY_Size[sizeof(QUERY)==32?1:-1];
typedef char EVENT_Size[sizeof(EVENT)==64?1:-1];
typedef char ENDPOINT_Size[sizeof(ENDPOINT)==64?1:-1];
typedef char CONTACT_Size[sizeof(CONTACT)==176?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==512?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char SMP_Size[sizeof(SMP)==12?1:-1];
typedef char WORK_Size[sizeof(WORK)==80?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char U_f_Offset[FIELD_OFFSET(U,f)==0?1:-1];
typedef char U_i_Offset[FIELD_OFFSET(U,i)==0?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char SOURCE_flags_Offset[FIELD_OFFSET(SOURCE,flags)==40?1:-1];
typedef char SOURCE_state_Offset[FIELD_OFFSET(SOURCE,state)==380?1:-1];
typedef char INPUT_amount_Offset[FIELD_OFFSET(INPUT,amount)==28?1:-1];
typedef char INPUT_flags_Offset[FIELD_OFFSET(INPUT,flags)==48?1:-1];
typedef char SUPPORT_normalZ_Offset[FIELD_OFFSET(SUPPORT,normalZ)==136?1:-1];
typedef char BODY_position_Offset[FIELD_OFFSET(BODY,position)==112?1:-1];
typedef char BODY_frame_Offset[FIELD_OFFSET(BODY,frame)==160?1:-1];
typedef char BODY_actionTime_Offset[FIELD_OFFSET(BODY,actionTime)==168?1:-1];
typedef char BODY_motionZ_Offset[FIELD_OFFSET(BODY,motionZ)==184?1:-1];
typedef char COMPANION_actor_Offset[FIELD_OFFSET(COMPANION,actor)==0?1:-1];
typedef char COMPANION_mode_Offset[FIELD_OFFSET(COMPANION,mode)==4?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_body_Offset[FIELD_OFFSET(ACTOR,body)==88?1:-1];
typedef char ACTOR_collision_Offset[FIELD_OFFSET(ACTOR,collision)==236?1:-1];
typedef char ACTOR_input_Offset[FIELD_OFFSET(ACTOR,input)==336?1:-1];
typedef char ACTOR_support_Offset[FIELD_OFFSET(ACTOR,support)==520?1:-1];
typedef char ACTOR_control_Offset[FIELD_OFFSET(ACTOR,control)==1216?1:-1];
typedef char ACTOR_camera_Offset[FIELD_OFFSET(ACTOR,camera)==3840?1:-1];
typedef char ACTOR_offset_Offset[FIELD_OFFSET(ACTOR,offset)==4112?1:-1];
typedef char ACTOR_animation_Offset[FIELD_OFFSET(ACTOR,animation)==4144?1:-1];
typedef char ACTOR_stamp_Offset[FIELD_OFFSET(ACTOR,stamp)==4892?1:-1];
typedef char ACTOR_transition_Offset[FIELD_OFFSET(ACTOR,transition)==6384?1:-1];
typedef char ACTOR_companion_Offset[FIELD_OFFSET(ACTOR,companion)==6416?1:-1];
typedef char ACTOR_properties_Offset[FIELD_OFFSET(ACTOR,properties)==6516?1:-1];
typedef char LINK_space_Offset[FIELD_OFFSET(LINK,space)==0?1:-1];
typedef char LINK_owner_Offset[FIELD_OFFSET(LINK,owner)==4?1:-1];
typedef char QUERY_object_Offset[FIELD_OFFSET(QUERY,object)==0?1:-1];
typedef char QUERY_provider_Offset[FIELD_OFFSET(QUERY,provider)==4?1:-1];
typedef char QUERY_reference_Offset[FIELD_OFFSET(QUERY,reference)==8?1:-1];
typedef char QUERY_tag_Offset[FIELD_OFFSET(QUERY,tag)==12?1:-1];
typedef char QUERY_point_Offset[FIELD_OFFSET(QUERY,point)==16?1:-1];
typedef char EVENT_deadline_Offset[FIELD_OFFSET(EVENT,deadline)==28?1:-1];
typedef char EVENT_point_Offset[FIELD_OFFSET(EVENT,point)==32?1:-1];
typedef char EVENT_velocity_Offset[FIELD_OFFSET(EVENT,velocity)==48?1:-1];
typedef char ENDPOINT_shape_Offset[FIELD_OFFSET(ENDPOINT,shape)==0?1:-1];
typedef char ENDPOINT_space_Offset[FIELD_OFFSET(ENDPOINT,space)==4?1:-1];
typedef char ENDPOINT_extra_Offset[FIELD_OFFSET(ENDPOINT,extra)==8?1:-1];
typedef char ENDPOINT_owner_Offset[FIELD_OFFSET(ENDPOINT,owner)==12?1:-1];
typedef char ENDPOINT_point_Offset[FIELD_OFFSET(ENDPOINT,point)==16?1:-1];
typedef char ENDPOINT_local_Offset[FIELD_OFFSET(ENDPOINT,local)==32?1:-1];
typedef char CONTACT_endpoint_Offset[FIELD_OFFSET(CONTACT,endpoint)==0?1:-1];
typedef char CONTACT_normal_Offset[FIELD_OFFSET(CONTACT,normal)==128?1:-1];
typedef char CONTACT_distance_Offset[FIELD_OFFSET(CONTACT,distance)==144?1:-1];
typedef char CONTACT_kind_Offset[FIELD_OFFSET(CONTACT,kind)==156?1:-1];
typedef char CONTACT_first_Offset[FIELD_OFFSET(CONTACT,first)==160?1:-1];
typedef char CONTACT_second_Offset[FIELD_OFFSET(CONTACT,second)==164?1:-1];
typedef char CONTACT_next_Offset[FIELD_OFFSET(CONTACT,next)==172?1:-1];
typedef char CONTEXT_actor_Offset[FIELD_OFFSET(CONTEXT,actor)==0?1:-1];
typedef char CONTEXT_state_Offset[FIELD_OFFSET(CONTEXT,state)==4?1:-1];
typedef char CONTEXT_variant_Offset[FIELD_OFFSET(CONTEXT,variant)==8?1:-1];
typedef char CONTEXT_source_Offset[FIELD_OFFSET(CONTEXT,source)==12?1:-1];
typedef char CONTEXT_stamp_Offset[FIELD_OFFSET(CONTEXT,stamp)==24?1:-1];
typedef char CONTEXT_mode_Offset[FIELD_OFFSET(CONTEXT,mode)==28?1:-1];
typedef char CONTEXT_time_Offset[FIELD_OFFSET(CONTEXT,time)==32?1:-1];
typedef char CONTEXT_flags24_Offset[FIELD_OFFSET(CONTEXT,flags24)==36?1:-1];
typedef char CONTEXT_flags28_Offset[FIELD_OFFSET(CONTEXT,flags28)==40?1:-1];
typedef char CONTEXT_flags2C_Offset[FIELD_OFFSET(CONTEXT,flags2C)==44?1:-1];
typedef char CONTEXT_actionFlag_Offset[FIELD_OFFSET(CONTEXT,actionFlag)==48?1:-1];
typedef char CONTEXT_combo_Offset[FIELD_OFFSET(CONTEXT,combo)==64?1:-1];
typedef char CONTEXT_link_Offset[FIELD_OFFSET(CONTEXT,link)==200?1:-1];
typedef char CONTEXT_relative_Offset[FIELD_OFFSET(CONTEXT,relative)==208?1:-1];
typedef char CONTEXT_direction_Offset[FIELD_OFFSET(CONTEXT,direction)==224?1:-1];
typedef char CONTEXT_offset_Offset[FIELD_OFFSET(CONTEXT,offset)==240?1:-1];
typedef char CONTEXT_contactKind_Offset[FIELD_OFFSET(CONTEXT,contactKind)==256?1:-1];
typedef char CONTEXT_contactInfo_Offset[FIELD_OFFSET(CONTEXT,contactInfo)==260?1:-1];
typedef char CONTEXT_alternateClip_Offset[FIELD_OFFSET(CONTEXT,alternateClip)==308?1:-1];
typedef char CONTEXT_query_Offset[FIELD_OFFSET(CONTEXT,query)==464?1:-1];
typedef char CONTEXT_event_Offset[FIELD_OFFSET(CONTEXT,event)==496?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char SMP_maximum_Offset[FIELD_OFFSET(SMP,maximum)==0?1:-1];
typedef char SMP_minimum_Offset[FIELD_OFFSET(SMP,minimum)==4?1:-1];
typedef char SMP_duration_Offset[FIELD_OFFSET(SMP,duration)==8?1:-1];
typedef char WORK_position_Offset[FIELD_OFFSET(WORK,position)==0?1:-1];
typedef char WORK_velocity_Offset[FIELD_OFFSET(WORK,velocity)==16?1:-1];
typedef char WORK_temp_Offset[FIELD_OFFSET(WORK,temp)==32?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==48?1:-1];
typedef char WORK_side_Offset[FIELD_OFFSET(WORK,side)==64?1:-1];
// Native stores the initial position at SP+0 without a later read.
extern "C" void func_00197500(CONTEXT*p)
{
 WORK w;int blocked=0;
 w.position.q=func_001A62E8(p->actor);
 w.velocity.q=Velocity(p->actor);
 INPUT*input=p->actor->input;
 if(p->actor->support && p->actor->support->normalZ>0.7f)blocked=1;
 for(;;){
  int previous=p->mode;int requestedMode;register CONTEXT*modeReceiver asm("$4");
  if(p->source && !Alive(p->source->flags))func_0019C828(p);
  if(Less(p->mode,23) && !Less(p->mode,9))goto dispatch;
  if(p->flags28 && func_001C4660(input,0x40,0.0f) && !func_00143D20(p->actor,0.075f)){
   func_001C4738(input,0x40);func_00195A00(p,6,p->variant,0);
  }
  if(func_001C4660(input,0x20,0.0f)){
   int before=p->mode;func_0019B110(p,0);
   if(p->mode!=before)func_001C4738(input,0x20);
  }
  if(func_001C4660(input,8,0.0f) && p->actor==D_002E1E40 && func_001DAEA8(27) && !func_00143D20(p->actor,0.3f)){
   func_00141CD0(p->actor,27);func_001C4738(input,8);SetState(D_002E1E40,100,27);
  }
 dispatch:
  switch(p->mode){
  case 0:
   if(D_002DDED0.time-p->time>D_002BF818){
    if(!(input->flags&0x40) && p->combo!=3)p->flags24=1;
    func_00195FB8(p,1,p->source);
   }else if(!p->actionFlag && input->amount>0.5f)func_00197370(p);
   break;
  case 2:
   if(D_002DDED0.time-p->time>D_002BF81C)func_00195FB8(p,3,p->source);
   else if(!p->actionFlag && input->amount>0.5f)func_00197370(p);
   break;
  case 1:case 7:
   if(w.velocity.f[2]<0.0f)func_00195FB8(p,4,p->source);
   break;
  case 6:
   if(p->source->state==3){modeReceiver=p;requestedMode=4;goto apply_mode;}
   if(p->actor->body->actionTime<D_002DDED0.time)func_0019C688(p);
   break;
  case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:
   if(p->actor->body->actionTime<D_002DDED0.time)func_0019C688(p);
   break;
  case 18:{
   float anticipation=func_0012F990(D_002F7900->properties,0x1C7);
   if(p->actor->body->actionTime-anticipation<=D_002DDED0.time){
    if(D_002F7900->companion.mode!=3){func_002206C8(&D_002F7900->companion,3);break;}
   }
   if(p->actor->body->actionTime<D_002DDED0.time)func_0019C688(p);
   break;
  }
  case 8:
   if(p->actor->body->actionTime<D_002DDED0.time)func_00195FB8(p,4,p->source);
   break;
  case 5:
   if(D_002DDED0.time-p->time>0.25f && blocked)SetState(p->actor,88,0);
   else if(func_0019A098(p->actor,&p->actor->stamp,p->time))func_0019F590(p->actor,0);
   break;
  case 3:case 4:{
   if(blocked){
    if(p->state==14)func_001928F8((CAMERA*)p->actor->control,10,0,0);
    else SetState(p->actor,88,0);
    break;
   }
   CONTACT*contact=func_00199D48(p,&w.side,&w.temp);
   if(contact){
    ENDPOINT*endpoint=&contact->endpoint[1-w.side];
    p->link=endpoint->shape;
    p->relative.q=func_0022FC48(0,p->link->space,endpoint->point.q);
    p->contactKind=contact->kind;
    void*feature;
    if(!w.side)feature=contact->second;else feature=contact->first;
    qword normal=w.temp.q;
    modeReceiver=p;p->contactInfo=feature;p->direction.q=normal;requestedMode=17;goto apply_mode;
   }else if(func_0019A098(p->actor,&p->actor->stamp,p->time))func_0019F590(p->actor,0);
   break;
  }
  case 17:{
   if(D_002DDED0.time-p->time>0.25f && func_001C46C0(input,0x40,0.25f)){
    func_00195A00(p,3,0,0);break;
   }
   if(!p->link->owner->collision){modeReceiver=p;requestedMode=4;goto apply_mode;}
   ACTOR*actor=p->actor;
   actor->offset.q=func_0011F088(actor->offset.q,D_002A2DD0.q,D_002DDED0.dt,&D_002BF820,0);
   w.temp.q=func_0022FC48(p->link->space,0,p->relative.q);
   if(D_002DDED0.time-p->time>0.03f && !func_001999D0(p,p->link,w.temp.q,p->contactKind,p->contactInfo,&p->direction)){
    modeReceiver=p;requestedMode=4;goto apply_mode;
   }
   w.scalar.q=Scalar(-1.0f);func_002046B0(p->actor,Scale(p->direction.q,w.scalar.q));
   if(func_001C4660(input,0x400,0.15f) && Test(p->actor,99,3)){
    func_001C4738(input,0x400);func_0019CC50((CAMERA*)p->actor->camera,0,0,0);
   }
   break;
  }
  case 19:case 20:
   if(func_001974C8(p->actor->collision)){modeReceiver=p;requestedMode=4;goto apply_mode;}
   if(!(input->flags&(func_00141EA8(p->actor,27)|8))){modeReceiver=p;requestedMode=4;goto apply_mode;}
   if(p->mode==19 && (!p->actor->animation || func_00131968(p->actor->animation))){modeReceiver=p;requestedMode=20;goto apply_mode;}
   break;
  case 21:{
   float now=D_002DDED0.time,deadline=p->event->deadline;
   if(deadline<now){
    ACTOR*saved=0;int transition;
    if(func_00132B10(p->actor,53)){saved=p->actor;transition=saved->transition;}
    qword incoming=Velocity(p->actor);
    register float zero asm("$f0");asm("mtc1 $zero,%0":"=f"(zero));
    register ACTOR*receiver asm("$6");register qword outgoing asm("$5");
    asm volatile("sq %5,%0\n\tswc1 %6,%1\n\tswc1 %6,%2\n\tlw %3,%7\n\tlq %4,%0":"=m"(w.temp.q),"=m"(w.temp.f[0]),"=m"(w.temp.f[1]),"=r"(receiver),"=r"(outgoing):"r"(incoming),"f"(zero),"m"(p->actor));
    SetVelocity(receiver,outgoing);
    func_00195A00(p,11,0,0);if(saved)saved->transition=transition;
    break;
   }
   if(p->query.provider && deadline<now+0.25f &&
      (func_00132B10(p->query.object,19)||func_00132B10(p->query.object,11)||
       func_00132B10(p->query.object,13)||func_00132B10(p->query.object,39)||
       func_00132B10(p->query.object,12)||func_00132B10(p->query.object,34)||func_00132B10(p->query.object,38))){
    func_00195A00(p,11,0,0);func_0019B110(p,p->query.object);break;
   }
   if(p->flags28 && p->actor->body->motionZ<0.0f){
    func_001305B8(p->alternateClip,p->actor,0.0f,1.0f,1,&p->actor->animation);
    p->flags28=0;ACTOR*actor=p->actor;VTE*entry=&actor->vt[35];
    void*receiver=(char*)actor+entry->delta;
    qword velocity=func_0019A750(p,6);((void(*)(void*,qword))entry->fn)(receiver,velocity);
    break;
   }
   if(p->query.provider || p->query.reference){
    register float prediction asm("$f12")=p->event->deadline-D_002DDED0.time;
    prediction=Minimum(prediction,0.7f);
    qword point=func_0019F3F8(p->actor,&p->query,prediction);
    point=func_0022FC48(0,p->actor->body->frame,point);
    func_0012E0F0(p->event,point,p->event->velocity.q);
   }
   break;
  }
  case 22:{
   if(func_001441A0(p->actor)<=0){modeReceiver=p;requestedMode=4;goto apply_mode;}
   {
    register float firstStamp asm("$f2")=p->time;
    register float firstElapsed asm("$f1")=D_002DDED0.time;
    register float firstLimit asm("$f0")=D_002BF82C;
    register float continuedStamp asm("$f3")=firstStamp;
    asm("sub.s %0,%0,%1":"+f"(firstElapsed):"f"(firstStamp));
    if(firstElapsed>firstLimit && blocked){SetState(p->actor,88,0);break;}
    if(D_002DDED0.time-continuedStamp>D_002BF82C && !(input->flags&func_00141EA8(p->actor,12))){modeReceiver=p;requestedMode=4;goto apply_mode;}
   }
   goto late_deadline;
  apply_mode:
   func_00195FB8(modeReceiver,requestedMode,0);break;
  late_deadline:
   if(D_002DDED0.time-p->time>D_002BF830)func_00195FB8(p,4,0);
   break;
  }
  }
  if(p->mode==previous || p->mode==-1)break;
 }
}
