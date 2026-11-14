// Transition actor controller state.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct M3 {qword r[3];};
struct NODE {M3 basis;qword orientation;char pad40[0x60];NODE *parent;char padA4[0xC];V velocity;};
struct O;
struct S {char pad[0x58];NODE *positionNode,*rotationNode;char pad60[0xF0];int state;float time;int sentinel,kind;O *nearest;char pad164[4];void *animation;char pad16C[0x10];void *rotationJob,*positionJob;char pad184[0xC];qword direction;};
struct WORLD;
#include "clock.h"
extern WORLD g_sw;
extern qword g_normalZ;
extern float D_002A97A8;
extern O *D_002E1E40;
extern int D_002C4398[];
extern "C" {
void DeleteCtrl(void **) asm("DeleteCtrl__FPP4CTRL");
void RecalcSwOxfFilterForObject(WORLD *,S *) asm("RecalcSwOxfFilterForObject__FP2SWP2SO");
void SetAloCnstrLin(S *,int) asm("SetAloCnstrLin__FP3ALOi");
void SetAloCnstrAng(S *,int) asm("SetAloCnstrAng__FP3ALOi");
qword DecomposeEulerMatrix(const void *) asm("DecomposeEulerMatrix__FP7MATRIX3");
void *PctrlNewPos(S *,NODE *,int,int,int,qword) asm("PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR");
int func_00224688(S *);
qword VecConvertXfs(NODE *,NODE *,qword) asm("VecConvertXfs__FP2XFT0G9VU_VECTOR");
M3 *BuildLookAtMatrix(M3 *,qword,qword) asm("BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1");
void ReparentBooty(S *,int,int) asm("ReparentBooty__FP3ALOii");
int CFindObjectsByClass(WORLD *,int,int,int,int,O **) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
qword PosOfLo(void *) asm("PosOfLo__FP2LO");
void FadeAloOut(S *,float) asm("FadeAloOut__FP3ALOf");
void SeekSma(void *,int) asm("SeekSma__FP3SMA3OID");
}
static inline qword ToVF(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"0"(a),"j"(b));return r;}
static inline qword Normalize(qword v){qword len,one,result;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(len),"=&j"(one):"j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(len));
 __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(result):"j"(v),"0"(len));return result;}
static inline float Length(qword v){qword one;float f;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=j"(one));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));
 __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline void Zero(float *v){v[0]=v[1]=v[2]=0.0f;}static inline void ZeroVelocity(NODE *n){Zero(n->velocity.f);}
static inline O *FindNearest(S *p,int count,O **objects,O *nearest,float best){
  for(int i=0;i<count;i++){
   O *object=objects[i];
   qword position=ToVF(PosOfLo(object));
   qword origin=PosOfLo(p);
   V delta;
   delta.q=Sub(position,origin);
   delta.f[2]+=delta.f[2];
   float distance=Length(delta.q);
   if(distance<best){best=distance;nearest=object;}
  }
return nearest;}
static inline M3 MakeBasis(qword direction,qword rawUp) return result;{
 qword v=rawUp,len,one,normalized;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(len),"=&j"(one):"j"(v));
 qword first=direction;
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(len));
 __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=&j"(normalized):"j"(v),"j"(len));
 BuildLookAtMatrix(&result,first,normalized);
}
// name: SafeHouse port (SetCarryStateBase)
extern "C" void SetCarryStateBase__FP2LOi(S *p,int state){
 int old=p->state;
 if(state==old)return;
 p->state=state;p->time=g_clock.t;p->sentinel=-1;
 DeleteCtrl(&p->positionJob);
 DeleteCtrl(&p->rotationJob);
 if(old==0||old==4)RecalcSwOxfFilterForObject(&g_sw,p);
 switch(p->state){
 case 0:{
  SetAloCnstrLin(p,0);SetAloCnstrAng(p,0);
  ZeroVelocity(p->positionNode);ZeroVelocity(p->rotationNode);
  qword position=p->positionNode->orientation;
  qword rotation=DecomposeEulerMatrix(p->rotationNode);
  p->positionJob=PctrlNewPos(p,p->positionNode,0,7,2,position);
  p->rotationJob=PctrlNewPos(p,p->rotationNode,0,7,2,rotation);
  RecalcSwOxfFilterForObject(&g_sw,p);
  break;
 }
 case 2:{
  SetAloCnstrLin(p,1);SetAloCnstrAng(p,1);
  ZeroVelocity(p->positionNode);ZeroVelocity(p->rotationNode);
  if(func_00224688(p)&&p->rotationNode){
   qword direction=Normalize(ToVF(VecConvertXfs(0,p->rotationNode->parent,p->direction)));
   qword rawUp=VecConvertXfs(0,p->rotationNode->parent,g_normalZ);
   M3 basis;basis=MakeBasis(direction,rawUp);
   p->rotationJob=PctrlNewPos(p,p->rotationNode,0,7,2,DecomposeEulerMatrix(&basis));
  }
  break;
 }
 case 1:{
  ReparentBooty(p,0,15);SetAloCnstrLin(p,0);
  if(p->kind!=0x29){SetAloCnstrAng(p,0);break;}
  SetAloCnstrAng(p,1);
  O *objects[32];
  int count=CFindObjectsByClass(&g_sw,0x105,0x38,0,32,objects);
  p->nearest=FindNearest(p,count,objects,D_002E1E40,D_002A97A8);
  break;
 }
 case 4:
  RecalcSwOxfFilterForObject(&g_sw,p);
  FadeAloOut(p,0.25f);
  break;
 }
 if(p->animation&&p->state>=0)SeekSma(p->animation,D_002C4398[p->state]);
}
