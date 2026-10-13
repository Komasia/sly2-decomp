// Trace a probe segment, record contacts, and apply the allowed impulse.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct O;
struct VE {short delta,pad;union {qword (*get)(void *);void (*set)(void *,qword);} f;};
struct NODE {char pad[0x70];V position;};
struct PHYS;
struct STATE {char pad[0x60];O *owner;};
struct O {char pad[0xC];VE *vt;char pad10[0x4C];NODE *rotation,*motion;char pad64[0x84];PHYS *physics;STATE *state;};
struct COLL {void *source;O *object;};
struct LSG {V point;char remainder[0x50];};
struct HIT {O *owner;int field4;O *object;int filter,channel;char pad14[0xC];V point,impulse;char pad40[0x20];};
struct POLY {float a,b,c;};
struct RANGE {float lo,hi;};
union F32 {float f;unsigned int bits;};
extern F32 D_002C4334;
extern float D_002C4330;
extern POLY D_002C4320;
extern RANGE D_002BBB60;
extern "C" {
COLL *func_0014CC58(int,qword,qword,int,COLL **,LSG *);
O *func_001F7530(O *,int);
void *func_002333B4(void *,int,int);
qword func_0022D348(NODE *,NODE *,qword);
qword func_001FAA00(O *,qword);
qword func_001FAA48(O *,qword,qword);
}
static inline qword ToVF(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword ToCPU(qword a){qword r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(a));return r;}
static inline qword ScalarWord(unsigned int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarBits(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=&j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword CrossXYZ(qword a,qword b){__asm__("vopmula.xyz ACC,%1,%0\n\tvopmsub.xyz %0,%0,%1":"+j"(b):"j"(a));return b;}
static inline qword Normalize(qword v){qword len,one,result;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(len),"=&j"(one):"j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(len));
 __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=&j"(result):"j"(v),"j"(len));return result;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline float Dot(qword a,qword b){qword d,one;float f;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));
 __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline qword AddScaled(qword old,qword v,qword k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(old):"j"(v),"j"(k));return old;}
static inline float ClampLo(float f,float lo,float hi){float r=lo;if(f<lo){}else if(hi<f)r=hi;else r=f;return r;}
static inline float Clamp(float f,float lo,float hi){float r;if(f<lo)r=lo;else if(hi<f)r=hi;else r=f;return r;}
static inline qword Get(O *o,int slot){VE *v=o->vt;return v[slot].f.get((char *)o+v[slot].delta);}
static inline void Set(O *o,int slot,qword q){VE *v=o->vt;v[slot].f.set((char *)o+v[slot].delta,q);}
extern "C" void func_00224820(O *owner,int filter,int channel,qword start,qword end,int queryCount,COLL **objects,int capacity,int *count,HIT *records){
 LSG hit;V scalar;
 COLL *collider=func_0014CC58(0,start,end,queryCount,objects,&hit);
 if(!collider)return;
 V normal;
 O *chain=collider->object;
 normal.q=Normalize(Sub(end,start));
 O *object=func_001F7530(chain,filter);
 if(!object)return;
 O *body=object->state->owner;
 int i;
 for(i=0;i<*count;i++)if(records[i].object==object)break;
 if(i>=*count&&*count<capacity){
  HIT *record=&records[(*count)++];
  func_002333B4(record,0,0x60);
  qword k=ScalarWord(D_002C4334.bits);
  qword point=hit.point.q;
  record->owner=owner;
  record->object=object;
  record->impulse.q=Scale(normal.q,k);
  record->filter=filter;record->channel=channel;record->point.q=point;
  scalar.q=k;
 }
 if(!body->physics)return;
 float along=Dot(ToVF(func_0022D348(body->motion,0,hit.point.q)),normal.q);
 float ratio=along/D_002C4334.f;
 float response=Clamp(D_002C4320.a+ratio*(D_002C4320.b+ratio*D_002C4320.c),D_002BBB60.lo,D_002BBB60.hi);
 if(0.0f<response){
 V impulse,linear,angular;
 {qword k=Scalar(response*D_002C4330);impulse.q=Scale(normal.q,k);scalar.q=k;}
 linear.q=func_001FAA00(body,impulse.q);
 angular.q=func_001FAA48(body,hit.point.q,impulse.q);
 qword delta=Sub(hit.point.q,body->rotation->position.q);
 float change=Dot(Add(linear.q,CrossXYZ(angular.q,delta)),normal.q);
 if(0.0f<change){
 V fraction,velocity,spin;
 fraction.q=ScalarBits(ClampLo((D_002C4334.f-along)/change,0.0f,1.0f));
 {qword old=ToVF(Get(body,33));qword k=fraction.q;velocity.q=AddScaled(old,linear.q,k);scalar.q=ToCPU(k);}
 {qword old=ToVF(Get(body,34));qword k=fraction.q;spin.q=AddScaled(old,angular.q,k);scalar.q=ToCPU(k);}
 Set(body,35,velocity.q);Set(body,36,spin.q);
 }
 }
}
