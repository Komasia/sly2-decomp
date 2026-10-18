// Complete linked warp weighting and shader-coordinate update WIP.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union V {qword q;float f[4];};
struct M4 {V r[4];};
struct RANGE {float lo,hi;};
struct O;
struct FRAME {char pad[0x40];M4 world;};
struct BINDING {void *data;FRAME *source;M4 *relative;};
struct BLOCK {int count;V *vertices;float *outputs[4];BLOCK *next;};
struct WARP {O *owner;BINDING *binding;char pad8[0x28];int kind;float minimum,minimumWeight,maximum,maximumWeight;char pad44[0xC];M4 matrix;BLOCK *blocks;char pad94[0xC];WARP *next;};
struct WRE {int kind,index;char pad8[8];V axis;char pad20[0x40];int column;float spatialFrequency,frequency,phase;char pad70[0x60];};
struct WR {char pad[0x54];int count;char pad58[8];WRE entries[8];char pad6E0[0x210];WARP *warps;char pad8F4[8];void *source;};
union PHASE {struct {V point;M4 inverseCopy,inverse;} before;struct {M4 source,product;} after;};
struct WORK {M4 matrix;V coefficients;RANGE limits;PHASE phase;V vertices[256];float weights[256];float sine,cosine;WR *owner;V center,worldCenter;};
extern V D_002A2DA0,D_002A2DB0,D_002A2DC0,D_002A2DD0;
extern "C" {
void *func_002333B4(void *,int,int);
M4 *func_0011C318(M4 *,const M4 *);
M4 *func_0011C168(M4 *,const M4 *,const M4 *);
void func_001AE5A0(void *,const void *,uint);
qword func_001A6F00(O *,O *,qword);
float func_0011CF60(float);
void func_0011D608(float,float *,float *);
}
static inline qword PointDirection(const M4 &m,qword v){qword r=m.r[0].q;__asm__("vmulax.xyz ACC,%0,%1x\n\tvmadday.xyz ACC,%2,%1y\n\tvmaddaz.xyz ACC,%3,%1z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(v),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q));return r;}
static inline qword PointPosition(const M4 &m,qword v){register qword r asm("vf1");r=m.r[3].q;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddaz.xyz ACC,%3,%4z\n\tvmaddw.xyz %0,%0,$vf0w":"+j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Clamp(float f,float lo,float hi){if(f<lo)f=lo;else if(hi<f)f=hi;return f;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword LoadVF(const V &v){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword SumXYZ(qword v){qword l,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(l),"=&j"(one):"j"(v));return l;}
static inline qword LengthV(qword v){qword l=SumXYZ(v);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(l));return l;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline float Length(qword v){return X(LengthV(v));}
static inline float Dot(qword a,qword b){qword l,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(l),"=&j"(one):"j"(a),"j"(b));return X(l);}
static inline void Identity(M4 &m){func_002333B4(&m,0,0x40);m.r[1].f[1]=m.r[2].f[2]=m.r[3].f[3]=m.r[0].f[0]=1.0f;}
static inline float BendDelta(V &home,qword point,qword center){
 qword delta;float one;
 asm("vsub.xyzw %0,%3,%4\n\t .set noat\n\tlui $1,0x3F80\n\tmtc1 $1,%1\n\t.set at\n\tsqc2 %0,%2":"=&j"(delta),"=f"(one),"=m"(home):"j"(point),"j"(center):"$1");
 return one;
}
static inline qword UnitAndSpatialFrequency(const WRE &entry,float &gain){
 register qword result asm("vf1"),axis asm("vf2"),one asm("vf3");
 register float constant asm("$f1"),frequency asm("$f0");
 asm("lqc2 %1,%5\n\tvmul.xyz %0,%1,%1\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%2,%0z\n\t.set noat\n\tlui $1,0x40C9\n\tori $1,$1,0x0FDB\n\tmtc1 $1,%4\n\t.set at\n\tlwc1 %3,%6\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tvdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q\n\tmul.s %3,%3,%4":"=&j"(result),"=&j"(axis),"=&j"(one),"=f"(frequency),"=f"(constant):"m"(entry.axis),"m"(entry.spatialFrequency):"$1");
 gain=frequency;return result;
}
static inline int PointHomeAndKind(V &home,qword point,const int &kind,qword &copy){
 register int value asm("$3");register qword snapshot asm("vf4");
 asm("lw %0,%3\n\tvmove.xyzw %1,%4\n\tsqc2 %1,%2":"=&r"(value),"=j"(snapshot),"=m"(home):"m"(kind),"j"(point));
 copy=snapshot;return value;
}
static inline BLOCK *OutputSlot(BLOCK *block,int index){
 register int address asm("$2");address=index;
 asm("sll %0,%0,2\n\taddu %0,%1,%0":"+&r"(address):"r"(block));return (BLOCK *)address;
}
static inline WARP *FirstWarp(const WR &owner){
 register WARP *warp asm("$20");asm("lw %0,%1":"=r"(warp):"m"(owner.warps));return warp;
}
static inline void InverseCenter(WORK &w){
 qword a=LoadVF(w.phase.before.inverse.r[0]),b=LoadVF(w.phase.before.inverse.r[1]);
 qword c=LoadVF(w.phase.before.inverse.r[2]),d=LoadVF(w.phase.before.inverse.r[3]);
 qword center=LoadVF(w.center);
 asm("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(center):"j"(a),"j"(b),"j"(c),"j"(d));
 w.phase.before.inverseCopy.r[0].q=a;w.center.q=center;
 w.phase.before.inverseCopy.r[1].q=b;w.phase.before.inverseCopy.r[2].q=c;w.phase.before.inverseCopy.r[3].q=d;
}
extern "C" void func_0022B7D8(WR *owner){
 WORK w;w.owner=owner;V *vertex;float *weight;
 for(WARP *warp=FirstWarp(*w.owner);warp;warp=warp->next){
  if(warp->kind==-1){Identity(w.matrix);w.center.q=D_002A2DD0.q;}
  else{
   w.matrix=warp->matrix;
   w.limits.lo=Min(warp->minimumWeight,warp->maximumWeight);
   w.limits.hi=Max(warp->minimumWeight,warp->maximumWeight);
   w.coefficients.f[1]=(warp->minimumWeight-warp->maximumWeight)/(warp->minimum-warp->maximum);
   w.coefficients.f[0]=warp->minimumWeight-w.coefficients.f[1]*warp->minimum;
   w.coefficients.f[2]=0.0f;
   const V *axis;
   switch(warp->kind){
   case 4:axis=&D_002A2DA0;break;
   case 5:axis=&D_002A2DB0;break;
   case 6:axis=&D_002A2DC0;break;
   default:w.center.q=D_002A2DD0.q;goto CenterReady;
   }
   {qword direction=LoadVF(*axis),midpoint=Scalar((warp->minimum+warp->maximum)*0.5f);
    qword center=Scale(direction,midpoint);w.phase.before.point.q=midpoint;w.center.q=center;}
CenterReady:
   func_0011C318(&w.phase.before.inverse,&w.matrix);InverseCenter(w);
   if(warp->binding->relative){func_0011C168(&w.phase.before.inverse,&warp->matrix,warp->binding->relative);w.matrix=w.phase.before.inverse;}
  }
  for(BLOCK *block=warp->blocks;block;block=block->next){
   func_001AE5A0(w.vertices,block->vertices,(uint)block->count*0x10);
   V *last=w.vertices+block->count;vertex=w.vertices;
   weight=w.weights;
   for(;vertex<last;vertex++,weight++){
    w.phase.before.point.q=PointDirection(w.matrix,vertex->q);
    float value;
    switch(warp->kind){
    case -1:*weight=1.0f;continue;
    case 0:value=Length(w.phase.before.point.q);break;
    case 1:w.phase.before.point.f[2]=0.0f;value=Length(LoadVF(w.phase.before.point));break;
    case 2:w.phase.before.point.f[1]=0.0f;value=Length(LoadVF(w.phase.before.point));break;
    case 3:w.phase.before.point.f[0]=0.0f;value=Length(LoadVF(w.phase.before.point));break;
    case 4:value=w.phase.before.point.f[0];break;
    case 5:value=w.phase.before.point.f[1];break;
    case 6:value=w.phase.before.point.f[2];break;
    default:*weight=1.0f;continue;
    }
    *weight=Clamp(w.coefficients.f[0]+value*(w.coefficients.f[1]+value*w.coefficients.f[2]),w.limits.lo,w.limits.hi);
   }
   w.phase.after.source=warp->binding->source->world;
   if(warp->binding->relative){func_0011C168(&w.phase.after.product,&w.phase.after.source,warp->binding->relative);w.phase.after.source=w.phase.after.product;}
   w.worldCenter.q=func_001A6F00(warp->owner,0,w.center.q);
   for(int i=0;i<w.owner->count;i++){
    WRE *entry=&w.owner->entries[i];
    float *output=OutputSlot(block,entry->index)->outputs[0];
    vertex=w.vertices;weight=w.weights;
    for(;vertex<last;vertex++,weight++,output+=4){
     qword point=PointPosition(w.phase.after.source,vertex->q),pointCopy;
     int kind=PointHomeAndKind(w.phase.after.product.r[0],point,entry->kind,pointCopy);
     switch(kind){
     case 0:{
      int column=entry->column;
      float frequency;qword axis=UnitAndSpatialFrequency(*entry,frequency);
      float angle=Dot(pointCopy,axis)*frequency;
      func_0011D608(func_0011CF60(angle),&w.sine,&w.cosine);
      output[column]=w.cosine* *weight;output[column+1]=w.sine* *weight;
      break;
     }
     case 1:{
      float one=BendDelta(w.phase.before.inverse.r[0],point,w.worldCenter.q);
      output[0]=*weight*w.phase.before.inverse.r[0].f[0];
      output[1]=*weight*w.phase.before.inverse.r[0].f[1];
      output[2]=*weight*w.phase.before.inverse.r[0].f[2];
      output[3]=one;
      break;
     }
     }
    }
   }
  }
 }
 w.owner->source=0;
}
