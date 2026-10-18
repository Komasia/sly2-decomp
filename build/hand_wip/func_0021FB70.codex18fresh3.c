typedef struct M3 M3;
typedef struct M4 M4;
typedef struct WORLD WORLD;
typedef struct SO SO;
typedef struct ASEG ASEG;
typedef struct GRAVITY GRAVITY;
typedef struct O O;
typedef struct RING RING;
typedef struct HISTORY HISTORY;
typedef struct S S;
typedef struct HIT HIT;
typedef struct HITPHASE HITPHASE;
typedef struct MATRIXPHASE MATRIXPHASE;
typedef struct WORK WORK;
typedef struct POLY POLY;
typedef struct CLOCK CLOCK;
typedef union V V;
typedef union GEOMETRY GEOMETRY;
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
typedef char FRAME;
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
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword MinXYZ(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword MaxXYZ(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline float Zb(qword v){float f;__asm__("pextuw %0, $zero, %1":"=r"(f):"r"(v));return f;}
static inline float Z(qword v){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(v));return f;}
static inline qword Scalar(qword *home,float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));*home=q;return *home;}
static inline float LengthXY(qword v){
 __asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
static inline float LengthXYZ(qword v){qword one;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return X(v);
}
static inline qword Curve(const qword *p,const qword *a,const qword *v,float t,float half,qword *home){
 qword time=Scalar(home,t);float quadratic=t*(t*half);qword square=Scalar(home,quadratic),r;
 __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(*p),"j"(*v),"j"(time),"j"(*a),"j"(square));return r;
}
static inline qword Previous(const V *first,const V *second,qword *home){
 qword twice=Scalar(home,2.0f),negative=Scalar(home,-1.0f),a,b;
 asm("lqc2 %0,%4\n\tlqc2 %1,%5\n\tvmulax.xyzw ACC,%0,%2x\n\tvmaddx.xyzw %1,%1,%3x":"=&j"(a),"=&j"(b):"j"(twice),"j"(negative),"m"(first->q),"m"(second->q));
 return b;
}
static inline float Clamp(float x,float lo,float hi){if(x<lo)return lo;if(hi<x)return hi;return x;}
static inline float ClampTime(float x,float lo,float hi){float r;if(x<lo)r=lo;else if(hi<x)r=hi;else r=x;return r;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Polynomial(const POLY *p,float x){return p->a+x*(p->b+x*p->c);}
void func_0021FB70(S *p,int updateBlends)
{
 qword scalar;
 FRAME frame;
 WORK w;
 qword start,target,acceleration,ownerPosition,velocity,apex,finalTarget,currentPosition;float blend,apexTime,time,heading,ownerHeading,turn,near;
 start=func_001A6F00(p->owner,0,p->localPoint.q);
 target=p->target.q;
 acceleration=p->selected->gravity->acceleration.q;
 ownerPosition=func_001A62E8(p->owner);
 blend=Clamp((LengthXY(Sub(target,ownerPosition))-p->minDistance)/(p->maxDistance-p->minDistance),0.0f,1.0f);
 velocity=func_001D6848(start,p->target.q,acceleration,Polynomial(&D_002C40F0,blend));
 apexTime=Max(-Z(velocity)/Z(acceleration),0.0f);
 apex=Curve(&start,&acceleration,&velocity,apexTime,0.5f,&scalar);
 if(func_001DAEA8(0x24))time=D_002C40E4*p->predictionTime;
 else time=p->predictionTime;
 {
  float half=0.5f;float accelerationZ,startZ,step,range;unsigned count,i;int pointCount;qword predicted,lower,upper,segmentStart;
  predicted=Curve(&start,&acceleration,&velocity,time,half,&scalar);
  accelerationZ=Zb(acceleration);
  func_001AE478(&frame);
  startZ=Zb(start);
  lower=MinXYZ(apex,predicted);
  upper=MaxXYZ(apex,predicted);
  upper=MaxXYZ(start,upper);
  lower=MinXYZ(start,lower);
  func_0020FAA0(&D_003DD490,lower,upper,func_0021FB18,p->selected->queryContext,&w.count,&w.objects);
  p->velocity.q=velocity;
  step=time*0.034482758f;
  segmentStart=start;
  for(i=1;i<29;i++){
   qword sample;time=(float)(int)i*step;
   sample=Curve(&start,&acceleration,&velocity,time,half,&scalar);
   if(func_0014CC58(1,segmentStart,sample,w.count,w.objects,&w.geometry.clip.hit)){
    int roots=func_0011D508(accelerationZ*half,Z(velocity),startZ-w.geometry.clip.hit.point.f[2],((float *)&scalar));
    float bestTime=0.0f,bestError=D_002A96A0;
    int j;for(j=0;j<roots;j++){
     float root=((float *)&scalar)[j];qword position;float error;
     if(root<0.0f)continue;
     position=Curve(&start,&acceleration,&velocity,root,0.5f,&w.geometry.clip.scalar.q);
     error=LengthXYZ(Sub(position,w.geometry.clip.hit.point.q));
     if(error<bestError){bestError=error;bestTime=root;}
    }
    time=bestTime;
    break;
   }
   segmentStart=sample;
  }
  range=D_002C4100*D_002DDED0.dt;
  time=ClampTime(time,p->flightTime-range,p->flightTime+range);
  p->flightTime=time;
  count=0;
  for(;;){
   if(time<0.1f)break;
   w.points[count].q=Curve(&start,&acceleration,&velocity,time,0.5f,&scalar);
   if(++count>=29)break;
   time=p->flightTime-(float)(int)count*step;
  }
  w.points[count].q=start;
  pointCount=count+1;
  if(p->history){
   RING *ring=p->history->ring+p->history->count;
   qword previous=Previous(&w.points[0],&w.points[1],&scalar);
   V *point=w.points;int i;
   for(i=0;i<p->history->count;i++){
    ring--;
    if(i<pointCount){
     qword current=(point++)->q;
     qword delta=Sub(current,previous);
     func_0011B830(&w.geometry.transform.orientation,delta,D_002A2DC0.q);
     func_00256D18(&w.geometry.transform.matrix.position,current);
     w.geometry.transform.matrix.basis=w.geometry.transform.orientation;
     previous=current;
     w.geometry.transform.matrix.basis.r[2].n[3]=0;
     w.geometry.transform.matrix.basis.r[1].n[3]=0;
     w.geometry.transform.matrix.basis.r[0].n[3]=0;
     w.geometry.transform.matrix.position.f[3]=1.0f;
     ring->valid=1.0f;
    }else ring->valid=0.0f;
    ring->time=D_002DDED0.time;
    ring->length=0.0f;
    ring->matrix=w.geometry.transform.matrix;
   }
   func_0021C5F8(p->history,start);
  }
 }
 finalTarget=p->target.q;
 currentPosition=func_001A62E8(p->owner);
 scalar=Sub(finalTarget,currentPosition);
 heading=func_002458F0(((float *)&scalar)[1],((float *)&scalar)[0]);
 ownerHeading=func_00204740(p->owner);
 heading=func_0011CF60(heading-ownerHeading);
 turn=Clamp(heading/p->turnThreshold,-1.0f,1.0f)*0.5f+0.5f;
 if(updateBlends){
  float oldBlend=p->farBlend,oldTurn,range;
  if(oldBlend>0.5f)oldTurn=p->weight11/oldBlend;
  else oldTurn=p->weight10/(1.0f-oldBlend);
  range=D_002C4104*D_002DDED0.dt;
  blend=Clamp(blend,oldBlend-range,oldBlend+range);
  turn=Clamp(turn,oldTurn-range,oldTurn+range);
 }
 near=1.0f-blend;
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

typedef char layout_pointer_width[(sizeof(void*)==4)?1:-1];
typedef char layout_integer_width[(sizeof(int)==4)?1:-1];
typedef char layout_float_width[(sizeof(float)==4)?1:-1];
typedef char layout_qword_width[(sizeof(qword)==16)?1:-1];
typedef char layout_qword_alignment[(__alignof__(qword)==16)?1:-1];
typedef char layout_frame_size[(sizeof(FRAME)==1)?1:-1];
typedef char layout_frame_alignment[(__alignof__(FRAME)==1)?1:-1];
typedef char layout_V_size[(sizeof(V)==0x10)?1:-1];
typedef char layout_M3_size[(sizeof(M3)==0x30)?1:-1];
typedef char layout_M4_size[(sizeof(M4)==0x40)?1:-1];
typedef char layout_GRAVITY_size[(sizeof(GRAVITY)==0x90)?1:-1];
typedef char layout_O_size[(sizeof(O)==0xF0)?1:-1];
typedef char layout_RING_size[(sizeof(RING)==0x50)?1:-1];
typedef char layout_HISTORY_size[(sizeof(HISTORY)==0x160)?1:-1];
typedef char layout_S_size[(sizeof(S)==0x140)?1:-1];
typedef char layout_HIT_size[(sizeof(HIT)==0x60)?1:-1];
typedef char layout_HITPHASE_size[(sizeof(HITPHASE)==0x70)?1:-1];
typedef char layout_MATRIXPHASE_size[(sizeof(MATRIXPHASE)==0x70)?1:-1];
typedef char layout_GEOMETRY_size[(sizeof(GEOMETRY)==0x70)?1:-1];
typedef char layout_WORK_size[(sizeof(WORK)==0x260)?1:-1];
typedef char layout_POLY_size[(sizeof(POLY)==0xC)?1:-1];
typedef char layout_CLOCK_size[(sizeof(CLOCK)==0x8)?1:-1];
typedef char layout_V_q[(((unsigned int)&(((V*)0)->q))==0x0)?1:-1];
typedef char layout_V_f[(((unsigned int)&(((V*)0)->f))==0x0)?1:-1];
typedef char layout_V_n[(((unsigned int)&(((V*)0)->n))==0x0)?1:-1];
typedef char layout_M3_r[(((unsigned int)&(((M3*)0)->r))==0x0)?1:-1];
typedef char layout_M4_basis[(((unsigned int)&(((M4*)0)->basis))==0x0)?1:-1];
typedef char layout_M4_position[(((unsigned int)&(((M4*)0)->position))==0x30)?1:-1];
typedef char layout_GRAVITY_acceleration[(((unsigned int)&(((GRAVITY*)0)->acceleration))==0x80)?1:-1];
typedef char layout_O_gravity[(((unsigned int)&(((O*)0)->gravity))==0xE8)?1:-1];
typedef char layout_O_queryContext[(((unsigned int)&(((O*)0)->queryContext))==0xEC)?1:-1];
typedef char layout_RING_time[(((unsigned int)&(((RING*)0)->time))==0x0)?1:-1];
typedef char layout_RING_valid[(((unsigned int)&(((RING*)0)->valid))==0x4)?1:-1];
typedef char layout_RING_length[(((unsigned int)&(((RING*)0)->length))==0x8)?1:-1];
typedef char layout_RING_matrix[(((unsigned int)&(((RING*)0)->matrix))==0x10)?1:-1];
typedef char layout_HISTORY_count[(((unsigned int)&(((HISTORY*)0)->count))==0x158)?1:-1];
typedef char layout_HISTORY_ring[(((unsigned int)&(((HISTORY*)0)->ring))==0x15C)?1:-1];
typedef char layout_S_owner[(((unsigned int)&(((S*)0)->owner))==0x0)?1:-1];
typedef char layout_S_selected[(((unsigned int)&(((S*)0)->selected))==0x10)?1:-1];
typedef char layout_S_turnThreshold[(((unsigned int)&(((S*)0)->turnThreshold))==0x18)?1:-1];
typedef char layout_S_minDistance[(((unsigned int)&(((S*)0)->minDistance))==0x1C)?1:-1];
typedef char layout_S_maxDistance[(((unsigned int)&(((S*)0)->maxDistance))==0x20)?1:-1];
typedef char layout_S_predictionTime[(((unsigned int)&(((S*)0)->predictionTime))==0x24)?1:-1];
typedef char layout_S_weight00[(((unsigned int)&(((S*)0)->weight00))==0x68)?1:-1];
typedef char layout_S_weight10[(((unsigned int)&(((S*)0)->weight10))==0x74)?1:-1];
typedef char layout_S_weight01[(((unsigned int)&(((S*)0)->weight01))==0x80)?1:-1];
typedef char layout_S_weight11[(((unsigned int)&(((S*)0)->weight11))==0x8C)?1:-1];
typedef char layout_S_primary[(((unsigned int)&(((S*)0)->primary))==0x98)?1:-1];
typedef char layout_S_nearBlend[(((unsigned int)&(((S*)0)->nearBlend))==0xA4)?1:-1];
typedef char layout_S_farBlend[(((unsigned int)&(((S*)0)->farBlend))==0xB0)?1:-1];
typedef char layout_S_secondary[(((unsigned int)&(((S*)0)->secondary))==0xBC)?1:-1];
typedef char layout_S_targetLocal[(((unsigned int)&(((S*)0)->targetLocal))==0xC0)?1:-1];
typedef char layout_S_localPoint[(((unsigned int)&(((S*)0)->localPoint))==0xD0)?1:-1];
typedef char layout_S_target[(((unsigned int)&(((S*)0)->target))==0xE0)?1:-1];
typedef char layout_S_velocity[(((unsigned int)&(((S*)0)->velocity))==0xF0)?1:-1];
typedef char layout_S_history[(((unsigned int)&(((S*)0)->history))==0x12C)?1:-1];
typedef char layout_S_flightTime[(((unsigned int)&(((S*)0)->flightTime))==0x130)?1:-1];
typedef char layout_HIT_point[(((unsigned int)&(((HIT*)0)->point))==0x0)?1:-1];
typedef char layout_HITPHASE_hit[(((unsigned int)&(((HITPHASE*)0)->hit))==0x0)?1:-1];
typedef char layout_HITPHASE_scalar[(((unsigned int)&(((HITPHASE*)0)->scalar))==0x60)?1:-1];
typedef char layout_MATRIXPHASE_matrix[(((unsigned int)&(((MATRIXPHASE*)0)->matrix))==0x0)?1:-1];
typedef char layout_MATRIXPHASE_orientation[(((unsigned int)&(((MATRIXPHASE*)0)->orientation))==0x40)?1:-1];
typedef char layout_GEOMETRY_clip[(((unsigned int)&(((GEOMETRY*)0)->clip))==0x0)?1:-1];
typedef char layout_GEOMETRY_transform[(((unsigned int)&(((GEOMETRY*)0)->transform))==0x0)?1:-1];
typedef char layout_WORK_points[(((unsigned int)&(((WORK*)0)->points))==0x0)?1:-1];
typedef char layout_WORK_geometry[(((unsigned int)&(((WORK*)0)->geometry))==0x1E0)?1:-1];
typedef char layout_WORK_count[(((unsigned int)&(((WORK*)0)->count))==0x250)?1:-1];
typedef char layout_WORK_objects[(((unsigned int)&(((WORK*)0)->objects))==0x254)?1:-1];
typedef char layout_POLY_a[(((unsigned int)&(((POLY*)0)->a))==0x0)?1:-1];
typedef char layout_POLY_b[(((unsigned int)&(((POLY*)0)->b))==0x4)?1:-1];
typedef char layout_POLY_c[(((unsigned int)&(((POLY*)0)->c))==0x8)?1:-1];
typedef char layout_CLOCK_time[(((unsigned int)&(((CLOCK*)0)->time))==0x0)?1:-1];
typedef char layout_CLOCK_dt[(((unsigned int)&(((CLOCK*)0)->dt))==0x4)?1:-1];
