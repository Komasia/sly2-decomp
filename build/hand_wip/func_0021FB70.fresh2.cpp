// (Claude agent, big14) fresh2
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
struct FRAME {int a[3];};
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
static inline qword Min(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Max(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float GetZ(qword v){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(v));return f;}
static inline float GetZb(qword v){float f;__asm__("pextuw %0, $zero, %1":"=r"(f):"r"(v));return f;}
template<class H> static inline qword Splat(H &home,float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));home=q;return home;}
static inline float LenXY(qword v){qword d,l;float g;
 __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(d):"j"(v));
 __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(l):"j"(d));
 __asm__("qmfc2.ni %0,%1":"=r"(g):"j"(l));return g;}
static inline float LenXYZ(qword v){qword d,one,l;float g;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));
 __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(l):"j"(d));
 __asm__("qmfc2.ni %0,%1":"=r"(g):"j"(l));return g;}
template<class H> static inline qword Arc(const qword &p,const qword &v,const qword &a,float t,float half,H &home){
 qword st=Splat(home,t);qword sq=Splat(home,t*(t*half));qword r;
 __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(p),"j"(v),"j"(st),"j"(a),"j"(sq));return r;}
template<class H> static inline qword Back(qword a,qword b,H &home){
 qword two=Splat(home,2.0f),neg=Splat(home,-1.0f),r;
 __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(two),"j"(b),"j"(neg));return r;}

static inline float Clamp(float x,float lo,float hi){if(x<lo)return lo;if(hi<x)return hi;return x;}
struct BLOCKS {
 V points[30];
 union { struct { HIT hit; qword home; } c; struct { M4 matrix; M3 orientation; } t; } g;
};

extern "C" void func_0021FB70(S *p,int updateBlends)
{
 V tmp;
 FRAME frame;
 BLOCKS b;
 int count; SO **objects;
 qword start=func_001A6F00(p->owner,0,p->localPoint.q);
 qword target=p->target.q;
 qword accel=p->selected->gravity->acceleration.q;
 qword ownerPos=func_001A62E8(p->owner);
 float d=LenXY(Sub(target,ownerPos));
 float blend=Clamp((d-p->minDistance)/(p->maxDistance-p->minDistance),0.0f,1.0f);
 qword velocity=func_001D6848(start,p->target.q,accel,D_002C40F0.a+blend*(D_002C40F0.b+blend*D_002C40F0.c));
 float tApex=-GetZ(velocity)/GetZ(accel);
 tApex=tApex<0.0f?0.0f:tApex;
 qword apex=Arc(start,velocity,accel,tApex,0.5f,tmp.q);
 float time;
 if(func_001DAEA8(0x24))time=D_002C40E4*p->predictionTime;
 else time=p->predictionTime;
 float half=0.5f;
 qword predicted=Arc(start,velocity,accel,time,half,tmp.q);
 float accelZ=GetZb(accel);
 func_001AE478(&frame);
 float startZ=GetZb(start);
 qword hi=Max(apex,predicted);
 qword lo=Min(apex,predicted);
 lo=Min(start,lo);
 hi=Max(start,hi);
 func_0020FAA0(&D_003DD490,lo,hi,func_0021FB18,p->selected->queryContext,&count,&objects);
 p->velocity.q=velocity;
 float step=time*0.034482758f;
 qword prev=start;
 for(unsigned i=1;i<29;i++){
  time=(float)(int)i*step;
  qword sample=Arc(start,velocity,accel,time,half,tmp.q);
  if(func_0014CC58(1,prev,sample,count,objects,&b.g.c.hit)){
   int n=func_0011D508(accelZ*half,GetZ(velocity),startZ-b.g.c.hit.point.f[2],tmp.f);
   float tBest=0.0f,dBest=D_002A96A0;
   for(int j=0;j<n;j++){
    float r=tmp.f[j];
    if(r<0.0f)continue;
    float e=LenXYZ(Sub(Arc(start,velocity,accel,r,0.5f,b.g.c.home),b.g.c.hit.point.q));
    if(e<dBest){dBest=e;tBest=r;}
   }
   time=tBest;
   break;
  }
  prev=sample;
 }
 float range=D_002C4100*D_002DDED0.dt;
 float lo2=p->flightTime-range,hi2=p->flightTime+range;
 if(time<lo2)time=lo2;else if(hi2<time)time=hi2;
 p->flightTime=time;
 unsigned c=0;
 while(!(time<0.1f)){
  b.points[c].q=Arc(start,velocity,accel,time,0.5f,tmp.q);
  if(++c>=29)break;
  time=p->flightTime-(float)(int)c*step;
 }
 b.points[c].q=start;
 int nPoints=c+1;
 if(p->history){
  RING *ring=p->history->ring+p->history->count;
  qword last=Back(b.points[0].q,b.points[1].q,tmp.q);
  V *pt=b.points;
  for(int i=0;i<p->history->count;i++){
   ring--;
   if(i<nPoints){
    qword cur=(pt++)->q;
    func_0011B830(&b.g.t.orientation,Sub(cur,last),D_002A2DC0.q);
    func_00256D18(&b.g.t.matrix.position,cur);
    b.g.t.matrix.basis=b.g.t.orientation;
    last=cur;
    b.g.t.matrix.basis.r[2].n[3]=0;
    b.g.t.matrix.basis.r[1].n[3]=0;
    b.g.t.matrix.basis.r[0].n[3]=0;
    b.g.t.matrix.position.f[3]=1.0f;
    ring->valid=1.0f;
   }else ring->valid=0.0f;
   ring->time=D_002DDED0.time;
   ring->length=0.0f;
   ring->matrix=b.g.t.matrix;
  }
  func_0021C5F8(p->history,start);
 }
 qword aim=p->target.q;
 qword here=func_001A62E8(p->owner);
 tmp.q=Sub(aim,here);
 float h=func_002458F0(tmp.f[1],tmp.f[0]);
 float hOwner=func_00204740(p->owner);
 h=func_0011CF60(h-hOwner);
 float turn=h/p->turnThreshold;
 if(turn<-1.0f)turn=-1.0f;else if(1.0f<turn)turn=1.0f;
 turn=turn*0.5f+0.5f;
 if(updateBlends){
  float old=p->farBlend,oldTurn;
  if(0.5f<old)oldTurn=p->weight11/old;
  else oldTurn=p->weight10/(1.0f-old);
  float r=D_002C4104*D_002DDED0.dt;
  if(blend<old-r)blend=old-r;else if(old+r<blend)blend=old+r;
  if(turn<oldTurn-r)turn=oldTurn-r;else if(oldTurn+r<turn)turn=oldTurn+r;
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
 func_001AE4A0(&frame,2);
}
