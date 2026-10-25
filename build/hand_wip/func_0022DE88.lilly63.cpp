// T1639 lilly62 = lilly61 + MEM-operand ("jV") macros SUB_M/ADD_M/ADVANCE_M/TRAPEZOID_M/COMBINATION_M used at 3 sites (angular desired/delta, kind-1 Trapezoid): aligned 104 / norm 43 (lilly61: 108 / 45). NOT a match. Notes: notes/220000.md "22DE88 (Lilly, T1639)".
// Advance every transform record, compose its world frame, and consume update flags.
// (older header lines below are history)
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned short ushort;
union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];M3(){}M3(const M3 &m){r[0].q=m.r[0].q;r[1].q=m.r[1].q;r[2].q=m.r[2].q;}M3 &operator=(const M3 &m){r[0].q=m.r[0].q;r[1].q=m.r[1].q;r[2].q=m.r[2].q;return *this;}};
struct M4 {M3 basis;V position;};
struct PROFILE {float speed,terminal,duration;};
struct CLOCK {float t,dt;};
union FLAGS {int bits;int *address;};
struct JOB;
struct E;
struct S {char unknown0[0x10];S *parent;char unknown14[0x2C];FLAGS flags;char unknown44[0xC];int count;E *records;};
union ACTION {struct {short type,state;} fields;uint pair;};
union SOURCE {E *origin;void *resource;float deadline;};
struct PAYLOAD {V value[4];};
struct E {
 M4 local,world;
 float begin,end;float *time,*rate;
 JOB *jobs;int kind;ACTION action;int tag;
 E *parent;int priority;SOURCE source;ushort force,damping;
 V velocity;PAYLOAD data;
};
struct WORLD {char unknown0[0x3D58];int generation;};
struct RATES {float angle,angular,linear,springAngle;};
extern WORLD D_003DD490;
extern CLOCK D_002DDED0;
extern V D_002A2DD0,D_002A2DA0;
extern PROFILE D_002C45F0,D_002C4600,D_002C4610;
extern float D_002C45FC,D_002C461C,D_002C4620,D_002C4624,D_002C4628,D_002C462C,D_002C4630;
extern "C" {
 void func_0022DD00(S *,E *);
 int func_0011D4D0(float,float,float);
 V *func_00256D18(V *,qword);
 M3 func_0011B500(float,qword);
 M3 func_0011B570(qword);
 void func_0011B3D0(M3 *);
 M3 func_0011BC00(const M3 *,const M3 *);
 void func_0011BCF8(M3 *,float *,V *);
 qword func_0011BFF0(M3 *);
 float func_0011CF60(float);
 float func_0011D018(float,float,float,PROFILE *,float *);
 void func_00117120(float,float,float,qword,qword,qword,qword,V *,V *,V *);
 M4 func_0022C8C0(E *,qword);
 qword func_0022CA18(E *,M4 *);
 qword func_0022CAD0(qword,qword);
 void func_002303A0(S *,E *,int);
 void func_00186A50(S *,void *);
 void func_001604E8(S *,void *);
 void func_0021CB18(S *,void *);
 void func_0022FA20(S *);
}
struct VU_FLOAT {qword qw;};
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}
static inline qword ScaleV(qword a,VU_FLOAT f){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(f.qw));return r;}
static inline qword LoadVF(const V &home){qword value;asm("lqc2 %0,%1":"=j"(value):"m"(home.q));return value;}
static inline qword LoadCPU(const V &home){qword value;asm("lq %0,%1":"=r"(value):"m"(home.q));return value;}
static inline qword Scalar(float f){V home;qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));home.q=q;return q;}
static inline qword LoadAfter(const V &home,qword dep){qword value;asm("lqc2 %0,%1":"=j"(value):"m"(home.q),"j"(dep));return value;}
static inline qword AdvanceV(qword p,qword velocity,qword time){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p),"j"(velocity),"j"(time),"j"(velocity),"j"(velocity));return r;}
static inline qword ScalarQ(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
#define SUB_MK(a,b,k) ({qword _r;__asm__("vsub.xyzw %0,%1,%2":"=j"(_r):"jV"(a),"jV"(b),"j"(k));_r;})
static inline qword AdvA12(qword p,qword v,qword t){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p),"j"(v),"j"(t),"j"(v));return r;}
static inline qword AdvS(qword p,qword v,float f){V home;qword t=ScalarQ(f);qword r=AdvA12(p,v,t);home.q=t;return r;}
#define SUB_MK12(a,b,k) ({qword _r;__asm__("vsub.xyzw %0,%1,%2":"=j"(_r):"jV"(a),"jV"(b),"j"(k),"j"(k));_r;})
static inline qword AdvB23(qword p,qword v,qword t){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p),"j"(v),"j"(t),"j"(v),"j"(v));return r;}
static inline qword AdvT23(qword p,qword v,float f){V home;qword t=ScalarQ(f);qword r=AdvB23(p,v,t);home.q=t;return r;}
#define SUB_MQ23(a,b,k) ({qword _r;__asm__("vsub.xyzw %0,%1,%2":"=j"(_r):"jV"(a),"jV"(b),"j"(k),"j"(k),"j"(k));_r;})
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword SubD(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b),"j"(a));return r;}
#define SUB_M(a,b) ({qword _r;__asm__("vsub.xyzw %0,%1,%2":"=j"(_r):"jV"(a),"jV"(b));_r;})
#define ADD_M(a,b) ({qword _r;__asm__("vadd.xyzw %0,%1,%2":"=j"(_r):"jV"(a),"jV"(b));_r;})
#define ADVANCE_M(p,v,t) ({qword _r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(_r):"jV"(p),"jV"(v),"jV"(t));_r;})
#define TRAPEZOID_M(p,o,n,t) ({qword _r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(_r):"jV"(p),"jV"(o),"jV"(n),"jV"(t));_r;})
#define COMBINATION_M(a,fa,b,fb) ({qword _r;__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(_r):"jV"(a),"jV"(fa),"jV"(b),"jV"(fb));_r;})
static inline qword Zero(){qword r;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Scale(qword a,qword f){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(f));return r;}
static inline qword Advance(qword p,qword velocity,qword time){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p),"j"(velocity),"j"(time));return r;}
static inline qword Trapezoid(qword p,qword oldVelocity,qword newVelocity,qword time){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(p),"j"(oldVelocity),"j"(newVelocity),"j"(time));return r;}
static inline qword Combination(qword a,qword fa,qword b,qword fb){qword r;__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(fa),"j"(b),"j"(fb));return r;}
static inline float X(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Y(qword a){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(a));return f;}
static inline float Z(qword a){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(a));return f;}
static inline float VF_X(qword a){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline qword DotV(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline float Dot(qword a,qword b){return VF_X(DotV(a,b));}
static inline float Length(qword a){qword r=DotV(a,a);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return X(r);}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword RotateSeed(const M3 &m,qword v,qword seed){asm("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(seed):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return seed;}
static inline qword Rotate(const M3 &m,qword a){return RotateSeed(m,a,a);}
static inline bool Near(qword a,qword b){return func_0011D4D0(X(a),X(b),1e-4f)&&func_0011D4D0(Y(a),Y(b),1e-4f)&&func_0011D4D0(Z(a),Z(b),1e-4f);}
static inline void ZeroXYZ(V &v){v.f[0]=v.f[1]=v.f[2]=0;}
static inline void ClearRows(M3 &m){m.r[2].f[3]=0.0f;m.r[1].f[3]=0.0f;m.r[0].f[3]=0.0f;}
static inline void Touch(E *e){e->priority=++D_003DD490.generation;}
static inline void ClearFlag(S *p,int bit){int flags=p->flags.bits;if((flags^1)&1)*p->flags.address&=~bit;else p->flags.bits=flags&~bit;}
#define Rotation func_0011B500
#define RotationVector func_0011B570
static inline qword RotRow(qword l0,qword l1,qword l2,qword r){qword o;asm("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(o):"j"(l0),"j"(l1),"j"(l2),"j"(r));return o;}
static inline M3 RotateBasis(const M3 &rotation,const M3 &basis,bool rotationW) {M3 r;
 qword l0=rotation.r[0].q,l1=rotation.r[1].q,l2=rotation.r[2].q;
 r.r[0].q=RotRow(l0,l1,l2,basis.r[0].q);
 r.r[1].q=RotRow(l0,l1,l2,basis.r[1].q);
 r.r[2].q=RotRow(l0,l1,l2,basis.r[2].q);
return r;}
static inline M3 RotateBasisN(const M3 &rotation,const M3 &basis,bool rotationW) return m {M3 t;
 qword l0=rotation.r[0].q,l1=rotation.r[1].q,l2=rotation.r[2].q;
 qword r0=RotRow(l0,l1,l2,basis.r[0].q);m.r[0].q=r0;t.r[0].q=r0;
 qword r1=RotRow(l0,l1,l2,basis.r[1].q);m.r[1].q=r1;t.r[1].q=r1;
 qword r2=RotRow(l0,l1,l2,basis.r[2].q);t.r[2].q=r2;m.r[2].q=r2;
}
static inline M3 RotateBasisV(const M3 &rotation,M3 basis,bool rotationW) {M3 r;
 qword l0=rotation.r[0].q,l1=rotation.r[1].q,l2=rotation.r[2].q;
 r.r[0].q=RotRow(l0,l1,l2,basis.r[0].q);
 r.r[1].q=RotRow(l0,l1,l2,basis.r[1].q);
 r.r[2].q=RotRow(l0,l1,l2,basis.r[2].q);
return r;}

#define MatrixParameter func_0022C8C0
static inline qword Pass(qword x){qword r;asm("" : "=r"(r) : "0"(x));return r;}
static inline qword PassS(qword x){qword r;asm("" : "=*r"(r) : "0"(x));return r;}
static inline qword EvaluateValue(E *e){V result;qword r;
 switch(e->action.fields.state){
 case 0:r=func_0022CA18(e,&e->local);break;
 case 1:func_00117120(e->end-e->begin,*e->time-e->begin,*e->rate,e->data.value[0].q,e->data.value[1].q,e->data.value[2].q,e->data.value[3].q,&result,0,0);r=result.q;break;
 case 2:case 3:case 4:r=e->data.value[0].q;break;
 case 5:r=func_0011BFF0(&(*(M3 *)&e->data.value[0]));break;
 default:r=D_002A2DD0.q;break;
 }
 return r;
}
static inline qword EvaluateVelocity(E *e){V result;
 switch(e->action.fields.state){
 case 3:case 4:return e->data.value[1].q;
 case 1:func_00117120(e->end-e->begin,*e->time-e->begin,*e->rate,e->data.value[0].q,e->data.value[1].q,e->data.value[2].q,e->data.value[3].q,0,&result,0);return result.q;
 case 0:case 2:case 5:default:return D_002A2DD0.q;
 }
}
static inline void Complete(S *p,E *e,bool angular){
 if(e->action.fields.type==8)return;
 if(angular && e->action.fields.type==11){if(e->action.fields.state==2)func_002303A0(p,e,12);}
 else if(e->action.fields.state==1)func_002303A0(p,e,6);
 else if(e->action.fields.state==2)func_002303A0(p,e,10);
}
static inline void DeadlineStep(E *e,float distance,float &step,float &rate){
 float minimum=distance;
 if(D_002DDED0.t<e->source.deadline)minimum=(distance*D_002DDED0.dt)/(e->source.deadline-D_002DDED0.t+D_002DDED0.dt);
 if(step<minimum){step=minimum;rate=step/D_002DDED0.dt;}
}
extern "C" void func_0022DE88(S *p){
 int unchanged=0;
 if(!p->parent || !(*p->parent->flags.address&4))unchanged=1;
 int i;
 int reset=*p->flags.address&0x10;
 for(i=0;i<p->count;i++){
  E *e=p->records+i;
  func_0022DD00(p,e);
  switch(e->action.fields.type){
  case 1:case 2:{
   switch(e->kind){
   case 1:{
    qword old=e->velocity.q;float dt=D_002DDED0.dt;
    qword velocity=Advance(old,e->data.value[3].q,Scalar(dt));
    bool moving=!(Near(D_002A2DD0.q,velocity)&&Near(D_002A2DD0.q,e->velocity.q));
    if(moving){
     unchanged=0;
     qword position=e->local.position.q;
     qword half=Scalar(dt*0.5f);
     qword average=Add(velocity,e->velocity.q);
     func_00256D18(&e->local.position,Advance(position,average,half));
     e->velocity.q=velocity;e->local.position.f[3]=1.0f;Touch(e);
    }else{ZeroXYZ(e->velocity);if(e->action.fields.type!=2)func_002303A0(p,e,3);else unchanged=0;}
   }break;
   case 6:{
    qword old=e->velocity.q;float dt=D_002DDED0.dt;
    qword velocity=Advance(old,e->data.value[3].q,Scalar(dt));
    bool moving=!(Near(D_002A2DD0.q,velocity)&&Near(D_002A2DD0.q,e->velocity.q));
    if(moving){
     unchanged=0;
     qword half=Scalar(dt*0.5f);
     qword average=Add(e->velocity.q,velocity);
     M3 matrix;matrix=RotateBasisN(RotationVector(Scale(average,half)),e->local.basis,true);
     func_0011B3D0(&matrix);e->local.basis=matrix;e->velocity.q=velocity;ClearRows(e->local.basis);Touch(e);
    }else{ZeroXYZ(e->velocity);if(e->action.fields.type!=2)func_002303A0(p,e,3);else unchanged=0;}
   }break;
   }
   break;
  }
  case 20:
   if(e->kind==6){
    unchanged=0;
    float angle=func_0011CF60(e->data.value[2].f[0]+D_002DDED0.dt*e->data.value[1].f[0]);
    e->data.value[2].f[0]=angle;
    e->local.basis=Rotation(angle,e->data.value[0].q);
    ClearRows(e->local.basis);Touch(e);
   }
   break;
  case 4:{
   E *origin=e->source.origin;
   e->local.position.f[0]=-origin->local.position.f[0];
   e->local.position.f[1]=-origin->local.position.f[1];
   e->local.position.f[2]=-origin->local.position.f[2];
   e->priority=origin->priority;
   break;
  }
  case 5:case 6:{
   if(e->action.fields.state==5){e->local.basis=(*(M3 *)&e->data.value[0]);ClearRows(e->local.basis);}
   else{qword goal=EvaluateValue(e);e->local=MatrixParameter(e,goal);}
   Touch(e);
   unsigned long v=e->action.pair;if(v==0x00020006)func_002303A0(p,e,10);
   unchanged=0;
   break;
  }
  case 21:unchanged=0;break;
  case 7:case 8:case 9:case 11:{
   switch(e->kind){case 6:case 7:{
    M3 old=e->local.basis;
    M3 relative;
    M3 result;
    V axis;qword relativeVelocity;
    if(e->action.fields.state==5){e->local.basis=(*(M3 *)&e->data.value[0]);ClearRows(e->local.basis);relativeVelocity=D_002A2DD0.q;}
    else{
     qword goal=Pass(EvaluateValue(e)),velocity=EvaluateVelocity(e);
     e->local=MatrixParameter(e,goal);
     relativeVelocity=func_0022CAD0(goal,velocity);
    }
    float angle,angular;relative=func_0011BC00(&old,&e->local.basis);
    func_0011BCF8(&relative,&angle,&axis);
    float projection=Dot(relativeVelocity,axis.q);
    PROFILE profile;
    if(e->action.fields.state==3){
     profile.speed=(float)e->force*D_002C45F0.speed;
     profile.terminal=(float)e->force*D_002C45F0.terminal;
     profile.duration=D_002C45F0.duration;
    }else{
     float prior=__builtin_fabsf(projection);
     profile.speed=(float)e->force*D_002C45F0.speed+prior;
     profile.terminal=(float)e->force*D_002C45F0.terminal+prior;
     profile.duration=D_002C45F0.duration;
    }
    float step;
    if(reset)step=angle;
    else{
     step=func_0011D018(0.0f,angle,D_002DDED0.dt,&profile,&angular);
     switch(e->action.fields.type){
     case 11:{
      float maximum=(float)e->force*D_002C45FC;
      qword axq=axis.q;qword desired=AdvT23(relativeVelocity,axq,angular-projection);
      qword delta=SUB_MQ23(desired,e->velocity.q,axq);
      float needed=Length(delta)/D_002DDED0.dt;
      if(maximum<needed){
       qword velocity=ADVANCE_M(e->velocity.q,delta,Scalar(maximum/needed));
       M3 rotation;
       M3 result;
       rotation=RotationVector(ScaleV(ADD_M(e->velocity.q,velocity),VuFloat(D_002DDED0.dt*0.5f)));
       result=RotateBasisN(rotation,old,false);func_0011B3D0(&result);
       e->velocity.q=velocity;e->local.basis=result;ClearRows(e->local.basis);goto finished;
      }
      break;
     }
     case 9:{
      float minimum;
      if(D_002DDED0.t<e->source.deadline)minimum=(angle*D_002DDED0.dt)/(e->source.deadline-D_002DDED0.t+D_002DDED0.dt);
      else minimum=angle;
      if(step<minimum){step=minimum;angular=step/D_002DDED0.dt;}
     }
     break;
     default:break;
     }
    }
    {
     if(angle<=step){Complete(p,e,true);e->velocity.q=relativeVelocity;}
     else{
      result=RotateBasisN(Rotation(step,axis.q),old,true);func_0011B3D0(&result);
      e->local.basis=result;ClearRows(e->local.basis);
      e->velocity.q=Advance(relativeVelocity,axis.q,Scalar(angular-projection));
     }
    }
   }break;
   default:{
    qword goal=Pass(EvaluateValue(e)),goalVelocity=Pass(EvaluateVelocity(e));
    qword current=func_0022CA18(e,&e->local),delta=SubD(goal,current);
    float distance=Length(delta);
    qword direction;
    if(1e-4f<distance)direction=Divide(delta,Scalar(distance));else direction=D_002A2DA0.q;
    float projection=Dot(goalVelocity,direction);
    PROFILE profile;
    switch(e->kind){
    case 11:case 12:
     profile.speed=(float)e->force*D_002C4610.speed+__builtin_fabsf(projection);
     profile.terminal=(float)e->force*D_002C4610.terminal+__builtin_fabsf(projection);
     profile.duration=D_002C4610.duration;
     break;
    default:
     profile.speed=(float)e->force*D_002C4600.speed+__builtin_fabsf(projection);
     profile.terminal=(float)e->force*D_002C4600.terminal+__builtin_fabsf(projection);
     profile.duration=D_002C4600.duration;
     break;
    }
    float linear;float step=distance;
    if(!reset){
     step=func_0011D018(0.0f,distance,D_002DDED0.dt,&profile,&linear);
     switch(e->action.fields.type){
     case 11:{
      int kind=e->kind;
      qword desired=Advance(goalVelocity,direction,Scalar(linear-projection));
      qword difference=SUB_M(desired,e->velocity.q);
      float needed=Length(difference)/D_002DDED0.dt;
      float maximum;
      switch(kind){case 11:case 12:maximum=(float)e->force*D_002C4620;break;default:maximum=(float)e->force*D_002C461C;break;}
      if(maximum<needed){
       qword tr=Scalar(maximum/needed);qword th=Scalar(D_002DDED0.dt*0.5f);
       qword velocity=ADVANCE_M(e->velocity.q,difference,tr);
       qword parameter=Advance(current,Add(e->velocity.q,velocity),th);
       e->velocity.q=velocity;
       e->local=MatrixParameter(e,parameter);goto finished;
      }
      break;
     }
     case 9:{
      float minimum;
      if(D_002DDED0.t<e->source.deadline)minimum=(distance*D_002DDED0.dt)/(e->source.deadline-D_002DDED0.t+D_002DDED0.dt);
      else minimum=distance;
      if(step<minimum){step=minimum;linear=step/D_002DDED0.dt;}
     }
     break;
     default:break;
     }
    }
    {
     qword ts=Scalar(step);e->local=MatrixParameter(e,Advance(current,direction,ts));
     if(distance<=step){Complete(p,e,false);e->velocity.q=goalVelocity;}
     else e->velocity.q=Advance(goalVelocity,direction,Scalar(linear-projection));
    }
   }break;
   }
  finished:
   unchanged=0;Touch(e);
   break;
  }
  case 13:func_00186A50(p,e->source.resource);break;
  case 15:func_001604E8(p,e->source.resource);break;
  case 16:func_0021CB18(p,e->source.resource);break;
  case 17:{
   V position,velocity;
   if(e->source.deadline<=D_002DDED0.t){position.q=e->data.value[0].q;ZeroXYZ(velocity);}
   else func_00117120(e->source.deadline-D_002DDED0.t+D_002DDED0.dt,D_002DDED0.dt,1.0f,e->local.position.q,e->velocity.q,e->data.value[0].q,e->data.value[1].q,&position,&velocity,0);
   func_00256D18(&e->local.position,position.q);e->local.position.f[3]=1.0f;
   e->velocity.q=velocity.q;Touch(e);unchanged=0;
   break;
  }
  case 18:{
   switch(e->kind){
   case 1:{
    qword goal=PassS(EvaluateValue(e));
    qword targetVelocity=EvaluateVelocity(e),old=e->velocity.q;
    float dt=D_002DDED0.dt;
    qword positionError=Sub(goal,e->local.position.q);
    targetVelocity=Sub(targetVelocity,old);
    float cf=(float)e->force,cd=(float)e->damping;qword force=Scalar(cf*D_002C4624),damping=Scalar(cd*D_002C4628);
    qword velocity=Advance(old,Combination(positionError,force,targetVelocity,damping),Scalar(dt));
    bool settled=e->action.fields.state==2 && Dot(velocity,velocity)<25.0f && Dot(positionError,positionError)<4.0f;
    if(settled){velocity=Zero();func_002303A0(p,e,19);}
    func_00256D18(&e->local.position,TRAPEZOID_M(e->local.position.q,old,velocity,Scalar(dt*0.5f)));
    e->local.position.f[3]=1.0f;e->velocity.q=velocity;
   }break;
   case 6:{
    M3 old=e->local.basis,target;
    M3 relative;
    M3 result;
    V axis;
    float dt=D_002DDED0.dt;
    qword angularVelocity;qword oldVelocity=e->velocity.q;
    if(e->action.fields.state==5){target=(*(M3 *)&e->data.value[0]);angularVelocity=D_002A2DD0.q;}
    else{
     qword goal=Pass(EvaluateValue(e)),velocity=EvaluateVelocity(e);
     const M4 &m=MatrixParameter(e,goal);target=m.basis;
     angularVelocity=func_0022CAD0(goal,velocity);
    }
    float springAngle;relative=func_0011BC00(&e->local.basis,&target);
    func_0011BCF8(&relative,&springAngle,&axis);
    int st=e->action.fields.state;float k=(float)e->force*D_002C462C,c=(float)e->damping*D_002C4630;qword force=Scalar(k*springAngle),damping=Scalar(c);
    qword difference=Sub(angularVelocity,oldVelocity);
    qword velocity=Advance(oldVelocity,Combination(axis.q,force,difference,damping),Scalar(dt));
    bool settled=st==2 && Dot(velocity,velocity)<0.0025000002f && springAngle<0.01f;
    if(settled){velocity=Zero();func_002303A0(p,e,19);}
    qword half=Scalar(dt*0.5f);
    qword rotation=Combination(oldVelocity,half,velocity,half);
    result=RotateBasisN(RotationVector(rotation),old,true);func_0011B3D0(&result);
    e->local.basis=result;e->velocity.q=velocity;ClearRows(e->local.basis);
   }break;
   }
   unchanged=0;Touch(e);
   break;
  }
  case 0:case 3:case 10:case 12:case 14:case 19:break;
  default:break;
  }
  if(e->parent){
   E *parent=e->parent;
   const M4 *pw=&parent->world,*pl=&e->local;
   register qword v1 __asm__("vf1")=pw->basis.r[0].q;
   register qword v2 __asm__("vf2")=pw->basis.r[1].q;
   register qword v3 __asm__("vf3")=pw->basis.r[2].q;
   register qword v4 __asm__("vf4")=pw->position.q;
   register qword v5 __asm__("vf5")=pl->basis.r[0].q;
   register qword v6 __asm__("vf6")=pl->basis.r[1].q;
   register qword v7 __asm__("vf7")=pl->basis.r[2].q;
   register qword v8 __asm__("vf8")=pl->position.q;
   __asm__ __volatile__("vcallms 0x60" : : "j"(v1),"j"(v2),"j"(v5),"j"(v6),"j"(v7),"j"(v8));
   int parentPriority=e->parent->priority,priority=e->priority;
   if(priority<=parentPriority)priority=parentPriority;
   e->priority=priority;
   int sync;
   __asm__ __volatile__("cfc2.i %0,$vi0":"=r"(sync):"j"(v3),"j"(v4),"j"(v5),"j"(v6),"j"(v7),"j"(v8));
   M4 r;
   r.basis.r[0].q=v5;r.basis.r[1].q=v6;r.basis.r[2].q=v7;r.position.q=v8;
   e->world.basis.r[0].q=r.basis.r[0].q;e->world.basis.r[1].q=r.basis.r[1].q;e->world.basis.r[2].q=r.basis.r[2].q;e->world.position.q=r.position.q;
  }else{
   e->world.basis.r[0].q=e->local.basis.r[0].q;e->world.basis.r[1].q=e->local.basis.r[1].q;e->world.basis.r[2].q=e->local.basis.r[2].q;e->world.position.q=e->local.position.q;
  }
 }
 if(unchanged)ClearFlag(p,4);
 if(reset)ClearFlag(p,0x10);
 func_0022FA20(p);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char transform_update_layout_assert[(sizeof(V)==16 && sizeof(M3)==0x30 && sizeof(M4)==0x40 && sizeof(E)==0x100 && OFF(E,local)==0 && OFF(E,world)==0x40 && OFF(E,begin)==0x80 && OFF(E,end)==0x84 && OFF(E,time)==0x88 && OFF(E,rate)==0x8C && OFF(E,jobs)==0x90 && OFF(E,kind)==0x94 && OFF(E,action)==0x98 && OFF(E,tag)==0x9C && OFF(E,parent)==0xA0 && OFF(E,priority)==0xA4 && OFF(E,source)==0xA8 && OFF(E,force)==0xAC && OFF(E,damping)==0xAE && OFF(E,velocity)==0xB0 && OFF(E,data)==0xC0 && OFF(S,parent)==0x10 && OFF(S,flags)==0x40 && OFF(S,count)==0x50 && OFF(S,records)==0x54 && OFF(WORLD,generation)==0x3D58 && sizeof(PROFILE)==12 && sizeof(RATES)==16 && sizeof(ACTION)==4 && sizeof(SOURCE)==4 && sizeof(PAYLOAD)==0x40)?1:-1];

typedef char raw_payload_layout_assert[(sizeof(PAYLOAD)==64 && (int)&((PAYLOAD*)0)->value[1]==16 && (int)&((PAYLOAD*)0)->value[3]==48 && sizeof(((V*)0)->f)==16 && sizeof(((V*)0)->n)==16 && __alignof__(V)==16 && __alignof__(M3)==16 && OFF(PROFILE,speed)==0 && OFF(PROFILE,terminal)==4 && OFF(PROFILE,duration)==8 && OFF(ACTION,fields.state)==2 && OFF(ACTION,pair)==0)?1:-1];
