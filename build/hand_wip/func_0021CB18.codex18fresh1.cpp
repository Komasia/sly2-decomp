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
struct WORK {union {SIMULATION simulation;ORIENTATION orientation;};V position,direction,deltaVelocity;M3 *output;};
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
 WORK w;w.output=&w.orientation.output;
 FRAME *frame=node->frame;CHAIN *chain=node->chain;FRAME *parent=frame->parent;
 if(D_002DDED0.t!=chain->time){
  if(node==chain->nodes){
   qword position=frame->world.r[3].q;w.position.q=position;
   if(owner->flags->bits&0x10)w.simulation.velocity.q=func_0022D348(parent,0,position);
   else{qword dt=ScalarWordHome(w.simulation.scalar,D_002DDED0.dtbits);w.simulation.velocity.q=Divide(Sub(LoadVF(w.position),LoadVF(chain->previousPosition)),dt);}
   chain->previousPosition.q=position;
   w.output=&w.orientation.output;
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
   qword velocity=LoadVF(w.simulation.velocity),position=Advance(LoadVF(w.position),velocity,scalar);
   qword previousDelta=w.direction.q;
   for(int i=node-chain->nodes;i<chain->count;i++){
    NODE *entry=&chain->nodes[i];
    qword currentPosition=LoadVF(entry->position),currentVelocity=LoadVF(entry->velocity);
    qword delta=Sub(currentPosition,position),deltaVelocity=Sub(currentVelocity,velocity);w.deltaVelocity.q=deltaVelocity;
    float angle=func_0011E4B0(delta,previousDelta,&w.simulation.scalar);
    if(chain->angleLimit<angle){
     func_0011B500(&w.simulation.matrices[1],angle-chain->angleLimit,w.simulation.scalar.q);
     delta=LimitRotation(w,delta);currentPosition=Add(position,delta);
    }
    qword bend=CrossXYZ(LoadVF(w.simulation.scalar),delta);
    float spring=chain->spring*angle*step;
    float linear=Max(-1.0f,-chain->linearDamping*step)+1.0f;
    float angular=Max(-1.0f,-chain->angularDamping*step);
    qword linearQ=ScalarHome(w.simulation.matrices[1].r[0],linear);
    qword angularQ=ScalarHome(w.simulation.matrices[1].r[0],angular);
    qword springQ=ScalarHome(w.simulation.matrices[1].r[0],spring);
    qword stepQ=ScalarHome(w.simulation.matrices[1].r[0],step);
    currentVelocity=BlendVelocity(currentVelocity,LoadVF(w.deltaVelocity),bend,LoadVF(chain->acceleration),linearQ,angularQ,springQ,stepQ);
    currentPosition=Advance(currentPosition,currentVelocity,stepQ);
    qword displacement=Sub(currentPosition,position),length=LengthV(displacement),fallback=FallbackDirection();
    qword direction;
    if(X(length)<0.0001f)direction=fallback;else direction=Divide(displacement,length);
    direction=VectorHome(w.simulation.scalar,direction);
    qword normalVelocity=Scale(direction,DotV(currentVelocity,direction));
    qword previousNormalVelocity=Scale(direction,DotV(velocity,direction));
    currentVelocity=Add(previousNormalVelocity,Sub(currentVelocity,normalVelocity));
    qword rest=LengthV(LoadVF(entry->segment));
    entry->velocity.q=currentVelocity;
    currentPosition=Advance(position,direction,rest);
    entry->position.q=currentPosition;
    velocity=currentVelocity;position=currentPosition;previousDelta=delta;
   }
  }
  chain->time=D_002DDED0.t;
 }
 qword localPosition=func_0022FC48(0,parent,node->position.q);
 qword to=Sub(localPosition,LoadVF(frame->position));
 qword from=Rotate(node->basis,LoadVF(node->segment));
 func_0011BA08(w.output,from,to);
 FinishBasis(w,node->basis,*frame);
 frame->basis.r[1].f[3]=0.0f;frame->basis.r[2].f[3]=0.0f;frame->basis.r[0].f[3]=0.0f;
 frame->generation=++D_003DD490.generation;
}
