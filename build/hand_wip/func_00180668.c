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
typedef struct P{NODE node;char padF0[0xD0];int state;float stateTime;int cooldown,active;void*binding;NODE*target;void*curve;float progress;U previousSelf,previousTarget;float stamp,heading;char pad208[8];U output;char pad220[0x50];RULE rules[5];float scale;char pad33C[4];POLY remaining;char pad34C[4];POLY angle;char pad35C[4];POLY simpleAngle;char pad36C[4];LM simpleClamp;}P;
typedef struct WORK{U nearest,direction,unit,scalar;NODE*objects[64];U avoidanceScalar,simpleTarget,target,self,force,selectorTarget;}WORK;
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
extern void func_001E7380(void*,qword,void*,qword*,qword*,float*,float*,float);
extern float func_001E6648(void*),func_00154C90(void*);
extern int func_0015E9C8(void*,int,int,void*,int,NODE**);
extern qword func_0011E9F8(qword,float);
static inline ulong Alive(NODE*p){return(p->flags>>60)&1;}
static inline qword Velocity(P*p){VTE*e=&p->node.vt[33];return((qword(*)(void*))e->fn)((char*)p+e->delta);}
static inline qword Transfer(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword ReadQword(const qword*p){qword r;__asm__("lq %0,%1":"=r"(r):"m"(*p));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword WordScalar(const float*p){int bits;qword r;__asm__("lw %0,%2\n\tqmtc2.ni %0,%1":"=r"(bits),"=j"(r):"m"(*p));return r;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword AddScale(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Squared(qword a){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));return d;}
static inline qword Root(qword a){register qword r __asm__("vf2");__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(a));return r;}
static inline float FloatX(qword a){int bits;float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float FloatY(qword a){int bits;float f;__asm__("prot3w %0,%1":"=r"(bits):"r"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float GprX(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Heading(qword a){return func_002458F0(FloatY(a),GprX(a));}
static inline float Length(qword a){return FloatX(Root(Squared(a)));}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword UnitOr(qword a,qword fallback){qword length=Root(Squared(a));if(FloatX(length)<0.0001f)return fallback;return Divide(a,length);}
static inline float Dot(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));return FloatX(d);}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
static inline float Clamp(float f,LM*p){float low=p->low,high=p->high;if(f<low)f=low;else if(high<f)f=high;return f;}
void func_00180668(P*p){
 WORK w;float distance,angle,amplitude;
 func_001F36E0(p);
 if(p->state==2||p->state==4)if(func_0017F550(p))func_00181268(p,0);
 if(p->state!=0&&p->state!=4)if(!p->target||!Alive(p->target))func_00181268(p,0);
 if(!p->active&&p->target&&Alive(p->target)){
  RULE*current=&p->rules[p->state];register qword delta __asm__("vf1");float distance,angle;
  w.selectorTarget.q=Transfer(func_001A62E8(p->target));
  delta=Sub(w.selectorTarget.q,func_001A62E8(p));
  distance=Length(delta);
  angle=func_0011CF60(Heading(func_001A6FC0(0,p,delta)));
  {int accept;
   accept=current->distanceEnabled?func_0011D910(&current->stayDistance,distance):current->angleEnabled;
   if(!accept)goto search_state;
   if(!current->angleEnabled)goto dispatch;
   if(func_0011D910(&current->stayAngle,angle))goto dispatch;
  }
search_state:{
   int state=4;
   RULE*rule=&p->rules[4];
   goto search_test;
search_next:
   --state;if(state<=0)goto dispatch;
search_test:{
   int accept;current=rule;
   accept=current->distanceEnabled?func_0011D910(&current->enterDistance,distance):current->angleEnabled;
   if(!accept){--rule;goto search_next;}
   if(current->angleEnabled&&!func_0011D910(&current->enterAngle,angle)){--rule;goto search_next;}
   func_00181268(p,state);
  }
 }
 }
dispatch:
 switch(p->state){
 case 0:break;
 case 1:case 2:{
  if(!p->cooldown){
   FRAME*frame=p->node.frame;qword delta;float heading;
   w.simpleTarget.q=func_001A62E8(p->target);
   delta=Sub(w.simpleTarget.q,func_001A62E8(p));
   heading=func_0011CF60(Heading(func_0022FCC8(0,frame->space,delta)));
   p->heading=Clamp(Evaluate(&p->simpleAngle,heading),&p->simpleClamp);
  }
  break;
 }
 case 3:{
  w.target.q=func_001A62E8(p->target);w.self.q=func_001A62E8(p);
  (void)Velocity(p);
  if(Length(Sub(w.target.q,p->previousTarget.q))>D_002BE820||Length(Sub(w.self.q,p->previousSelf.q))>D_002BE820||D_002DDED0.time-p->stamp>D_002BE824){
   (void)func_001C02D0(p->binding,w.self.q,w.target.q,p->curve);
   p->progress=0.0f;p->previousTarget=w.target;p->previousSelf=w.self;p->stamp=D_002DDED0.time;
  }
  func_001E7380(p->curve,w.self.q,0,&w.nearest.q,&w.direction.q,0,&p->progress,p->progress);
  w.scalar.q=WordScalar(&D_002BE828);
  w.unit.q=UnitOr(Sub(AddScale(w.nearest.q,w.direction.q,w.scalar.q),w.self.q),D_002A2DD0.q);
  distance=func_001E6648(p->curve)-p->progress;
  angle=Heading(func_001A6FC0(0,p,w.unit.q));
  {float response=func_00154C90(D_002DE578);
   float remaining=Clamp(Evaluate(&p->remaining,distance),&D_002BBB60);
   float turn=Clamp(Evaluate(&p->angle,angle),&D_002BBB60);
   float gain=Clamp(Evaluate(&D_002BE830,response),&D_002BBB60);
   amplitude=((remaining*turn)*gain)*p->scale;
  }
  w.scalar.q=Scalar(amplitude);w.force.q=Scale(w.unit.q,w.scalar.q);
  {int count=func_0015E9C8(D_003DD490,0x105,0x49,0,64,w.objects);
   NODE**current=w.objects;
   if(count>0)do{
    NODE*object=*current;
    if(object!=(NODE*)p&&object->group!=p->node.group){
     qword length;
     w.scalar.q=Sub(w.self.q,func_001A62E8(object));w.scalar.i[2]=0;
     length=Root(Squared(Transfer(ReadQword(&w.scalar.q))));
     if(FloatX(length)<0.0001f)w.scalar=D_002A2DA0;else w.scalar.q=Divide(w.scalar.q,length);
     {float weight=Clamp(Evaluate(&D_002BE840,FloatX(length)),&D_002BE850);
      float facing=Clamp(Evaluate(&D_002BE860,Dot(w.scalar.q,w.unit.q)),&D_002BBB60);
      w.avoidanceScalar.q=Scalar(weight*facing);
      w.force.q=AddScale(w.force.q,w.scalar.q,w.avoidanceScalar.q);
     }
    }
    current++;
   }while(--count);
  }
  p->output.q=func_0011E9F8(w.force.q,amplitude);
  p->heading=func_002458F0(w.unit.f[1],w.unit.f[0]);
  break;
 }
 case 4:break;
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
