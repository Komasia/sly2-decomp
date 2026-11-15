/* JOBSTATION::Update: going: held when the guard is held still, hurrying when the object is farther than 1000 (xy),
 * else a new goal (the station point out of the object's frame) once the object has moved more than 250 since the
 * last one; hurrying: held, going again within 700, else the goal follows the object the same way; held: going again
 * once free. Repeats while the state changes (until the job is done).
 * Matching notes (Claude agent): pos is a plain qword (spilled pseudo) so posLast=pos goes qmfc2+sq; the goto loop and
 * the explicit 250.0f local stop loop.c hoisting the case-1 constant. */#include "h2_aijobs.h"
/* a goal (SafeHouse aijobs.h GOAL): a path, an object, or a fixed point */
void Update__5AIJOB(JOBSTATION*);
int FJobDone(JOBSTATION*) asm("FJobDone__FP5AIJOB");
qword PosOfLo__FP2LO(void*);
qword ConvertPos__FP2LOT0G9VU_VECTOR(void*,void*,qword);
int func_00209098(void*);   /* SafeHouse port: FGuardStill (0x209098) */
void SetState__10JOBSTATIONi(JOBSTATION*,int);
void func_002562A8(struct GOAL*);   /* the goal cleared */
void SetGoal__7JOBGOTOP4GOAL(void*,const struct GOAL*);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=&j"(r):"j"(a),"j"(b));return r;}
static inline qword SubIn(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline float LenXY(qword v){float r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(v):"0"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(v):"0"(v));__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(v));return r;}
// name: SafeHouse port (JOBSTATION::Update)
void Update__10JOBSTATION(JOBSTATION*p){
 struct GOAL goal;qword pos;float dist;int state;float lim=250.0f;
 Update__5AIJOB(p);
 pos=PosOfLo__FP2LO(p->plo);
 dist=LenXY(Sub(pos,PosOfLo__FP2LO(p->aijob.pguard)));
 goto test;
 top:{
  state=p->st;
  switch(state){
  case STATS_Going:
   if(func_00209098(p->aijob.pguard))SetState__10JOBSTATIONi(p,STATS_Held);
   else if(1000.0f<dist)SetState__10JOBSTATIONi(p,STATS_Hurrying);
   else if(lim<LenXY(SubIn(p->posLast,pos))){
    qword v;p->posLast=pos;v=ConvertPos__FP2LOT0G9VU_VECTOR(p->plo,0,p->pos);
    func_002562A8(&goal);goal.pos=v;SetGoal__7JOBGOTOP4GOAL(p->aijob.pchild,&goal);
   }
   break;
  case STATS_Hurrying:
   if(func_00209098(p->aijob.pguard))SetState__10JOBSTATIONi(p,STATS_Held);
   else if(dist<700.0f)SetState__10JOBSTATIONi(p,STATS_Going);
   else if(lim<LenXY(SubIn(p->posLast,pos))){
    p->posLast=pos;func_002562A8(&goal);goal.pos=pos;SetGoal__7JOBGOTOP4GOAL(p->aijob.pchild,&goal);
   }
   break;
  case STATS_Held:if(!func_00209098(p->aijob.pguard))SetState__10JOBSTATIONi(p,STATS_Going);break;
  }
  if(state==p->st)return;
 }
 test:
 if(!FJobDone(p))goto top;
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_float[(sizeof(float)==4)?1:-1];
typedef char layout_GOAL[(sizeof(struct GOAL)==32)?1:-1];
typedef char layout_GOAL_pos[((unsigned)&((struct GOAL*)0)->pos==0x10)?1:-1];
typedef char layout_JOBSTATION[(sizeof(JOBSTATION)==0x70)?1:-1];
typedef char layout_JOBSTATION_plo[((unsigned)&((JOBSTATION*)0)->plo==0x30)?1:-1];
typedef char layout_JOBSTATION_pos[((unsigned)&((JOBSTATION*)0)->pos==0x40)?1:-1];
typedef char layout_JOBSTATION_st[((unsigned)&((JOBSTATION*)0)->st==0x50)?1:-1];
typedef char layout_JOBSTATION_posLast[((unsigned)&((JOBSTATION*)0)->posLast==0x60)?1:-1];
