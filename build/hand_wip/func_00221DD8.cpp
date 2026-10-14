// Update the camera's manual/passive angles, side transitions, and final frame.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
struct LM {float lo,hi;};
struct POLY {float a,b,c;};
struct PROFILE {float speed,terminal,duration;};
struct PROFILEA;
struct SOUND;
struct FOLLOW {char unknown0[0xE0];int enabled;char unknownE4[4];int state;};
struct VOLUME;
struct O {
 char unknown0[0x4C8];int field4C8,sentinel;char unknown4D0[0x24];int eventMode;
 char unknown4F8[8];V eventPosition;char unknown510[0x18];VOLUME *attached;
 char unknown52C[0xBB8];int mode;
};
struct INPUT {
 char unknown0[0x103C];float field103C,field1040;char unknown1044[0x2C];
 float field1070,field1074,field1078;
};
struct VOLUME {
 char unknown0[0x10C];FOLLOW *follow;char unknown110[0x10];int cylindrical;
 char unknown124[8];int circular;float angleLimit;char unknown134[4];float startTime;
 char unknown13C[4];float phase;char unknown144[0xC];V origin;float circleRadius;
 int modes,forceFlag,idleFlag;float forceTime,forceWeight,idleTime,idleWeight;
 int axisMode;char unknown184[8];int skipAvoidance;O *controlled;
 char unknown194[0xC];POLY influence;char unknown1AC[4];LM influenceLimits;
};
struct CONFIG {
 char unknown0[4];float addition;char unknown8[8];V coefficients[3];LM limits[3];
 float lateral,vertical,pointBlend,strength,speedGain;char unknown6C[4];
 V fallback;float spring,damping;LM radiusLimits;
};
struct S {
 O *owner;char unknown4[0xC];VOLUME *selected;CONFIG *config;
 float yaw,pitch,distance,vertical;int transition;float targetYaw,targetPitch;
 int side,snap,changed;float yawVelocity,pitchVelocity,changedTime,trackYaw;
 float leftYaw,leftPitch,rightYaw,rightPitch,lastInputTime,strength,distanceVelocity,verticalVelocity;
 V previousTarget;char unknown80[4];float yawOffset,pitchOffset,yawOffsetVelocity,pitchOffsetVelocity;
};
struct Q {int flags;char unknown4[0xC];V point,delta;float yaw,pitch,time;int axisMode;V alternate;};
struct CLOCK {float t,dt;char unknown8[8];float manualDt,activity;};
struct CAMERA {
 char unknown0[0x40];float scale40,scale44;char unknown48[4];float extraDistance;
 char unknown50[0x10];M4 world;char unknownA0[0x240];V response,responseVelocity;
 int mode;float overrideYaw,overridePitch;
};
struct NOTIFY {char unknown0[4];float lastActivity;};
struct EULER {float yaw,pitch,radius;};
union HOME {V vector;PROFILE profile;};
struct WORK {
 V point,tracked,direction,coordinates,temporary,finalPoint,sideAxis;
 PROFILE first;HOME second;
 EULER left,right,result;
 float planar,z,baseYaw,basePitch;
};
extern CLOCK D_002DDED0;
extern CAMERA D_002DDF40;
extern V D_002DE220,D_002A2DA0,D_002A2DC0,D_002A2DD0;
extern NOTIFY D_002DEB30;
extern int D_002C4118;
extern LM D_002C41B0,D_002C4200,D_002BBB60;
extern POLY D_002C41F0,D_002C4220;
extern PROFILE D_002C4230,D_002C4208,D_002C4260;
extern PROFILEA D_002C4240,D_002C4250;
extern float D_002C41D8,D_002C41DC,D_002C41E0,D_002C41E4,D_002C41E8,D_002C41EC;
extern float D_002C426C,D_002C4270,D_002C4274,D_002C4278,D_002C427C,D_002C4280;
extern "C" {
 int func_00132B10(O *,int);
 void func_002236E8(S *);
 void func_00221CE8(S *,Q *);
 void func_00220DD8(CONFIG *,Q *,V *,VOLUME *);
 void func_0014E6D0(CAMERA *,V *,V *,qword,float,float);
 float func_0011D018(PROFILE *,float,float,float,float *);
 void func_00221408(VOLUME *,qword,V *,V *);
 void func_002215C0(VOLUME *,float *,V *,LM *,int,V *,float,float);
 void func_0011EF08(qword,float *,float *,float *);
 void func_0011EFB0(qword,float *,float *,float *);
 float func_0011CF60(float);
 float func_0011CFE0(float,float);
 float func_0011D948(LM *,float);
 float func_0011D340(float,float,float,float,PROFILEA *,float *);
 float func_0011D2D0(float,float,float,PROFILE *,float *);
 float func_00244B68(float);
 float func_002458F0(float,float);
 SOUND *func_001FBB90(int);
 void func_001FB2F8(SOUND *,int);
 void func_001619A0(NOTIFY *,int,int);
 qword func_001A62E8(O *);
 M3 *func_001A6318(O *);
 qword func_001A6FC0(VOLUME *,void *,qword);
 qword func_0011E208(float,float,float);
 void func_00223A70(S *,qword,qword,V *);
 qword func_0014F110(CAMERA *,qword,qword);
 void func_0011BC88(M3 *,float *,float *);
 void func_0014E1A8(CAMERA *,qword,qword,float,float);
}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scalar(V &home,float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));home.q=r;return r;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword CrossXYZ(qword a,qword b){__asm__("vopmula.xyz ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0":"+j"(a):"j"(b));return a;}
static inline qword DotV(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword LengthV(qword a){qword r=DotV(a,a);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));return r;}
static inline qword LengthXYV(qword a){__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(a));return a;}
static inline float X(qword a){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword Unit(qword a,qword fallback){qword length=LengthV(a);if(X(length)<1e-4f)return fallback;return Divide(a,length);}
static inline float Clamp(float f,float lo,float hi){if(f<lo)return lo;if(hi<f)return hi;return f;}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Abs(float f){return __builtin_fabsf(f);}
static inline float Wrap(float f){return func_0011CF60(f);}
static inline float Polynomial(const POLY &p,float f){return p.a+f*(p.b+f*p.c);}
static inline float UnitLimit(float f){return func_0011D948(&D_002BBB60,f);}
static inline void ProfileScale(PROFILE &p,const PROFILE &source,float scale){p.speed=source.speed*scale;p.terminal=source.terminal*scale;p.duration=source.duration;}
static inline bool Reached(float old,float previous,float current,float target){
 float a=Wrap(old-previous),b=Wrap(current-target);
 if(a*b<=0.0f || Abs(Wrap(current-target))<1e-4f)return Abs(Wrap(current-target))<1.5707964f;
 return false;
}
extern "C" void func_00221DD8(S *p,Q *input,INPUT *driver){
 WORK w;
 O *owner=p->owner,*player=0;
 VOLUME *volume=p->selected;
 float manualDt=D_002DDED0.manualDt;
 if(func_00132B10(owner,0x34))player=owner;
 func_002236E8(p);
 int modes,forceFlag,idleFlag;
 if(volume){modes=volume->modes;forceFlag=volume->forceFlag;idleFlag=volume->idleFlag;}
 else{modes=4;forceFlag=idleFlag=0;}
 func_00221CE8(p,input);
 func_00220DD8(p->config,input,&w.point,volume);
 if(player && player->eventMode==2)func_0014E6D0(&D_002DDF40,&D_002DDF40.response,&D_002DDF40.responseVelocity,Sub(player->eventPosition.q,w.point.q),8.0f,-6.0f);
 w.tracked.q=Add(w.point.q,D_002DE220.q);
 if(volume && volume->controlled)input->flags&=~1;
 float strength=(input->flags&1)?0.0f:p->config->strength;
 p->strength=func_0011D018(&D_002C4230,p->strength,strength,D_002DDED0.dt,0);
 p->lastInputTime=Max(p->lastInputTime,input->time);
 w.right.pitch=w.left.yaw=w.left.pitch=w.right.yaw=0.0f;
 if(volume && (modes&3)){
  func_00221408(volume,w.point.q,&w.coordinates,&w.direction);
  if(volume->cylindrical){
   func_0011EF08(w.coordinates.q,&w.coordinates.f[0],&w.coordinates.f[1],&w.coordinates.f[2]);
   if(!p->snap)w.coordinates.f[0]+=func_0011CFE0(Wrap(p->trackYaw-w.coordinates.f[0]),volume->angleLimit);
   p->trackYaw=w.coordinates.f[0];
  }
  if(modes&1){
   func_002215C0(volume,w.coordinates.f,p->config->coefficients,p->config->limits,1,&w.temporary,volume->phase,p->config->addition);
   func_0011EFB0(Sub(w.temporary.q,w.tracked.q),&w.left.yaw,&w.left.pitch,&w.left.radius);
  }
  if(modes&2){
   func_002215C0(volume,w.coordinates.f,p->config->coefficients,p->config->limits,2,&w.temporary,volume->phase,p->config->addition);
   func_0011EFB0(Sub(w.temporary.q,w.tracked.q),&w.right.yaw,&w.right.pitch,&w.right.radius);
  }
 }
 if(p->snap)p->side=4;
 if(D_002DDF40.mode){
  if(D_002DDF40.mode==2){
   p->side=4;p->yaw=D_002DDF40.overrideYaw;
   p->pitch=func_0011D948(&D_002C41B0,D_002DDF40.overridePitch-func_00244B68(p->config->vertical*D_002DDF40.scale44));
  }else if(!(modes&3)){p->side=4;p->yaw=input->yaw;p->pitch=p->config->radiusLimits.lo;}
  else if(!(modes&2))p->side=1;
  else if(!(modes&1))p->side=2;
  else{
   float left=Wrap(w.left.yaw-input->yaw),right=Wrap(w.right.yaw-input->yaw);
   p->side=Abs(left)<Abs(right)?1:2;
  }
  p->lastInputTime=D_002DDED0.t;
  p->changedTime=D_002DDED0.t-D_002C41DC;
 }
 if(!(p->side&modes) && p->side>0 && p->side<3)p->side=4;
 if(volume && volume->controlled){
  w.temporary.q=Sub(func_001A62E8(volume->controlled),input->point.q);w.temporary.n[2]=0;
  qword length=LengthV(w.temporary.q);
  w.temporary.q=X(length)<1e-4f?D_002A2DD0.q:Divide(w.temporary.q,length);
  float influence=Clamp(Polynomial(volume->influence,X(length)),volume->influenceLimits.lo,volume->influenceLimits.hi);
  w.coordinates.q=Scale(w.temporary.q,Scalar(w.finalPoint,influence));
 }else w.coordinates=input->delta;
 float yaw=p->yaw,pitch=p->pitch;
 bool manual=(modes&4) && (p->transition || driver->field1078>0.0f || p->yawVelocity!=0.0f || p->pitchVelocity!=0.0f);
 if(manual){
  if(p->side!=4)func_001FB2F8(func_001FBB90(3),0);
  if(driver->field1078>0.0f)p->transition=0;
  if(p->transition){
   PROFILEA *profile=(player && player->mode==4)?&D_002C4250:&D_002C4240;
   yaw=func_0011D340(yaw,p->yawVelocity,p->targetYaw,manualDt,profile,&p->yawVelocity);
   pitch=func_0011D340(pitch,p->pitchVelocity,p->targetPitch,manualDt,profile,&p->pitchVelocity);
   if(yaw==p->targetYaw && pitch==p->targetPitch)p->transition=0;
  }else{
   float change=D_002C41EC*manualDt;
   p->yawVelocity=Clamp(driver->field1070*Abs(driver->field1070)*D_002C41E4,p->yawVelocity-change,p->yawVelocity+change);
   p->pitchVelocity=Clamp(driver->field1074*Abs(driver->field1074)*D_002C41E8,p->pitchVelocity-change,p->pitchVelocity+change);
   float angle=func_002458F0(Abs(driver->field1074),Abs(driver->field1070));
   if(angle<0.2617994f)p->pitchVelocity=0.0f;else if(1.3089969f<angle)p->yawVelocity=0.0f;
   yaw=Wrap(yaw+p->yawVelocity*manualDt);
   pitch=func_0011D948(&D_002C41B0,Wrap(pitch+p->pitchVelocity*manualDt));
   if(D_002DDED0.activity-D_002DEB30.lastActivity>5.0f){D_002DEB30.lastActivity=D_002DDED0.activity;func_001619A0(&D_002DEB30,6,0);}
  }
  p->side=4;p->changed=1;p->changedTime=D_002DDED0.t;
 }else if(p->side==4){
  w.temporary.f[0]=driver->field103C;w.temporary.f[1]=driver->field1040;w.temporary.n[2]=0;
  w.temporary.q=Unit(w.temporary.q,D_002A2DA0.q);
  w.finalPoint.q=Sub(w.tracked.q,D_002DDF40.world.position.q);w.finalPoint.f[2]*=0.3f;
  qword length=LengthV(w.finalPoint.q);float distance=X(length);
  w.finalPoint.q=distance<1e-4f?D_002A2DA0.q:Divide(w.finalPoint.q,length);
  int axisMode=(!volume || volume->axisMode==-1)?input->axisMode:volume->axisMode;
  if(axisMode==0)w.sideAxis.q=CrossXYZ(D_002A2DC0.q,w.finalPoint.q);
  else if(axisMode==1)w.sideAxis=w.finalPoint;
  w.sideAxis.q=Unit(w.sideAxis.q,D_002A2DA0.q);
  float steering=func_0011CFE0(X(DotV(w.coordinates.q,w.sideAxis.q))/distance,D_002C41E0)*p->strength;
  float shape=Clamp(Polynomial(D_002C41F0,w.temporary.f[1]),D_002C4200.lo,D_002C4200.hi);
  float elapsed=D_002DDED0.t-p->changedTime;
  float gain=Clamp(Polynomial(D_002C4220,elapsed),D_002BBB60.lo,D_002BBB60.hi);
  float passiveYaw=Wrap(yaw+steering*shape*gain*D_002DDED0.dt);
  float motion=Min(1.0f,X(LengthXYV(w.coordinates.q))*0.0016666667f),passivePitch;
  if(motion>0.1f){
   ProfileScale(w.first,D_002C4260,motion);
   float target=func_0011D948(&p->config->radiusLimits,pitch);
   passivePitch=func_0011D2D0(pitch,target,D_002DDED0.dt,&w.first,0);
  }else passivePitch=pitch;
  if(!(modes&3)){yaw=passiveYaw;pitch=passivePitch;}
  else{
   float alpha,desiredYaw,desiredPitch;
   if(!volume->follow && !volume->circular){alpha=1.0f;desiredYaw=w.left.yaw;desiredPitch=w.left.pitch;}
   else if(player && player->attached==volume){alpha=3.0f;desiredYaw=w.left.yaw;desiredPitch=w.left.pitch;}
   else if(p->side==1){alpha=1.0f;desiredYaw=w.left.yaw;desiredPitch=w.left.pitch;}
   else if(p->side==2){alpha=1.0f;desiredYaw=w.right.yaw;desiredPitch=w.right.pitch;}
   else{
    M3 ownerBasis=*func_001A6318(owner);w.second.vector=ownerBasis.r[0];w.second.vector.n[2]=0;
    w.second.vector.q=Unit(w.second.vector.q,D_002A2DA0.q);
    w.direction.q=func_001A6FC0(volume,0,w.direction.q);
    float projection=X(DotV(w.second.vector.q,w.direction.q));
    alpha=projection*projection*(3.0f-2.0f*Abs(projection));
    if(!(modes&2) || projection>0.0f){desiredYaw=w.left.yaw;desiredPitch=w.left.pitch;}
    else{desiredYaw=w.right.yaw;desiredPitch=w.right.pitch;}
   }
   float speed=0.0f;
   if(player){float scale=(player->sentinel!=-1 && player->field4C8==0)?0.005f:0.0016666667f;speed=Min(1.0f,X(LengthXYV(w.coordinates.q))*scale);}
   speed*=p->config->speedGain;
   if(idleFlag){
    float a=D_002DDED0.t-(p->lastInputTime+D_002C41D8),b=D_002DDED0.t-(p->changedTime+D_002C41DC),idle=0.0f;
    if(volume->idleTime>0.0f)idle=UnitLimit(a/volume->idleTime)*UnitLimit(b/volume->idleTime);
    else if(a>0.0f && b>0.0f)idle=1.0f;
    idle*=volume->idleWeight;
    if(speed*alpha<idle){alpha=1.0f;speed=idle;}
   }
   if(forceFlag && !p->changed){
    float gain=volume->forceTime>0.0f?UnitLimit((D_002DDED0.t-volume->startTime)/volume->forceTime):1.0f;
    float force=gain*volume->forceWeight;
    if(speed*alpha<force){alpha=1.0f;speed=force;}
   }
   ProfileScale(w.second.profile,D_002C4208,speed);
   float smoothYaw=func_0011D2D0(yaw,Wrap(yaw+Wrap(desiredYaw-yaw)),D_002DDED0.dt,&w.second.profile,0);
   float smoothPitch=func_0011D2D0(pitch,Wrap(pitch+Wrap(desiredPitch-pitch)),D_002DDED0.dt,&w.second.profile,0);
   float a=Wrap(desiredYaw-smoothYaw),b=Wrap(desiredYaw-passiveYaw);
   if(Abs(b)<Abs(a))smoothYaw=passiveYaw;
   a=Wrap(desiredPitch-smoothPitch);b=Wrap(desiredPitch-passivePitch);
   if(Abs(b)<Abs(a))smoothPitch=passivePitch;
   float passive=Wrap(passiveYaw-yaw),smooth=Wrap(smoothYaw-yaw);
   yaw=Wrap(yaw+(1.0f-alpha)*passive+alpha*smooth);
   passive=Wrap(passivePitch-pitch);smooth=Wrap(smoothPitch-pitch);
   pitch=Wrap(pitch+(1.0f-alpha)*passive+alpha*smooth);
   if(!p->snap){
    FOLLOW *follow=p->selected->follow;
    if(!follow || follow->enabled || follow->state<3){
     bool reached=false;
     if(modes&1){
      if(Reached(p->yaw,p->leftYaw,yaw,w.left.yaw) && Reached(p->pitch,p->leftPitch,pitch,w.left.pitch)){p->changed=1;p->side=1;reached=true;}
     }
     if(!reached && (modes&2)){
      if(Reached(p->yaw,p->rightYaw,yaw,w.right.yaw) && Reached(p->pitch,p->rightPitch,pitch,w.right.pitch)){p->side=2;p->changed=1;}
     }
    }
   }
  }
 }
 float lateral,vertical;
 switch(p->side){
 case 1:w.result=w.left;vertical=p->config->vertical;lateral=p->config->lateral;break;
 case 2:w.result=w.right;lateral=-p->config->lateral;vertical=p->config->vertical;break;
 case 4:{
  w.result.yaw=yaw;w.result.pitch=pitch;
  if(!(modes&3)){w.result.radius=Abs(p->config->addition);vertical=p->config->vertical;lateral=p->config->lateral;break;}
  float alpha;
  if(!(modes&2))alpha=1.0f;
  else if(!(modes&1))alpha=0.0f;
  else{
   if(p->yaw<w.left.yaw && p->yaw<w.right.yaw){
    if(w.right.yaw<w.left.yaw)w.left.yaw-=6.2831855f;else w.right.yaw-=6.2831855f;
   }else if(w.left.yaw<p->yaw && w.right.yaw<p->yaw){
    if(w.left.yaw<w.right.yaw)w.left.yaw+=6.2831855f;else w.right.yaw+=6.2831855f;
   }
   alpha=(p->yaw-w.right.yaw)/(w.left.yaw-w.right.yaw);
   alpha=alpha*alpha*(3.0f-2.0f*alpha);
  }
  w.result.radius=alpha*w.left.radius+(1.0f-alpha)*w.right.radius;
  lateral=alpha*p->config->lateral+(1.0f-alpha)*(-p->config->lateral);
  vertical=p->config->vertical;
  break;
 }
 }
 if(D_002DDF40.mode){p->distanceVelocity=0.0f;p->verticalVelocity=0.0f;}
 else{
  float damping=p->config->damping*D_002C426C*D_002DDED0.dt+1.0f;
  float spring=p->config->spring*D_002C4270*D_002DDED0.dt;
  p->distanceVelocity=damping*p->distanceVelocity+(w.result.radius-p->distance)*spring;
  p->verticalVelocity=damping*p->verticalVelocity+(vertical-p->vertical)*spring;
  w.result.radius=p->distance+p->distanceVelocity*D_002DDED0.dt;
  vertical=p->vertical+p->verticalVelocity*D_002DDED0.dt;
 }
 w.temporary.q=func_0011E208(w.result.yaw,w.result.pitch,w.result.radius);
 w.finalPoint.q=Add(w.tracked.q,w.temporary.q);
 if(!volume || !volume->skipAvoidance){
  if(D_002DDF40.mode)func_00223A70(p,w.tracked.q,w.finalPoint.q,&w.finalPoint);
  else if(!D_002C4118)w.finalPoint.q=func_0014F110(&D_002DDF40,p->previousTarget.q,w.finalPoint.q);
 }
 w.temporary.q=Sub(w.finalPoint.q,w.tracked.q);
 func_0011EFB0(w.temporary.q,&w.result.yaw,&w.result.pitch,&w.result.radius);
 p->previousTarget=w.finalPoint;
 float scale=(w.result.radius+D_002DDF40.extraDistance)/w.result.radius;
 w.finalPoint.q=Add(w.tracked.q,Scale(w.temporary.q,Scalar(w.sideAxis,scale)));
 float yawCorrection=func_00244B68(lateral*D_002DDF40.scale40);
 float pitchCorrection=-func_00244B68(vertical*D_002DDF40.scale44);
 if(p->snap){
  if(D_002DDF40.mode)p->yawOffset=0.0f;
  else{
   func_0011EF08(w.temporary.q,0,&w.planar,&w.z);
   func_0011BC88(&D_002DDF40.world.basis,&w.baseYaw,&w.basePitch);
   float targetYaw=Wrap(w.result.yaw+3.1415927f+yawCorrection);
   float targetPitch=Wrap(func_002458F0(-w.z,w.planar)+pitchCorrection);
   p->yawOffset=Wrap(w.baseYaw-targetYaw);
   p->pitchOffset=Wrap(w.basePitch-targetPitch);
  }
  p->yawOffsetVelocity=0.0f;p->pitchOffsetVelocity=0.0f;
 }else{
  p->yawOffsetVelocity+=(p->yawOffset*D_002C4274+p->yawOffsetVelocity*D_002C4278)*D_002DDED0.dt;
  p->pitchOffsetVelocity+=(p->pitchOffset*D_002C427C+p->pitchOffsetVelocity*D_002C4280)*D_002DDED0.dt;
  p->yawOffset+=p->yawOffsetVelocity*D_002DDED0.dt;
  p->pitchOffset+=p->pitchOffsetVelocity*D_002DDED0.dt;
 }
 func_0014E1A8(&D_002DDF40,w.finalPoint.q,w.tracked.q,yawCorrection+p->yawOffset,pitchCorrection+p->pitchOffset);
 p->vertical=vertical;p->yaw=w.result.yaw;p->pitch=w.result.pitch;p->distance=w.result.radius;
 p->leftYaw=w.left.yaw;p->leftPitch=w.left.pitch;p->rightYaw=w.right.yaw;p->rightPitch=w.right.pitch;
 p->snap=0;
}
