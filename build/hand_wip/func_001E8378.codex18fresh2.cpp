
typedef int qword __attribute__((mode(TI)));
struct VEC {
 qword q;
 VEC(){}
 VEC(qword value):q(value){}
 operator qword()const{return q;}
};

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
extern "C"{
extern CLOCK D_002DDED0;
extern float D_002C3658[4],D_002C3668[4];
extern qword D_002A2DA0,D_002A2DC0;
extern qword func_0022D348(OWNER*,OWNER*,qword);
extern void func_001AE5A0(void*,const void*,unsigned int);
extern int func_0014C748(qword,qword,qword,int,HIT*,float);
extern M4*func_0011C318(M4*,M4*);
extern void func_001E6330(PATH*);
}
static inline VEC Read(const U*v){qword q;__asm__("lq %0,%1":"=r"(q):"m"(v->q));return q;}
static inline VEC FirstPoint(const M4*m,VEC vValue){qword v=vValue.q;register qword r __asm__("vf6");__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m->row[0]),"j"(m->row[1]),"j"(m->row[2]),"j"(m->row[3]),"j"(v));return r;}
static inline VEC Point(const M4*m,VEC vValue){qword v=vValue.q;qword r=m->row[0];__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m->row[1]),"j"(m->row[2]),"j"(m->row[3]),"j"(v));return r;}
static inline VEC Sub(VEC aValue,VEC bValue){qword a=aValue.q;qword b=bValue.q;qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline VEC Bc(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline float Float(VEC vValue){qword v=vValue.q;float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline VEC Sq(VEC vValue){qword v=vValue.q;qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(v));return r;}
static inline VEC Dot(VEC aValue,VEC bValue){qword a=aValue.q;qword b=bValue.q;qword r=a,one;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(r),"=&j"(one):"j"(b));return r;}
static inline VEC Length(VEC vValue){qword v=vValue.q;qword r=Sq(v);__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(r));return r;}
static inline VEC Norm(VEC vValue,VEC lenValue){qword v=vValue.q;qword len=lenValue.q;qword r;__asm__ volatile("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(v),"j"(len));return r;}
static inline VEC MulX(VEC aValue,VEC bValue){qword a=aValue.q;qword b=bValue.q;qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline VEC AddScaled(VEC aValue,VEC bValue,VEC sValue){qword a=aValue.q;qword b=bValue.q;qword s=sValue.q;qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline VEC AddScaled2(VEC aValue,VEC bValue,VEC cValue,VEC sValue){qword a=aValue.q;qword b=bValue.q;qword c=cValue.q;qword s=sValue.q;qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(b),"j"(c),"j"(s));return r;}
static inline VEC AddForces(VEC aValue,VEC bValue,VEC sValue,VEC cValue,VEC tValue){qword a=aValue.q;qword b=bValue.q;qword s=sValue.q;qword c=cValue.q;qword t=tValue.q;qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(a),"j"(b),"j"(s),"j"(c),"j"(t));return r;}
static inline void Publish(U*home,VEC valueValue){qword value=valueValue.q;
 __asm__ volatile("sqc2 %1,%0":"=m"(home->q):"j"(value));
}
static inline VEC Lerp(VEC aValue,VEC bValue,float fraction,U*scalar){qword a=aValue.q;qword b=bValue.q;
 qword r,low,high;
 low=Bc(1.f-fraction);
 Publish(scalar,low);
 high=Bc(fraction);
 Publish(scalar,high);
 __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x"
  :"=j"(r):"j"(a),"j"(b),"j"(low),"j"(high));
 return r;
}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float SqrtF(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
static inline VEC PublishedScalar(U*home,float scalar){
 qword value=Bc(scalar);
 Publish(home,value);
 return value;
}
static inline VEC LerpValue(VEC aValue,VEC bValue,float fraction){qword a=aValue.q;qword b=bValue.q;
 qword r,low=Bc(1.f-fraction),high=Bc(fraction);
 __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x"
  :"=j"(r):"j"(a),"j"(b),"j"(low),"j"(high));
 return r;
}
extern "C" void func_001E8378(P*input){
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
 register qword anchorStart __asm__("vf12")=w.worldStart.q;
 register qword anchorEnd __asm__("vf14")=w.worldEnd.q;
 register qword anchorVelocityStart __asm__("vf13")=velocityStart;
 register qword anchorVelocityEnd __asm__("vf11")=w.velocityEnd.q;
 for(pass=0;pass<4;pass++){
  float weight=D_002C3658[pass];
  float predictDt=weight*D_002DDED0.dt;
  float amplitude,rest;
  w.newP[0].q=Lerp(positions[0].q,anchorStart,weight,&w.phase.math.first);
  w.newV[0].q=Lerp(velocities[0].q,anchorVelocityStart,weight,&w.phase.math.first);
  w.newP[last].q=Lerp(positions[last].q,anchorEnd,weight,&w.phase.math.first);
  w.newV[last].q=Lerp(velocities[last].q,anchorVelocityEnd,weight,&w.phase.math.first);
  if(last>1){
   char *forceRow=(char*)&w+0x1010;
   U *oldVelocity=p->velocities+1,*oldPosition=p->positions+1;
   int remaining=last-1;
   do {
    VEC velocity;
    w.phase.math.first.q=Bc(predictDt);
    velocity=AddScaled(oldVelocity->q,((U*)forceRow)->q,w.phase.math.first.q);
    ((U*)(forceRow-0xC00))->q=velocity;
    w.phase.math.first.q=Bc(predictDt*.5f);
    ((U*)(forceRow-0x1000))->q=AddScaled2(oldPosition->q,oldVelocity->q,velocity,w.phase.math.first.q);
    forceRow+=16;++oldVelocity;++oldPosition;
   }while(--remaining);
  }
  rest=p->distances[last];
  amplitude=(.75f-.25f/interior)*SqrtF(Max(rest*rest-Float(Sq(Sub(w.newP[0].q,w.newP[last].q))),0.f));
  {
  char *velocityRow=(char*)&w+0x410;
  for(i=1;i<last;i++,velocityRow+=16){
   VEC force,len;
   float integrateDt;
   w.phase.math.first.q=Bc(-p->drag);
   force=AddScaled(p->acceleration,((U*)(velocityRow))->q,w.phase.math.first.q);
   if(p->stretch!=0.f||p->stretchVelocity!=0.f){
    VEC leftLen,rightLen;
    float leftRest,rightRest,leftScale,rightScale;
    w.phase.math.first.q=Sub(((U*)(velocityRow-0x410))->q,((U*)(velocityRow-0x400))->q);
    leftLen=Length(w.phase.math.first.q);
    w.phase.math.second.q=Sub(((U*)(velocityRow-0x3F0))->q,((U*)(velocityRow-0x400))->q);
    if(Float(leftLen)<.0001f)w.phase.math.first.q=D_002A2DA0;else w.phase.math.first.q=Norm(w.phase.math.first.q,leftLen);
    rightLen=Length(w.phase.math.second.q);
    if(Float(rightLen)<.0001f)w.phase.math.second.q=D_002A2DA0;else w.phase.math.second.q=Norm(w.phase.math.second.q,rightLen);
    leftRest=p->distances[i]-p->distances[i-1];
    rightRest=p->distances[i+1]-p->distances[i];
    w.phase.math.leftProjection.q=MulX(w.phase.math.first.q,Dot(Sub(((U*)(velocityRow-0x10))->q,((U*)(velocityRow))->q),w.phase.math.first.q));
    leftScale=p->stretch*(Float(leftLen)-leftRest);
    rightScale=p->stretch*(Float(rightLen)-rightRest);
    w.phase.math.rightProjection.q=MulX(w.phase.math.second.q,Dot(Sub(((U*)(velocityRow+0x10))->q,((U*)(velocityRow))->q),w.phase.math.second.q));
    {
     VEC leftWeight=PublishedScalar(&w.phase.math.scalar,leftScale);
     VEC damping=PublishedScalar(&w.phase.math.scalar,p->stretchVelocity);
     VEC rightWeight=Bc(rightScale);
     force=AddForces(force,w.phase.math.first.q,leftWeight,w.phase.math.leftProjection.q,damping);
     force=AddForces(force,w.phase.math.second.q,rightWeight,w.phase.math.rightProjection.q,damping);
    }
   }
   if(p->bend!=0.f||p->bendVelocity!=0.f){
    float ratio=(p->distances[i]-p->distances[i-1])/(p->distances[i+1]-p->distances[i-1]);
    w.phase.math.first.q=Lerp(((U*)(velocityRow-0x410))->q,((U*)(velocityRow-0x3F0))->q,ratio,&w.phase.math.scalar);
    w.phase.math.second.q=Lerp(((U*)(velocityRow-0x10))->q,((U*)(velocityRow+0x10))->q,ratio,&w.phase.math.scalar);
    w.phase.math.leftProjection.q=Sub(w.phase.math.first.q,((U*)(velocityRow-0x400))->q);
    len=Length(w.phase.math.leftProjection.q);
    if(Float(len)<.0001f)w.phase.math.leftProjection.q=D_002A2DC0;else w.phase.math.leftProjection.q=Norm(w.phase.math.leftProjection.q,len);
    w.phase.math.rightProjection.q=MulX(w.phase.math.leftProjection.q,Dot(Sub(w.phase.math.second.q,((U*)(velocityRow))->q),w.phase.math.leftProjection.q));
    {
     VEC stiffness=PublishedScalar(&w.phase.math.scalar,p->bend*Float(len));
     VEC damping=PublishedScalar(&w.phase.math.scalar,p->bendVelocity);
     force=AddForces(force,w.phase.math.leftProjection.q,stiffness,w.phase.math.rightProjection.q,damping);
    }
   }
   if(p->shape!=0.f||p->shapeVelocity!=0.f){
    float ratio=p->distances[i]/p->distances[last];
    w.phase.math.first.q=Lerp(w.newP[0].q,w.newP[last].q,ratio,&w.phase.math.scalar);
    w.phase.math.second.q=LerpValue(w.newV[0].q,w.newV[last].q,ratio);
    w.phase.math.leftProjection.q=Sub(w.phase.math.first.q,((U*)(velocityRow-0x400))->q);
    len=Length(w.phase.math.leftProjection.q);
    if(Float(len)<.0001f)w.phase.math.leftProjection.q=D_002A2DC0;else w.phase.math.leftProjection.q=Norm(w.phase.math.leftProjection.q,len);
    w.phase.math.rightProjection.q=MulX(w.phase.math.leftProjection.q,Dot(Sub(w.phase.math.second.q,((U*)(velocityRow))->q),w.phase.math.leftProjection.q));
    {
     VEC stiffness=PublishedScalar(&w.phase.math.scalar,p->shape*(Float(len)-amplitude*(4.f*ratio)*(1.f-ratio)));
     VEC damping=PublishedScalar(&w.phase.math.scalar,p->shapeVelocity);
     force=AddForces(force,w.phase.math.leftProjection.q,stiffness,w.phase.math.rightProjection.q,damping);
    }
   }
   integrateDt=D_002C3668[pass]*D_002DDED0.dt;
   w.phase.math.first.q=Bc(integrateDt);
   ((U*)(velocityRow+0x800))->q=AddScaled(((U*)(velocityRow+0x800))->q,force,w.phase.math.first.q);
   w.phase.math.first.q=Bc(integrateDt*.5f);
   ((U*)(velocityRow+0x400))->q=AddScaled2(((U*)(velocityRow+0x400))->q,velocities[i].q,((U*)(velocityRow))->q,w.phase.math.first.q);
   ((U*)(velocityRow+0xC00))->q=force;
  }
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

typedef char VectorValue_Size[(sizeof(VEC)==16)?1:-1];
typedef char VectorValue_q_Offset[((unsigned)&((VEC*)0)->q==0)?1:-1];
