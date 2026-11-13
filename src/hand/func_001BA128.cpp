#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct M3{qword rows[3];};
struct SPACE;
struct NODE{char pad[0x30];qword position;char pad40[0x60];SPACE*space;};
struct MOTION{char pad[0x20];qword angles;};
struct VOLUME;
struct POOL;
struct P{char pad[0xFE0];P*next;char padFE4[0x2C];VOLUME*first,*second;int state;float changed;int id;POOL*animation;P*target;MOTION*motion;int pad1030;NODE*node;char pad1038[8];qword axis;};
struct ROW{int key;P*object;};
struct GAME;
extern "C"{
void UpdateStepguard(P*) asm("UpdateStepguard__FP9STEPGUARDf");
int FGuardState(P*,int) asm("FGuardState__FP5GUARDi");
qword PosOfLo(P*) asm("PosOfLo__FP2LO");
qword ConvertPos(P*,void*,qword) asm("ConvertPos__FP2LOT0G9VU_VECTOR");
int FPointInShape(VOLUME*,qword) asm("FPointInShape__FP2LOG9VU_VECTOR");
void SetStrikeState(P*,int) asm("SetStrikeState__FP5GUARDi");
int FAsegaRetracted(POOL*) asm("FAsegaRetracted__FP5ASEGA");
qword PosConvertXfs(SPACE*,SPACE*,qword) asm("PosConvertXfs__FP2XFT0G9VU_VECTOR");
M3*BuildRotateVectorsMatrix(M3*,qword,qword) asm("BuildRotateVectorsMatrix__FP7MATRIX3G9VU_VECTORT1");
qword DecomposeEulerMatrix(M3*) asm("DecomposeEulerMatrix__FP7MATRIX3");
void*__10STACKSCOPE(void*);
void _$_10STACKSCOPE(void*,int);
int func_001BA100(void*,ROW*);
void func_0020FAA0(GAME*,qword,qword,int(*)(void*,ROW*),void*,int*,ROW***);
extern P*D_003E1444;
extern float D_002A7620;
extern qword D_002C0A80,D_002C0A90,D_002C0AA0;
extern GAME g_sw;
}
struct MARK{MARK(){__10STACKSCOPE(this);}~MARK(){_$_10STACKSCOPE(this,2);}};
static inline qword Vector(qword r){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(r));return v;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Add(qword a,qword b){qword q;__asm__("vadd.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Square(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char ROW_Size[sizeof(ROW)==8?1:-1];
typedef char NODE_position_Offset[FIELD_OFFSET(NODE,position)==48?1:-1];
typedef char NODE_space_Offset[FIELD_OFFSET(NODE,space)==160?1:-1];
typedef char MOTION_angles_Offset[FIELD_OFFSET(MOTION,angles)==32?1:-1];
typedef char ROW_object_Offset[FIELD_OFFSET(ROW,object)==4?1:-1];
typedef char P_next_Offset[FIELD_OFFSET(P,next)==4064?1:-1];
typedef char P_first_Offset[FIELD_OFFSET(P,first)==4112?1:-1];
typedef char P_second_Offset[FIELD_OFFSET(P,second)==4116?1:-1];
typedef char P_state_Offset[FIELD_OFFSET(P,state)==4120?1:-1];
typedef char P_animation_Offset[FIELD_OFFSET(P,animation)==4132?1:-1];
typedef char P_target_Offset[FIELD_OFFSET(P,target)==4136?1:-1];
typedef char P_motion_Offset[FIELD_OFFSET(P,motion)==4140?1:-1];
typedef char P_node_Offset[FIELD_OFFSET(P,node)==4148?1:-1];
typedef char P_axis_Offset[FIELD_OFFSET(P,axis)==4160?1:-1];
extern "C" void func_001BA128(P*p){
 UpdateStepguard(p);
 switch(p->state){
 case 0:{
  if(!FGuardState(p,0x25))break;
  VOLUME*volume;
  if(FGuardState(p,9)){volume=p->first;p->target=0;}
  else if(FGuardState(p,2)){volume=p->second;p->target=0;}
  else break;
  float nearest=D_002A7620;
  for(P*node=D_003E1444;node;node=node->next){
   if(node==p||FGuardState(node,7))continue;
   qword origin=Vector(PosOfLo(p));
   float distance=Square(Sub(origin,PosOfLo(node)));
   if(nearest<distance)continue;
   if(FPointInShape(volume,PosOfLo(node))){p->target=node;nearest=distance;}
  }
  if(!p->target&&!FGuardState(p,2)){
   qword position=Vector(ConvertPos(p,0,D_002C0A80));
   qword low=Add(position,D_002C0A90);
   qword high=Add(position,D_002C0AA0);
   MARK arena;
   int count;ROW**rows;
   func_0020FAA0(&g_sw,low,high,func_001BA100,0,&count,&rows);
   for(int i=0;i<count;i++){
    ROW*row=rows[i];
    if(FPointInShape(volume,PosOfLo(row->object))){p->target=row->object;break;}
   }
  }
  if(p->target)SetStrikeState(p,1);
  break;
 }
 case 1:{
  if(FAsegaRetracted(p->animation)){SetStrikeState(p,0);break;}
  NODE*node=p->node;
  qword position=PosOfLo(p->target);
  qword local=PosConvertXfs(0,node->space,position);
  qword direction=Sub(local,p->node->position);
  M3 matrix;BuildRotateVectorsMatrix(&matrix,p->axis,direction);
  MOTION*motion=p->motion;
  motion->angles=DecomposeEulerMatrix(&matrix);
  break;
 }
 default:break;
 }
}
