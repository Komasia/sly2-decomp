typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
typedef union U{qword q;float f[4];int i[4];}U;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct FRAME{char pad0[0xA0];void*space;}FRAME;
typedef struct NODE{char pad0[12];VTE*vt;char pad10[0x18];ulong flags;char pad30[0x2C];FRAME*frame;char pad60[0x8C];void*group;}NODE;
typedef struct LM{float low,high;}LM;
typedef struct RULE{int distanceEnabled,angleEnabled;LM enterDistance,stayDistance,enterAngle,stayAngle;}RULE;
typedef struct POLY{float a,b,c;}POLY;
typedef struct CLOCK{float time,dt;}CLOCK;
typedef struct CURVE_FIELDS{void*curve;float progress;}CURVE_FIELDS;
typedef struct P{NODE node;char padF0[0xD0];int state;float stateTime;int cooldown,active;void*binding;NODE*target;void*curve;float progress;U previousSelf,previousTarget;float stamp,heading;char pad208[8];U output;char pad220[0x50];RULE rules[5];float scale;char pad33C[4];POLY remaining;char pad34C[4];POLY angle;char pad35C[4];POLY simpleAngle;char pad36C[4];LM simpleClamp;}P;
typedef struct WORK{U nearest,direction,unit,scalar;NODE*objects[64];U avoidanceScalar,simpleTarget,target,self,force,selectorTarget;}WORK;
extern "C"{
extern U D_002A2DD0,D_002A2DA0;
extern float D_002BE820,D_002BE824;
extern float D_002BE828;
extern POLY D_002BE830,D_002BE840,D_002BE860;
extern LM D_002BE850,D_002BBB60;
extern CLOCK D_002DDED0;
extern char D_002DE578[],D_003DD490[];
extern void func_001F36E0(P*);
extern int func_0017F550(P*);
extern void func_00181268(P*,int);
extern qword func_001A62E8(void*),func_001A6FC0(void*,void*,qword),func_0022FCC8(void*,void*,qword);
extern float func_002458F0(float,float),func_0011CF60(float);
extern int func_0011D910(LM*,float);
extern int func_001C02D0(void*,qword,qword,void*);
extern void func_001E7380(void*,qword,void*,qword*,float,qword*,float*,float*);
extern float func_001E6648(void*),func_00154C90(void*);
extern int func_0015E9C8(void*,int,int,void*,int,NODE**);
extern qword func_0011E9F8(qword,float);
}
static inline ulong Alive(NODE*p){return(p->flags>>60)&1;}
static inline qword Transfer(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline float FloatX(qword a){int bits;float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float FloatY(qword a){int bits;float f;__asm__("prot3w %0,%1":"=r"(bits):"r"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float GprX(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Heading(qword a){return func_002458F0(FloatY(a),GprX(a));}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
static inline float Clamp(float f,LM*p){float low=p->low,high=p->high;if(f<low)f=low;else if(high<f)f=high;return f;}

static inline float DifferenceLength(const U*a,const U*b){float f;__asm__("lqc2 $vf2,%1\n\tlqc2 $vf1,%2\n\tvsub.xyzw $vf1,$vf2,$vf1\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tqmfc2.ni $2,$vf1\n\tmtc1 $2,%0":"=f"(f):"m"(a->q),"m"(b->q):"$2","vf1","vf2");return f;}

extern "C" void func_00180668(P*p){
 WORK w;
 register float primary __asm__("$f20"),secondary __asm__("$f21");
 func_001F36E0(p);
 if(p->state==2||p->state==4){if(func_0017F550(p))func_00181268(p,0);}
 if(p->state!=0&&p->state!=4){if(!p->target||!Alive(p->target))func_00181268(p,0);}
 if(p->active)goto dispatch;
 if(!p->target)goto dispatch;
 if(!Alive(p->target))goto dispatch;
 {
  RULE*rule=&p->rules[p->state];
  w.selectorTarget.q=Transfer(func_001A62E8(p->target));
  register qword raw __asm__("$2")=func_001A62E8(p);
  register qword deltaArgument __asm__("$6");register void*space __asm__("$4");register P*actor __asm__("$5");
  __asm__("lqc2 $vf1,%5\n\tdaddu %3,$zero,$zero\n\tqmtc2.ni %0,$vf2\n\tdaddu %4,%6,$zero\n\tvsub.xyzw $vf1,$vf1,$vf2\n\tvmul.xyz $vf2,$vf1,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z\n\tqmfc2.ni %2,$vf1\n\tvsqrt $Q,$vf2x\n\tvwaitq\n\tvaddq.x $vf2,$vf0,$Q\n\tqmfc2.ni %0,$vf2\n\tmtc1 %0,%1":"+r"(raw),"=f"(secondary),"=r"(deltaArgument),"=&r"(space),"=r"(actor):"m"(w.selectorTarget.q),"r"(p):"vf1","vf2","vf3");
  primary=func_0011CF60(Heading(func_001A6FC0(space,actor,deltaArgument)));
  {
   int accept;if(!rule->distanceEnabled)accept=rule->angleEnabled;else accept=func_0011D910(&rule->stayDistance,secondary);
   if(!accept)goto search_state;
   if(!rule->angleEnabled)goto dispatch;
   if(func_0011D910(&rule->stayAngle,primary))goto dispatch;
  }
 search_state:{
   register int state __asm__("$19")=4;
   register RULE*next __asm__("$18")=&p->rules[4];
   for(;state>0;--next,--state){
    rule=next;
    int accept;if(!rule->distanceEnabled)accept=rule->angleEnabled;else accept=func_0011D910(&rule->enterDistance,secondary);
    if(accept&&(!rule->angleEnabled||func_0011D910(&rule->enterAngle,primary)))break;
   }
   func_00181268(p,state);
  }
 }
 dispatch:
 switch(p->state){
 case 0:case 4:break;
 case 1:case 2:{
  if(p->cooldown)break;
  FRAME*frame=p->node.frame;
  w.simpleTarget.q=func_001A62E8(p->target);
  qword own=func_001A62E8(p);
  register qword delta __asm__("vf1");
  __asm__("vsub.xyzw %0,%1,%2":"=j"(delta):"j"(w.simpleTarget.q),"j"(own));
  float heading=func_0011CF60(Heading(func_0022FCC8(0,frame->space,delta)));
  p->heading=Clamp(Evaluate(&p->simpleAngle,heading),&p->simpleClamp);
  break;
 }
 case 3:{
  w.target.q=func_001A62E8(p->target);
  w.self.q=func_001A62E8(p);
  {VTE&entry=p->node.vt[33];(void)((qword(*)(void*))entry.fn)((char*)p+entry.delta);}
  {
   register float threshold __asm__("$f1"),distance __asm__("$f0");
   register int refresh __asm__("$4");
   __asm__("lqc2 $vf2,%3\n\tlui $2,%%hi(%5)\n\tlqc2 $vf1,%4\n\tdaddu %2,$zero,$zero\n\tvsub.xyzw $vf1,$vf2,$vf1\n\tlwc1 %1,%%lo(%5)($2)\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,$Q\n\tqmfc2.ni $2,$vf1\n\tmtc1 $2,%0":"=f"(distance),"=f"(threshold),"=r"(refresh):"m"(w.target.q),"m"(p->previousTarget.q),"i"(&D_002BE820):"$2","vf1","vf2","memory");
   if(threshold<distance)refresh=1;
   else if(threshold<DifferenceLength(&w.self,&p->previousSelf))refresh=1;
   else if(D_002BE824<D_002DDED0.time-p->stamp)refresh=1;
   if(refresh){
    (void)func_001C02D0(p->binding,w.self.q,w.target.q,p->curve);
    register float stamp __asm__("$f0");
    __asm__("lq $3,%4\n\tlui $2,%%hi(%6)\n\tsw $zero,%0\n\tsq $3,%1\n\tlq $3,%5\n\tsq $3,%2\n\tlwc1 %3,%%lo(%6)($2)":"=m"(p->progress),"=m"(p->previousTarget.q),"=m"(p->previousSelf.q),"=f"(stamp):"m"(w.target.q),"m"(w.self.q),"i"(&D_002DDED0):"$2","$3","memory");
    p->stamp=stamp;
   }
  }
  register void*projectionCurve __asm__("$4"),*projectionMetric __asm__("$6");
  register qword projectionSelf __asm__("$5");register qword*projectionPoint __asm__("$7"),*projectionDirection __asm__("$8");
  register float projectionProgress __asm__("$f12");
  __asm__("lw %0,0x1d8(%7)\n\tdaddu %1,$zero,$zero\n\tlq %2,%6\n\tdaddu %3,%8,$zero\n\tlwc1 %4,0x1dc(%7)\n\taddiu %5,%8,0x10":"=&r"(projectionCurve),"=&r"(projectionMetric),"=&r"(projectionSelf),"=&r"(projectionPoint),"=f"(projectionProgress),"=r"(projectionDirection):"m"(w.self.q),"r"(p),"p"(&w.nearest.q),"X"(*(CURVE_FIELDS*)&p->curve));
  func_001E7380(projectionCurve,projectionSelf,projectionMetric,projectionPoint,projectionProgress,projectionDirection,0,&p->progress);
  register void*totalCurve __asm__("$4");
  {
   register qword direction __asm__("vf4"),length __asm__("vf1"),fallback __asm__("$2");
   register float epsilon __asm__("$f1");
   __asm__("lui $2,%%hi(%8)\n\tlqc2 $vf1,%6\n\tlw $2,%%lo(%8)($2)\n\tqmtc2.ni $2,$vf3\n\tlqc2 $vf2,%5\n\tvadda.xyzw ACC,$vf2,$vf0\n\tvmaddx.xyzw $vf2,$vf1,$vf3x\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%3\n\t.set at\n\tlqc2 $vf1,%7\n\tlui $2,%%hi(%9)\n\tvsub.xyzw %0,$vf2,$vf1\n\taddiu $2,$2,%%lo(%9)\n\tvmul.xyz %1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\tlq %2,0($2)\n\tvsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q\n\tsqc2 $vf3,%4":"=j"(direction),"=j"(length),"=r"(fallback),"=f"(epsilon),"=m"(w.scalar.q):"m"(w.nearest.q),"m"(w.direction.q),"m"(w.self.q),"i"(&D_002BE828),"i"(&D_002A2DD0):"$1","vf2","vf3","memory");
   if(FloatX(length)<epsilon)length=fallback;
   else __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(length):"j"(direction));
   __asm__("lw %0,%1":"=r"(totalCurve):"m"(p->curve));
   w.unit.q=length;
  }
  register void*directionSpace __asm__("$4");register P*directionActor __asm__("$5");register qword directionArgument __asm__("$6");
  {register float total __asm__("$f0")=func_001E6648(totalCurve);register float progress __asm__("$f1");
   __asm__("lwc1 %0,%1":"=f"(progress):"m"(p->progress));
   __asm__("daddu %0,$zero,$zero\n\tlq %1,%3\n\tdaddu %2,%4,$zero":"=&r"(directionSpace),"=&r"(directionArgument),"=r"(directionActor):"m"(w.unit.q),"r"(p));
   primary=total-progress;
  }
  secondary=Heading(func_001A6FC0(directionSpace,directionActor,directionArgument));
  register qword unitCarrier __asm__("vf2");
  {
   register float response __asm__("$f7")=func_00154C90(D_002DE578);
   register float value __asm__("$f0"),coefficient __asm__("$f1"),constant __asm__("$f2");
   register float low __asm__("$f3"),high __asm__("$f4");
   register float remaining __asm__("$f6"),turn __asm__("$f3"),gain __asm__("$f2");
   register POLY*polynomial __asm__("$3");
   __asm__("addiu %0,%1,0x340":"=r"(polynomial):"r"(p));
   coefficient=polynomial->c;value=polynomial->b;
   coefficient=primary*coefficient;constant=p->remaining.a;low=D_002BBB60.low;
   value=value+coefficient;primary=primary*value;value=constant+primary;
   high=D_002BBB60.high;
   if(value<low)remaining=low;else if(high<value)remaining=high;else remaining=value;
   register POLY*angle __asm__("$2");
   __asm__("addiu %0,%1,0x350":"=r"(angle):"r"(p));
   constant=p->angle.a;coefficient=angle->c;value=angle->b;
   coefficient=secondary*coefficient;low=D_002BBB60.low;
   value=value+coefficient;value=secondary*value;value=constant+value;
   high=D_002BBB60.high;
   if(value<low)turn=low;else if(high<value)turn=high;else turn=value;
   polynomial=&D_002BE830;
   register float lowGain __asm__("$f5")=D_002BBB60.low;
   constant=polynomial->a;coefficient=polynomial->c;value=polynomial->b;
   coefficient=response*coefficient;value=value+coefficient;value=response*value;value=constant+value;
   high=D_002BBB60.high;
   if(value<lowGain)gain=lowGain;else if(high<value)gain=high;else gain=value;
   value=remaining*turn;coefficient=p->scale;
   __asm__("lqc2 %0,%1":"=j"(unitCarrier):"m"(w.unit.q));
   value=value*gain;primary=value*coefficient;
  }
  {
   register qword force __asm__("vf3");
   __asm__("mfc1 $2,%3\n\tqmtc2.ni $2,$vf1\n\tvmulx.xyzw %0,%2,$vf1x\n\tsqc2 $vf1,%1":"=j"(force),"=m"(w.scalar.q):"j"(unitCarrier),"f"(primary):"$2","vf1");
   w.force.q=force;
  }
  {
   register NODE**buffer __asm__("$16")=w.objects;
   register int queried __asm__("$2")=func_0015E9C8(D_003DD490,0x105,0x49,0,64,buffer);
   if(queried>0){
   char*distanceBase=(char*)0x2c0000;
   register char*facingBase __asm__("$22");register NODE**cursor __asm__("$18");
   __asm__("lui %0,%%hi(%2)\n\tdaddu %1,%3,$zero":"=&r"(facingBase),"=r"(cursor):"i"(&D_002BE860),"r"(buffer));
   register char*distanceLimitBase __asm__("$23"),*limitBase __asm__("$21");
   register POLY*distanceWeight __asm__("$20"),*facingWeight __asm__("$19");
   register int count __asm__("$16");
   __asm__("lui %0,0x2c\n\tlui %1,0x2c\n\taddiu %2,%5,%%lo(%8)\n\taddiu %3,%6,%%lo(%9)\n\tdaddu %4,%7,$zero":"=&r"(distanceLimitBase),"=&r"(limitBase),"=&r"(distanceWeight),"=&r"(facingWeight),"=r"(count):"r"(distanceBase),"r"(facingBase),"r"(queried),"i"(&D_002BE840),"i"(&D_002BE860));
   do{
    NODE*object=*cursor;
    if(object!=(NODE*)p&&object->group!=p->node.group){
     register qword raw __asm__("$2")=func_001A62E8(object);
     register qword planar __asm__("vf3"),length __asm__("vf2");
     register float epsilon __asm__("$f1");register U*axis __asm__("$3");
     __asm__("qmtc2.ni %0,%1\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%3\n\t.set at\n\tlqc2 $vf2,%7\n\tlui %4,%%hi(%8)\n\tvsub.xyzw $vf1,$vf2,%1\n\taddiu %4,%4,%%lo(%8)\n\tsqc2 $vf1,%5\n\tsw $zero,%6\n\tlq %0,%5\n\tqmtc2.ni %0,%1\n\tvmul.xyz $vf1,%1,%1\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,%2,$vf1z\n\tvsqrt $Q,$vf1x\n\tvwaitq\n\tvaddq.x %2,$vf0,$Q":"+r"(raw),"=j"(planar),"=j"(length),"=f"(epsilon),"=r"(axis),"=m"(w.scalar.q),"=m"(w.scalar.i[2]):"m"(w.self.q),"i"(&D_002A2DA0):"$1","vf1");
     register float norm __asm__("$f0");
     __asm__("qmfc2.ni $2,%1\n\tmtc1 $2,%0":"=f"(norm):"j"(length):"$2");
     if(norm<epsilon)w.scalar=*axis;
     else{register qword normalized __asm__("vf1");
      __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(normalized):"j"(planar),"j"(length));w.scalar.q=normalized;
     }
     {
      register float coefficient __asm__("$f2"),argument __asm__("$f1"),value __asm__("$f0");
      register qword bits __asm__("$3");
      __asm__("lwc1 %0,%3\n\tqmfc2.ni $3,%4\n\tmtc1 $3,%1\n\tlwc1 %2,%5":"=f"(coefficient),"=f"(argument),"=f"(value):"m"(distanceWeight->c),"j"(length),"m"(distanceWeight->b):"$3");
      coefficient=argument*coefficient;
      register float constant __asm__("$f3");
      __asm__("lwc1 %0,-0x17c0(%1)":"=f"(constant):"r"(distanceBase),"X"(*(float*)(distanceBase-0x17c0)));
      register float low __asm__("$f4")=*(float*)(distanceLimitBase-0x17b0);
      register LM*limits __asm__("$2");
      __asm__("lui %0,%%hi(%1)\n\taddiu %0,%0,%%lo(%1)":"=r"(limits):"i"(&D_002BE850));
      value=value+coefficient;argument=argument*value;value=constant+argument;
      register float high __asm__("$f5")=limits->high;
      register float weight __asm__("$f6");
      if(value<low)weight=low;else if(high<value)weight=high;else weight=value;
      __asm__("lqc2 %0,%2\n\tlui %1,%%hi(%4)\n\tlqc2 $vf1,%3\n\taddiu %1,%1,%%lo(%4)\n\tvmul.xyz %0,%0,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf3,%0z":"=j"(length),"=r"(limits):"m"(w.scalar.q),"m"(w.unit.q),"i"(&D_002BBB60):"vf1","vf3");
      coefficient=facingWeight->c;
      __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(length));
      value=facingWeight->b;argument=GprX(bits);
      constant=*(float*)(facingBase-0x17a0);coefficient=argument*coefficient;
      low=*(float*)(limitBase-0x44a0);
      value=value+coefficient;argument=argument*value;constant=constant+argument;
      high=limits->high;
      if(constant<low)value=low;else if(high<constant)value=high;else value=constant;
      float scale=weight*value;
      __asm__("lqc2 $vf3,%2\n\tlqc2 $vf2,%3\n\tmfc1 $3,%4\n\tqmtc2.ni $3,$vf1\n\tvadda.xyzw ACC,$vf3,$vf0\n\tvmaddx.xyzw $vf3,$vf2,$vf1x\n\tsqc2 $vf1,%0\n\tsqc2 $vf3,%1":"=m"(w.avoidanceScalar.q),"=m"(w.force.q):"m"(w.force.q),"m"(w.scalar.q),"f"(scale):"$3","vf1","vf2","vf3");
     }
    }
    ++cursor;
   }while(--count);
   }
  }
  register qword limited __asm__("$2")=func_0011E9F8(w.force.q,primary);
  register float headingY __asm__("$f12"),headingX __asm__("$f13");
  __asm__("lwc1 %0,%2\n\tlwc1 %1,%3":"=f"(headingY),"=f"(headingX):"m"(w.unit.f[1]),"m"(w.unit.f[0]));
  p->output.q=limited;
  p->heading=func_002458F0(headingY,headingX);
  break;
 }
 }
}

typedef char layout_size_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_size_voidpointer[(sizeof(void*)==4)?1:-1];
typedef char layout_size_ulong[(sizeof(ulong)==8)?1:-1];
typedef char layout_size_U[(sizeof(U)==16)?1:-1];
typedef char layout_size_VTE[(sizeof(VTE)==8)?1:-1];
typedef char layout_size_FRAME[(sizeof(FRAME)==0xA4)?1:-1];
typedef char layout_size_NODE[(sizeof(NODE)==0xF0)?1:-1];
typedef char layout_size_LM[(sizeof(LM)==8)?1:-1];
typedef char layout_size_RULE[(sizeof(RULE)==0x28)?1:-1];
typedef char layout_size_POLY[(sizeof(POLY)==12)?1:-1];
typedef char layout_size_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_size_P[(sizeof(P)==0x380)?1:-1];
typedef char layout_size_WORK[(sizeof(WORK)==0x1A0)?1:-1];
typedef char layout_VTE_delta[((unsigned long)&((VTE*)0)->delta==0x0)?1:-1];
typedef char layout_VTE_fn[((unsigned long)&((VTE*)0)->fn==0x4)?1:-1];
typedef char layout_FRAME_space[((unsigned long)&((FRAME*)0)->space==0xa0)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_flags[((unsigned long)&((NODE*)0)->flags==0x28)?1:-1];
typedef char layout_NODE_frame[((unsigned long)&((NODE*)0)->frame==0x5c)?1:-1];
typedef char layout_NODE_group[((unsigned long)&((NODE*)0)->group==0xec)?1:-1];
typedef char layout_LM_low[((unsigned long)&((LM*)0)->low==0x0)?1:-1];
typedef char layout_LM_high[((unsigned long)&((LM*)0)->high==0x4)?1:-1];
typedef char layout_RULE_distanceEnabled[((unsigned long)&((RULE*)0)->distanceEnabled==0x0)?1:-1];
typedef char layout_RULE_angleEnabled[((unsigned long)&((RULE*)0)->angleEnabled==0x4)?1:-1];
typedef char layout_RULE_enterDistance[((unsigned long)&((RULE*)0)->enterDistance==0x8)?1:-1];
typedef char layout_RULE_stayDistance[((unsigned long)&((RULE*)0)->stayDistance==0x10)?1:-1];
typedef char layout_RULE_enterAngle[((unsigned long)&((RULE*)0)->enterAngle==0x18)?1:-1];
typedef char layout_RULE_stayAngle[((unsigned long)&((RULE*)0)->stayAngle==0x20)?1:-1];
typedef char layout_POLY_a[((unsigned long)&((POLY*)0)->a==0x0)?1:-1];
typedef char layout_POLY_b[((unsigned long)&((POLY*)0)->b==0x4)?1:-1];
typedef char layout_POLY_c[((unsigned long)&((POLY*)0)->c==0x8)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_P_node[((unsigned long)&((P*)0)->node==0x0)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x1c0)?1:-1];
typedef char layout_P_cooldown[((unsigned long)&((P*)0)->cooldown==0x1c8)?1:-1];
typedef char layout_P_active[((unsigned long)&((P*)0)->active==0x1cc)?1:-1];
typedef char layout_P_binding[((unsigned long)&((P*)0)->binding==0x1d0)?1:-1];
typedef char layout_P_target[((unsigned long)&((P*)0)->target==0x1d4)?1:-1];
typedef char layout_P_curve[((unsigned long)&((P*)0)->curve==0x1d8)?1:-1];
typedef char layout_P_progress[((unsigned long)&((P*)0)->progress==0x1dc)?1:-1];
typedef char layout_P_previousSelf[((unsigned long)&((P*)0)->previousSelf==0x1e0)?1:-1];
typedef char layout_P_previousTarget[((unsigned long)&((P*)0)->previousTarget==0x1f0)?1:-1];
typedef char layout_P_stamp[((unsigned long)&((P*)0)->stamp==0x200)?1:-1];
typedef char layout_P_heading[((unsigned long)&((P*)0)->heading==0x204)?1:-1];
typedef char layout_P_output[((unsigned long)&((P*)0)->output==0x210)?1:-1];
typedef char layout_P_rules[((unsigned long)&((P*)0)->rules==0x270)?1:-1];
typedef char layout_P_scale[((unsigned long)&((P*)0)->scale==0x338)?1:-1];
typedef char layout_P_remaining[((unsigned long)&((P*)0)->remaining==0x340)?1:-1];
typedef char layout_P_angle[((unsigned long)&((P*)0)->angle==0x350)?1:-1];
typedef char layout_P_simpleAngle[((unsigned long)&((P*)0)->simpleAngle==0x360)?1:-1];
typedef char layout_P_simpleClamp[((unsigned long)&((P*)0)->simpleClamp==0x370)?1:-1];
typedef char layout_WORK_nearest[((unsigned long)&((WORK*)0)->nearest==0x0)?1:-1];
typedef char layout_WORK_direction[((unsigned long)&((WORK*)0)->direction==0x10)?1:-1];
typedef char layout_WORK_unit[((unsigned long)&((WORK*)0)->unit==0x20)?1:-1];
typedef char layout_WORK_scalar[((unsigned long)&((WORK*)0)->scalar==0x30)?1:-1];
typedef char layout_WORK_objects[((unsigned long)&((WORK*)0)->objects==0x40)?1:-1];
typedef char layout_WORK_avoidanceScalar[((unsigned long)&((WORK*)0)->avoidanceScalar==0x140)?1:-1];
typedef char layout_WORK_simpleTarget[((unsigned long)&((WORK*)0)->simpleTarget==0x150)?1:-1];
typedef char layout_WORK_target[((unsigned long)&((WORK*)0)->target==0x160)?1:-1];
typedef char layout_WORK_self[((unsigned long)&((WORK*)0)->self==0x170)?1:-1];
typedef char layout_WORK_force[((unsigned long)&((WORK*)0)->force==0x180)?1:-1];
typedef char layout_WORK_selectorTarget[((unsigned long)&((WORK*)0)->selectorTarget==0x190)?1:-1];

typedef char layout_size_CURVE_FIELDS[(sizeof(CURVE_FIELDS)==8)?1:-1];
typedef char layout_curve_progress_adjacent[((unsigned long)&((P*)0)->progress-(unsigned long)&((P*)0)->curve==4)?1:-1];
