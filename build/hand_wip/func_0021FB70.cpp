// Predict a collision-limited trajectory, rebuild history frames, and update blends.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
struct FRAME {};
struct WORLD;
struct SO;
struct ASEG;
struct GRAVITY {char unknown0[0x80];V acceleration;};
struct O {char unknown0[0xE8];GRAVITY *gravity;void *queryContext;};
struct RING {float time,valid,length;M4 matrix;};
struct HISTORY {char unknown0[0x158];int count;RING *ring;};
struct S {
 O *owner;char unknown4[0xC];O *selected;char unknown14[4];
 float turnThreshold,minDistance,maxDistance,predictionTime;
 char unknown28[0x40];float weight00;char unknown6C[8];
 float weight10;char unknown78[8];float weight01;char unknown84[8];
 float weight11;char unknown90[8];ASEG *primary;char unknown9C[8];
 float nearBlend;char unknownA8[8];float farBlend;char unknownB4[8];
 ASEG *secondary;V targetLocal,localPoint,target,velocity;char unknown100[0x2C];
 HISTORY *history;float flightTime;
};
struct HIT {V point;char unknown10[0x50];};
struct HITPHASE {HIT hit;V scalar;};
struct MATRIXPHASE {M4 matrix;M3 orientation;};
union GEOMETRY {HITPHASE clip;MATRIXPHASE transform;};
struct WORK {
 V scalar;
 FRAME frame;
 V points[30];
 GEOMETRY geometry;
 int count;SO **objects;
 V start,acceleration,velocity,apex,current,target,predicted,sample;
};
struct POLY {float a,b,c;};
struct CLOCK {float time,dt;};
extern WORLD D_003DD490;
extern CLOCK D_002DDED0;
extern POLY D_002C40F0;
extern float D_002C40E4,D_002C4100,D_002C4104,D_002A96A0;
extern V D_002A2DC0;
extern "C" {
 qword func_001A6F00(O *,O *,qword);
 qword func_001A62E8(O *);
 qword func_001D6848(qword,qword,qword,float);
 int func_001DAEA8(int);
 FRAME *func_001AE478(FRAME *);
 void func_001AE4A0(FRAME *,int);
 void func_0020FAA0(WORLD *,qword,qword,int (*)(void *,SO *),void *,int *,SO ***);
 int func_0021FB18(void *,SO *);
 SO *func_0014CC58(int,qword,qword,int,SO **,HIT *);
 int func_0011D508(float,float,float,float *);
 M3 *func_0011B830(M3 *,qword,qword);
 V *func_00256D18(V *,qword);
 void func_0021C5F8(HISTORY *,qword);
 float func_002458F0(float,float);
 float func_00204740(O *);
 float func_0011CF60(float);
 void func_001384C0(ASEG *);
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword MinXYZ(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword MaxXYZ(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline float Z(qword v){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(v));return f;}
static inline qword Scalar(V &home,float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));home.q=q;return home.q;}
static inline float LengthXY(qword v){
 __asm__("vmul.xy %0,%0,%0":"+j"(v));
 __asm__("vaddy.x %0,%0,%0y":"+j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
static inline float LengthXYZ(qword v){qword one;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
static inline qword Curve(qword p,qword v,qword a,float t,float half,V &home){
 qword time=Scalar(home,t);float quadratic=t*(t*half);qword square=Scalar(home,quadratic),r;
 __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(p),"j"(v),"j"(time),"j"(a),"j"(square));return r;
}
static inline qword Previous(qword first,qword second,V &home){
 qword twice=Scalar(home,2.0f),negative=Scalar(home,-1.0f),r;
 __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(first),"j"(twice),"j"(second),"j"(negative));return r;
}
static inline float Clamp(float x,float lo,float hi){if(x<lo)return lo;if(hi<x)return hi;return x;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Polynomial(const POLY &p,float x){return p.a+x*(p.b+x*p.c);}
static inline void CopyMatrix(M4 *d,const M4 &s){
 d->basis.r[0]=s.basis.r[0];d->basis.r[1]=s.basis.r[1];d->basis.r[2]=s.basis.r[2];d->position=s.position;
}
extern "C" void func_0021FB70(S *p,int updateBlends)
{
 WORK w;
 w.start.q=func_001A6F00(p->owner,0,p->localPoint.q);
 w.predicted.q=p->target.q;
 w.acceleration.q=p->selected->gravity->acceleration.q;
 qword ownerPosition=func_001A62E8(p->owner);
 float blend=Clamp((LengthXY(Sub(w.predicted.q,ownerPosition))-p->minDistance)/(p->maxDistance-p->minDistance),0.0f,1.0f);
 w.velocity.q=func_001D6848(w.start.q,p->target.q,w.acceleration.q,Polynomial(D_002C40F0,blend));
 float apexTime=Max(-Z(w.velocity.q)/Z(w.acceleration.q),0.0f);
 w.apex.q=Curve(w.start.q,w.velocity.q,w.acceleration.q,apexTime,0.5f,w.scalar);
 float time;
 if(func_001DAEA8(0x24))time=D_002C40E4*p->predictionTime;
 else time=p->predictionTime;
 {
  float half=0.5f;
  w.predicted.q=Curve(w.start.q,w.velocity.q,w.acceleration.q,time,half,w.scalar);
  float accelerationZ=Z(w.acceleration.q);
  func_001AE478(&w.frame);
  float startZ=Z(w.start.q);
  qword upper=MaxXYZ(w.apex.q,w.predicted.q);
  qword lower=MinXYZ(w.apex.q,w.predicted.q);
  lower=MinXYZ(w.start.q,lower);
  upper=MaxXYZ(w.start.q,upper);
  func_0020FAA0(&D_003DD490,lower,upper,func_0021FB18,p->selected->queryContext,&w.count,&w.objects);
  p->velocity.q=w.velocity.q;
  float step=time*0.034482758f;
  qword segmentStart=w.start.q;
  for(int i=1;i<29;i++){
   time=(float)i*step;
   w.sample.q=Curve(w.start.q,w.velocity.q,w.acceleration.q,time,half,w.scalar);
   if(func_0014CC58(1,segmentStart,w.sample.q,w.count,w.objects,&w.geometry.clip.hit)){
    int roots=func_0011D508(accelerationZ*half,Z(w.velocity.q),startZ-w.geometry.clip.hit.point.f[2],w.scalar.f);
    float bestTime=0.0f,bestError=D_002A96A0;
    for(int j=0;j<roots;j++){
     float root=w.scalar.f[j];
     if(root<0.0f)continue;
     qword position=Curve(w.start.q,w.velocity.q,w.acceleration.q,root,half,w.geometry.clip.scalar);
     float error=LengthXYZ(Sub(position,w.geometry.clip.hit.point.q));
     if(error<bestError){bestError=error;bestTime=root;}
    }
    time=bestTime;
    break;
   }
   segmentStart=w.sample.q;
  }
  float range=D_002C4100*D_002DDED0.dt;
  time=Clamp(time,p->flightTime-range,p->flightTime+range);
  p->flightTime=time;
  int count=0;
  if(!(time<0.1f)){
   do{
    w.points[count].q=Curve(w.start.q,w.velocity.q,w.acceleration.q,time,half,w.scalar);
    ++count;
    if(count>=29)break;
    time=p->flightTime-(float)count*step;
   }while(!(time<0.1f));
  }
  w.points[count].q=w.start.q;
  int pointCount=count+1;
  if(p->history){
   RING *ring=p->history->ring+p->history->count;
   qword previous=Previous(w.points[0].q,w.points[1].q,w.scalar);
   V *point=w.points;
   for(int i=0;i<p->history->count;i++){
    ring--;
    if(i<pointCount){
     w.current.q=(point++)->q;
     qword delta=Sub(w.current.q,previous);
     func_0011B830(&w.geometry.transform.orientation,delta,D_002A2DC0.q);
     func_00256D18(&w.geometry.transform.matrix.position,w.current.q);
     w.geometry.transform.matrix.basis=w.geometry.transform.orientation;
     previous=w.current.q;
     w.geometry.transform.matrix.basis.r[2].n[3]=0;
     w.geometry.transform.matrix.basis.r[1].n[3]=0;
     w.geometry.transform.matrix.basis.r[0].n[3]=0;
     w.geometry.transform.matrix.position.f[3]=1.0f;
     ring->valid=1.0f;
    }else ring->valid=0.0f;
    ring->time=D_002DDED0.time;
    ring->length=0.0f;
    CopyMatrix(&ring->matrix,w.geometry.transform.matrix);
   }
   func_0021C5F8(p->history,w.start.q);
  }
 }
 w.target.q=p->target.q;
 qword currentPosition=func_001A62E8(p->owner);
 w.scalar.q=Sub(w.target.q,currentPosition);
 float heading=func_002458F0(w.scalar.f[1],w.scalar.f[0]);
 float ownerHeading=func_00204740(p->owner);
 heading=func_0011CF60(heading-ownerHeading);
 float turn=Clamp(heading/p->turnThreshold,-1.0f,1.0f)*0.5f+0.5f;
 if(updateBlends){
  float oldBlend=p->farBlend,oldTurn;
  if(oldBlend>0.5f)oldTurn=p->weight11/oldBlend;
  else oldTurn=p->weight10/(1.0f-oldBlend);
  float range=D_002C4104*D_002DDED0.dt;
  blend=Clamp(blend,oldBlend-range,oldBlend+range);
  turn=Clamp(turn,oldTurn-range,oldTurn+range);
 }
 float near=1.0f-blend;
 p->weight11=turn*blend;
 p->weight10=turn*near;
 p->weight01=(1.0f-turn)*blend;
 p->weight00=(1.0f-turn)*near;
 func_001384C0(p->primary);
 p->nearBlend=near;
 p->farBlend=blend;
 func_001384C0(p->secondary);
 func_001AE4A0(&w.frame,2);
}
