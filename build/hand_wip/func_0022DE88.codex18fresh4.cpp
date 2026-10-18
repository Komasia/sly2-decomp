// Advance every transform record, compose its world frame, and consume update flags.
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
 M3 *func_0011BC00(M3 *,const M3 *,const M3 *);
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
static inline qword Scalar(V &home,float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));home.q=q;return q;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
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
static inline float Length(qword a){qword r=DotV(a,a);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return VF_X(r);}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword RotateSeed(const M3 &m,qword v,qword seed){asm("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(seed):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return seed;}
static inline qword Rotate(const M3 &m,qword a){return RotateSeed(m,a,a);}
static inline bool Near(qword a,qword b){return func_0011D4D0(X(a),X(b),1e-4f)&&func_0011D4D0(Y(a),Y(b),1e-4f)&&func_0011D4D0(Z(a),Z(b),1e-4f);}
static inline void ZeroXYZ(V &v){v.f[1]=0;v.f[2]=0;v.f[0]=0;}
static inline void ClearRows(M3 &m){m.r[2].n[3]=0;m.r[1].n[3]=0;m.r[0].n[3]=0;}
static inline void Touch(E *e){e->priority=++D_003DD490.generation;}
static inline void ClearFlag(S *p,int bit){int flags=p->flags.bits;if((flags^1)&1)*p->flags.address&=~bit;else p->flags.bits=flags&~bit;}
#define Rotation func_0011B500
#define RotationVector func_0011B570
static inline M3 RotateBasis(const M3 &rotation,const M3 &basis,bool rotationW) {M3 r;
 qword a=Rotate(rotation,basis.r[0].q),b=Rotate(rotation,basis.r[1].q),c=RotateSeed(rotation,basis.r[2].q,rotationW?rotation.r[0].q:basis.r[2].q);
 r.r[0].q=a;r.r[1].q=b;r.r[2].q=c;
return r;}
static inline M3 Relative(const M3 &a,const M3 &b) {M3 r;func_0011BC00(&r,&a,&b);return r;}
#define MatrixParameter func_0022C8C0
static inline qword EvaluateValue(E *e,V &result){
 switch(e->action.fields.state){
 case 0:return func_0022CA18(e,&e->local);
 case 1:func_00117120(e->end-e->begin,*e->time-e->begin,*e->rate,e->data.value[0].q,e->data.value[1].q,e->data.value[2].q,e->data.value[3].q,&result,0,0);return result.q;
 case 2:case 3:case 4:return e->data.value[0].q;
 case 5:return func_0011BFF0(&(*(M3 *)&e->data.value[0]));
 default:return D_002A2DD0.q;
 }
}
static inline qword EvaluateVelocity(E *e,V &result){
 switch(e->action.fields.state){
 case 1:func_00117120(e->end-e->begin,*e->time-e->begin,*e->rate,e->data.value[0].q,e->data.value[1].q,e->data.value[2].q,e->data.value[3].q,0,&result,0);return result.q;
 case 3:case 4:return e->data.value[1].q;
 case 0:case 2:case 5:default:return D_002A2DD0.q;
 }
}
static inline void Complete(S *p,E *e,bool angular){
 if(e->action.fields.type==8)return;
 if(angular && e->action.fields.type==11){if(e->action.fields.state==2)func_002303A0(p,e,12);}
 else if(e->action.fields.state==1)func_002303A0(p,e,6);
 else if(e->action.fields.state==2)func_002303A0(p,e,10);
}
static inline float DeadlineStep(E *e,float distance,float step,float &rate){
 float minimum=distance;
 if(D_002DDED0.t<e->source.deadline)minimum=(distance*D_002DDED0.dt)/(e->source.deadline-D_002DDED0.t+D_002DDED0.dt);
 if(step<minimum){step=minimum;rate=step/D_002DDED0.dt;}
 return step;
}
static inline M4 ComposeWorld(E *e){
 M4 r;E *parent=e->parent;
 asm volatile("lqc2 $vf1,%0\n\tlqc2 $vf4,48+%0\n\tlqc2 $vf2,16+%0\n\tlqc2 $vf3,32+%0\n\tlqc2 $vf5,%1\n\tlqc2 $vf6,16+%1\n\tlqc2 $vf7,32+%1\n\tlqc2 $vf8,48+%1\n\tvcallms 0x60"
 : :"m"(parent->world),"m"(e->local):"vf1","vf2","vf3","vf4","vf5","vf6","vf7","vf8");
 int priority=parent->priority;if(priority<e->priority)priority=e->priority;e->priority=priority;
 register qword r0 asm("vf5"),r1 asm("vf6"),r2 asm("vf7"),r3 asm("vf8");
 asm volatile("cfc2.i $3,$vi0":"=j"(r0),"=j"(r1),"=j"(r2),"=j"(r3): :"$3");
 r.basis.r[0].q=r0;r.basis.r[1].q=r1;r.basis.r[2].q=r2;r.position.q=r3;return r;
}
extern "C" void func_0022DE88(S *p){
 int unchanged=0;
 if(!p->parent || !(*p->parent->flags.address&4))unchanged=1;
 int reset=*p->flags.address&0x10;
 for(int i=0;i<p->count;i++){
  E *e=p->records+i;
  func_0022DD00(p,e);
  switch(e->action.fields.type){
  case 1:case 2:{
   if(e->kind==1){
    V scalar;float dt=D_002DDED0.dt;
    qword velocity=Advance(e->velocity.q,e->data.value[3].q,Scalar(scalar,dt));
    bool moving=false;
    if(!Near(D_002A2DD0.q,velocity))moving=true;
    else if(!Near(D_002A2DD0.q,e->velocity.q))moving=true;
    if(moving){
     unchanged=0;
     qword average=Add(velocity,e->velocity.q),half=Scalar(scalar,dt*0.5f);
     func_00256D18(&e->local.position,Advance(e->local.position.q,average,half));
     e->velocity.q=velocity;e->local.position.f[3]=1.0f;Touch(e);
    }else{ZeroXYZ(e->velocity);if(e->action.fields.type!=2)func_002303A0(p,e,3);else unchanged=0;}
   }else if(e->kind==6){
    V scalar;float dt=D_002DDED0.dt;
    qword velocity=Advance(e->velocity.q,e->data.value[3].q,Scalar(scalar,dt));
    bool moving=false;
    if(!Near(D_002A2DD0.q,velocity))moving=true;
    else if(!Near(D_002A2DD0.q,e->velocity.q))moving=true;
    if(moving){
     unchanged=0;
     qword average=Add(velocity,e->velocity.q),half=Scalar(scalar,dt*0.5f);
     M3 matrix=RotateBasis(RotationVector(Scale(average,half)),e->local.basis,true);
     func_0011B3D0(&matrix);e->local.basis=matrix;e->velocity.q=velocity;ClearRows(e->local.basis);Touch(e);
    }else{ZeroXYZ(e->velocity);if(e->action.fields.type!=2)func_002303A0(p,e,3);else unchanged=0;}
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
   else{V value;e->local=MatrixParameter(e,EvaluateValue(e,value));}
   Touch(e);unchanged=0;
   if(e->action.pair==0x00020006)func_002303A0(p,e,10);
   break;
  }
  case 21:unchanged=0;break;
  case 7:case 8:case 9:case 11:{
   switch(e->kind){case 6:case 7:{
    M3 old=e->local.basis;
    V scratch,axis,relativeVelocity,scalar;
    if(e->action.fields.state==5){e->local.basis=(*(M3 *)&e->data.value[0]);ClearRows(e->local.basis);relativeVelocity.q=D_002A2DD0.q;}
    else{
     qword goal=EvaluateValue(e,scratch),velocity=EvaluateVelocity(e,scratch);
     e->local=MatrixParameter(e,goal);
     relativeVelocity.q=func_0022CAD0(goal,velocity);
    }
    float angle,angular;M3 relative=Relative(old,e->local.basis);
    func_0011BCF8(&relative,&angle,&axis);
    float projection=Dot(relativeVelocity.q,axis.q);
    PROFILE profile;
    if(e->action.fields.state==3){
     profile.speed=(float)e->force*D_002C45F0.speed;
     profile.duration=D_002C45F0.duration;
     profile.terminal=(float)e->force*D_002C45F0.terminal;
    }else{
     float prior=__builtin_fabsf(projection);
     profile.speed=prior+(float)e->force*D_002C45F0.speed;
     profile.duration=D_002C45F0.duration;
     profile.terminal=prior+(float)e->force*D_002C45F0.terminal;
    }
    float step=angle;
    if(!reset){
     step=func_0011D018(0.0f,angle,D_002DDED0.dt,&profile,&angular);
     switch(e->action.fields.type){
     case 11:{
      qword desired=Advance(relativeVelocity.q,axis.q,Scalar(scalar,angular-projection));
      qword delta=Sub(desired,e->velocity.q);
      float needed=Length(delta)/D_002DDED0.dt,maximum=(float)e->force*D_002C45FC;
      if(maximum<needed){
       qword velocity=Advance(e->velocity.q,delta,Scalar(scalar,maximum/needed));
       qword rotation=Scale(Add(e->velocity.q,velocity),Scalar(scalar,D_002DDED0.dt*0.5f));
       M3 result=RotateBasis(RotationVector(rotation),old,false);func_0011B3D0(&result);
       e->velocity.q=velocity;e->local.basis=result;ClearRows(e->local.basis);goto finished;
      }
      break;
     }
     case 9:step=DeadlineStep(e,angle,step,angular);
     break;
     default:break;
     }
    }
    {
     if(angle<=step){Complete(p,e,true);e->velocity.q=relativeVelocity.q;}
     else{
      M3 result=RotateBasis(Rotation(step,axis.q),old,true);func_0011B3D0(&result);
      e->local.basis=result;ClearRows(e->local.basis);
      e->velocity.q=Advance(relativeVelocity.q,axis.q,Scalar(scalar,angular-projection));
     }
    }
   }break;
   default:{
    V scratch,goal,goalVelocity,scalar;
    goal.q=EvaluateValue(e,scratch);goalVelocity.q=EvaluateVelocity(e,scratch);
    qword current=func_0022CA18(e,&e->local),delta=Sub(goal.q,current);
    float distance=Length(delta);
    qword direction;
    if(1e-4f<distance)direction=Divide(delta,Scalar(scalar,distance));else direction=D_002A2DA0.q;
    float projection=Dot(goalVelocity.q,direction);
    PROFILE profile;
    switch(e->kind){
    case 11:case 12:
     profile.speed=__builtin_fabsf(projection)+(float)e->force*D_002C4610.speed;
     profile.duration=D_002C4610.duration;
     profile.terminal=__builtin_fabsf(projection)+(float)e->force*D_002C4610.terminal;
     break;
    default:
     profile.speed=__builtin_fabsf(projection)+(float)e->force*D_002C4600.speed;
     profile.duration=D_002C4600.duration;
     profile.terminal=__builtin_fabsf(projection)+(float)e->force*D_002C4600.terminal;
     break;
    }
    float linear;float step=distance;
    if(!reset){
     step=func_0011D018(0.0f,distance,D_002DDED0.dt,&profile,&linear);
     switch(e->action.fields.type){
     case 11:{
      qword desired=Advance(goalVelocity.q,direction,Scalar(scalar,linear-projection));
      qword difference=Sub(desired,e->velocity.q);
      float needed=Length(difference)/D_002DDED0.dt;
      float maximum=(float)e->force*((e->kind==11 || e->kind==12)?D_002C4620:D_002C461C);
      if(maximum<needed){
       qword old=e->velocity.q,velocity=Advance(old,difference,Scalar(scalar,maximum/needed));
       e->velocity.q=velocity;
       qword parameter=Advance(current,Add(old,velocity),Scalar(scalar,D_002DDED0.dt*0.5f));
       e->local=MatrixParameter(e,parameter);goto finished;
      }
      break;
     }
     case 9:step=DeadlineStep(e,distance,step,linear);
     break;
     default:break;
     }
    }
    {
     e->local=MatrixParameter(e,Advance(current,direction,Scalar(scalar,step)));
     if(distance<=step){Complete(p,e,false);e->velocity.q=goalVelocity.q;}
     else e->velocity.q=Advance(goalVelocity.q,direction,Scalar(scalar,linear-projection));
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
   e->velocity=velocity;Touch(e);unchanged=0;
   break;
  }
  case 18:{
   if(e->kind==1){
    V scratch,goal,scalar;
    goal.q=EvaluateValue(e,scratch);
    qword targetVelocity=EvaluateVelocity(e,scratch),old=e->velocity.q;
    float dt=D_002DDED0.dt;
    qword positionError=Sub(goal.q,e->local.position.q),velocityError=Sub(targetVelocity,old);
    qword force=Scalar(scalar,(float)e->force*D_002C4624),damping=Scalar(scalar,(float)e->damping*D_002C4628);
    qword velocity=Advance(old,Combination(positionError,force,velocityError,damping),Scalar(scalar,dt));
    if(e->action.fields.state==2 && Dot(velocity,velocity)<25.0f && Dot(positionError,positionError)<4.0f){velocity=Zero();func_002303A0(p,e,19);}
    func_00256D18(&e->local.position,Trapezoid(e->local.position.q,old,velocity,Scalar(scalar,dt*0.5f)));
    e->local.position.f[3]=1.0f;e->velocity.q=velocity;
   }else if(e->kind==6){
    M3 old=e->local.basis,target;
    float dt=D_002DDED0.dt;
    V scratch,axis,angularVelocity,oldVelocity,scalar;
    oldVelocity=e->velocity;
    if(e->action.fields.state==5){target=(*(M3 *)&e->data.value[0]);angularVelocity.q=D_002A2DD0.q;}
    else{
     qword goal=EvaluateValue(e,scratch),velocity=EvaluateVelocity(e,scratch);
     target=MatrixParameter(e,goal).basis;
     angularVelocity.q=func_0022CAD0(goal,velocity);
    }
    float springAngle;M3 relative=Relative(e->local.basis,target);
    func_0011BCF8(&relative,&springAngle,&axis);
    qword force=Scalar(scalar,(float)e->force*D_002C462C*springAngle),damping=Scalar(scalar,(float)e->damping*D_002C4630);
    qword difference=Sub(angularVelocity.q,oldVelocity.q);
    qword velocity=Advance(oldVelocity.q,Combination(axis.q,force,difference,damping),Scalar(scalar,dt));
    if(e->action.fields.state==2 && Dot(velocity,velocity)<0.0025000002f && springAngle<0.01f){velocity=Zero();func_002303A0(p,e,19);}
    qword half=Scalar(scalar,dt*0.5f);
    qword rotation=Combination(oldVelocity.q,half,velocity,half);
    M3 result=RotateBasis(RotationVector(rotation),old,true);func_0011B3D0(&result);
    e->local.basis=result;e->velocity.q=velocity;ClearRows(e->local.basis);
   }
   unchanged=0;Touch(e);
   break;
  }
  case 0:case 3:case 10:case 12:case 14:case 19:break;
  default:break;
  }
  if(e->parent)e->world=ComposeWorld(e);
  else e->world=e->local;
 }
 if(unchanged)ClearFlag(p,4);
 if(reset)ClearFlag(p,0x10);
 func_0022FA20(p);
}
