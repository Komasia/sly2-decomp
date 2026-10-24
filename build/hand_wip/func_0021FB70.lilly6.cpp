// (Claude agent, big14) fresh8: aligned 152. fresh7 + points loop as for(;;){if(time<0.1f)break;...if(++count>=29)break;...} (fixes c.le -> c.lt/bc1fl). Left: Scalar home stores not sunk (target load_mems promotes them: home must be a fixed scalar MEM, ours is union V), &frame/D_002A96A0 hi kept in s-regs, f23/f25 roles.
// Predict a collision-limited trajectory, rebuild history frames, and update blends.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
struct STACKSCOPE {STACKSCOPE();~STACKSCOPE();};
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
 V points[30];
 GEOMETRY geometry;
 int count;SO **objects;
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
 STACKSCOPE *func_001AE478(STACKSCOPE *);
 void func_001AE4A0(STACKSCOPE *,int);
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
struct VU_VECTOR{qword q;VU_VECTOR(){}VU_VECTOR(qword qw){q=qw;}};
static inline VU_VECTOR SubV(VU_VECTOR a,VU_VECTOR b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a.q),"j"(b.q));return VU_VECTOR(r);}

static inline qword MinXYZ(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword MaxXYZ(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline float Zb(qword v){float f;__asm__("pextuw %0, $zero, %1":"=r"(f):"r"(v));return f;}
static inline float Zi(qword v){int n;__asm__("pextuw %0, $zero, %1":"=r"(n):"r"(v));return *(float*)&n;}
static inline float Z(qword v){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(v));return f;}
static inline qword Scalar(V &home,float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));home.q=q;return home.q;}
static inline float LengthXY(qword v){
 __asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
static inline float LengthXYZV(VU_VECTOR w){qword v=w.q;qword one;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
static inline float LengthXYZ(qword v){qword one;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
struct VU_FLOAT {qword qw;};
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}
static inline qword CurveVu(const qword &p,const qword &a,const qword &v,VU_FLOAT time,VU_FLOAT square){qword r;
 __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(p),"j"(v),"j"(time.qw),"j"(a),"j"(square.qw));return r;
}
static inline qword Curve(const qword &p,const qword &a,const qword &v,float t,float half){return CurveVu(p,a,v,VuFloat(t),VuFloat(t*(t*half)));}
static inline qword Previous(qword first,qword second,VU_FLOAT twice,VU_FLOAT negative){qword r;
 __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(first),"j"(twice.qw),"j"(second),"j"(negative.qw));return r;
}
static inline float Clamp(float x,float lo,float hi){if(x<lo)return lo;if(hi<x)return hi;return x;}
static inline float ClampTime(float x,float lo,float hi){float r;if(x<lo)r=lo;else if(hi<x)r=hi;else r=x;return r;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Polynomial(const POLY &p,float x){return p.a+x*(p.b+x*p.c);}
extern "C" void func_0021FB70(S *p,int updateBlends)
{
 qword start=func_001A6F00(p->owner,0,p->localPoint.q);
 qword target=p->target.q;
 qword acceleration=p->selected->gravity->acceleration.q;
 qword ownerPosition=func_001A62E8(p->owner);
 float blend=Clamp((LengthXY(Sub(target,ownerPosition))-p->minDistance)/(p->maxDistance-p->minDistance),0.0f,1.0f);
 qword velocity=func_001D6848(start,p->target.q,acceleration,Polynomial(D_002C40F0,blend));
 float apexTime=Max(-Z(velocity)/Z(acceleration),0.0f);
 qword apex=Curve(start,acceleration,velocity,apexTime,0.5f);
 float time;
 if(func_001DAEA8(0x24))time=D_002C40E4*p->predictionTime;
 else time=p->predictionTime;
 qword predicted=Curve(start,acceleration,velocity,time,0.5f);
 STACKSCOPE frame;
 qword lower=MinXYZ(apex,predicted);
 qword upper=MaxXYZ(apex,predicted);
 upper=MaxXYZ(start,upper);
 lower=MinXYZ(start,lower);
 int count;SO **objects;
 func_0020FAA0(&D_003DD490,lower,upper,func_0021FB18,p->selected->queryContext,&count,&objects);
 p->velocity.q=velocity;
 float step=time*0.034482758f;
 V points[30];
 qword segmentStart=start;
 unsigned i;
 for(i=1;i<29;i++){
  time=(float)(int)i*step;
  qword sample=Curve(start,acceleration,velocity,time,0.5f);
  HIT hit;
  if(func_0014CC58(1,segmentStart,sample,count,objects,&hit)){
   V roots;
   int n=func_0011D508(Zb(acceleration)*0.5f,Z(velocity),Zb(start)-hit.point.f[2],roots.f);
   float bestTime=0.0f,bestError=D_002A96A0;
   for(int j=0;j<n;j++){
    float root=roots.f[j];
    if(root<0.0f)continue;
    qword position=Curve(start,acceleration,velocity,root,0.5f);
    float error=LengthXYZV(SubV(position,hit.point.q));
    if(error<bestError){bestError=error;bestTime=root;}
   }
   time=bestTime;
   break;
  }
  segmentStart=sample;
 }
 float range=D_002C4100*D_002DDED0.dt;
 p->flightTime=ClampTime(time,p->flightTime-range,p->flightTime+range);
 time=p->flightTime;
 i=0;
 for(;;){
  if(time<0.1f)break;
  points[i].q=Curve(start,acceleration,velocity,time,0.5f);
  if(++i>=29)break;
  time=p->flightTime-(float)(int)i*step;
 }
 (points+i)->q=start;
 int pointCount=i+1;
 if(p->history){
  RING *ring=p->history->ring+p->history->count;
  qword previous=Previous(points[0].q,points[1].q,VuFloat(2.0f),VuFloat(-1.0f));
  V *point=points;
  M4 matrix;M3 orientation;
  for(int i=0;i<p->history->count;i++){
   ring--;
   if(i<pointCount){
    V *pc=point++;
    qword current=pc->q;
    qword delta=Sub(current,previous);
    func_0011B830(&orientation,delta,D_002A2DC0.q);
    M4 *pmat=&matrix;
    func_00256D18(&matrix.position,current);
    pmat->basis=orientation;
    previous=current;
    matrix.basis.r[2].n[3]=0;
    matrix.basis.r[1].n[3]=0;
    matrix.basis.r[0].n[3]=0;
    pmat->position.f[3]=1.0f;
    ring->valid=1.0f;
   }else ring->valid=0.0f;
   ring->time=D_002DDED0.time;
   ring->length=0.0f;
   ring->matrix=matrix;
  }
  func_0021C5F8(p->history,start);
 }
 qword finalTarget=p->target.q;
 qword currentPosition=func_001A62E8(p->owner);
 V delta;
 delta.q=Sub(finalTarget,currentPosition);
 float heading=func_002458F0(delta.f[1],delta.f[0]);
 float ownerHeading=func_00204740(p->owner);
 heading=func_0011CF60(heading-ownerHeading);
 float turn=Clamp(heading/p->turnThreshold,-1.0f,1.0f)*0.5f+0.5f;
 if(updateBlends){
  float oldBlend=p->farBlend,oldTurn;
  if(oldBlend>0.5f)oldTurn=p->weight11/oldBlend;
  else oldTurn=p->weight10/(1.0f-oldBlend);
  float dt=D_002DDED0.dt;
  float range=D_002C4104*dt;
  blend=Clamp(blend,oldBlend-range,oldBlend+range);
  turn=Clamp(turn,oldTurn-range,oldTurn+range);
 }
 float left=1.0f-turn;
 float near=1.0f-blend;
 p->weight00=left*near;
 p->weight10=turn*near;
 p->weight01=left*blend;
 p->weight11=turn*blend;
 func_001384C0(p->primary);
 p->nearBlend=near;
 p->farBlend=blend;
 func_001384C0(p->secondary);
}
