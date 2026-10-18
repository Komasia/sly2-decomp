// Update the linked geometry and material display for the actor probe.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned char uchar;
union V {qword q;float f[4];};
union F32 {float f;uint bits;};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
struct POLY {float a,b,c;};
struct RANGE {float lo,hi;};
struct TIMING {float first,second,effect;POLY primary;unsigned field18;POLY secondary;};
struct RGBA_RAW {uchar r,g,b,a;};
union LANE {qword q;uint word;RGBA_RAW color;};
union PHASE {M3 copy;LANE colors[3];};
struct WORK {LANE scalar;M4 result;PHASE phase;M3 scaled;float distance;V source,end,extended,effect;};
struct O;
struct RESOURCE {char pad[0x6C];int id;};
struct LINK {char pad[0x7C];RESOURCE *resource;};
struct CONDITION;
struct DISPLAY {char pad[0xA0];float offset;};
struct O {char pad[0x150];int mode;char pad154[0xC];LINK *attachment;int field164;O *source;DISPLAY *first,*segment,*second;int frame,collided;F32 height;int cue;CONDITION *condition;};
struct WORLD {char pad[0x3B0C];int state;char pad3B10[0xC40];float timeA,timeB;char pad4758[0xC];int current,required;};
struct CAMERA {char pad[0x90];V position;};
struct MATERIAL;
extern WORLD D_003DD490;
extern CAMERA D_002DDF40;
extern V D_002A2DC0;
extern float D_002DDED0,D_002C4498,D_002C449C,D_002C44D8;
extern TIMING D_002C4494;
extern POLY D_002C44A0,D_002C44B0,D_002C44C0;
extern RANGE D_002BBB60,D_002C44D0;
extern "C" {
void func_001F3C70(O *);
int func_001DAEA8(int);
int func_00163400(CONDITION *);
void func_0022A220(O *);
qword func_001A62E8(O *);
void func_0011EE08(qword,qword,qword,qword *,float *,float *);
M4 *func_001A6318(DISPLAY *);
void *func_0023320C(void *,const void *,int);
qword *func_00256D18(qword *,qword);
void func_001A5EE8(DISPLAY *,M4 *,float,float);
void func_001A5FB8(DISPLAY *,qword,qword,float,float);
MATERIAL *func_0013E368(WORLD *,int);
void func_001CD780(qword,MATERIAL *,const RGBA_RAW *,const RGBA_RAW *,float);
}
static inline void RecordScalar(LANE &home,qword value){asm("sqc2 %1,%0":"=m"(home.q):"j"(value));}
static inline qword LoadVF(const V &v){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(v));return q;}
static inline qword ToCPU(qword q){qword r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(q));return r;}
static inline void StoreCPU(V &v,qword q){__asm__("sq %1,%0":"=m"(v):"r"(q));}
static inline qword LoadUp(){qword q;__asm__("lqc2 %0,0(%1)":"=j"(q):"r"(&D_002A2DC0),"m"(D_002A2DC0));return q;}
static inline qword LoadUpPort(){register const V *address asm("$5")=&D_002A2DC0;qword q;asm("lqc2 %0,0(%1)":"=j"(q):"r"(address),"m"(*address));return q;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Poly(const POLY &p,float f){return p.a+f*(p.b+f*p.c);}
static inline float Clamp(float f,float lo,float hi){float r;if(f<lo)r=lo;else if(hi<f)r=hi;else r=f;return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarWord(uint f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword AddScaled(qword old,qword v,qword k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(old):"j"(v),"j"(k));return old;}
static inline qword AddScaledCoefficient(qword old,qword v,qword k){__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%0x":"+j"(k):"j"(old),"j"(v));return k;}
static inline void ScaleRows(M3 &d,const M3 &s,qword scalar){register qword a asm("vf1"),b asm("vf2"),k asm("vf3")=scalar;asm("lqc2 %0,%1":"=j"(a):"m"(s.r[0]));asm("vmulx.xyzw %0,%0,%1x":"+j"(a):"j"(k));asm("sqc2 %1,%0":"=m"(d.r[0]):"j"(a));asm("lqc2 %0,%1":"=j"(b):"m"(s.r[1]));asm("vmulx.xyzw %0,%0,%1x":"+j"(b):"j"(k));asm("sqc2 %1,%0":"=m"(d.r[1]):"j"(b));asm("lqc2 %0,%1":"=j"(a):"m"(s.r[2]));asm("vmulx.xyzw %0,%1,%0x":"+j"(k):"j"(a));d.r[2].q=k;}
static inline void SetMatrix(M4 &m,const M3 &basis,qword position){M4 *pm=&m;func_00256D18(&m.position.q,position);qword x=basis.r[0].q,y=basis.r[1].q;StoreCPU(pm->basis.r[0],x);asm("sq %1,16(%2)":"=m"(pm->basis.r[1]):"r"(y),"r"(pm));qword z=basis.r[2].q;asm("sq %1,32(%2)":"=m"(pm->basis.r[2]):"r"(z),"r"(pm));m.basis.r[0].f[3]=m.basis.r[1].f[3]=m.basis.r[2].f[3]=0.0f;pm->position.f[3]=1.0f;}
static inline qword ExtendEndpoint(const V &end,float scale,LANE &home){register qword up asm("vf2"),old asm("vf3"),scalar asm("vf1");asm("lqc2 %0,0(%1)":"=j"(up):"r"(&D_002A2DC0),"m"(D_002A2DC0));asm("lqc2 %0,%1":"=j"(old):"m"(end));asm("qmtc2.ni %1,%0":"=j"(scalar):"r"(scale));asm("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(old):"j"(up),"j"(scalar));RecordScalar(home,scalar);return old;}

static inline float PrimaryResponse(unsigned &worldPage,unsigned &clockPage,unsigned &rangePage,float &lower,RANGE *&bounds){
 register unsigned world asm("$19"),clock asm("$6"),rangeHigh asm("$5");
 register float value asm("$f3"),low asm("$f0");register RANGE *range asm("$2");
 asm("lui $2,%%hi(%6)\n\tlui $3,%%hi(%8)\n\tdaddu %0,$2,$zero\n\tlui $4,%%hi(%8+4)\n\taddiu $2,$2,%%lo(%6)\n\tlwc1 $f3,%%lo(%8)($3)\n\tlwc1 $f2,%%lo(%8+4)($4)\n\tlui $3,%%hi(%7)\n\tlwc1 $f4,0x4754($2)\n\tlui $4,%%hi(%8+12)\n\tlwc1 $f0,0x4750($2)\n\tdaddu %1,$3,$zero\n\tadd.s $f4,$f4,$f2\n\tlwc1 $f1,%%lo(%7)($3)\n\tadd.s $f0,$f0,$f3\n\taddiu $3,$4,%%lo(%8+12)\n\tlwc1 $f3,8($3)\n\tlui $2,%%hi(%9)\n\tlwc1 $f2,4($3)\n\tdaddu %2,$2,$zero\n\tmax.s $f4,$f4,$f0\n\tlwc1 $f5,%%lo(%8+12)($4)\n\tsub.s $f1,$f1,$f4\n\tlwc1 %4,%%lo(%9)($2)\n\taddiu %5,$2,%%lo(%9)\n\tmul.s $f3,$f1,$f3\n\tadd.s $f2,$f2,$f3\n\tmul.s $f1,$f1,$f2\n\tadd.s %3,$f5,$f1"
 :"=r"(world),"=r"(clock),"=r"(rangeHigh),"=f"(value),"=f"(low),"=r"(range):"i"(&D_003DD490),"i"(&D_002DDED0),"i"(&D_002C4494),"i"(&D_002BBB60):"$3","$4","$f1","$f2","$f4","$f5","memory");
 worldPage=world;clockPage=clock;rangePage=rangeHigh;lower=low;bounds=range;return value;
}
static inline float FirstClamp(float input,float lower,float upper){register float value asm("$f3")=input,low asm("$f0")=lower,high asm("$f4")=upper,result asm("$f12");if(value<low)result=low;else if(high<value)result=high;else result=value;return result;}
static inline float SecondaryResponse(unsigned worldPage,unsigned clockPage,unsigned rangePage,float first,float &retained,float &lower,RANGE *&bounds){
 register float value asm("$f3"),low asm("$f4"),keep asm("$f21");register RANGE *range asm("$3");
 asm("addiu $2,%4,-0x2b70\n\tlui $3,%%hi(%8+8)\n\tlwc1 $f3,0x4750($2)\n\tlui $4,%%hi(%8+28)\n\tlwc1 $f2,%%lo(%8+8)($3)\n\taddiu $2,$4,%%lo(%8+28)\n\tlwc1 $f0,-0x2130(%5)\n\taddiu %2,%6,-0x44a0\n\tadd.s $f4,$f3,$f2\n\tlwc1 $f1,8($2)\n\tlwc1 $f2,4($2)\n\tmov.s %3,%7\n\tlwc1 $f3,%%lo(%8+28)($4)\n\tsub.s $f0,$f0,$f4\n\tlwc1 %1,-0x44a0(%6)\n\tmul.s $f1,$f0,$f1\n\tadd.s $f2,$f2,$f1\n\tmul.s $f0,$f0,$f2\n\tadd.s %0,$f3,$f0"
 :"=f"(value),"=f"(low),"=&r"(range),"=f"(keep):"r"(worldPage),"r"(clockPage),"r"(rangePage),"f"(first),"i"(&D_002C4494):"$2","$4","$f0","$f1","$f2","memory");
 retained=keep;lower=low;bounds=range;return value;
}
static inline float SecondClamp(float input,float lower,float upper){register float value asm("$f3")=input,low asm("$f4")=lower,high asm("$f5")=upper,result asm("$f0");if(value<low)result=low;else if(high<value)result=high;else result=value;return result;}
static inline WORLD *WorldAtPage(unsigned page){WORLD *world;asm("addiu %0,%1,-0x2b70":"=r"(world):"r"(page));return world;}

extern "C" void func_0022A908(O *owner){
 WORK w;
 func_001F3C70(owner);
 unsigned worldPage,clockPage,rangePage;float lower;RANGE *bounds;
 float response=PrimaryResponse(worldPage,clockPage,rangePage,lower,bounds);
 float mainWeight=FirstClamp(response,lower,bounds->hi);
 float firstWeight=mainWeight;
 response=SecondaryResponse(worldPage,clockPage,rangePage,firstWeight,mainWeight,lower,bounds);
 float effectWeight=SecondClamp(response,lower,bounds->hi);
 switch(owner->mode){
 case 0:if(WorldAtPage(worldPage)->state)mainWeight=effectWeight=0.0f;break;
 case 2:if(WorldAtPage(worldPage)->current<WorldAtPage(worldPage)->required||WorldAtPage(worldPage)->state||(owner->cue!=-1&&func_001DAEA8(owner->cue))||(owner->condition&&!func_00163400(owner->condition)))mainWeight=effectWeight=0.0f;break;
 case 1:if(!WorldAtPage(worldPage)->state)mainWeight=effectWeight=0.0f;break;
 }
 if(mainWeight==0.0f)return;
 func_0022A220(owner);
 qword camera=D_002DDF40.position.q;
 StoreCPU(w.source,func_001A62E8(owner->source));
 {qword up=LoadUp(),scalar=ScalarWord(owner->height.bits);qword old=LoadVF(w.source);w.end.q=AddScaled(old,up,scalar);RecordScalar(w.scalar,scalar);}
 func_0011EE08(camera,w.source.q,w.end.q,0,0,&w.distance);
 float scale=Clamp(Poly(D_002C44C0,w.distance),D_002C44D0.lo,D_002C44D0.hi);
 w.extended.q=ExtendEndpoint(w.end,scale*D_002C44D8,w.scalar);
 if(owner->first){
  M4 *original=func_001A6318(owner->first);qword scalar=Scalar(scale);RecordScalar(w.scalar,scalar);
  ScaleRows(w.scaled,original->basis,scalar);func_0023320C(&w.phase.copy,&w.scaled,0x30);
  SetMatrix(w.result,w.phase.copy,w.extended.q);
  func_001A5EE8(owner->first,&w.result,mainWeight,mainWeight);
 }
 if(owner->segment)func_001A5FB8(owner->segment,w.source.q,w.extended.q,scale,mainWeight);
 if(owner->second){
  M4 *original=func_001A6318(owner->second);qword scalar=Scalar(scale);RecordScalar(w.scalar,scalar);
  ScaleRows(w.scaled,original->basis,scalar);func_0023320C(&w.phase.copy,&w.scaled,0x30);
  SetMatrix(w.result,w.phase.copy,w.source.q);
  func_001A5EE8(owner->second,&w.result,mainWeight,mainWeight);
 }
 float offset=0.0f;
 if(0.0f<effectWeight&&owner->attachment&&owner->attachment->resource&&owner->attachment->resource->id!=-1){
  if(owner->first)offset=scale*owner->first->offset;
  qword scalar=Scalar(offset);RecordScalar(w.scalar,scalar);
  qword effect=AddScaledCoefficient(LoadVF(w.extended),LoadUpPort(),scalar);
  w.scalar.word=0x80603030;w.phase.colors[0].word=0xFFC0C0C0;
  w.scalar.color.a=(uchar)(int)(effectWeight*w.scalar.color.a);
  w.phase.colors[0].color.a=(uchar)(int)(effectWeight*w.phase.colors[0].color.a);
  RGBA_RAW *first=&w.phase.colors[1].color,*second=&w.phase.colors[2].color;
  *first=w.scalar.color;*second=w.phase.colors[0].color;
  w.effect.q=effect;
  MATERIAL *material=func_0013E368(WorldAtPage(worldPage),owner->attachment->resource->id);
  func_001CD780(ToCPU(LoadVF(w.effect)),material,first,second,scale);
 }
}
