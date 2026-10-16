typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};struct M3{U row[3];};struct VTE{short delta,pad;void*fn;};
struct OBJECT;struct PROVIDER;struct REFERENCE;struct EVENT;struct EFFECT;struct SCENE;struct SECONDARY;
struct DATA{char pad0[4];float amount;};struct SOURCE{char pad0[0x114];DATA*data;char pad118[0x64];int state;};
struct CLIP{char pad0[0x74];float duration;};struct ANIMATION{char pad0[0x14];CLIP*clip;};struct COMPONENT{void*object;};
struct BODY{char pad0[0x70];U position;char pad80[0x20];void*frame;};struct MOTION{char pad0[0x80];U acceleration;};
struct ACTOR{char pad0[12];VTE*vt;char pad10[0x48];BODY*body;char pad5C[0x8C];MOTION*motion;char padEC[0x28];DATA*data;char pad118[0x78];U velocity;char pad1A0[8];float heading;char pad1AC[0x31C];int category;char pad4CC[0x434];char secondary[0x30];CLIP*secondaryClip;char pad934[0x50];SOURCE*secondaryFocus;char pad988[0x688];U offset;char pad1020[0x10];ANIMATION*animation;COMPONENT component;char pad1038[0x4DC];CLIP*clip1514;CLIP*clip1518;char pad151C[0x338];SOURCE*primaryFocus;char pad1858[0x4D0];EFFECT*effect;};
struct LINK{void*space;void*target;};union WORD{int bits;float amount;};struct TRACK{int opaque;WORD control;float weight;};struct QUERY{OBJECT*object;PROVIDER*provider;REFERENCE*reference;int tag;U point;};
struct CONTEXT{ACTOR*actor;int state,variant;SOURCE*source;char pad10[8];float stamp;int mode;float time;int flags24,flags28,flags2C;int actionFlag;float gain,turnGain,height;int combo;float time44,time48,time4C;char pad50[0x6C];int fieldBC;char padC0[8];LINK*link;char padCC[4];U relative,direction,offset;char pad100[0x20];CLIP*base[5];CLIP*alternate[5];CLIP*special148,*special14C,*special150,*special154,*special158,*special15C;char pad160[8];float oldScale;void*focus;char pad170[4];int focused;CLIP*scripted;float scriptedGain;char pad180[4];TRACK tracks[4];char pad1B4[4];CLIP*multi;SOURCE*scriptFocus;char pad1C0[8];CLIP*special1C8;char pad1CC[4];QUERY query;EVENT*event;};
struct CLOCK{float time,dt;};struct RANGE{float low,high;};struct TWO_ROWS{U row[2];};
struct WORK{U temp;M3 basis;U scalar,bodyPosition,goal,delta,acceleration,velocity,endVelocity,duration;};
extern "C"{extern SCENE D_003DD490;extern CLOCK D_002DDED0;extern ACTOR*D_002E1E40;extern U D_002A2DB0,D_002A2DC0,D_002A2DD0;extern float D_002BF780[],D_002BF7A0;extern RANGE D_002BF798;
void func_00204F78(ACTOR*,void*,int);void func_00134320(SCENE*,void*);void func_00183B80(SOURCE*,int);void func_002303A0(ACTOR*,BODY*,int);void func_001CCAC0(SECONDARY*,int);void func_0018E540(ACTOR*,int);void func_001F0660(EFFECT*,int);void func_00140C88(ACTOR*,void*);void func_0012E460(EVENT**);void func_001F6860(ACTOR*,int);
qword func_0022FC48(void*,void*,qword);qword func_0022FCC8(void*,void*,qword);void func_0011E2D8(qword,qword,qword,TWO_ROWS*);qword func_001A62E8(ACTOR*);void func_00204DA8(ACTOR*,float);qword func_0019A750(CONTEXT*,int);void func_00204660(ACTOR*,float);void func_001384C0(CLIP*);int func_00132B10(OBJECT*,int);qword func_0019F3F8(ACTOR*,QUERY*,float);float func_00196928(qword,qword,float,float,float,float);EVENT*func_0012DE58(ACTOR*,BODY*,int,float,qword,qword);void func_002046B0(ACTOR*,qword);void func_001F15B8(COMPONENT*);void func_001305B8(CLIP*,ACTOR*,float,float,int,ANIMATION**);}
static inline void Notify(ACTOR*p,int slot){VTE&v=p->vt[slot];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetVelocity(ACTOR*p,qword value){VTE&v=p->vt[35];((void(*)(void*,qword))v.fn)((char*)p+v.delta,value);}
static inline void ClearXYZ(U*v){v->i[2]=0;v->i[1]=0;v->i[0]=0;}
static inline void ClearVelocity(ACTOR*p){ClearXYZ(&p->velocity);}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword a,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScaled(qword a,qword b,qword k){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));return r;}
static inline qword Divide(qword a,qword k){qword r;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(k),"j"(a));return r;}
static inline qword Rotate(M3*m,qword vector){__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(vector):"j"(m->row[0].q),"j"(m->row[1].q),"j"(m->row[2].q),"j"(vector));return vector;}
static inline float Maximum(float a,float b){__asm__("max.s %0,%1,%2":"=f"(a):"f"(a),"f"(b));return a;}
static inline bool Less(int x,int limit){return x<limit;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char DATA_Size[sizeof(DATA)==8?1:-1];
typedef char SOURCE_Size[sizeof(SOURCE)==384?1:-1];
typedef char CLIP_Size[sizeof(CLIP)==120?1:-1];
typedef char ANIMATION_Size[sizeof(ANIMATION)==24?1:-1];
typedef char COMPONENT_Size[sizeof(COMPONENT)==4?1:-1];
typedef char BODY_Size[sizeof(BODY)==176?1:-1];
typedef char MOTION_Size[sizeof(MOTION)==144?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==7472?1:-1];
typedef char LINK_Size[sizeof(LINK)==8?1:-1];
typedef char WORD_Size[sizeof(WORD)==4?1:-1];
typedef char WORD_bits_Offset[FIELD_OFFSET(WORD,bits)==0?1:-1];
typedef char WORD_amount_Offset[FIELD_OFFSET(WORD,amount)==0?1:-1];
typedef char TRACK_Size[sizeof(TRACK)==12?1:-1];
typedef char QUERY_Size[sizeof(QUERY)==32?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==512?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char RANGE_Size[sizeof(RANGE)==8?1:-1];
typedef char TWO_ROWS_Size[sizeof(TWO_ROWS)==32?1:-1];
typedef char WORK_Size[sizeof(WORK)==192?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char DATA_amount_Offset[FIELD_OFFSET(DATA,amount)==4?1:-1];
typedef char SOURCE_data_Offset[FIELD_OFFSET(SOURCE,data)==276?1:-1];
typedef char SOURCE_state_Offset[FIELD_OFFSET(SOURCE,state)==380?1:-1];
typedef char CLIP_duration_Offset[FIELD_OFFSET(CLIP,duration)==116?1:-1];
typedef char ANIMATION_clip_Offset[FIELD_OFFSET(ANIMATION,clip)==20?1:-1];
typedef char COMPONENT_object_Offset[FIELD_OFFSET(COMPONENT,object)==0?1:-1];
typedef char BODY_position_Offset[FIELD_OFFSET(BODY,position)==112?1:-1];
typedef char BODY_frame_Offset[FIELD_OFFSET(BODY,frame)==160?1:-1];
typedef char MOTION_acceleration_Offset[FIELD_OFFSET(MOTION,acceleration)==128?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_body_Offset[FIELD_OFFSET(ACTOR,body)==88?1:-1];
typedef char ACTOR_motion_Offset[FIELD_OFFSET(ACTOR,motion)==232?1:-1];
typedef char ACTOR_data_Offset[FIELD_OFFSET(ACTOR,data)==276?1:-1];
typedef char ACTOR_velocity_Offset[FIELD_OFFSET(ACTOR,velocity)==400?1:-1];
typedef char ACTOR_heading_Offset[FIELD_OFFSET(ACTOR,heading)==424?1:-1];
typedef char ACTOR_category_Offset[FIELD_OFFSET(ACTOR,category)==1224?1:-1];
typedef char ACTOR_secondary_Offset[FIELD_OFFSET(ACTOR,secondary)==2304?1:-1];
typedef char ACTOR_secondaryClip_Offset[FIELD_OFFSET(ACTOR,secondaryClip)==2352?1:-1];
typedef char ACTOR_secondaryFocus_Offset[FIELD_OFFSET(ACTOR,secondaryFocus)==2436?1:-1];
typedef char ACTOR_offset_Offset[FIELD_OFFSET(ACTOR,offset)==4112?1:-1];
typedef char ACTOR_animation_Offset[FIELD_OFFSET(ACTOR,animation)==4144?1:-1];
typedef char ACTOR_component_Offset[FIELD_OFFSET(ACTOR,component)==4148?1:-1];
typedef char ACTOR_clip1514_Offset[FIELD_OFFSET(ACTOR,clip1514)==5396?1:-1];
typedef char ACTOR_clip1518_Offset[FIELD_OFFSET(ACTOR,clip1518)==5400?1:-1];
typedef char ACTOR_primaryFocus_Offset[FIELD_OFFSET(ACTOR,primaryFocus)==6228?1:-1];
typedef char ACTOR_effect_Offset[FIELD_OFFSET(ACTOR,effect)==7464?1:-1];
typedef char LINK_space_Offset[FIELD_OFFSET(LINK,space)==0?1:-1];
typedef char LINK_target_Offset[FIELD_OFFSET(LINK,target)==4?1:-1];
typedef char TRACK_opaque_Offset[FIELD_OFFSET(TRACK,opaque)==0?1:-1];
typedef char TRACK_control_Offset[FIELD_OFFSET(TRACK,control)==4?1:-1];
typedef char TRACK_weight_Offset[FIELD_OFFSET(TRACK,weight)==8?1:-1];
typedef char QUERY_object_Offset[FIELD_OFFSET(QUERY,object)==0?1:-1];
typedef char QUERY_provider_Offset[FIELD_OFFSET(QUERY,provider)==4?1:-1];
typedef char QUERY_reference_Offset[FIELD_OFFSET(QUERY,reference)==8?1:-1];
typedef char QUERY_tag_Offset[FIELD_OFFSET(QUERY,tag)==12?1:-1];
typedef char QUERY_point_Offset[FIELD_OFFSET(QUERY,point)==16?1:-1];
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
typedef char CONTEXT_gain_Offset[FIELD_OFFSET(CONTEXT,gain)==52?1:-1];
typedef char CONTEXT_turnGain_Offset[FIELD_OFFSET(CONTEXT,turnGain)==56?1:-1];
typedef char CONTEXT_height_Offset[FIELD_OFFSET(CONTEXT,height)==60?1:-1];
typedef char CONTEXT_combo_Offset[FIELD_OFFSET(CONTEXT,combo)==64?1:-1];
typedef char CONTEXT_time44_Offset[FIELD_OFFSET(CONTEXT,time44)==68?1:-1];
typedef char CONTEXT_time48_Offset[FIELD_OFFSET(CONTEXT,time48)==72?1:-1];
typedef char CONTEXT_time4C_Offset[FIELD_OFFSET(CONTEXT,time4C)==76?1:-1];
typedef char CONTEXT_fieldBC_Offset[FIELD_OFFSET(CONTEXT,fieldBC)==188?1:-1];
typedef char CONTEXT_link_Offset[FIELD_OFFSET(CONTEXT,link)==200?1:-1];
typedef char CONTEXT_relative_Offset[FIELD_OFFSET(CONTEXT,relative)==208?1:-1];
typedef char CONTEXT_direction_Offset[FIELD_OFFSET(CONTEXT,direction)==224?1:-1];
typedef char CONTEXT_offset_Offset[FIELD_OFFSET(CONTEXT,offset)==240?1:-1];
typedef char CONTEXT_base_Offset[FIELD_OFFSET(CONTEXT,base)==288?1:-1];
typedef char CONTEXT_alternate_Offset[FIELD_OFFSET(CONTEXT,alternate)==308?1:-1];
typedef char CONTEXT_special148_Offset[FIELD_OFFSET(CONTEXT,special148)==328?1:-1];
typedef char CONTEXT_special14C_Offset[FIELD_OFFSET(CONTEXT,special14C)==332?1:-1];
typedef char CONTEXT_special150_Offset[FIELD_OFFSET(CONTEXT,special150)==336?1:-1];
typedef char CONTEXT_special154_Offset[FIELD_OFFSET(CONTEXT,special154)==340?1:-1];
typedef char CONTEXT_special158_Offset[FIELD_OFFSET(CONTEXT,special158)==344?1:-1];
typedef char CONTEXT_special15C_Offset[FIELD_OFFSET(CONTEXT,special15C)==348?1:-1];
typedef char CONTEXT_oldScale_Offset[FIELD_OFFSET(CONTEXT,oldScale)==360?1:-1];
typedef char CONTEXT_focus_Offset[FIELD_OFFSET(CONTEXT,focus)==364?1:-1];
typedef char CONTEXT_focused_Offset[FIELD_OFFSET(CONTEXT,focused)==372?1:-1];
typedef char CONTEXT_scripted_Offset[FIELD_OFFSET(CONTEXT,scripted)==376?1:-1];
typedef char CONTEXT_scriptedGain_Offset[FIELD_OFFSET(CONTEXT,scriptedGain)==380?1:-1];
typedef char CONTEXT_tracks_Offset[FIELD_OFFSET(CONTEXT,tracks)==388?1:-1];
typedef char CONTEXT_multi_Offset[FIELD_OFFSET(CONTEXT,multi)==440?1:-1];
typedef char CONTEXT_scriptFocus_Offset[FIELD_OFFSET(CONTEXT,scriptFocus)==444?1:-1];
typedef char CONTEXT_special1C8_Offset[FIELD_OFFSET(CONTEXT,special1C8)==456?1:-1];
typedef char CONTEXT_query_Offset[FIELD_OFFSET(CONTEXT,query)==464?1:-1];
typedef char CONTEXT_event_Offset[FIELD_OFFSET(CONTEXT,event)==496?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char RANGE_low_Offset[FIELD_OFFSET(RANGE,low)==0?1:-1];
typedef char RANGE_high_Offset[FIELD_OFFSET(RANGE,high)==4?1:-1];
typedef char TWO_ROWS_row_Offset[FIELD_OFFSET(TWO_ROWS,row)==0?1:-1];
typedef char WORK_temp_Offset[FIELD_OFFSET(WORK,temp)==0?1:-1];
typedef char WORK_basis_Offset[FIELD_OFFSET(WORK,basis)==16?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==64?1:-1];
typedef char WORK_bodyPosition_Offset[FIELD_OFFSET(WORK,bodyPosition)==80?1:-1];
typedef char WORK_goal_Offset[FIELD_OFFSET(WORK,goal)==96?1:-1];
typedef char WORK_delta_Offset[FIELD_OFFSET(WORK,delta)==112?1:-1];
typedef char WORK_acceleration_Offset[FIELD_OFFSET(WORK,acceleration)==128?1:-1];
typedef char WORK_velocity_Offset[FIELD_OFFSET(WORK,velocity)==144?1:-1];
typedef char WORK_endVelocity_Offset[FIELD_OFFSET(WORK,endVelocity)==160?1:-1];
typedef char WORK_duration_Offset[FIELD_OFFSET(WORK,duration)==176?1:-1];
extern "C" void func_00195FB8(CONTEXT*p,int newMode,SOURCE*source){WORK w;
 if(newMode==p->mode)return;
 switch(p->mode){
 case 17:func_00204F78(p->actor,p->link->target,0);p->link=0;break;
 case 7:{SOURCE*old=p->source;p->source=0;func_00134320(&D_003DD490,old);break;}
 case 6:{SOURCE*old=p->source;p->source=0;if(p->actor->category!=1){func_00134320(&D_003DD490,old);if(old->state==1)func_00183B80(old,0);}func_002303A0(p->actor,p->actor->body,2);p->actor->velocity.q=D_002A2DD0.q;break;}
 case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 18:
  func_002303A0(p->actor,p->actor->body,2);p->actor->velocity.q=D_002A2DD0.q;
  if(Less(p->mode,16)&&!Less(p->mode,14)){if(p->actor!=D_002E1E40)func_001CCAC0((SECONDARY*)p->actor->secondary,-1);else func_0018E540(p->actor,-1);}break;
 case 19:case 20:if(Less(newMode,21)&&!Less(newMode,19))break;if(p->actor->effect)func_001F0660(p->actor->effect,0x5F8);func_00140C88(p->actor,0);break;
 case 21:func_0012E460(&p->event);func_002303A0(p->actor,p->actor->body,2);func_001F6860(p->actor,0);break;
 }
 ANIMATION*active=p->actor->animation;CLIP*clip=0;p->mode=newMode;p->source=source;p->time=D_002DDED0.time;int flags=1;float blend=0.0f,weight=1.0f;
 switch(newMode){
 case 17:{flags=9;Notify(p->actor,91);func_00204F78(p->actor,p->link->target,1);w.temp.q=func_0022FC48(p->link->space,0,p->relative.q);
  w.scalar.q=Scalar(-1.0f);w.basis.row[0].q=Scale(p->direction.q,w.scalar.q);func_0011E2D8(w.basis.row[0].q,D_002A2DC0.q,D_002A2DB0.q,(TWO_ROWS*)&w.basis.row[1]);
  ACTOR*actor=p->actor;qword delta=Sub(w.temp.q,Rotate(&w.basis,p->offset.q));w.temp.q=delta;actor->offset.q=Sub(delta,func_001A62E8(actor));ClearVelocity(p->actor);p->flags28=0;clip=p->special154;
  if(p->focused){func_00204DA8(p->actor,p->oldScale);func_00140C88(p->actor,0);p->focused=0;}break;}
 case 0:case 1:case 4:case 5:case 7:
  switch(p->state){case 13:clip=p->special148;break;case 14:clip=p->special158;break;case 16:clip=p->actor->clip1514;break;case 15:clip=p->actor->clip1518;break;}
  if(!clip)clip=p->base[p->variant];if(!clip)clip=p->base[0];break;
 case 2:case 3:if(p->state==14)clip=p->special15C;if(!clip)clip=p->alternate[p->variant];if(!clip)clip=p->alternate[0];if(!clip)clip=p->base[0];p->flags28=0;break;
 case 6:func_002303A0(p->actor,p->actor->body,17);func_00134320(&D_003DD490,source);func_00183B80(source,1);ClearVelocity(p->actor);clip=p->actor->animation->clip;break;
 case 8:func_002303A0(p->actor,p->actor->body,17);ClearVelocity(p->actor);clip=active->clip;break;
 case 11:case 12:case 13:case 14:case 15:
  func_002303A0(p->actor,p->actor->body,17);ClearVelocity(p->actor);p->flags28=0;p->variant=0;clip=p->base[0];
  if(Less(p->mode,16)&&!Less(p->mode,14)){ACTOR*actor=p->actor;if(actor==D_002E1E40){actor->primaryFocus=p->source;func_0018E540(actor,0);}else{actor->secondaryFocus=p->source;weight=0.0f;func_001CCAC0((SECONDARY*)p->actor->secondary,0);clip=p->actor->secondaryClip;blend=clip->duration*0.5f;}}break;
 case 9:case 10:case 16:case 18:{func_002303A0(p->actor,p->actor->body,17);ClearVelocity(p->actor);p->flags28=0;ACTOR*actor=p->actor;VTE&v=actor->vt[35];void*receiver=(char*)actor+v.delta;qword velocity=func_0019A750(p,4);((void(*)(void*,qword))v.fn)(receiver,velocity);p->variant=0;if(p->mode==16)clip=p->special14C;else clip=p->special148;active=0;break;}
 case -1:if(p->focused){func_00204DA8(p->actor,p->oldScale);func_00140C88(p->actor,0);p->focused=0;}p->fieldBC=0;p->state=-1;break;
 case 19:func_00204660(p->actor,p->actor->heading-D_002BF780[p->variant]);p->flags28=0;clip=p->scripted;func_00140C88(p->actor,p->scriptFocus);p->scriptFocus->data->amount=D_002BF798.low*0.5f+D_002BF798.high*0.5f;if(p->actor->effect)func_001F0660(p->actor->effect,0x5F7);break;
 case 20:p->tracks[0].control.bits=0;p->tracks[1].control.bits=0;p->tracks[2].control.bits=0;p->tracks[3].control.bits=0;p->scriptedGain=1.0f;func_001384C0(p->multi);clip=p->multi;flags=9;break;
 case 21:{float minimum=-1000.0f,maximum=-1.0f;w.bodyPosition.q=p->actor->body->position.q;
  if(p->query.object&&(func_00132B10(p->query.object,19)||func_00132B10(p->query.object,11))){minimum=0.0f;maximum=500.0f;}
  w.goal.q=func_0019F3F8(p->actor,&p->query,D_002BF7A0);w.delta.q=Sub(w.goal.q,w.bodyPosition.q);w.acceleration.q=p->actor->motion->acceleration.q;
  maximum=func_00196928(w.delta.q,w.acceleration.q,1000.0f,minimum,1.0f,maximum);maximum=Maximum(D_002BF7A0,maximum);float duration=maximum;w.temp.q=Scalar(duration);qword full=w.temp.q;w.temp.q=Scalar(duration*-0.5f);
  w.velocity.q=AddScaled(Divide(w.delta.q,full),w.acceleration.q,w.temp.q);w.duration.q=full;SetVelocity(p->actor,w.velocity.q);
  w.temp.q=w.duration.q;w.endVelocity.q=AddScaled(w.velocity.q,w.acceleration.q,w.temp.q);float deadline=D_002DDED0.time+duration;
  qword localGoal=func_0022FC48(0,p->actor->body->frame,w.goal.q);qword localEnd=func_0022FCC8(0,p->actor->body->frame,w.endVelocity.q);
  p->event=func_0012DE58(p->actor,p->actor->body,5,deadline,localGoal,localEnd);func_001F6860(p->actor,1);ClearVelocity(p->actor);func_002046B0(p->actor,w.delta.q);clip=p->base[0];break;}
 case 22:clip=p->special1C8;flags=9;break;
 }
 switch(p->mode){case 0:case 2:p->actionFlag=0;break;case 18:func_00134320(&D_003DD490,p->actor);break;}
 if(p->mode!=-1){if(!active||active->clip!=clip){func_001F15B8(&p->actor->component);func_001305B8(clip,p->actor,blend,weight,flags,&p->actor->animation);}Notify(p->actor,90);}
}