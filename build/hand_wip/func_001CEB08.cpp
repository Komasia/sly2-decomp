typedef int qw __attribute__((mode(TI)));
union U {qw q;float f[4];int i[4];};
struct POLY {float a,b,c;};
struct RIP {int kind;char p4[0x10];float start,duration;char p1C[4];POLY scale;char p2C[0x44];U position;char p80[0x10];U velocity;U acceleration;char pB0[0x20];U angular;char pE0[0x10];float radius,restitution,friction;};
struct SHAPE {void*frame;void*owner;};
struct CLOCK {float time,dt;};
struct PROX {float fraction,distance;};
struct WORK {U temporary,scalar,tangent,afterTangent;PROX proximity;qw contact;U firstTorque,frictionTorque,frictionAxis,inertia,normal,offset;};
extern "C" {
extern CLOCK D_002DDED0;
extern float D_002C1F60,D_002C1F64,D_002C1F68,D_002C1F6C;
extern qw D_002A2DA0,D_002A2DD0;
int func_00132B10(void*,int);
void func_00228C18(void*,qw,qw*,qw*);
qw func_0022D348(void*,void*,qw);
void func_001CEAA8(RIP*,float);
void func_0011EE08(qw,qw,qw,qw*,float*,float*);
int func_001CEB08(RIP*,SHAPE*,qw,qw);
}
static inline qw ToVu(qw a){qw r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qw Add(qw a,qw b){qw r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qw Sub(qw a,qw b){qw r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qw Bc(U*storage,float f){qw r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));storage->q=r;return storage->q;}
static inline qw Scale(qw v,qw scalar){qw r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(scalar));return r;}
static inline qw AddScaled(qw a,qw v,qw scalar){qw r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(v),"j"(scalar));return r;}
static inline qw Blend(qw a,qw b,qw scalar){return AddScaled(a,Sub(b,a),scalar);}
static inline qw Weighted(qw a,qw fa,qw b,qw fb){qw r;__asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(fa),"j"(b),"j"(fb));return r;}
static inline qw Cross(qw a,qw b){qw r;__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qw DotV(qw a,qw b){qw r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline float Scalar(qw q){float r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(q));return r;}
static inline float Dot(qw a,qw b){return Scalar(DotV(a,b));}
static inline qw Divide(qw a,qw scale){qw r;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(scale),"j"(a));return r;}
static inline qw Norm(qw a){qw len=DotV(a,a),r;float f;__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(len));f=Scalar(len);if(f<0.0001f)r=D_002A2DA0;else r=Divide(a,len);return r;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
int func_001CEB08(RIP*p,SHAPE*shape,qw point,qw normal){
 WORK w;float radius,elastic,friction;
 normal=ToVu(normal);
 w.contact=point;
 if(p->kind==8){radius=p->radius;elastic=p->restitution;friction=p->friction;}else{radius=100.0f;elastic=0.7f;friction=0.8f;}
 radius*=Evaluate(&p->scale,(D_002DDED0.time-p->start)/p->duration);
 w.normal.q=normal;
 if(func_00132B10(shape->owner,0x59)){
  func_00228C18(shape->owner,w.contact,&w.temporary.q,0);
  qw v=Blend(p->velocity.q,w.temporary.q,Bc(&w.scalar,D_002C1F64));
  qw difference=Sub(w.temporary.q,v);
  float duration=D_002C1F60;
  p->velocity.q=v;
  p->acceleration.q=Divide(difference,Bc(&w.scalar,duration));
  func_001CEAA8(p,duration);
  return 1;
 }
 w.offset.q=Scale(w.normal.q,Bc(&w.temporary,-radius));
 w.firstTorque.q=Cross(w.offset.q,w.normal.q);
 w.temporary.q=func_0022D348(shape->frame,0,w.contact);
 radius=Max(10.0f,radius);
 float invInertia=2.5f/(radius*radius);
 qw relative=Sub(Add(p->velocity.q,Cross(p->angular.q,w.offset.q)),w.temporary.q);
 float numerator=Dot(relative,w.normal.q)*(-1.0f-elastic);
 qw response=AddScaled(w.normal.q,Cross(w.firstTorque.q,w.offset.q),Bc(&w.scalar,invInertia));
 float denominator=Dot(response,w.normal.q);
 qw frictionScale=Bc(&w.scalar,-friction);
 float impulse=numerator/denominator;
 qw after=AddScaled(relative,response,Bc(&w.scalar,impulse));
 qw tangent=Sub(after,Scale(w.normal.q,DotV(after,w.normal.q)));
 w.frictionAxis.q=AddScaled(w.normal.q,Norm(tangent),frictionScale);
 w.frictionTorque.q=Cross(w.offset.q,w.frictionAxis.q);
 qw fricResponse=AddScaled(w.frictionAxis.q,Cross(w.frictionTorque.q,w.offset.q),Bc(&w.inertia,invInertia));
 float fricImpulse=Dot(relative,w.normal.q)*(-1.0f-elastic)/Dot(fricResponse,w.normal.q);
 qw fricAfter=AddScaled(relative,fricResponse,Bc(&w.scalar,fricImpulse));
 w.tangent.q=tangent;
 w.afterTangent.q=Sub(fricAfter,Scale(w.normal.q,DotV(fricAfter,w.normal.q)));
 func_0011EE08(D_002A2DD0,w.tangent.q,w.afterTangent.q,0,&w.proximity.fraction,&w.proximity.distance);
 qw originalScalar=Bc(&w.scalar,(1.0f-w.proximity.fraction)*impulse);
 qw frictionScalar=Bc(&w.scalar,w.proximity.fraction*fricImpulse);
 qw v=Weighted(w.normal.q,originalScalar,w.frictionAxis.q,frictionScalar);
 p->velocity.q=Add(p->velocity.q,v);
 qw torque=Weighted(w.firstTorque.q,originalScalar,w.frictionTorque.q,frictionScalar);
 p->angular.q=AddScaled(p->angular.q,torque,w.inertia.q);
 if(p->velocity.f[2]<D_002C1F68){p->velocity.f[2]=D_002C1F68;func_001CEAA8(p,D_002C1F6C);}
 float distance=Max(Dot(Sub(w.contact,p->position.q),w.normal.q),0.0f)+1.0f;
 p->position.q=AddScaled(p->position.q,w.normal.q,Bc(&w.scalar,distance));
 return 1;
}

typedef char layout_ceb08_0[(sizeof(qw)==16)?1:-1];
typedef char layout_ceb08_1[(sizeof(U)==16)?1:-1];
typedef char layout_ceb08_2[(sizeof(void*)==4)?1:-1];
typedef char layout_ceb08_3[(sizeof(POLY)==12)?1:-1];
typedef char layout_ceb08_4[(sizeof(SHAPE)==8)?1:-1];
typedef char layout_ceb08_5[(sizeof(PROX)==8)?1:-1];
typedef char layout_ceb08_6[(sizeof(WORK)==0xC0)?1:-1];
typedef char layout_ceb08_7[((unsigned)&((RIP*)0)->kind==0x0)?1:-1];
typedef char layout_ceb08_8[((unsigned)&((RIP*)0)->start==0x14)?1:-1];
typedef char layout_ceb08_9[((unsigned)&((RIP*)0)->duration==0x18)?1:-1];
typedef char layout_ceb08_10[((unsigned)&((RIP*)0)->scale==0x20)?1:-1];
typedef char layout_ceb08_11[((unsigned)&((RIP*)0)->position==0x70)?1:-1];
typedef char layout_ceb08_12[((unsigned)&((RIP*)0)->velocity==0x90)?1:-1];
typedef char layout_ceb08_13[((unsigned)&((RIP*)0)->acceleration==0xA0)?1:-1];
typedef char layout_ceb08_14[((unsigned)&((RIP*)0)->angular==0xD0)?1:-1];
typedef char layout_ceb08_15[((unsigned)&((RIP*)0)->radius==0xF0)?1:-1];
typedef char layout_ceb08_16[((unsigned)&((RIP*)0)->restitution==0xF4)?1:-1];
typedef char layout_ceb08_17[((unsigned)&((RIP*)0)->friction==0xF8)?1:-1];
typedef char layout_ceb08_18[((unsigned)&((SHAPE*)0)->frame==0x0)?1:-1];
typedef char layout_ceb08_19[((unsigned)&((SHAPE*)0)->owner==0x4)?1:-1];
typedef char layout_ceb08_20[((unsigned)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_ceb08_21[((unsigned)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_ceb08_22[((unsigned)&((PROX*)0)->fraction==0x0)?1:-1];
typedef char layout_ceb08_23[((unsigned)&((PROX*)0)->distance==0x4)?1:-1];
typedef char layout_ceb08_24[((unsigned)&((WORK*)0)->temporary==0x0)?1:-1];
typedef char layout_ceb08_25[((unsigned)&((WORK*)0)->scalar==0x10)?1:-1];
typedef char layout_ceb08_26[((unsigned)&((WORK*)0)->tangent==0x20)?1:-1];
typedef char layout_ceb08_27[((unsigned)&((WORK*)0)->afterTangent==0x30)?1:-1];
typedef char layout_ceb08_28[((unsigned)&((WORK*)0)->proximity==0x40)?1:-1];
typedef char layout_ceb08_29[((unsigned)&((WORK*)0)->contact==0x50)?1:-1];
typedef char layout_ceb08_30[((unsigned)&((WORK*)0)->firstTorque==0x60)?1:-1];
typedef char layout_ceb08_31[((unsigned)&((WORK*)0)->frictionTorque==0x70)?1:-1];
typedef char layout_ceb08_32[((unsigned)&((WORK*)0)->frictionAxis==0x80)?1:-1];
typedef char layout_ceb08_33[((unsigned)&((WORK*)0)->inertia==0x90)?1:-1];
typedef char layout_ceb08_34[((unsigned)&((WORK*)0)->normal==0xA0)?1:-1];
typedef char layout_ceb08_35[((unsigned)&((WORK*)0)->offset==0xB0)?1:-1];
