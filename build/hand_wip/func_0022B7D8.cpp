// Write per-vertex weights and shader coordinates for linked warp bindings.
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
static inline qword PointPosition(const M4 &m,qword v){qword r=m.r[3].q;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddaz.xyz ACC,%3,%4z\n\tvmaddw.xyz %0,%0,$vf0w":"+j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Clamp(float f,float lo,float hi){if(f<lo)f=lo;else if(hi<f)f=hi;return f;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword LoadVF(const V &v){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword SumXYZ(qword v){qword l,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(l),"=&j"(one):"j"(v));return l;}
static inline qword LengthV(qword v){qword l=SumXYZ(v);__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(l));return l;}
static inline float X(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline float Length(qword v){return X(LengthV(v));}
static inline float Dot(qword a,qword b){qword l,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(l),"=&j"(one):"j"(a),"j"(b));return X(l);}
static inline qword Unit(qword v){qword length=LengthV(v),r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"0"(length));return r;}
static inline qword Point(const M4 &m,qword v){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(v):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q));return v;}
static inline void Identity(M4 &m){func_002333B4(&m,0,0x40);m.r[1].f[1]=m.r[2].f[2]=m.r[3].f[3]=m.r[0].f[0]=1.0f;}
extern "C" void func_0022B7D8(WR *owner){
 WORK w;w.owner=owner;
 for(WARP *warp=w.owner->warps;warp;warp=warp->next){
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
   default:axis=0;break;
   }
   if(axis){w.phase.before.point.q=Scalar((warp->minimum+warp->maximum)*0.5f);w.center.q=Scale(axis->q,w.phase.before.point.q);}
   else w.center.q=D_002A2DD0.q;
   func_0011C318(&w.phase.before.inverse,&w.matrix);w.phase.before.inverseCopy=w.phase.before.inverse;
   w.center.q=Point(w.phase.before.inverseCopy,w.center.q);
   if(warp->binding->relative){func_0011C168(&w.phase.before.inverse,&warp->matrix,warp->binding->relative);w.matrix=w.phase.before.inverse;}
  }
  for(BLOCK *block=warp->blocks;block;block=block->next){
   func_001AE5A0(w.vertices,block->vertices,(uint)block->count*0x10);
   V *last=w.vertices+block->count,*vertex=w.vertices;
   float *weight=w.weights;
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
    float *output=block->outputs[entry->index];
    V *vertex=w.vertices;float *weight=w.weights;
    for(;vertex<last;vertex++,weight++,output+=4){
     w.phase.after.product.r[0].q=PointPosition(w.phase.after.source,vertex->q);
     switch(entry->kind){
     case 0:{
      int column=entry->column;
      float angle=Dot(w.phase.after.product.r[0].q,Unit(entry->axis.q))*(entry->spatialFrequency*6.2831855f);
      func_0011D608(func_0011CF60(angle),&w.sine,&w.cosine);
      output[column]=w.cosine* *weight;output[column+1]=w.sine* *weight;
      break;
     }
     case 1:{
      w.phase.before.inverse.r[0].q=Sub(w.phase.after.product.r[0].q,w.worldCenter.q);
      output[0]=*weight*w.phase.before.inverse.r[0].f[0];
      output[1]=*weight*w.phase.before.inverse.r[0].f[1];
      output[2]=*weight*w.phase.before.inverse.r[0].f[2];
      output[3]=1.0f;
      break;
     }
     }
    }
   }
  }
 }
 w.owner->source=0;
}
