// Complete chain update WIP. The union retains the real phase-dependent matrix homes.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union V {qword q;float f[4];};
struct M3 {V r[3];};
struct M4 {V r[4];};
struct FRAME {M3 basis;V position;M4 world;char pad80[0x20];FRAME *parent;uint generation;};
struct CHAIN;
struct NODE {M3 basis;V segment,position,velocity;CHAIN *chain;FRAME *frame;int field68,field6C;};
struct CHAIN {int count;NODE *nodes;int substeps;float spring,linearDamping,angularDamping,angleLimit,time;V acceleration;char pad30[0x10];V previousPosition;};
struct FLAGS {uint bits;};
struct OWNER {char pad[0x40];FLAGS *flags;};
struct CLOCK {float t;union {float dt;int dtbits;};};
struct WORLD {char pad[0x3D58];uint generation;};
struct SIMULATION {V velocity,scalar;M3 matrices[3];};
struct ORIENTATION {V precedingVelocity;M3 rotation,output;};
struct KINETIC {V currentVelocity,currentPosition,delta,previousPosition,previousVelocity;};
struct WORK {union {SIMULATION simulation;ORIENTATION orientation;};V position,direction,deltaVelocity;M3 *output;KINETIC saved;};
extern CLOCK D_002DDED0;
extern V D_002A2DA0;
extern WORLD D_003DD490;
extern "C" {
qword func_0022D348(FRAME *,FRAME *,qword);
qword func_0022FC48(FRAME *,FRAME *,qword);
float func_0011E4B0(qword,qword,V *);
M3 *func_0011B500(M3 *,float,qword);
M3 *func_0011BA08(M3 *,qword,qword);
}
static inline qword LoadVF(const V &v){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(v));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarHome(V &home,float f){home.q=Scalar(f);return home.q;}
static inline qword ScalarWordHome(V &home,int bits){qword value;asm("qmtc2.ni %1,%0":"=j"(value):"r"(bits));home.q=value;return home.q;}
static inline qword DirectionFromPrevious(qword position,const V &previous){
 register qword value asm("vf2"),prior asm("vf1");
 asm("lqc2 %1,%2\n\tqmtc2.ni %3,%0\n\tvsub.xyzw %0,%0,%1":"=j"(value),"=j"(prior):"m"(previous),"r"(position));return value;
}
static inline qword DirectionFromParent(const V &position,const V &parent){
 register qword value asm("vf3"),prior asm("vf1");
 asm("lqc2 %1,%3\n\tlqc2 %0,%2\n\tvsub.xyzw %0,%0,%1":"=j"(value),"=j"(prior):"m"(position),"m"(parent));return value;
}
static inline qword FallbackDirection(){register qword value asm("$2");asm("lq %0,%1":"=r"(value):"m"(D_002A2DA0));return value;}
static inline qword VectorHome(V &home,qword value){asm("sqc2 %1,%0":"=m"(home.q):"j"(value));return value;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword Advance(qword p,qword v,qword k){qword r;__asm__("vadda.xyzw ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p),"j"(v),"j"(k));return r;}
static inline qword Divide(qword v,qword scalar){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(scalar));return r;}
static inline qword DotV(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword LengthV(qword v){qword r=DotV(v,v);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return r;}
static inline qword CrossXYZ(qword a,qword b){__asm__("vopmula.xyz ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0":"+j"(a):"j"(b));return a;}
static inline qword RotateSeed(const M3 &m,qword v,qword seed){__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(seed):"j"(LoadVF(m.r[0])),"j"(LoadVF(m.r[1])),"j"(LoadVF(m.r[2])),"j"(v));return seed;}
static inline qword Rotate(const M3 &m,qword v){return RotateSeed(m,v,v);}
static inline qword BlendVelocity(qword velocity,qword delta,qword bend,qword acceleration,qword linear,qword angular,qword spring,qword step){qword r;
 __asm__("vmulax.xyzw ACC,%1,%5x\n\tvmaddax.xyzw ACC,%2,%6x\n\tvmaddax.xyzw ACC,%3,%7x\n\tvmaddx.xyzw %0,%4,%8x":"=j"(r):"j"(velocity),"j"(delta),"j"(bend),"j"(acceleration),"j"(linear),"j"(angular),"j"(spring),"j"(step));return r;}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline void RootBasis(M3 &result,const M3 &world,const M3 &basis) {
 qword a=Rotate(world,LoadVF(basis.r[0])),b=Rotate(world,LoadVF(basis.r[1]));
 qword c=RotateSeed(world,LoadVF(basis.r[2]),LoadVF(world.r[0]));
 result.r[0].q=a;result.r[1].q=b;result.r[2].q=c;
}
static inline void RotateBasis(M3 &result,const M3 &rotation,const M3 &basis) {
 qword c=Rotate(rotation,LoadVF(basis.r[2]));
 qword a=Rotate(rotation,LoadVF(basis.r[0])),b=Rotate(rotation,LoadVF(basis.r[1]));
 result.r[0].q=a;result.r[1].q=b;result.r[2].q=c;
}
static inline qword RotateRows(qword a,qword b,qword c,qword v,qword seed){
 asm("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(seed):"j"(a),"j"(b),"j"(c),"j"(v));return seed;
}
static inline void RootGeometry(WORK &w,const M3 &world,const NODE &node){
 qword a=LoadVF(world.r[0]),b=LoadVF(world.r[1]),c=LoadVF(world.r[2]);
 qword u=LoadVF(node.basis.r[0]),v=LoadVF(node.basis.r[1]);
 u=RotateRows(a,b,c,u,u);v=RotateRows(a,b,c,v,v);
 qword last=LoadVF(node.basis.r[2]);a=RotateRows(a,b,c,last,a);
 qword segment=LoadVF(node.segment);qword direction=RotateRows(u,v,a,segment,b);
 w.simulation.matrices[1].r[0].q=u;w.simulation.matrices[0].r[0].q=u;
 w.simulation.matrices[1].r[1].q=v;w.simulation.matrices[0].r[1].q=v;
 w.simulation.matrices[1].r[2].q=a;w.simulation.matrices[0].r[2].q=a;
 w.direction.q=direction;
}
static inline void FinishBasis(WORK &w,const M3 &basis,FRAME &frame){
 qword a=LoadVF(w.orientation.output.r[0]),b=LoadVF(w.orientation.output.r[1]),c=LoadVF(w.orientation.output.r[2]);
 qword last=LoadVF(basis.r[2]);last=RotateRows(a,b,c,last,last);
 qword first=LoadVF(basis.r[0]);first=RotateRows(a,b,c,first,first);
 qword second=LoadVF(basis.r[1]);second=RotateRows(a,b,c,second,second);
 w.orientation.rotation.r[0].q=a;w.orientation.rotation.r[1].q=b;w.orientation.rotation.r[2].q=c;
 w.simulation.matrices[2].r[0].q=first;w.simulation.matrices[2].r[1].q=second;w.simulation.matrices[2].r[2].q=last;
 w.orientation.output.r[0].q=first;w.orientation.output.r[1].q=second;w.orientation.output.r[2].q=last;
 frame.basis=w.orientation.output;
}
static inline qword LimitRotation(WORK &w,qword delta){
 qword a=LoadVF(w.simulation.matrices[1].r[0]),b=LoadVF(w.simulation.matrices[1].r[1]),c=LoadVF(w.simulation.matrices[1].r[2]);
 w.simulation.matrices[0].r[0].q=a;
 qword result=RotateRows(a,b,c,delta,delta);
 w.simulation.matrices[0].r[1].q=b;w.simulation.matrices[0].r[2].q=c;
 return result;
}
extern "C" void func_0021CB18(OWNER *owner,NODE *node){
 WORK w;
 register unsigned int clockPort asm("$2");
 register CLOCK *clock asm("$5");
 asm("lui %0,%%hi(%1)":"=r"(clockPort):"i"(&D_002DDED0));
 asm("addiu %0,%1,%%lo(%2)":"=r"(clock):"r"(clockPort),"i"(&D_002DDED0));
 FRAME *frame=node->frame;
 float currentTime;
 {
  register float time asm("$f1");
  asm("lwc1 %0,%%lo(%2)(%1)":"=f"(time):"r"(clockPort),"i"(&D_002DDED0):"memory");
  currentTime=time;
 }
 CHAIN *chain=node->chain;FRAME *parent;
 {
  asm("la %0,%2+%a1":"=r"(clockPort):"p"(&w),"i"((int)&((WORK *)0)->orientation.output));
  parent=frame->parent;w.output=(M3 *)clockPort;
 }
 if(currentTime!=chain->time){
  if(node==chain->nodes){
   qword position=frame->world.r[3].q;w.position.q=position;
   if(owner->flags->bits&0x10)w.simulation.velocity.q=func_0022D348(parent,0,position);
   else{
    register unsigned int word asm("$5")=(unsigned int)clock;
    register qword dt asm("vf1"),previous asm("vf2"),point asm("vf3");
    asm("lw %0,%6\n\tlqc2 %2,%7\n\tqmtc2.ni %0,%1\n\tlqc2 %3,%8\n\tvsub.xyzw %2,%3,%2\n\tsqc2 %1,%4\n\tvdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %1,%2,Q\n\tsqc2 %1,%5"
        :"+r"(word),"=&j"(dt),"=&j"(previous),"=&j"(point),"=m"(w.simulation.scalar.q),"=m"(w.simulation.velocity.q)
        :"m"(clock->dtbits),"m"(chain->previousPosition.q),"m"(w.position.q));
   }
   chain->previousPosition.q=position;
   {
    register M3 *output asm("$3");
    asm("la %0,%3+%a2\n\tsw %0,%1":"=&r"(output),"=m"(w.output):"p"(&w),"i"((int)&((WORK *)0)->orientation.output));
   }
   RootGeometry(w,*(M3 *)&parent->world,*node);
  }
  else{
   int previousCount=0;
   for(int offset=0;previousCount<node-chain->nodes;offset+=sizeof(NODE)){
    NODE *previous=(NODE *)((int)chain->nodes+offset);previousCount++;
    previous->position.q=func_0022FC48(previous->frame,0,previous->segment.q);
    previous->velocity.q=func_0022D348(previous->frame,0,previous->position.q);
   }
   w.simulation.velocity.q=node[-1].velocity.q;w.position.q=node[-1].position.q;
   if(previousCount>=2)w.direction.q=DirectionFromPrevious(w.position.q,node[-2].position);
   else w.direction.q=DirectionFromParent(w.position,parent->world.r[3]);
  }
  float step=D_002DDED0.dt/(float)chain->substeps;
  for(int iteration=0;iteration<chain->substeps;iteration++){
   float offset=(iteration-chain->substeps+1)*step;
   qword scalar=ScalarHome(w.simulation.scalar,offset);
   register qword velocity asm("vf11")=LoadVF(w.simulation.velocity),position asm("vf10")=Advance(LoadVF(w.position),velocity,scalar);
   qword previousDelta=w.direction.q;
   for(int i=node-chain->nodes;i<chain->count;i++){
    NODE *entry=&chain->nodes[i];
    qword deltaArgument;
    {
     register qword previousPosition asm("vf10")=position,previousVelocity asm("vf11")=velocity;
     register qword currentPosition asm("vf8"),currentVelocity asm("vf7"),delta asm("vf9"),deltaVelocity asm("vf5");
     asm("lqc2 %0,%6\n\tlqc2 %1,%7\n\tvsub.xyzw %2,%0,%4\n\tvsub.xyzw %3,%1,%5"
         :"=&j"(currentPosition),"=&j"(currentVelocity),"=j"(delta),"=j"(deltaVelocity)
         :"j"(previousPosition),"j"(previousVelocity),"m"(entry->position.q),"m"(entry->velocity.q));
     asm("sqc2 %5,%0\n\tsqc2 %6,%1\n\tsqc2 %7,%2\n\tsqc2 %8,%3\n\tsqc2 %9,%4"
         :"=m"(w.saved.currentPosition.q),"=m"(w.saved.currentVelocity.q),"=m"(w.saved.delta.q),"=m"(w.saved.previousPosition.q),"=m"(w.saved.previousVelocity.q)
         :"j"(currentPosition),"j"(currentVelocity),"j"(delta),"j"(previousPosition),"j"(previousVelocity));
     deltaArgument=delta;w.deltaVelocity.q=deltaVelocity;
    }
    float angle=func_0011E4B0(deltaArgument,previousDelta,&w.simulation.scalar);
    register qword currentVelocity asm("vf7")=*(volatile qword *)&w.saved.currentVelocity.q;
    register qword currentPosition asm("vf8")=*(volatile qword *)&w.saved.currentPosition.q;
    register qword delta asm("vf9")=*(volatile qword *)&w.saved.delta.q;
    register qword precedingPosition asm("vf10")=*(volatile qword *)&w.saved.previousPosition.q;
    register qword precedingVelocity asm("vf11")=*(volatile qword *)&w.saved.previousVelocity.q;
    if(chain->angleLimit<angle){
     func_0011B500(&w.simulation.matrices[1],angle-chain->angleLimit,w.simulation.scalar.q);
     asm("lqc2 $vf1,%4\n\tlqc2 $vf2,%5\n\tlqc2 $vf3,%6\n\tlqc2 %0,%7\n\tsqc2 $vf1,%1\n\tvmulax.xyz ACC,$vf1,%0x\n\tvmadday.xyz ACC,$vf2,%0y\n\tvmaddz.xyz %0,$vf3,%0z\n\tsqc2 $vf2,%2\n\tsqc2 $vf3,%3"
         :"=j"(delta),"=m"(w.simulation.matrices[0].r[0].q),"=m"(w.simulation.matrices[0].r[1].q),"=m"(w.simulation.matrices[0].r[2].q)
         :"m"(w.simulation.matrices[1].r[0].q),"m"(w.simulation.matrices[1].r[1].q),"m"(w.simulation.matrices[1].r[2].q),"m"(w.saved.delta.q):"vf1","vf2","vf3");
     precedingVelocity=*(volatile qword *)&w.saved.previousVelocity.q;
     currentVelocity=*(volatile qword *)&w.saved.currentVelocity.q;
     precedingPosition=*(volatile qword *)&w.saved.previousPosition.q;
     currentPosition=Add(precedingPosition,delta);
    }
    register const qword *fallbackAddress asm("$21")=&D_002A2DA0.q;
    register float linear asm("$f0"),spring asm("$f2"),angular asm("$f1");
    asm("lwc1 %0,%3\n\tlwc1 %1,%4\n\tneg.s %0,%0\n\tlwc1 %2,%5\n\tmul.s %1,%1,%6"
        :"=f"(linear),"=f"(spring),"=f"(angular):"m"(chain->linearDamping),"m"(chain->spring),"m"(chain->angularDamping),"f"(angle));
    register float unit asm("$f3")=1.0f;angular=-angular;
    register qword bend asm("vf5");
    asm("lqc2 %0,%3\n\tmul.s %1,%1,%5\n\tvopmula.xyz ACC,%0,%4\n\tvopmsub.xyz %0,%4,%0\n\tmul.s %2,%2,%5"
        :"=j"(bend),"+f"(linear),"+f"(spring):"m"(w.simulation.scalar.q),"j"(delta),"f"(step));
    register qword velocityDelta asm("vf12");asm("lqc2 %0,%1":"=j"(velocityDelta):"m"(w.deltaVelocity.q));
    angular*=step;register float tolerance asm("$f4")=0.0001f;
    linear=Max(-1.0f,linear);
    register qword stepQ asm("vf6");
    asm("mfc1 $2,%2\n\tadd.s %1,%1,%3\n\tqmtc2.ni $2,%0":"=j"(stepQ),"+f"(linear):"f"(step),"f"(unit):"$2");
    register int scalarBits asm("$3");asm("mfc1 %0,%1":"=r"(scalarBits):"f"(spring));
    angular=Max(-1.0f,angular);
    register qword springQ asm("vf4"),linearQ asm("vf3"),angularQ asm("vf2"),fallback asm("$2");
    asm("qmtc2.ni %0,%1\n\tlq %4,%8\n\tmfc1 $4,%6\n\tqmtc2.ni $4,%2\n\tmfc1 %0,%7\n\tsqc2 %2,%5\n\tqmtc2.ni %0,%3"
        :"+r"(scalarBits),"=j"(springQ),"=j"(linearQ),"=j"(angularQ),"=&r"(fallback),"=m"(w.simulation.matrices[1].r[0].q)
        :"f"(linear),"f"(angular),"m"(*fallbackAddress):"$4");
    *(volatile qword *)&w.simulation.matrices[1].r[0].q=angularQ;
    *(volatile qword *)&w.simulation.matrices[1].r[0].q=springQ;
    *(volatile qword *)&w.simulation.matrices[1].r[0].q=stepQ;
    register qword acceleration asm("vf1");asm("lqc2 %0,%1":"=j"(acceleration):"m"(chain->acceleration.q));
    asm("vmulax.xyzw ACC,%0,%4x\n\tvmaddax.xyzw ACC,%1,%5x\n\tvmaddax.xyzw ACC,%2,%6x\n\tvmaddx.xyzw %0,%3,%7x":"+j"(currentVelocity):"j"(velocityDelta),"j"(bend),"j"(acceleration),"j"(linearQ),"j"(angularQ),"j"(springQ),"j"(stepQ));
    asm("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(currentPosition):"j"(currentVelocity),"j"(stepQ));
    register qword displacement asm("vf3"),length asm("vf1");
    asm("vsub.xyzw %0,%2,%3\n\tvmul.xyz %1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\tvsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q"
        :"=&j"(displacement),"=&j"(length):"j"(currentPosition),"j"(precedingPosition):"vf2");
    qword directionValue;
    if(X(length)<tolerance)directionValue=fallback;
    else directionValue=Divide(displacement,length);
    register qword direction asm("vf5")=directionValue;
    asm("sqc2 %1,%0":"=m"(w.simulation.scalar.q):"j"(direction));
    register qword normal asm("vf2"),previousNormal asm("vf4");
    asm("vmul.xyz %0,%2,%4\n\tvaddw.x $vf1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf1,%0z\n\tvmul.xyz %1,%3,%4\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %1,$vf3,%1z"
        :"=&j"(normal),"=&j"(previousNormal):"j"(currentVelocity),"j"(precedingVelocity),"j"(direction):"vf1","vf3");
    register qword rest asm("vf1");
    asm("vmulx.xyzw %1,%6,%1x\n\tvsub.xyzw %1,%0,%1\n\tvmulx.xyzw %2,%6,%2x\n\tlqc2 %3,%5\n\tvadd.xyzw %0,%2,%1\n\tvmul.xyz %3,%3,%3\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,%3,%3y\n\tvmaddz.x %3,$vf3,%3z\n\tsqc2 %0,%4"
        :"+j"(currentVelocity),"+j"(normal),"+j"(previousNormal),"=&j"(rest),"=m"(entry->velocity.q):"m"(entry->segment.q),"j"(direction):"vf3");
    asm("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(rest));
    asm("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(currentPosition):"j"(precedingPosition),"j"(direction),"j"(rest));
    entry->position.q=currentPosition;
    velocity=currentVelocity;position=currentPosition;previousDelta=delta;
   }
  }
  chain->time=D_002DDED0.t;
 }
 qword localPosition=func_0022FC48(0,parent,node->position.q);
 qword to=Sub(localPosition,LoadVF(frame->position));
 qword from=Rotate(node->basis,LoadVF(node->segment));
 {
  register M3 *output asm("$4");
  asm("lw %0,%1":"=r"(output):"m"(w.output));
  func_0011BA08(output,from,to);
 }
 FinishBasis(w,node->basis,*frame);
 frame->basis.r[1].f[3]=0.0f;frame->basis.r[2].f[3]=0.0f;frame->basis.r[0].f[3]=0.0f;
 frame->generation=++D_003DD490.generation;
}
