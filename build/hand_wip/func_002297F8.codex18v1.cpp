// Complete contact force, friction, orientation and water update WIP.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct M3 {qword r[3];};
struct M4 {M3 basis;qword position;};
struct COEF {float f[3];};
struct O;
struct VE {short delta,pad;qword (*get)(void *);};
struct NODE {char pad[0x98];short kind;};
struct CONSTRAINT {qword direction;int kind;};
struct PHYS {char pad[0x80];V direction;char pad90[0x20];CONSTRAINT constraint;float mass,spring,friction;};
struct STATE {V minimum,maximum;};
struct EMITTER;
struct WATER;
struct O {char pad[0xC];VE *vt;char pad10[0x48];NODE *body,*rotation,*motion;char pad64[0x84];PHYS *physics;STATE *state;char padF0[0x84];EMITTER *emitter;};
union PHASE {V vectors[3];M3 basis;};
union AXIS {COEF coefficients;V vector;};
struct WORK {V point,normal,velocity;PHASE phase;AXIS axis;V angularNormal,angularTangent,scalar;float angle;V linear,angular;};
extern qword D_002A2DD0;
extern M3 D_002A2D00;
extern COEF D_002C4470,D_002C4480;
extern float D_002DDED4;
extern "C" {
float func_00229468(O *,O *,qword *,qword *);
int func_0011D4D0(float,float,float);
qword func_001FA810(CONSTRAINT *,NODE *,qword);
void func_001FAC30(O *,qword);
qword func_001A62E8(O *);
void func_00228C18(O *,qword,qword *,qword *);
float func_0011E290(qword,qword,qword *,qword *);
int func_00230380(int);
void func_001F5E10(O *,qword,const COEF *,qword,const COEF *);
void func_001F5C30(O *,const M3 *,const COEF *,qword,const COEF *);
M4 *func_001A6318(O *);
void func_0011B938(const M3 *,M3 *,M3 *);
void func_0011BCF8(const M3 *,float *,qword *);
void func_001FAC98(O *,qword);
void func_0015A2C0(O *,WATER *,float,qword,qword,float,float);
int func_00132B10(O *,int);
void func_001FB098(EMITTER *,float);
void func_00258040(EMITTER **,EMITTER *);
}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){qword v;float f;__asm__("prot3w %0,%1":"=r"(v):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline float Z(qword q){qword v;float f;__asm__("pextuw %0,$zero,%1":"=r"(v):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline bool Near(qword a,qword b,float epsilon){return func_0011D4D0(X(a),X(b),epsilon)&&func_0011D4D0(Y(a),Y(b),epsilon)&&func_0011D4D0(Z(a),Z(b),epsilon);}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword Get(O *o,int slot){VE *v=o->vt;return v[slot].get((char *)o+v[slot].delta);}
static inline const COEF *Coefficients4470(){register const COEF *value asm("$2");asm("lui %0,%%hi(%1)\n\taddiu %0,%0,%%lo(%1)":"=r"(value):"i"(&D_002C4470));return value;}
static inline const COEF *Coefficients4480(){register const COEF *value asm("$2");asm("lui %0,%%hi(%1)\n\taddiu %0,%0,%%lo(%1)":"=r"(value):"i"(&D_002C4480));return value;}
static inline float Friction(const PHYS &a,const PHYS &b){
 register float value asm("$f20"),first asm("$f1"),second asm("$f0");
 asm("lwc1 %1,%3\n\tlwc1 %2,%4\n\tmul.s %0,%1,%2":"=f"(value),"=f"(first),"=f"(second):"m"(a.friction),"m"(b.friction));return value;
}
static inline qword LinearDelta(V &home,const V &velocity,qword linear){
   register qword value asm("vf2"),input asm("vf1");
   asm("sq %3,%2\n\tqmtc2.ni %3,%0\n\tlqc2 %1,%4\n\tvsub.xyzw %0,%1,%0":"=&j"(value),"=&j"(input),"=m"(home):"r"(linear),"m"(velocity));return value;
}
static inline qword AddNormal(const V &motion,const V &projection){register qword value asm("vf3"),part asm("vf1");asm("lqc2 %1,%3\n\tlqc2 %0,%2\n\tvadd.xyzw %0,%0,%1":"=&j"(value),"=&j"(part):"m"(motion),"m"(projection));return value;}
static inline qword AddTangent(const V &motion,const V &projection){register qword value asm("vf2"),part asm("vf1");asm("lqc2 %1,%3\n\tlqc2 %0,%2\n\tvadd.xyzw %0,%0,%1":"=&j"(value),"=&j"(part):"m"(motion),"m"(projection));return value;}
static inline qword NegativeAngular(const V &angular,float sign,qword &scalar){
 register qword value asm("vf2"),factor asm("vf1");
 asm("qmtc2.ni %2,%1\n\tlqc2 %0,%3\n\tvmulx.xyzw %0,%0,%1x":"=&j"(value),"=&j"(factor):"r"(sign),"m"(angular));scalar=factor;return value;
}
static inline void Gain(COEF *out,const COEF *in,float amount,float friction){float *d=out->f;const float *s=in->f;for(int i=2;i>=0;i--)*d++=*s++*amount*friction;}
static inline void Gain(COEF *out,const COEF *in,float friction){float *d=out->f;const float *s=in->f;for(int i=2;i>=0;i--)*d++=*s++*friction;}
static inline void Zero(V &v,float zero){v.f[0]=v.f[1]=v.f[2]=zero;}
static inline float Times(float a,float b){return a*b;}
static inline void Clear(EMITTER **emitter){if(emitter&&*emitter){func_001FB098(*emitter,0.0f);func_00258040(emitter,0);}}
extern "C" void func_002297F8(O *a,O *b){
 WORK w;
 float span=func_00229468(b,a,&w.point.q,&w.normal.q);
 float epsilon=0.0001f;
 if(span<epsilon)return;
 float spring=Near(D_002A2DD0,a->physics->direction.q,epsilon)?0.0f:a->physics->spring*b->physics->spring;
 float friction=Friction(*a->physics,*b->physics);
 float factor=0.0f;
 if(spring!=factor){
  qword k=Scalar(-spring*span);w.velocity.q=k;
  func_001FAC30(a,func_001FA810(&a->physics->constraint,a->motion,Scale(a->physics->direction.q,k)));
 }
 if(friction!=factor){
  func_00228C18(b,func_001A62E8(a),&w.velocity.q,&w.phase.vectors[0].q);
  qword linear=Get(a,33);qword relative=LinearDelta(w.linear,w.velocity,linear);
  float dot=func_0011E290(relative,w.normal.q,&w.phase.vectors[1].q,&w.phase.vectors[2].q);
  if(span==1.0f||factor<dot)factor=1.0f;else factor=span*0.5f+0.5f;
  if(func_00230380(a->body->kind)){
   Gain(&w.axis.coefficients,Coefficients4470(),factor,friction);
   func_001F5E10(a,D_002A2DD0,0,AddNormal(w.linear,w.phase.vectors[1]),&w.axis.coefficients);
   Gain(&w.axis.coefficients,Coefficients4470(),span,friction);
   func_001F5E10(a,D_002A2DD0,0,AddTangent(w.linear,w.phase.vectors[2]),&w.axis.coefficients);
  }
  if(func_00230380(a->rotation->kind)){
   w.angular.q=Get(a,34);
   qword k;
   qword negative=NegativeAngular(w.angular,-1.0f,k);
   w.scalar.q=k;func_0011E290(negative,w.normal.q,&w.angularNormal.q,&w.angularTangent.q);
   Gain(&w.axis.coefficients,Coefficients4480(),span,friction);
   func_001F5C30(a,&D_002A2D00,0,AddNormal(w.angular,w.angularNormal),&w.axis.coefficients);
   Gain(&w.axis.coefficients,Coefficients4480(),friction);
   func_001F5C30(a,&D_002A2D00,0,AddTangent(w.angular,w.angularTangent),&w.axis.coefficients);
  }
 }
 else Zero(w.velocity,factor);
 float zero=0.0f;
 if(spring!=zero){
  func_0011B938(&func_001A6318(a)->basis,&w.phase.basis,0);
  func_0011BCF8(&w.phase.basis,&w.angle,&w.axis.vector.q);
  qword k=Scalar(w.angle*Times(spring,3.0f)*span);
  qword rotation=Scale(w.axis.vector.q,k);w.angularNormal.q=k;
  func_001FAC98(a,rotation);
 }
 if(zero<span&&span<1.0f&&0.9f<w.normal.f[2]){
  float radius=((a->state->maximum.f[0]-a->state->minimum.f[0])+(a->state->maximum.f[1]-a->state->minimum.f[1]))*0.25f;
  func_0015A2C0(a,(WATER *)b,D_002DDED4,w.velocity.q,w.point.q,0.1f,radius);
 }
 else if(func_00132B10(a,0x32))Clear(&a->emitter);
}
