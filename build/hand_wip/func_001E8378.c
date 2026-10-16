
typedef int qword __attribute__((mode(TI)));
typedef union U {qword q;float f[4];} U;
typedef struct M4 {qword row[4];} M4;
typedef struct OWNER {char unknown0[0x40];M4 world;} OWNER;
typedef struct PATH PATH;
typedef struct VTE {short delta,pad;M4*(*fn)(PATH*);} VTE;
struct PATH {char unknown0[0xC];VTE*vt;char unknown10[0xD8];int count;char unknownEC[4];float *values;U *points;};
typedef struct P {qword acceleration,unknown10,localStart,localEnd;OWNER *start,*end;PATH *path;int mode;int unknown50;U *positions,*velocities;float *distances;float drag,stretch,stretchVelocity,bend,bendVelocity,shape,shapeVelocity;} P;
typedef struct HIT {qword point[2],plane[2];float fraction[2];int enabled;void *surface[2];char unknown54[0xC];} HIT;
typedef union PHASE {struct {U first,second,leftProjection,rightProjection,scalar;} math;M4 inverse;} PHASE;
typedef struct WORK {U newP[64],newV[64],oldP[64],oldV[64],forces[64];PHASE phase;HIT hit;int count;U worldStart,worldEnd,velocityEnd;} WORK;
typedef struct CLOCK {float time,dt;} CLOCK;
extern CLOCK D_002DDED0;
extern float D_002C3658[4],D_002C3668[4];
extern qword D_002A2DA0,D_002A2DC0;
extern qword func_0022D348(OWNER*,OWNER*,qword);
extern void func_001AE5A0(void*,const void*,unsigned int);
extern int func_0014C748(qword,qword,qword,int,HIT*,float);
extern M4*func_0011C318(M4*,M4*);
extern void func_001E6330(PATH*);
static inline qword Read(const U*v){qword q;__asm__("lq %0,%1":"=r"(q):"m"(v->q));return q;}
static inline qword FirstPoint(const M4*m,qword v){register qword r __asm__("vf6");__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m->row[0]),"j"(m->row[1]),"j"(m->row[2]),"j"(m->row[3]),"j"(v));return r;}
static inline qword Point(const M4*m,qword v){qword r=m->row[0];__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m->row[1]),"j"(m->row[2]),"j"(m->row[3]),"j"(v));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Bc(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline float Float(qword v){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline qword Sq(qword v){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(v));return r;}
static inline qword Dot(qword a,qword b){qword r=a,one;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(r),"=&j"(one):"j"(b));return r;}
static inline qword Length(qword v){qword r=Sq(v);__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(r));return r;}
static inline qword Norm(qword v,qword len){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(v),"j"(len));return r;}
static inline qword MulX(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword AddScaled2(qword a,qword b,qword c,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(b),"j"(c),"j"(s));return r;}
static inline qword AddForces(qword a,qword b,qword s,qword c,qword t){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(a),"j"(b),"j"(s),"j"(c),"j"(t));return r;}
static inline qword Lerp(qword a,qword b,float f,U*scalar){qword r,s,t;scalar->q=Bc(1.f-f);s=scalar->q;scalar->q=Bc(f);t=scalar->q;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(s),"j"(t));return r;}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float SqrtF(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
void func_001E8378(P*input){
 register P*p __asm__("$18")=input;
 WORK w;
 register qword velocityStart __asm__("s1");
 int pass,i,last,interior;
 w.worldStart.q=FirstPoint(&p->start->world,p->localStart);
 w.count=p->path->count;
 velocityStart=func_0022D348(p->start,0,Read(&w.worldStart));
 w.worldEnd.q=FirstPoint(&p->end->world,p->localEnd);
 w.velocityEnd.q=func_0022D348(p->end,0,Read(&w.worldEnd));
 if((unsigned int)w.count>64)return;
 func_001AE5A0(w.oldP,p->positions,w.count*16);
 last=w.count-1;
 func_001AE5A0(w.oldV,p->velocities,w.count*16);
 interior=w.count-2;
 {
 register U *positions __asm__("$16")=p->positions;
 register U *velocities __asm__("$30")=p->velocities;
 for(pass=0;pass<4;pass++){
  float weight=D_002C3658[pass];
  float predictDt=weight*D_002DDED0.dt;
  float amplitude,rest;
  w.newP[0].q=Lerp(positions[0].q,w.worldStart.q,weight,&w.phase.math.first);
  w.newV[0].q=Lerp(velocities[0].q,velocityStart,weight,&w.phase.math.first);
  w.newP[last].q=Lerp(positions[last].q,w.worldEnd.q,weight,&w.phase.math.first);
  w.newV[last].q=Lerp(velocities[last].q,w.velocityEnd.q,weight,&w.phase.math.first);
  for(i=1;i<last;i++){
   w.phase.math.first.q=Bc(predictDt);
   w.newV[i].q=AddScaled(velocities[i].q,w.forces[i].q,w.phase.math.first.q);
   w.phase.math.first.q=Bc(predictDt*.5f);
   w.newP[i].q=AddScaled2(positions[i].q,velocities[i].q,w.newV[i].q,w.phase.math.first.q);
  }
  rest=p->distances[last];
  amplitude=(.75f-.25f/interior)*SqrtF(Max(rest*rest-Float(Sq(Sub(w.newP[0].q,w.newP[last].q))),0.f));
  for(i=1;i<last;i++){
   qword force,len;
   float integrateDt;
   w.phase.math.first.q=Bc(-p->drag);
   force=AddScaled(p->acceleration,w.newV[i].q,w.phase.math.first.q);
   if(p->stretch!=0.f||p->stretchVelocity!=0.f){
    qword leftLen,rightLen;
    float leftRest,rightRest,leftScale,rightScale;
    w.phase.math.first.q=Sub(w.newP[i-1].q,w.newP[i].q);
    leftLen=Length(w.phase.math.first.q);
    w.phase.math.second.q=Sub(w.newP[i+1].q,w.newP[i].q);
    if(Float(leftLen)<.0001f)w.phase.math.first.q=D_002A2DA0;else w.phase.math.first.q=Norm(w.phase.math.first.q,leftLen);
    rightLen=Length(w.phase.math.second.q);
    if(Float(rightLen)<.0001f)w.phase.math.second.q=D_002A2DA0;else w.phase.math.second.q=Norm(w.phase.math.second.q,rightLen);
    leftRest=p->distances[i]-p->distances[i-1];
    rightRest=p->distances[i+1]-p->distances[i];
    w.phase.math.leftProjection.q=MulX(w.phase.math.first.q,Dot(Sub(w.newV[i-1].q,w.newV[i].q),w.phase.math.first.q));
    leftScale=p->stretch*(Float(leftLen)-leftRest);
    rightScale=p->stretch*(Float(rightLen)-rightRest);
    w.phase.math.rightProjection.q=MulX(w.phase.math.second.q,Dot(Sub(w.newV[i+1].q,w.newV[i].q),w.phase.math.second.q));
    w.phase.math.scalar.q=Bc(leftScale);
    force=AddForces(force,w.phase.math.first.q,w.phase.math.scalar.q,w.phase.math.leftProjection.q,Bc(p->stretchVelocity));
    w.phase.math.scalar.q=Bc(rightScale);
    force=AddForces(force,w.phase.math.second.q,w.phase.math.scalar.q,w.phase.math.rightProjection.q,Bc(p->stretchVelocity));
   }
   if(p->bend!=0.f||p->bendVelocity!=0.f){
    float ratio=(p->distances[i]-p->distances[i-1])/(p->distances[i+1]-p->distances[i-1]);
    w.phase.math.first.q=Lerp(w.newP[i-1].q,w.newP[i+1].q,ratio,&w.phase.math.scalar);
    w.phase.math.second.q=Lerp(w.newV[i-1].q,w.newV[i+1].q,ratio,&w.phase.math.scalar);
    w.phase.math.leftProjection.q=Sub(w.phase.math.first.q,w.newP[i].q);
    len=Length(w.phase.math.leftProjection.q);
    if(Float(len)<.0001f)w.phase.math.leftProjection.q=D_002A2DC0;else w.phase.math.leftProjection.q=Norm(w.phase.math.leftProjection.q,len);
    w.phase.math.rightProjection.q=MulX(w.phase.math.leftProjection.q,Dot(Sub(w.phase.math.second.q,w.newV[i].q),w.phase.math.leftProjection.q));
    w.phase.math.scalar.q=Bc(p->bend*Float(len));
    force=AddForces(force,w.phase.math.leftProjection.q,w.phase.math.scalar.q,w.phase.math.rightProjection.q,Bc(p->bendVelocity));
   }
   if(p->shape!=0.f||p->shapeVelocity!=0.f){
    float ratio=p->distances[i]/p->distances[last];
    w.phase.math.first.q=Lerp(w.newP[0].q,w.newP[last].q,ratio,&w.phase.math.scalar);
    w.phase.math.second.q=Lerp(w.newV[0].q,w.newV[last].q,ratio,&w.phase.math.scalar);
    w.phase.math.leftProjection.q=Sub(w.phase.math.first.q,w.newP[i].q);
    len=Length(w.phase.math.leftProjection.q);
    if(Float(len)<.0001f)w.phase.math.leftProjection.q=D_002A2DC0;else w.phase.math.leftProjection.q=Norm(w.phase.math.leftProjection.q,len);
    w.phase.math.rightProjection.q=MulX(w.phase.math.leftProjection.q,Dot(Sub(w.phase.math.second.q,w.newV[i].q),w.phase.math.leftProjection.q));
    w.phase.math.scalar.q=Bc(p->shape*(Float(len)-amplitude*(4.f*ratio)*(1.f-ratio)));
    force=AddForces(force,w.phase.math.leftProjection.q,w.phase.math.scalar.q,w.phase.math.rightProjection.q,Bc(p->shapeVelocity));
   }
   integrateDt=D_002C3668[pass]*D_002DDED0.dt;
   w.phase.math.first.q=Bc(integrateDt);
   w.oldV[i].q=AddScaled(w.oldV[i].q,force,w.phase.math.first.q);
   w.phase.math.first.q=Bc(integrateDt*.5f);
   w.oldP[i].q=AddScaled2(w.oldP[i].q,velocities[i].q,w.newV[i].q,w.phase.math.first.q);
   w.forces[i].q=force;
  }
 }
 }
 if(p->mode==3){
  int oldIndex=1,j;
  p->positions[0].q=w.worldStart.q;p->velocities[0].q=velocityStart;
  for(i=1;i<last;i++){
   float step=p->distances[i]-p->distances[i-1];
   if(Float(Length(Sub(w.worldEnd.q,p->positions[i-1].q)))<step)break;
   for(j=oldIndex;j<w.count;j++){
    float fraction;
    if(!func_0014C748(p->positions[i-1].q,w.oldP[j-1].q,w.oldP[j].q,1,&w.hit,step)){
     p->positions[i].q=w.oldP[j-1].q;fraction=0.f;
    }else{
     if(!(w.hit.fraction[1]<1.f))continue;
     p->positions[i].q=w.hit.point[1];fraction=w.hit.fraction[1];
    }
    p->path->values[i]=step;
    oldIndex=j;
    p->velocities[i].q=Lerp(w.oldV[j-1].q,w.oldV[j].q,fraction,&w.phase.math.first);
    break;
   }
  }
  p->positions[i].q=w.worldEnd.q;p->velocities[i].q=w.velocityEnd.q;
  w.count=i+1;
  p->distances[i]=p->distances[i-1]+Float(Length(Sub(p->positions[i].q,p->positions[i-1].q)));
  p->path->values[i]=p->distances[i];p->path->count=w.count;
 }else{
  p->positions[0].q=w.worldStart.q;p->velocities[0].q=velocityStart;
  p->positions[last].q=w.worldEnd.q;p->velocities[last].q=w.velocityEnd.q;
  func_001AE5A0(p->positions+1,w.oldP+1,interior*16);
  func_001AE5A0(p->velocities+1,w.oldV+1,interior*16);
 }
 {
  PATH *path=p->path;VTE *entry=&path->vt[31];
  M4 *world=entry->fn((PATH*)((char*)path+entry->delta));
  func_0011C318(&w.phase.inverse,world);
 }
 for(i=0;i<w.count;i++)p->path->points[i].q=Point(&w.phase.inverse,p->positions[i].q);
 if(p->mode!=3){
  p->path->values[0]=0.f;
  for(i=1;i<w.count;i++)p->path->values[i]=p->path->values[i-1]+Float(Length(Sub(p->path->points[i-1].q,p->path->points[i].q)));
 }
 func_001E6330(p->path);
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char spring_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(M4)==64 && sizeof(VTE)==8 && sizeof(HIT)==96 && sizeof(PHASE)==80 && sizeof(WORK)==0x14F0 && sizeof(CLOCK)==8 && OFF(OWNER,world)==0x40 && OFF(VTE,delta)==0x0 && OFF(VTE,fn)==0x4 && OFF(PATH,vt)==0xC && OFF(PATH,count)==0xE8 && OFF(PATH,values)==0xF0 && OFF(PATH,points)==0xF4 && OFF(P,acceleration)==0x0 && OFF(P,localStart)==0x20 && OFF(P,localEnd)==0x30 && OFF(P,start)==0x40 && OFF(P,end)==0x44 && OFF(P,path)==0x48 && OFF(P,mode)==0x4C && OFF(P,positions)==0x54 && OFF(P,velocities)==0x58 && OFF(P,distances)==0x5C && OFF(P,drag)==0x60 && OFF(P,stretch)==0x64 && OFF(P,stretchVelocity)==0x68 && OFF(P,bend)==0x6C && OFF(P,bendVelocity)==0x70 && OFF(P,shape)==0x74 && OFF(P,shapeVelocity)==0x78 && OFF(HIT,point)==0x0 && OFF(HIT,plane)==0x20 && OFF(HIT,fraction)==0x40 && OFF(HIT,enabled)==0x48 && OFF(HIT,surface)==0x4C && OFF(WORK,newP)==0x0 && OFF(WORK,newV)==0x400 && OFF(WORK,oldP)==0x800 && OFF(WORK,oldV)==0xC00 && OFF(WORK,forces)==0x1000 && OFF(WORK,phase)==0x1400 && OFF(WORK,hit)==0x1450 && OFF(WORK,count)==0x14B0 && OFF(WORK,worldStart)==0x14C0 && OFF(WORK,worldEnd)==0x14D0 && OFF(WORK,velocityEnd)==0x14E0 && OFF(CLOCK,time)==0x0 && OFF(CLOCK,dt)==0x4)?1:-1];
