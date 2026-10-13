// Integrate the remaining chain segments and update the attached local basis.
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
struct CLOCK {float t,dt;};
struct WORLD {char pad[0x3D58];uint generation;};
struct WORK {V velocity,scalar;M3 matrices[3];V position,direction,deltaVelocity;M3 *output;};
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
static inline float Max(float a,float b){return a<b?b:a;}
static inline M3 RootBasis(const M3 &world,const M3 &basis) return result {
 qword a=Rotate(world,LoadVF(basis.r[0])),b=Rotate(world,LoadVF(basis.r[1]));
 qword c=RotateSeed(world,LoadVF(basis.r[2]),LoadVF(world.r[0]));
 result.r[0].q=a;result.r[1].q=b;result.r[2].q=c;
}
static inline M3 RotateBasis(const M3 &rotation,const M3 &basis) return result {
 qword c=Rotate(rotation,LoadVF(basis.r[2]));
 qword a=Rotate(rotation,LoadVF(basis.r[0])),b=Rotate(rotation,LoadVF(basis.r[1]));
 result.r[0].q=a;result.r[1].q=b;result.r[2].q=c;
}
static inline M3 BendRotation(float angle,qword axis) return result {func_0011B500(&result,angle,axis);}
extern "C" void func_0021CB18(OWNER *owner,NODE *node){
 WORK w;w.output=(M3 *)&w.matrices[0].r[2];
 FRAME *frame=node->frame;CHAIN *chain=node->chain;FRAME *parent=frame->parent;
 if(D_002DDED0.t!=chain->time){
  if(node==chain->nodes){
   qword position=frame->world.r[3].q;w.position.q=position;
   if(owner->flags->bits&0x10)w.velocity.q=func_0022D348(parent,0,position);
   else{qword dt=Scalar(D_002DDED0.dt);w.scalar.q=dt;w.velocity.q=Divide(Sub(LoadVF(w.position),LoadVF(chain->previousPosition)),dt);}
   chain->previousPosition.q=position;
   w.output=(M3 *)&w.matrices[0].r[2];
   w.matrices[1]=RootBasis(*(M3 *)&parent->world,node->basis);
   w.matrices[0]=w.matrices[1];
   w.direction.q=RotateSeed(w.matrices[0],LoadVF(node->segment),LoadVF(parent->world.r[1]));
  }
  else{
   int previousCount=0;
   for(int offset=0;previousCount<node-chain->nodes;offset+=sizeof(NODE)){
    NODE *previous=(NODE *)((int)chain->nodes+offset);previousCount++;
    previous->position.q=func_0022FC48(previous->frame,0,previous->segment.q);
    previous->velocity.q=func_0022D348(previous->frame,0,previous->position.q);
   }
   w.velocity.q=node[-1].velocity.q;w.position.q=node[-1].position.q;
   if(previousCount>=2)w.direction.q=Sub(LoadVF(w.position),LoadVF(node[-2].position));
   else w.direction.q=Sub(LoadVF(w.position),LoadVF(parent->world.r[3]));
  }
  float step=D_002DDED0.dt/(float)chain->substeps;
  for(int iteration=0;iteration<chain->substeps;iteration++){
   float offset=(iteration-chain->substeps+1)*step;
   qword scalar=Scalar(offset);w.scalar.q=scalar;
   qword velocity=LoadVF(w.velocity),position=Advance(LoadVF(w.position),velocity,scalar);
   qword previousDelta=w.direction.q;
   for(int i=node-chain->nodes;i<chain->count;i++){
    NODE *entry=&chain->nodes[i];
    qword currentPosition=LoadVF(entry->position),currentVelocity=LoadVF(entry->velocity);
    qword delta=Sub(currentPosition,position),deltaVelocity=Sub(currentVelocity,velocity);w.deltaVelocity.q=deltaVelocity;
    float angle=func_0011E4B0(delta,previousDelta,&w.scalar);
    if(chain->angleLimit<angle){
     w.matrices[1]=BendRotation(angle-chain->angleLimit,w.scalar.q);
     w.matrices[0]=w.matrices[1];delta=Rotate(w.matrices[0],delta);currentPosition=Add(position,delta);
    }
    qword bend=CrossXYZ(LoadVF(w.scalar),delta);
    float spring=chain->spring*angle*step;
    float linear=Max(-1.0f,-chain->linearDamping*step)+1.0f;
    float angular=Max(-1.0f,-chain->angularDamping*step);
    qword linearQ=Scalar(linear),angularQ=Scalar(angular),springQ=Scalar(spring),stepQ=Scalar(step);
    w.matrices[1].r[0].q=linearQ;w.matrices[1].r[0].q=angularQ;
    w.matrices[1].r[0].q=springQ;w.matrices[1].r[0].q=stepQ;
    currentVelocity=BlendVelocity(currentVelocity,LoadVF(w.deltaVelocity),bend,LoadVF(chain->acceleration),linearQ,angularQ,springQ,stepQ);
    currentPosition=Advance(currentPosition,currentVelocity,stepQ);
    qword displacement=Sub(currentPosition,position),length=LengthV(displacement),direction=D_002A2DA0.q;
    if(!(X(length)<0.0001f))direction=Divide(displacement,length);
    w.scalar.q=direction;
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
 M3 result=RotateBasis(*w.output,node->basis);
 *(M3 *)&w.scalar=*w.output;
 w.matrices[2]=result;*w.output=w.matrices[2];
 frame->basis=*w.output;
 frame->basis.r[1].f[3]=0.0f;frame->basis.r[2].f[3]=0.0f;frame->basis.r[0].f[3]=0.0f;
 frame->generation=++D_003DD490.generation;
}
