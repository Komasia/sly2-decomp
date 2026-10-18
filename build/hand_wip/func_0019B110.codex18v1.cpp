
typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;
union U{qword q;float f[4];int i[4];};struct VTE{short delta,pad;void*fn;};struct ACTOR;struct OBJECT;struct COLLISION;struct SPACE;struct CONTROL;struct CURVE;struct HELPER_E0;struct MOVE;
struct PHYSICS{char pad0[0x80];U gravity;};struct BODY{char pad0[0xA8];float deadline;char padAC[0x14];U goal,velocity;};
struct ACTOR{char pad0[0xC];VTE*vt;char pad10[0x48];BODY*body;char pad5C[0x8C];PHYSICS*physics;COLLISION*collision;char padF0[0x128];U*attachedPosition;char pad21C[0x24];U offset;char pad250[0xDB0];uint mask;char pad1004[0x3CC];int partnerMode;char pad13D4[0x540];int inactive;char pad1918[4];OBJECT*target;char pad1920[0x610];float radius;};
struct MOVE{ACTOR*actor;char pad4[12];float parameter,value;char pad18[0xA4];OBJECT*previousTarget;};
class WRITER{public:char pad0[8];float height;char padC[0x10];uint mask;virtual void f1();virtual void f2();virtual void f3(ACTOR*,U*,void*,float);};class PREFIX_E0{public:char bytes[0xE0];};class PREFIX_190{public:char bytes[0x190];};
struct HELPER_E0:PREFIX_E0,WRITER{HELPER_E0*next;float parameterA,parameterB;};struct CURVE:PREFIX_190,WRITER{CURVE*next;float parameterA,parameterB;};
struct OBJECT{char pad0[0xC];VTE*vt;char pad10[0xD0];OBJECT*next;char padE4[4];uint flags;char padEC[0x1C];float height;char pad10C[0x10];uint mask;};
struct I3{int index[3];};struct MESH{char pad0[0xC];VTE*vt;char pad10[0xD4];U*vertices;int count;I3*triangles;char padF0[0x10];MESH*next;char pad104[4];float height;};struct TRIREF{int index;float u,v;};
struct FILTERSET{int count;COLLISION**objects;};typedef int(*FILTER)(void*,void*);typedef float(*SCORE)(void*,float);
struct SPLINEARG{CONTROL*control;MOVE*move;CURVE*curve;int padC;U velocity;};struct ARG{MOVE*move;void*object;int pad8[2];U vector;};
union SCRATCH{SPLINEARG spline;ARG first;struct{U prefix;ARG second;}nested;struct{ARG argument;U delta,sample;}point;struct{COLLISION*objects[2];char pad8[8];FILTERSET set;}filter;TRIREF triangle;U v[4];};
struct WORK{U position,initialVelocity,point,bestPoint,velocity,bestVelocity;TRIREF selectedTriangle;U predictVelocity,tempPoint;SCRATCH scratch;float duration,score,curveStart,curveTime,meshScore,currentDistance,bestDistance,distanceScore,pointParameter,curveDistance,curveParameter;};struct CLOCK{float time,dt;};
extern "C"{
extern ACTOR*D_002F7900;extern CLOCK D_002DDED0;extern U D_002A2DD0;extern float D_002A65B8,D_002A65BC;extern float D_002BF8E0,D_002BF8E4,D_002BF8E8,D_002BF8EC,D_002BF8F0,D_002BF8F4,D_002BF8F8,D_002BF8FC,D_002BF904,D_002BF908,D_002BF90C,D_002BF914,D_002BF918;
extern HELPER_E0*D_003E13D8,*D_003E13FC,*D_003E1408;extern CURVE*D_003E13CC,*D_003E13C0,*D_003E13F0;extern OBJECT*D_003E13B4;extern MESH*D_003E142C;
qword func_001A62E8(void*);qword func_0019A750(MOVE*,int);void*func_002333B4(void*,int,uint);int func_00132B10(void*,int);
void func_0019A4A0(MOVE*,qword,void*,qword,qword,float*,float*,U*,U*);int func_0019AE00(MOVE*,FILTER,void*,float,qword,qword,qword,qword,U*);int func_0020F948(void*,void*);int func_0019B0A8(void*,void*);float func_0019B088(MOVE*,void*,float,float);
void func_001E6F60(CURVE*,qword,SPACE*,U*,U*,float*,float*);void func_001E7410(CURVE*,SCORE,void*,U*,U*,float*,float*);float func_001E77E8(CURVE*),func_001E6648(CURVE*);float func_001E64C8(CURVE*,float),func_001E63C0(CURVE*,float);void func_0011D9E0(SCORE,void*,float,float,float,float,float*,float*);float func_0019AA58(void*,float),func_0019ABB8(void*,float),func_0019ABF0(void*,float),func_0019AC88(void*,float),func_0019AAB8(void*,float),func_0019AB38(void*,float);
void func_00193A68(CONTROL*,CURVE*,U*,U*,float);void func_0019C300(MOVE*,void*,qword,float*,U*,U*,float);void func_00185310(MESH*,qword,void*,TRIREF*,U*,U*);int func_00185D18(MESH*,qword,qword,qword,float,float,TRIREF*,U*,U*);void func_001E6F10(CURVE*,float,U*,U*);qword func_001A6F00(SPACE*,void*,qword);float func_002458F0(float,float);void func_00195FB8(MOVE*,int,void*);
}
static inline qword Read(U*p){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(*p));return q;}
static inline void Store(U*p,qword q){__asm__("sqc2 %1,%0":"=m"(*p):"j"(q));}
static inline qword Add(qword a,qword b){qword q;__asm__("vadd.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Square(qword a){qword q,k;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(q),"=&j"(k):"0"(a));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline float Length(qword a){qword q,k;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(q),"=&j"(k):"0"(a));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(q));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword Velocity(ACTOR*p){VTE&v=p->vt[33];return ((qword(*)(void*))v.fn)((char*)p+v.delta);}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char PHYSICS_Size[sizeof(PHYSICS)==144?1:-1];
typedef char BODY_Size[sizeof(BODY)==224?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==8000?1:-1];
typedef char MOVE_Size[sizeof(MOVE)==192?1:-1];
typedef char WRITER_Size[sizeof(WRITER)==36?1:-1];
typedef char PREFIX_E0_Size[sizeof(PREFIX_E0)==224?1:-1];
typedef char PREFIX_190_Size[sizeof(PREFIX_190)==400?1:-1];
typedef char HELPER_E0_Size[sizeof(HELPER_E0)==272?1:-1];
typedef char CURVE_Size[sizeof(CURVE)==448?1:-1];
typedef char OBJECT_Size[sizeof(OBJECT)==288?1:-1];
typedef char I3_Size[sizeof(I3)==12?1:-1];
typedef char MESH_Size[sizeof(MESH)==268?1:-1];
typedef char TRIREF_Size[sizeof(TRIREF)==12?1:-1];
typedef char FILTERSET_Size[sizeof(FILTERSET)==8?1:-1];
typedef char SPLINEARG_Size[sizeof(SPLINEARG)==32?1:-1];
typedef char ARG_Size[sizeof(ARG)==32?1:-1];
typedef char SCRATCH_Size[sizeof(SCRATCH)==64?1:-1];
typedef char WORK_Size[sizeof(WORK)==256?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char U_f_Offset[FIELD_OFFSET(U,f)==0?1:-1];
typedef char U_i_Offset[FIELD_OFFSET(U,i)==0?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char PHYSICS_gravity_Offset[FIELD_OFFSET(PHYSICS,gravity)==128?1:-1];
typedef char BODY_deadline_Offset[FIELD_OFFSET(BODY,deadline)==168?1:-1];
typedef char BODY_goal_Offset[FIELD_OFFSET(BODY,goal)==192?1:-1];
typedef char BODY_velocity_Offset[FIELD_OFFSET(BODY,velocity)==208?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_body_Offset[FIELD_OFFSET(ACTOR,body)==88?1:-1];
typedef char ACTOR_physics_Offset[FIELD_OFFSET(ACTOR,physics)==232?1:-1];
typedef char ACTOR_collision_Offset[FIELD_OFFSET(ACTOR,collision)==236?1:-1];
typedef char ACTOR_attachedPosition_Offset[FIELD_OFFSET(ACTOR,attachedPosition)==536?1:-1];
typedef char ACTOR_offset_Offset[FIELD_OFFSET(ACTOR,offset)==576?1:-1];
typedef char ACTOR_mask_Offset[FIELD_OFFSET(ACTOR,mask)==4096?1:-1];
typedef char ACTOR_partnerMode_Offset[FIELD_OFFSET(ACTOR,partnerMode)==5072?1:-1];
typedef char ACTOR_inactive_Offset[FIELD_OFFSET(ACTOR,inactive)==6420?1:-1];
typedef char ACTOR_target_Offset[FIELD_OFFSET(ACTOR,target)==6428?1:-1];
typedef char ACTOR_radius_Offset[FIELD_OFFSET(ACTOR,radius)==7984?1:-1];
typedef char MOVE_actor_Offset[FIELD_OFFSET(MOVE,actor)==0?1:-1];
typedef char MOVE_parameter_Offset[FIELD_OFFSET(MOVE,parameter)==16?1:-1];
typedef char MOVE_value_Offset[FIELD_OFFSET(MOVE,value)==20?1:-1];
typedef char MOVE_previousTarget_Offset[FIELD_OFFSET(MOVE,previousTarget)==188?1:-1];
typedef char WRITER_height_Offset[FIELD_OFFSET(WRITER,height)==8?1:-1];
typedef char WRITER_mask_Offset[FIELD_OFFSET(WRITER,mask)==28?1:-1];
typedef char HELPER_E0_height_Offset[sizeof(PREFIX_E0)+FIELD_OFFSET(WRITER,height)==232?1:-1];
typedef char HELPER_E0_mask_Offset[sizeof(PREFIX_E0)+FIELD_OFFSET(WRITER,mask)==252?1:-1];
typedef char HELPER_E0_next_Offset[FIELD_OFFSET(HELPER_E0,next)==260?1:-1];
typedef char HELPER_E0_parameterA_Offset[FIELD_OFFSET(HELPER_E0,parameterA)==264?1:-1];
typedef char HELPER_E0_parameterB_Offset[FIELD_OFFSET(HELPER_E0,parameterB)==268?1:-1];
typedef char CURVE_height_Offset[sizeof(PREFIX_190)+FIELD_OFFSET(WRITER,height)==408?1:-1];
typedef char CURVE_mask_Offset[sizeof(PREFIX_190)+FIELD_OFFSET(WRITER,mask)==428?1:-1];
typedef char CURVE_next_Offset[FIELD_OFFSET(CURVE,next)==436?1:-1];
typedef char CURVE_parameterA_Offset[FIELD_OFFSET(CURVE,parameterA)==440?1:-1];
typedef char CURVE_parameterB_Offset[FIELD_OFFSET(CURVE,parameterB)==444?1:-1];
typedef char OBJECT_vt_Offset[FIELD_OFFSET(OBJECT,vt)==12?1:-1];
typedef char OBJECT_next_Offset[FIELD_OFFSET(OBJECT,next)==224?1:-1];
typedef char OBJECT_flags_Offset[FIELD_OFFSET(OBJECT,flags)==232?1:-1];
typedef char OBJECT_height_Offset[FIELD_OFFSET(OBJECT,height)==264?1:-1];
typedef char OBJECT_mask_Offset[FIELD_OFFSET(OBJECT,mask)==284?1:-1];
typedef char I3_index_Offset[FIELD_OFFSET(I3,index)==0?1:-1];
typedef char MESH_vt_Offset[FIELD_OFFSET(MESH,vt)==12?1:-1];
typedef char MESH_vertices_Offset[FIELD_OFFSET(MESH,vertices)==228?1:-1];
typedef char MESH_count_Offset[FIELD_OFFSET(MESH,count)==232?1:-1];
typedef char MESH_triangles_Offset[FIELD_OFFSET(MESH,triangles)==236?1:-1];
typedef char MESH_next_Offset[FIELD_OFFSET(MESH,next)==256?1:-1];
typedef char MESH_height_Offset[FIELD_OFFSET(MESH,height)==264?1:-1];
typedef char TRIREF_index_Offset[FIELD_OFFSET(TRIREF,index)==0?1:-1];
typedef char TRIREF_u_Offset[FIELD_OFFSET(TRIREF,u)==4?1:-1];
typedef char TRIREF_v_Offset[FIELD_OFFSET(TRIREF,v)==8?1:-1];
typedef char FILTERSET_count_Offset[FIELD_OFFSET(FILTERSET,count)==0?1:-1];
typedef char FILTERSET_objects_Offset[FIELD_OFFSET(FILTERSET,objects)==4?1:-1];
typedef char SPLINEARG_control_Offset[FIELD_OFFSET(SPLINEARG,control)==0?1:-1];
typedef char SPLINEARG_move_Offset[FIELD_OFFSET(SPLINEARG,move)==4?1:-1];
typedef char SPLINEARG_curve_Offset[FIELD_OFFSET(SPLINEARG,curve)==8?1:-1];
typedef char SPLINEARG_velocity_Offset[FIELD_OFFSET(SPLINEARG,velocity)==16?1:-1];
typedef char ARG_move_Offset[FIELD_OFFSET(ARG,move)==0?1:-1];
typedef char ARG_object_Offset[FIELD_OFFSET(ARG,object)==4?1:-1];
typedef char ARG_vector_Offset[FIELD_OFFSET(ARG,vector)==16?1:-1];
typedef char SCRATCH_spline_Offset[FIELD_OFFSET(SCRATCH,spline)==0?1:-1];
typedef char SCRATCH_first_Offset[FIELD_OFFSET(SCRATCH,first)==0?1:-1];
typedef char SCRATCH_nested_Offset[FIELD_OFFSET(SCRATCH,nested)==0?1:-1];
typedef char SCRATCH_point_Offset[FIELD_OFFSET(SCRATCH,point)==0?1:-1];
typedef char SCRATCH_filter_Offset[FIELD_OFFSET(SCRATCH,filter)==0?1:-1];
typedef char SCRATCH_triangle_Offset[FIELD_OFFSET(SCRATCH,triangle)==0?1:-1];
typedef char SCRATCH_v_Offset[FIELD_OFFSET(SCRATCH,v)==0?1:-1];
typedef char WORK_position_Offset[FIELD_OFFSET(WORK,position)==0?1:-1];
typedef char WORK_initialVelocity_Offset[FIELD_OFFSET(WORK,initialVelocity)==16?1:-1];
typedef char WORK_point_Offset[FIELD_OFFSET(WORK,point)==32?1:-1];
typedef char WORK_bestPoint_Offset[FIELD_OFFSET(WORK,bestPoint)==48?1:-1];
typedef char WORK_velocity_Offset[FIELD_OFFSET(WORK,velocity)==64?1:-1];
typedef char WORK_bestVelocity_Offset[FIELD_OFFSET(WORK,bestVelocity)==80?1:-1];
typedef char WORK_selectedTriangle_Offset[FIELD_OFFSET(WORK,selectedTriangle)==96?1:-1];
typedef char WORK_predictVelocity_Offset[FIELD_OFFSET(WORK,predictVelocity)==112?1:-1];
typedef char WORK_tempPoint_Offset[FIELD_OFFSET(WORK,tempPoint)==128?1:-1];
typedef char WORK_scratch_Offset[FIELD_OFFSET(WORK,scratch)==144?1:-1];
typedef char WORK_duration_Offset[FIELD_OFFSET(WORK,duration)==208?1:-1];
typedef char WORK_score_Offset[FIELD_OFFSET(WORK,score)==212?1:-1];
typedef char WORK_curveStart_Offset[FIELD_OFFSET(WORK,curveStart)==216?1:-1];
typedef char WORK_curveTime_Offset[FIELD_OFFSET(WORK,curveTime)==220?1:-1];
typedef char WORK_meshScore_Offset[FIELD_OFFSET(WORK,meshScore)==224?1:-1];
typedef char WORK_currentDistance_Offset[FIELD_OFFSET(WORK,currentDistance)==228?1:-1];
typedef char WORK_bestDistance_Offset[FIELD_OFFSET(WORK,bestDistance)==232?1:-1];
typedef char WORK_distanceScore_Offset[FIELD_OFFSET(WORK,distanceScore)==236?1:-1];
typedef char WORK_pointParameter_Offset[FIELD_OFFSET(WORK,pointParameter)==240?1:-1];
typedef char WORK_curveDistance_Offset[FIELD_OFFSET(WORK,curveDistance)==244?1:-1];
typedef char WORK_curveParameter_Offset[FIELD_OFFSET(WORK,curveParameter)==248?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
extern "C" void func_0019B110(MOVE*p,void*forced){
 WORK w;void*selected=0;int mode=-1;float auxiliary=0,parameter=0;
 w.position.q=func_001A62E8(p->actor);w.initialVelocity.q=Velocity(p->actor);uint mask=p->actor->mask;
 // The native triangle home is zeroed/copied without any later read.
 (void)func_002333B4(&w.selectedTriangle,0,12);
 float best=forced?D_002A65B8:D_002A65BC;w.predictVelocity.q=func_0019A750(p,4);float selectedDuration=0;
 if(func_00132B10(p->actor,53)){
  for(HELPER_E0*node=D_003E13D8;node;node=(HELPER_E0*)node->next){
   if(!(node->mask&mask))continue;
   node->f3(p->actor,&w.tempPoint,0,0);
   if(node!=forced&&node->height<w.position.f[2]-w.tempPoint.f[2])continue;
   func_0019A4A0(p,w.predictVelocity.q,node,w.tempPoint.q,D_002A2DD0.q,&w.duration,&w.score,&w.point,&w.velocity);
   w.velocity.f[2]=w.predictVelocity.f[2]+w.duration*p->actor->physics->gravity.f[2];
   if(node!=forced){if(D_002BF8E0<=w.score)continue;w.score=func_0019B088(p,node,w.score,D_002BF8E4);if(best<=w.score)continue;
    if(func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.predictVelocity.q,w.point.q,w.velocity.q,0))continue;
   }
   w.bestPoint.q=w.point.q;w.bestVelocity.q=w.velocity.q;mode=9;selected=node;best=Min(best,w.score);selectedDuration=w.duration;
  }
  for(CURVE*node=D_003E13CC;node;node=(CURVE*)node->next){
   if(!(node->mask&mask))continue;
   if(node!=forced){func_001E6F60(node,p->actor->attachedPosition->q,0,&w.tempPoint,0,0,0);if(node->height<w.position.f[2]-w.tempPoint.f[2])continue;}
   w.scratch.spline.control=(CONTROL*)((char*)p->actor+0x4C0);w.scratch.spline.move=(MOVE*)((char*)p->actor+0x2C0);w.scratch.spline.curve=node;w.scratch.spline.velocity.q=w.predictVelocity.q;
   func_001E7410(node,func_0019AA58,&w.scratch.spline,0,0,&w.curveStart,0);
   float start=w.curveStart,step=func_001E77E8(node),low=func_001E64C8(node,50.0f),high=func_001E64C8(node,func_001E6648(node)-50.0f);
   func_0011D9E0(func_0019AA58,&w.scratch.spline,start,step,low,high,&w.curveTime,&w.score);
   if(node!=forced){if(D_002BF8E0<=w.score)continue;w.score=func_0019B088(p,node,w.score,D_002BF8E8);if(best<=w.score)continue;}
   func_00193A68(w.scratch.spline.control,node,&w.tempPoint,&w.scratch.v[2],w.curveTime);
   func_0019A4A0(p,w.predictVelocity.q,node,w.tempPoint.q,w.scratch.v[2].q,&w.duration,0,&w.point,&w.velocity);
   w.velocity.f[2]=w.predictVelocity.f[2]+w.duration*p->actor->physics->gravity.f[2];
   if(node!=forced&&func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.predictVelocity.q,w.point.q,w.velocity.q,0))continue;
   selected=node;best=Min(best,w.score);parameter=w.curveTime;mode=10;w.bestPoint.q=w.point.q;w.bestVelocity.q=w.velocity.q;selectedDuration=w.duration;auxiliary=func_001E63C0(node,parameter);
  }
  for(OBJECT*node=D_003E13B4;node;node=node->next){
   if(node!=forced){if(forced)continue;if((node->flags&1)==0)continue;if(!func_00132B10(node,19))continue;}
   if(!(node->mask&mask))continue;
   Store(&w.tempPoint,func_001A62E8(node));
   if(node!=forced){if(node->height<w.position.f[2]-w.tempPoint.f[2])continue;if(1000000.0f<Square(Sub(Read(&w.tempPoint),Read(&w.position))))continue;}
   w.scratch.first.vector.q=D_002A2DD0.q;w.scratch.first.move=p;w.scratch.first.object=node;
   func_0011D9E0(func_0019ABB8,&w.scratch.first,0.5f,0.25f,0.25f,3.0f,&w.duration,&w.score);
   func_0019C300(w.scratch.first.move,w.scratch.first.object,w.scratch.first.vector.q,0,&w.point,&w.velocity,w.duration);
   if(node!=forced){if(D_002BF8E0<=w.score)continue;w.score=func_0019B088(p,node,w.score,D_002BF8EC);if(best<=w.score)continue;
    if(func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.initialVelocity.q,w.point.q,w.velocity.q,&w.tempPoint))continue;
   }
   Store(&w.bestPoint,Add(Read(&w.point),Read(&p->actor->offset)));mode=14;selected=node;w.bestVelocity.q=w.velocity.q;best=Min(w.score,best);selectedDuration=w.duration;
  }
  for(MESH*node=D_003E142C;node;node=node->next){
   func_00185310(node,w.position.q,0,0,&w.tempPoint,0);
   if(node!=forced){if(node->height<w.position.f[2]-w.tempPoint.f[2])continue;if(1000.0f<Length(Sub(Read(&w.tempPoint),Read(&w.position))))continue;}
   w.scratch.nested.second.vector.q=w.predictVelocity.q;w.scratch.nested.second.move=p;w.scratch.nested.second.object=node;
   func_0011D9E0(func_0019AC88,&w.scratch.nested.second,1.0f,0.25f,0.25f,2.0f,&w.duration,&w.meshScore);
   if(node!=forced){if(D_002BF8E0<=w.meshScore)continue;w.meshScore=func_0019B088(p,node,w.meshScore,D_002BF908);if(best<=w.meshScore)continue;}
   (void)func_00185D18(node,w.position.q,w.predictVelocity.q,p->actor->physics->gravity.q,p->actor->radius,w.duration,&w.scratch.triangle,&w.point,&w.velocity);
   if(node!=forced&&func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.initialVelocity.q,w.point.q,w.velocity.q,0))continue;
   Store(&w.bestPoint,Add(Read(&w.point),Read(&p->actor->offset)));mode=16;selected=node;w.bestVelocity.q=w.velocity.q;best=Min(w.meshScore,best);selectedDuration=w.duration;__asm__ __volatile__("ldl $3,7+%1\n\tldr $3,%1\n\tlw $4,8+%1\n\tsdl $3,7+%0\n\tsdr $3,%0\n\tsw $4,8+%0":"=m"(w.selectedTriangle):"m"(w.scratch.triangle):"$3","$4");
  }
 }
 if(func_00132B10(p->actor,55)&&D_002F7900&&D_002F7900->partnerMode==15&&!D_002F7900->inactive){
  w.tempPoint.q=func_001A62E8(D_002F7900->target);
  func_0019A4A0(p,w.predictVelocity.q,D_002F7900->target,w.tempPoint.q,D_002A2DD0.q,&w.duration,&w.score,&w.point,&w.velocity);
  w.velocity.f[2]=w.predictVelocity.f[2]+w.duration*p->actor->physics->gravity.f[2];
  if(D_002F7900->target==forced)goto partnerAccepted;
  if(D_002BF8E0<=w.score)goto partnerDone;
  w.score=func_0019B088(p,D_002F7900,w.score,D_002BF904);if(best<=w.score)goto partnerDone;
  w.scratch.filter.objects[0]=p->actor->collision;w.scratch.filter.objects[1]=D_002F7900->collision;w.scratch.filter.set.count=2;w.scratch.filter.set.objects=w.scratch.filter.objects;
  if(func_0019AE00(p,func_0019B0A8,&w.scratch.filter.set,w.duration,w.position.q,w.predictVelocity.q,w.point.q,w.velocity.q,0))goto partnerDone;
 partnerAccepted:
  w.bestPoint.q=w.point.q;mode=18;w.bestVelocity.q=w.velocity.q;selected=D_002F7900->target;selectedDuration=w.duration;best=Min(best,w.score);
 }
 partnerDone:
 for(CURVE*node=D_003E13C0;node;node=(CURVE*)node->next){
  if(!(node->mask&p->actor->mask))continue;
  func_001E6F60(node,w.position.q,0,&w.tempPoint,0,0,&w.currentDistance);
  if(node!=forced){if(node->height<w.position.f[2]-w.tempPoint.f[2])continue;if(1000.0f<Length(Sub(Read(&w.tempPoint),Read(&w.position))))continue;}
  float start=w.currentDistance;w.scratch.first.move=p;w.scratch.first.object=node;
  float high=func_001E6648(node)-50.0f;
  func_0011D9E0(func_0019ABF0,&w.scratch.first,start,100.0f,50.0f,high,&w.bestDistance,&w.distanceScore);
  if(node!=forced){if(D_002BF8E0<=w.distanceScore)continue;w.distanceScore=func_0019B088(p,node,w.distanceScore,D_002BF8F0);if(best<=w.distanceScore)continue;}
  w.scratch.nested.second.move=p;w.scratch.nested.second.object=node;
  func_001E6F10(node,w.bestDistance,&w.tempPoint,0);w.scratch.nested.second.vector.q=func_001A6F00(0,node,w.tempPoint.q);
  func_0011D9E0(func_0019ABB8,&w.scratch.nested.second,0.5f,0.25f,0.25f,3.0f,&w.duration,0);
  func_0019C300(w.scratch.nested.second.move,w.scratch.nested.second.object,w.scratch.nested.second.vector.q,0,&w.point,&w.velocity,w.duration);
  if(node!=forced&&func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.initialVelocity.q,w.point.q,w.velocity.q,&w.tempPoint))continue;
  Store(&w.bestPoint,Add(Read(&w.point),Read(&p->actor->offset)));mode=15;selected=node;w.bestVelocity.q=w.velocity.q;best=Min(w.distanceScore,best);selectedDuration=w.duration;auxiliary=w.bestDistance;
 }
 for(HELPER_E0*node=D_003E13FC;node;node=(HELPER_E0*)node->next){
  if(!(node->mask&mask))continue;
  Store(&w.tempPoint,func_001A62E8(node));if(node->height<w.position.f[2]-w.tempPoint.f[2])continue;
  Store(&w.scratch.point.delta,Sub(Read(&w.position),Read(&w.tempPoint)));w.scratch.point.argument.vector.q=w.initialVelocity.q;w.scratch.point.argument.move=p;w.scratch.point.argument.object=node;
  float angle=func_002458F0(w.scratch.point.delta.f[1],w.scratch.point.delta.f[0])*node->parameterB;
  func_0011D9E0(func_0019AAB8,&w.scratch.point.argument,angle,D_002BF914,D_002A65B8,D_002A65BC,&w.pointParameter,&w.score);
  w.score=w.score*D_002BF90C;
  if(node!=forced){if(D_002BF8E0<=w.score)continue;w.score=func_0019B088(p,node,w.score,D_002BF8F8);if(best<=w.score)continue;}
  node->f3(p->actor,&w.scratch.point.sample,0,w.pointParameter);
  func_0019A4A0(p,w.initialVelocity.q,node,w.scratch.point.sample.q,D_002A2DD0.q,&w.duration,0,&w.point,&w.velocity);
  w.velocity.f[2]=w.initialVelocity.f[2]+w.duration*p->actor->physics->gravity.f[2];
  if(node!=forced&&func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.initialVelocity.q,w.point.q,w.velocity.q,0))continue;
  w.bestPoint.q=w.point.q;mode=12;w.bestVelocity.q=w.velocity.q;selected=node;best=Min(w.score,best);selectedDuration=w.duration;auxiliary=w.pointParameter;
 }
 for(CURVE*node=D_003E13F0;node;node=(CURVE*)node->next){
  if(!(node->mask&mask))continue;
  func_001E6F60(node,w.position.q,0,&w.tempPoint,0,0,&w.curveDistance);if(node->height<w.position.f[2]-w.tempPoint.f[2])continue;
  float start=w.curveDistance;w.scratch.first.vector.q=w.initialVelocity.q;w.scratch.first.move=p;w.scratch.first.object=node;
  float high=func_001E6648(node)-30.0f;
  func_0011D9E0(func_0019AB38,&w.scratch.first,start,D_002BF918,30.0f,high,&w.curveParameter,&w.score);
  w.score=w.score*D_002BF90C;
  if(node!=forced){if(D_002BF8E0<=w.score)continue;w.score=func_0019B088(p,node,w.score,D_002BF8F4);if(best<=w.score)continue;}
  node->f3(p->actor,&w.scratch.v[2],0,w.curveParameter);
  func_0019A4A0(p,w.initialVelocity.q,node,w.scratch.v[2].q,D_002A2DD0.q,&w.duration,0,&w.point,&w.velocity);
  w.velocity.f[2]=w.initialVelocity.f[2]+w.duration*p->actor->physics->gravity.f[2];
  if(node!=forced&&func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.initialVelocity.q,w.point.q,w.velocity.q,0))continue;
  w.bestPoint.q=w.point.q;mode=11;w.bestVelocity.q=w.velocity.q;selected=node;best=Min(w.score,best);selectedDuration=w.duration;auxiliary=w.curveParameter;
 }
 for(HELPER_E0*node=D_003E1408;node;node=(HELPER_E0*)node->next){
  if(!(node->mask&mask))continue;
  node->f3(p->actor,&w.tempPoint,0,0);
  if(node!=forced&&node->height<w.position.f[2]-w.tempPoint.f[2])continue;
  func_0019A4A0(p,w.initialVelocity.q,node,w.tempPoint.q,D_002A2DD0.q,&w.duration,&w.score,&w.point,&w.velocity);
  w.velocity.f[2]=w.initialVelocity.f[2]+w.duration*p->actor->physics->gravity.f[2];
  if(node!=forced){if(D_002BF8E0<=w.score)continue;w.score=func_0019B088(p,node,w.score,D_002BF8FC);if(best<=w.score)continue;
   if(func_0019AE00(p,func_0020F948,p->actor->collision,w.duration,w.position.q,w.initialVelocity.q,w.point.q,w.velocity.q,0))continue;
  }
  mode=13;w.bestPoint.q=w.point.q;w.bestVelocity.q=w.velocity.q;selected=node;best=Min(best,w.score);selectedDuration=w.duration;
 }
 if(mode!=-1){BODY*body=p->actor->body;body->deadline=D_002DDED0.time+selectedDuration;Store(&body->goal,Sub(Read(&w.bestPoint),Read(&p->actor->offset)));body->velocity.q=w.bestVelocity.q;p->parameter=parameter;p->value=auxiliary;func_00195FB8(p,mode,selected);}
}
