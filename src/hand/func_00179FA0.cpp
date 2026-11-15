/* JOBUSE::Enter (0xAC): the use's place and orientation from its object: a path (the nearest point, facing along it),
 * then by class: CID_PATH_0D (SafeHouse: a chair; facing away from it unless reversed), a spire (a rope), a pipe (a
 * ladder: its frame, offset for the hands), a hook of kind 3 (a bar: its x row, offset for the hands), else the ground
 * under the place (no object). The move then starts with the
 * guard's state bits for that kind (func_00207A20: a state's bit; 0x1B chair, 0x27 pipe, 0x28 bar, 0x29 spire) set
 * only for the move's own enter, the guard turned toward the place (walking: its heading; on a ladder (kMove 2): a
 * look-at frame), the kind-2 player given the target, and the job locks the guard.
 * Layout: SafeHouse port (aijobs.h JOBUSE; guard.h GUARD grfState +0x2C0, kMove +0xF80, ploMove +0xF84, move +0xFD0). */
#include "cid.h"
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct M3{qword r[3];};
struct MOVEREF;
struct GUARD{char pad[0x124];int kind;char pad128[0x2C0-0x128];unsigned long grfState;char pad2C8[0xF80-0x2C8];int kMove;GUARD*ploMove;char padF88[0xFD0-0xF88];char move[0];};
struct K2PLAY{char pad[0x58];GUARD*ploTarget;int fReverse;int nExtra;};
struct KINDE{char pad[8];K2PLAY*pk2play;};
struct JOBUSE{char pad[0x10];GUARD*pguard;char pad14[0x40-0x14];KINDE*pkinde;char pad44[0x50-0x44];U pos;GUARD*ploTarget;int fReverse,nExtra,fBasis;M3 mat;};
union TEMP{struct{U direction;M3 rotation;}first;M3 basis;};
struct WORK{TEMP temp;float curve;};
struct LIMIT{float low,high;};
extern "C"{
 extern unsigned long D_002DFB70;
 extern int D_002DFB78;
 extern qword g_normalZ;
 extern LIMIT D_002BE6B8;
 unsigned long func_00207A20(int);
 int FIsBasicDerivedFrom(GUARD*,int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
 qword PosOfLo(GUARD*) asm("PosOfLo__FP2LO");
 M3*MatJtLo(GUARD*) asm("MatJtLo__FP2LO");
 void NearestCrvAll(GUARD*,qword,void*,qword*,qword*,float*,float*) asm("NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2");
 float atan2f(float,float) asm("atan2f");
 float RadNormalize(float) asm("RadNormalize__Ff");
 void BuildRotateMatrixAxis(M3*,float,qword) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
 M3*BuildLookAtMatrix(M3*,qword,qword) asm("BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1");
 void MatPipeFrame(GUARD*,int,M3*,float) asm("MatPipeFrame__FP2LOfiPv");
 void OffsetUseByHands(JOBUSE*) asm("OffsetUseByHands__FP6JOBUSE");
 int FDropOnGround(qword*,float,float,int,int(*)(void)) asm("FDropOnGround__FP6VECTORffiPv");
 void Enter(JOBUSE*) asm("Enter__7JOBMOVE");
 void SetMoveHeading(MOVEREF*,float) asm("SetMoveHeading__FP7MOVEREF");
 void func_00209840(MOVEREF*,M3*);
 void SetK2Target(K2PLAY*,qword) asm("SetK2Target__FP6K2PLAYG9VU_VECTOR");
 void LockJob(JOBUSE*) asm("LockJob__FP5AIJOB");
}
static inline MOVEREF*Control(GUARD*p){return (MOVEREF*)((char*)p+0xFD0);}
static inline float Angle(qword delta){qword x;int y;float fx,fy;__asm__("qmfc2.ni %0,%1":"=r"(x):"j"(delta));__asm__("prot3w %0,%1":"=r"(y):"r"(x));__asm__("mtc1 %1,%0":"=f"(fx):"r"(x));__asm__("mtc1 %1,%0":"=f"(fy):"r"(y));return atan2f(fy,fx);}
static inline qword HeadingInputs(JOBUSE*p,U*home,qword current,GUARD**pguard){
 register qword a __asm__("vf1"),b __asm__("vf2");GUARD*o;
 __asm__("qmtc2.ni %3,%1\n\tlw %2,%4\n\tlqc2 %0,%5":"=j"(a),"=j"(b),"=&r"(o):"r"(current),"m"(p->pguard),"m"(home->q));
 __asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));*pguard=o;return a;
}
static inline qword BasisInputs(JOBUSE*p,U*home,qword current,GUARD**pguard){
 register qword a __asm__("vf1"),b __asm__("vf2");GUARD*o;
 __asm__("lqc2 %0,%5\n\tqmtc2.ni %3,%1\n\tlw %2,%4":"=j"(a),"=j"(b),"=&r"(o):"r"(current),"m"(p->pguard),"m"(home->q));
 __asm__("vsub.xyzw %0,%1,%0":"+j"(b):"j"(a));*pguard=o;return b;
}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char TEMP_Size[sizeof(TEMP)==64?1:-1];
typedef char WORK_Size[sizeof(WORK)==80?1:-1];
typedef char P_kind_Offset[FIELD_OFFSET(GUARD,kind)==292?1:-1];
typedef char P_flags_Offset[FIELD_OFFSET(GUARD,grfState)==704?1:-1];
typedef char P_mode_Offset[FIELD_OFFSET(GUARD,kMove)==3968?1:-1];
typedef char P_linked_Offset[FIELD_OFFSET(GUARD,ploMove)==3972?1:-1];
typedef char P_control_Offset[FIELD_OFFSET(GUARD,move)==4048?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(JOBUSE,pguard)==16?1:-1];
typedef char C_driver_Offset[FIELD_OFFSET(JOBUSE,pkinde)==64?1:-1];
typedef char C_point_Offset[FIELD_OFFSET(JOBUSE,pos)==80?1:-1];
typedef char C_target_Offset[FIELD_OFFSET(JOBUSE,ploTarget)==96?1:-1];
typedef char C_reverse_Offset[FIELD_OFFSET(JOBUSE,fReverse)==100?1:-1];
typedef char C_extra_Offset[FIELD_OFFSET(JOBUSE,nExtra)==104?1:-1];
typedef char C_basisValid_Offset[FIELD_OFFSET(JOBUSE,fBasis)==108?1:-1];
typedef char C_matrix_Offset[FIELD_OFFSET(JOBUSE,mat)==112?1:-1];
typedef char INFO_target_Offset[FIELD_OFFSET(K2PLAY,ploTarget)==88?1:-1];
typedef char INFO_reverse_Offset[FIELD_OFFSET(K2PLAY,fReverse)==92?1:-1];
typedef char INFO_extra_Offset[FIELD_OFFSET(K2PLAY,nExtra)==96?1:-1];
typedef char DRIVER_info_Offset[FIELD_OFFSET(KINDE,pk2play)==8?1:-1];
typedef char WORK_temp_Offset[FIELD_OFFSET(WORK,temp)==0?1:-1];
typedef char WORK_curve_Offset[FIELD_OFFSET(WORK,curve)==64?1:-1];
typedef char TEMP_first_direction_Offset[FIELD_OFFSET(TEMP,first.direction)==0?1:-1];
typedef char TEMP_first_rotation_Offset[FIELD_OFFSET(TEMP,first.rotation)==16?1:-1];
typedef char TEMP_basis_Offset[FIELD_OFFSET(TEMP,basis)==0?1:-1];
typedef char LIMIT_low_Offset[FIELD_OFFSET(LIMIT,low)==0?1:-1];
typedef char LIMIT_high_Offset[FIELD_OFFSET(LIMIT,high)==4?1:-1];
// name: SafeHouse port (JOBUSE::Enter)
extern "C" void Enter__6JOBUSE(JOBUSE*p){
 WORK work;U pos,otherPoint,direction;
 if(!D_002DFB78){
  unsigned long a=func_00207A20(0x1B),b=func_00207A20(0x27),c=func_00207A20(0x28),d=func_00207A20(0x29);
  D_002DFB78=1;D_002DFB70=a|b|c|d;
 }
 unsigned long mask=D_002DFB70;
 unsigned long old=p->pguard->grfState&mask;
 p->pguard->grfState &= ~mask;
 unsigned long active=0;
 if(p->ploTarget){
  float heading;
  if(FIsBasicDerivedFrom(p->ploTarget,CID_PATH)){
   GUARD*ploTarget=p->ploTarget;
   qword position=PosOfLo(p->pguard);
   NearestCrvAll(ploTarget,position,0,&p->pos.q,&work.temp.first.direction.q,0,&work.curve);
   heading=atan2f(work.temp.first.direction.f[1],work.temp.first.direction.f[0]);
  }else{
   p->pos.q=PosOfLo(p->ploTarget);
   M3*a=MatJtLo(p->ploTarget);
   M3*b=MatJtLo(p->ploTarget);
   heading=atan2f(((U*)a->r)->f[1],((U*)b->r)->f[0]);
  }
  if(FIsBasicDerivedFrom(p->ploTarget,CID_PATH_0D)){
   active|=func_00207A20(0x1B);
   if(!p->fReverse)heading=RadNormalize(heading+3.1415927410125732421875f);
   p->fBasis=1;
   BuildRotateMatrixAxis(&work.temp.first.rotation,heading,g_normalZ);
   p->mat=work.temp.first.rotation;
  }else if(FIsBasicDerivedFrom(p->ploTarget,CID_SPIRE)){
   active|=func_00207A20(0x29);
  }else if(FIsBasicDerivedFrom(p->ploTarget,CID_PIPE)){
   active|=func_00207A20(0x27);
   p->fBasis=1;
   MatPipeFrame(p->ploTarget,p->fReverse,&p->mat,work.curve);
   OffsetUseByHands(p);
  }else if(FIsBasicDerivedFrom(p->ploTarget,CID_HOOK)&&p->ploTarget->kind==3){
   active|=func_00207A20(0x28);
   p->fBasis=1;
   M3*m=MatJtLo(p->ploTarget);
   (void)BuildLookAtMatrix(&work.temp.basis,m->r[0],g_normalZ);
   p->mat=work.temp.basis;
   OffsetUseByHands(p);
  }else{
  (void)FDropOnGround(&p->pos.q,D_002BE6B8.high,D_002BE6B8.low,1,0);
  p->ploTarget=0;
  }
 }
 p->pguard->grfState|=active;
 Enter(p);
 p->pguard->grfState &= ~active;
 p->pguard->grfState |= old;
 if(p->pkinde){
  switch(p->pguard->kMove){
  case -1:case 0:case 3:{
   pos=p->pos;
   qword current=PosOfLo(p->pguard);
   GUARD*pguard; qword delta=HeadingInputs(p,&pos,current,&pguard);
   MOVEREF*move=Control(pguard);
   float angle=Angle(delta);
   SetMoveHeading(move,angle);
   break;
  }
  case 2:{
   otherPoint=p->pos;
   qword current=PosOfLo(p->pguard);
   GUARD*pguard;direction.q=BasisInputs(p,&otherPoint,current,&pguard);
   M3*m=MatJtLo(pguard->ploMove);
   (void)BuildLookAtMatrix(&work.temp.basis,m->r[0],direction.q);
   func_00209840(Control(p->pguard),&work.temp.basis);
   break;
  }
  }
  p->pkinde->pk2play->nExtra=p->nExtra;
  p->pkinde->pk2play->ploTarget=p->ploTarget;
  p->pkinde->pk2play->fReverse=p->fReverse;
  SetK2Target(p->pkinde->pk2play,p->pos.q);
 }
 LockJob(p);
}
