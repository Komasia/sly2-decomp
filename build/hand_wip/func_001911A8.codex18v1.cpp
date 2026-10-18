typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;typedef unsigned long ulong;
union U{qword q;float f[4];int i[4];};struct VTE{short delta,pad;void*fn;};struct INPUT{char pad0[0x1C];float amount;char pad20[0x10];uint flags;};struct ANIM;struct COLLISION;struct CONTACT;struct NODE{uint left,right;void*poly;};struct MODEL;struct ARRAY{int count;qword*points;};struct SHAPE{MODEL*model;void*owner;float radius;VTE*vt;ulong flags;char pad18[0x6C-0x18];int capacity;char pad70[4];NODE*tree;char pad78[0x18];ARRAY world;};
struct MOVE;struct CAMERA;struct ACTOR;struct ATTACH{void*scene;char pad4[0x30];ACTOR*actor;char pad38[0x6C];};struct ACTOR{char pad0[12];VTE*vt;char pad10[0xDC];COLLISION*collision;char padF0[0x60];INPUT*input;char pad154[0xEC];U offset;char pad250[0x18];SHAPE*shape;char pad26C[0xF5C-0x26C];void*target;float parameter;char padF64[0xCC];ANIM*animation;char pad1034[0xB8];int special;};
struct CONTEXT{ACTOR*actor;float stamp;int action,step;float hold;ACTOR*focus;char pad18[8];float parameter;char pad24[0x41C];ATTACH attach;char pad4E4[0x1C];int inhibited;};struct FRAME{};struct REQ{int bytes,alignment;};union SCRATCH{U scalar;REQ request;};struct SPAN{U first,last,firstPlane,lastPlane;float from,to;int flags;void*firstFace,*lastFace;};struct WORK{FRAME frame;SPAN spans[8];SCRATCH scratch;int count;SHAPE**objects;CONTACT*contacts;int capacity;NODE*end;int oldStep;U endpoint,low,high,midpoint,position;};struct CLOCK{float time,dt;};struct SCENE;
extern "C"{extern SCENE D_003DD490;extern CLOCK D_002DDED0;extern uint D_002DFBC4;extern U D_002A2DC0;extern float D_002BF5B0,D_002BF5B4,D_002BF5B8;
int func_001C46C0(INPUT*,uint,float);int func_001C4660(INPUT*,uint,float);void func_001C4738(INPUT*,int);void func_00195A00(MOVE*,int,int,ACTOR*);void func_0019CC50(CAMERA*,int,ACTOR*,void*);int func_00131968(ANIM*);void func_00192BD8(CONTEXT*,int);
FRAME*func_001AE478(FRAME*);void func_001AE4A0(FRAME*,int);void*func_001AE318(REQ*);qword func_001A62E8(ACTOR*);int func_0020F948(COLLISION*,SHAPE*);void func_0020FAA0(SCENE*,qword,qword,int(*)(COLLISION*,SHAPE*),COLLISION*,int*,SHAPE***);int func_0014C6A0(SHAPE*,qword,qword,int,SPAN*);void func_001F38A8(SHAPE*);qword func_0011F288(int,qword*);qword func_0011F2B8(int,qword*);void func_001A9B28(SCENE*,SHAPE*,SHAPE*,int,NODE*,CONTACT**);int func_00118A88(NODE*,int,qword,float,int*,NODE**);void func_001A8B50(SCENE*,SHAPE*,SHAPE*,int,NODE*,NODE*,CONTACT**);void FreeSwXpList__FP2SWP2XP(SCENE*,CONTACT*);void func_001CD098(ATTACH*,ACTOR*);int func_00132B10(ACTOR*,int);int func_001423A0(ACTOR*);int func_001441A0(ACTOR*);int func_00141EA8(ACTOR*,int);}
static inline void SetControl(ACTOR*p,int code){VTE&v=p->vt[88];((void(*)(void*,int))v.fn)((char*)p+v.delta,code);}
static inline int Allow(ACTOR*p,int code){VTE&v=p->vt[99];return ((int(*)(void*,int))v.fn)((char*)p+v.delta,code);}
static inline void Use(ACTOR*target,ACTOR*actor){VTE&v=target->vt[51];((void(*)(void*,ACTOR*))v.fn)((char*)target+v.delta,actor);}
static inline qword Vector(qword q){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(q));return v;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Length(qword q){float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf2,%0z":"+j"(q): :"vf2");__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(q));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline int Near(qword a,qword b,float distance){return Length(Sub(a,b))<distance;}
static inline MOVE*Move(ACTOR*p){return (MOVE*)((char*)p+0x2C0);}static inline CAMERA*Camera(ACTOR*p){return(CAMERA*)((char*)p+0xF00);}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char ulong_Size[sizeof(ulong)==8?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char INPUT_Size[sizeof(INPUT)==52?1:-1];
typedef char NODE_Size[sizeof(NODE)==12?1:-1];
typedef char ARRAY_Size[sizeof(ARRAY)==8?1:-1];
typedef char SHAPE_Size[sizeof(SHAPE)==152?1:-1];
typedef char ATTACH_Size[sizeof(ATTACH)==164?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==4336?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==1284?1:-1];
typedef char FRAME_Size[sizeof(FRAME)==1?1:-1];
typedef char REQ_Size[sizeof(REQ)==8?1:-1];
typedef char SCRATCH_Size[sizeof(SCRATCH)==16?1:-1];
typedef char SPAN_Size[sizeof(SPAN)==96?1:-1];
typedef char WORK_Size[sizeof(WORK)==912?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char INPUT_amount_Offset[FIELD_OFFSET(INPUT,amount)==28?1:-1];
typedef char INPUT_flags_Offset[FIELD_OFFSET(INPUT,flags)==48?1:-1];
typedef char NODE_left_Offset[FIELD_OFFSET(NODE,left)==0?1:-1];
typedef char NODE_right_Offset[FIELD_OFFSET(NODE,right)==4?1:-1];
typedef char NODE_poly_Offset[FIELD_OFFSET(NODE,poly)==8?1:-1];
typedef char ARRAY_count_Offset[FIELD_OFFSET(ARRAY,count)==0?1:-1];
typedef char ARRAY_points_Offset[FIELD_OFFSET(ARRAY,points)==4?1:-1];
typedef char SHAPE_model_Offset[FIELD_OFFSET(SHAPE,model)==0?1:-1];
typedef char SHAPE_owner_Offset[FIELD_OFFSET(SHAPE,owner)==4?1:-1];
typedef char SHAPE_radius_Offset[FIELD_OFFSET(SHAPE,radius)==8?1:-1];
typedef char SHAPE_vt_Offset[FIELD_OFFSET(SHAPE,vt)==12?1:-1];
typedef char SHAPE_flags_Offset[FIELD_OFFSET(SHAPE,flags)==16?1:-1];
typedef char SHAPE_capacity_Offset[FIELD_OFFSET(SHAPE,capacity)==108?1:-1];
typedef char SHAPE_tree_Offset[FIELD_OFFSET(SHAPE,tree)==116?1:-1];
typedef char SHAPE_world_Offset[FIELD_OFFSET(SHAPE,world)==144?1:-1];
typedef char ATTACH_scene_Offset[FIELD_OFFSET(ATTACH,scene)==0?1:-1];
typedef char ATTACH_actor_Offset[FIELD_OFFSET(ATTACH,actor)==52?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_collision_Offset[FIELD_OFFSET(ACTOR,collision)==236?1:-1];
typedef char ACTOR_input_Offset[FIELD_OFFSET(ACTOR,input)==336?1:-1];
typedef char ACTOR_offset_Offset[FIELD_OFFSET(ACTOR,offset)==576?1:-1];
typedef char ACTOR_shape_Offset[FIELD_OFFSET(ACTOR,shape)==616?1:-1];
typedef char ACTOR_target_Offset[FIELD_OFFSET(ACTOR,target)==3932?1:-1];
typedef char ACTOR_parameter_Offset[FIELD_OFFSET(ACTOR,parameter)==3936?1:-1];
typedef char ACTOR_animation_Offset[FIELD_OFFSET(ACTOR,animation)==4144?1:-1];
typedef char ACTOR_special_Offset[FIELD_OFFSET(ACTOR,special)==4332?1:-1];
typedef char CONTEXT_actor_Offset[FIELD_OFFSET(CONTEXT,actor)==0?1:-1];
typedef char CONTEXT_stamp_Offset[FIELD_OFFSET(CONTEXT,stamp)==4?1:-1];
typedef char CONTEXT_action_Offset[FIELD_OFFSET(CONTEXT,action)==8?1:-1];
typedef char CONTEXT_step_Offset[FIELD_OFFSET(CONTEXT,step)==12?1:-1];
typedef char CONTEXT_hold_Offset[FIELD_OFFSET(CONTEXT,hold)==16?1:-1];
typedef char CONTEXT_focus_Offset[FIELD_OFFSET(CONTEXT,focus)==20?1:-1];
typedef char CONTEXT_parameter_Offset[FIELD_OFFSET(CONTEXT,parameter)==32?1:-1];
typedef char CONTEXT_attach_Offset[FIELD_OFFSET(CONTEXT,attach)==1088?1:-1];
typedef char CONTEXT_inhibited_Offset[FIELD_OFFSET(CONTEXT,inhibited)==1280?1:-1];
typedef char REQ_bytes_Offset[FIELD_OFFSET(REQ,bytes)==0?1:-1];
typedef char REQ_alignment_Offset[FIELD_OFFSET(REQ,alignment)==4?1:-1];
typedef char SPAN_first_Offset[FIELD_OFFSET(SPAN,first)==0?1:-1];
typedef char SPAN_last_Offset[FIELD_OFFSET(SPAN,last)==16?1:-1];
typedef char SPAN_firstPlane_Offset[FIELD_OFFSET(SPAN,firstPlane)==32?1:-1];
typedef char SPAN_lastPlane_Offset[FIELD_OFFSET(SPAN,lastPlane)==48?1:-1];
typedef char SPAN_from_Offset[FIELD_OFFSET(SPAN,from)==64?1:-1];
typedef char SPAN_to_Offset[FIELD_OFFSET(SPAN,to)==68?1:-1];
typedef char SPAN_flags_Offset[FIELD_OFFSET(SPAN,flags)==72?1:-1];
typedef char SPAN_firstFace_Offset[FIELD_OFFSET(SPAN,firstFace)==76?1:-1];
typedef char SPAN_lastFace_Offset[FIELD_OFFSET(SPAN,lastFace)==80?1:-1];
typedef char WORK_frame_Offset[FIELD_OFFSET(WORK,frame)==0?1:-1];
typedef char WORK_spans_Offset[FIELD_OFFSET(WORK,spans)==16?1:-1];
typedef char WORK_scratch_Offset[FIELD_OFFSET(WORK,scratch)==784?1:-1];
typedef char WORK_count_Offset[FIELD_OFFSET(WORK,count)==800?1:-1];
typedef char WORK_objects_Offset[FIELD_OFFSET(WORK,objects)==804?1:-1];
typedef char WORK_contacts_Offset[FIELD_OFFSET(WORK,contacts)==808?1:-1];
typedef char WORK_capacity_Offset[FIELD_OFFSET(WORK,capacity)==812?1:-1];
typedef char WORK_end_Offset[FIELD_OFFSET(WORK,end)==816?1:-1];
typedef char WORK_oldStep_Offset[FIELD_OFFSET(WORK,oldStep)==820?1:-1];
typedef char WORK_endpoint_Offset[FIELD_OFFSET(WORK,endpoint)==832?1:-1];
typedef char WORK_low_Offset[FIELD_OFFSET(WORK,low)==848?1:-1];
typedef char WORK_high_Offset[FIELD_OFFSET(WORK,high)==864?1:-1];
typedef char WORK_midpoint_Offset[FIELD_OFFSET(WORK,midpoint)==880?1:-1];
typedef char WORK_position_Offset[FIELD_OFFSET(WORK,position)==896?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
static inline qword Read128(U*p){qword q;__asm__("lq %0,%1":"=r"(q):"m"(p->q));return q;}
extern "C" void func_001911A8(CONTEXT*argument){register CONTEXT*p __asm__("$19")=argument;WORK w;INPUT*input=p->actor->input;
 for(;;){
 register int previous __asm__("$3")=p->step;
 register int action __asm__("$2");
 __asm__("lw %0,%2\n\tsw %3,%1":"=r"(action),"=m"(w.oldStep):"m"(p->action),"r"(previous));
 register int savedStep __asm__("$5")=w.oldStep;
 switch(action){
 case 1:if(0.15f<D_002DDED0.time-p->hold&&func_001C46C0(input,0x40,0.25f)){func_00195A00(Move(p->actor),7,0,p->focus);break;}camera_input:if(func_001C4660(input,0x400,0.15f)&&Allow(p->actor,3)){func_001C4738(input,0x400);func_0019CC50(Camera(p->actor),0,0,0);}break;
 case 3:case 4:if(func_001C46C0(input,0x40,0.1f))goto move_one;goto camera_input;
 case 7:{ACTOR*focus=p->focus;SetControl(p->actor,0);Use(focus,p->actor);break;}
 case 8:{
  if(savedStep==7)goto step_seven;
  if(savedStep==8)goto step_eight;
  goto collision_query;
 step_seven:if(func_00131968(p->actor->animation))func_00192BD8(p,9);break;
 step_eight:if(func_00131968(p->actor->animation))SetControl(p->actor,0);break;
 collision_query:
  (void)func_001AE478(&w.frame);
  {

   int i=0;
   qword position=func_001A62E8(p->actor);
   register ACTOR*actor __asm__("$5")=p->actor;
   register COLLISION*collision __asm__("$8");qword base;register qword up __asm__("vf1");
   register qword factor __asm__("vf3");
   __asm__("lui $3,%%hi(%6)\n\tlui $4,%%hi(%7)\n\tlw $3,%%lo(%6)($3)\n\taddiu $4,$4,%%lo(%7)\n\tlqc2 %0,%4\n\tlqc2 $vf1,0($4)\n\tqmtc2.ni $3,%2\n\tqmtc2.ni %5,$vf4\n\tvmulx.xyzw $vf1,$vf1,%2x\n\tvadd.xyzw %0,$vf4,%0\n\tlw %1,%8":"=j"(base),"=r"(collision),"=j"(factor),"=j"(up):"m"(actor->offset.q),"r"(position),"i"(&D_002BF5B0),"i"(&D_002A2DC0),"m"(actor->collision):"$3","$4","vf4","memory");
   register qword endpoint __asm__("vf4");
   __asm__("vadd.xyzw %0,%1,%2":"=j"(endpoint):"j"(base),"j"(up));
   *(volatile qword*)&w.endpoint.q=endpoint;
   register int*count __asm__("$9")=&w.count;register SHAPE***objects __asm__("$10")=&w.objects;
   register int*countSaved __asm__("$20")=count;register SHAPE***objectsSaved __asm__("$22")=objects;
   *(volatile qword*)&w.scratch.scalar.q=factor;
   register qword endpointArgument __asm__("$5");
   __asm__("lq %0,%1":"=r"(endpointArgument):"m"(w.endpoint.q));
   func_0020FAA0(&D_003DD490,endpointArgument,base,func_0020F948,collision,count,objects);
   for(;i<w.count;i++){int spans=func_0014C6A0(w.objects[i],base,w.endpoint.q,8,w.spans);for(int j=0;j<spans;j++){if(w.spans[j].from!=0.0f)goto arena_done;}}
   SHAPE*shape=p->actor->shape;ARRAY*world=&shape->world;func_001F38A8(shape);w.low.q=func_0011F288(world->count,world->points);w.high.q=func_0011F2B8(world->count,world->points);
   func_0020FAA0(&D_003DD490,Read128(&w.low),Read128(&w.high),func_0020F948,p->actor->collision,countSaved,objectsSaved);
   int maximum=0;if(w.count>0){i=w.count;SHAPE**objects=w.objects;do{SHAPE*object=*objects++;if(!(object->capacity<maximum))maximum=object->capacity;}while(--i);}

   register int boundary __asm__("$2"),limit __asm__("$4");
   __asm__("addiu %0,$zero,0x1554\n\taddiu %1,$zero,0x1555":"=r"(boundary),"=r"(limit));
   if(boundary<maximum)maximum=limit;
   register REQ*request __asm__("$6")=&w.scratch.request;
   register int bytes __asm__("$3")=sizeof(NODE)*maximum;
   register int alignment __asm__("$5")=16;
   request->bytes=bytes;request->alignment=alignment;i=0;
   NODE*nodes=(NODE*)func_001AE318(request);
   register qword half __asm__("vf2"),midpoint __asm__("vf1");
   __asm__(".set noat\n\tlui $1,0x3f00\n\tmtc1 $1,$f0\n\t.set at\n\tlqc2 %1,%2\n\tmfc1 $2,$f0\n\tqmtc2.ni $2,%0\n\tlqc2 $vf3,%3\n\tvmulax.xyzw ACC,%1,%0x\n\tvmaddx.xyzw %1,$vf3,%0x":"=j"(half),"=j"(midpoint):"m"(w.low.q),"m"(w.high.q):"$1","$2","$f0","vf3");
   *(volatile qword*)&w.scratch.scalar.q=half;
   *(volatile qword*)&w.midpoint.q=midpoint;
   register int foundCount __asm__("$2");register float radius __asm__("$f20");
   __asm__("lqc2 $vf2,%2\n\tlw %0,%3\n\tlqc2 $vf4,%4\n\tvsub.xyzw $vf1,$vf4,$vf2\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tqmfc2.ni $3,$vf1\n\tmtc1 $3,%1":"=r"(foundCount),"=f"(radius):"m"(w.low.q),"m"(w.count),"m"(w.midpoint.q):"$3","vf1","vf2","vf4");
   for(int available=foundCount;i<available;available=w.count){SHAPE*object=w.objects[i];w.contacts=0;
    if(object->flags&(1UL<<49))func_001A9B28(&D_003DD490,object,shape,0,0,&w.contacts);
    else{w.capacity=maximum;w.end=nodes;int result=func_00118A88(object->tree,0x7FFFFFFF,w.midpoint.q,radius,&w.capacity,&w.end);if(result==2){int count=w.end-nodes;--w.end;func_001A8B50(&D_003DD490,shape,object,count,object->tree,w.end,&w.contacts);}}
    if(w.contacts)goto free_contacts;
    ++i;
   }
   func_00192BD8(p,8);
  }
  goto arena_done;
 }
 case 9:w.position.q=Vector(func_001A62E8(p->focus));if(Near(w.position.q,Vector(func_001A62E8(p->attach.actor)),D_002BF5B4)){func_001CD098(&p->attach,p->focus);SetControl(p->actor,0);}break;
 case 10:if(!p->actor->animation||func_00131968(p->actor->animation))SetControl(p->actor,0);else if(D_002BF5B8<D_002DDED0.time-p->stamp){if(0.0f<p->actor->input->amount||(p->actor->input->flags&0xD0)){SetControl(p->actor,0);return;}}break;
 case 11:case 12:if(!p->actor->animation||func_00131968(p->actor->animation))SetControl(p->actor,0);break;
 case 5:if(func_00132B10(p->focus,11)&&func_001423A0(p->actor)){p->actor->target=p->focus;p->actor->parameter=p->parameter;SetControl(p->actor,8);}break;
 case 2:if(func_001441A0(p->actor)<=0)goto disable_control;
  if(p->actor->special==4){SetControl(p->actor,0);break;}
  if(D_002DFBC4&1)break;
  {uint mask=func_00141EA8(p->actor,0x28);if(input->flags&mask)break;}
 disable_control:SetControl(p->actor,0);break;
 case 6:default:if(func_001C46C0(input,0x40,0.1f)){move_one:func_00195A00(Move(p->actor),1,0,0);break;}if(func_001C4660(input,0x400,0.15f)&&Allow(p->actor,3)){if(p->action==0||p->action==13){camera_commit:func_001C4738(input,0x400);func_0019CC50(Camera(p->actor),0,0,0);break;}}goto default_control;
 free_contacts:FreeSwXpList__FP2SWP2XP(&D_003DD490,w.contacts);
 arena_done:func_001AE4A0(&w.frame,2);break;
 default_control:if(p->inhibited)break;if(D_002DFBC4&1)break;if(input->flags&0x20)break;SetControl(p->actor,0);break;
 }
 if(p->step==w.oldStep||p->step==-1)break;
 }
}
