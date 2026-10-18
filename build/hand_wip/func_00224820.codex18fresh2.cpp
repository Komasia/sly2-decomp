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
void *func_002333B4(void *,int,unsigned int);
qword func_0022D348(NODE *,NODE *,qword);
qword func_001FAA00(O *,qword);
qword func_001FAA48(O *,qword,qword);
}
static inline qword ToVF(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword ScalarWord(unsigned int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarBits(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline void RecordScalar(V &home,qword value){asm("sqc2 %1,%0":"=m"(home.q):"j"(value));}
static inline void RecordCPU(V &home,qword value){asm("sq %1,%0":"=m"(home.q):"r"(value));}
static inline qword LoadFraction(const qword &home){register qword value asm("vf2");asm("lqc2 %0,%1":"=j"(value):"m"(home));return value;}
static inline qword ToCPU(qword value){qword result;asm("qmfc2.ni %0,%1":"=r"(result):"j"(value));return result;}

static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=&j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword CrossXYZ(qword a,qword b){__asm__("vopmula.xyz ACC,%1,%0\n\tvopmsub.xyz %0,%0,%1":"+j"(b):"j"(a));return b;}
static inline qword Normalize(qword v){qword len,one;register qword result asm("vf4");
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
static inline O *RetainOwner(O *input){register O *owner asm("$21");asm("daddu %0,%1,$zero":"=r"(owner):"r"(input));return owner;}
static inline float PolynomialBounds(float ratio,float &lower,RANGE *&bounds){
 register float x asm("$f2")=ratio,value asm("$f0"),lo asm("$f4");register RANGE *range asm("$2");
 asm("lui %2,%%hi(%4)\n\taddiu $3,%2,%%lo(%4)\n\tlwc1 $f3,%%lo(%4)(%2)\n\tlwc1 %0,8($3)\n\tlui %2,%%hi(%5)\n\tlwc1 $f1,4($3)\n\tlwc1 %1,%%lo(%5)(%2)\n\taddiu %2,%2,%%lo(%5)\n\tmul.s %0,%3,%0\n\tadd.s $f1,$f1,%0\n\tmul.s %3,%3,$f1\n\tadd.s %0,$f3,%3"
 :"=&f"(value),"=&f"(lo),"=&r"(range),"+f"(x):"i"(&D_002C4320),"i"(&D_002BBB60):"$3","$f1","$f3","memory");
 lower=lo;bounds=range;return value;
}
static inline float ClampRange(float input,float lo,RANGE *range){register float f asm("$f0")=input,hi asm("$f5")=range->hi,r asm("$f3");if(f<lo)r=lo;else if(hi<f)r=hi;else r=f;return r;}
static inline qword MotionAndSpeedHigh(qword value,unsigned &high){
 register qword velocity asm("vf4");register unsigned page asm("$3");
 asm("qmtc2.ni %2,%0\n\tlui %1,%%hi(%3)":"=j"(velocity),"=r"(page):"r"(value),"i"(&D_002C4334));high=page;return velocity;
}
static inline float ProjectionAndSpeed(qword velocity,qword normal,unsigned high,float &speed,unsigned &retained){
 register qword v asm("vf4")=velocity,n asm("vf3")=normal;
 register unsigned saved asm("$16");register float word asm("$2"),target asm("$f2");
 asm("daddu %0,%5,$zero\n\tvmul.xyz $vf1,%3,%4\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tlwc1 %2,%%lo(%6)(%5)\n\tqmfc2.ni %1,$vf1"
 :"=&r"(saved),"=r"(word),"=f"(target):"j"(v),"j"(n),"r"(high),"i"(&D_002C4334):"vf1","vf2","memory");
 speed=target;retained=saved;return word;
}
extern "C" void func_00224820(O *inputOwner,int filter,int channel,qword start,qword end,int queryCount,COLL **objects,int capacity,int *count,HIT *records){
 O *owner=RetainOwner(inputOwner);LSG hit;V scalar;
 COLL *collider=func_0014CC58(0,start,end,queryCount,objects,&hit);
 if(!collider)return;
 qword normal;
 O *chain=collider->object;
 normal=Normalize(Sub(end,start));
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
  record->impulse.q=Scale(normal,k);
  record->filter=filter;record->channel=channel;record->point.q=point;RecordScalar(scalar,k);
 }
 if(!body->physics)return;
 unsigned speedHigh,savedSpeedHigh;float targetSpeed;
 qword pointVelocity=MotionAndSpeedHigh(func_0022D348(body->motion,0,hit.point.q),speedHigh);
 float along=ProjectionAndSpeed(pointVelocity,normal,speedHigh,targetSpeed,savedSpeedHigh);
 float ratio=along/targetSpeed;
 float lower;RANGE *bounds;float rawResponse=PolynomialBounds(ratio,lower,bounds);
 float response=ClampRange(rawResponse,lower,bounds);
 float floor=0.0f;
 if(floor<response){
 qword impulse,linear,angular;
 {qword k=Scalar(response*D_002C4330);impulse=Scale(normal,k);RecordScalar(scalar,k);}
 linear=func_001FAA00(body,impulse);
 angular=func_001FAA48(body,hit.point.q,impulse);
 qword delta=Sub(hit.point.q,body->rotation->position.q);
 float change=Dot(Add(linear,CrossXYZ(angular,delta)),normal);
 if(floor<change){
 qword fraction,velocity,spin;
 fraction=ScalarBits(floor=ClampLo((((F32 *)(savedSpeedHigh+0x4334u))->f-along)/change,floor,1.0f));
 {qword old=ToVF(Get(body,33));qword k=LoadFraction(fraction);velocity=AddScaled(old,linear,k);RecordCPU(scalar,ToCPU(k));}
 {qword old=ToVF(Get(body,34));qword k=LoadFraction(fraction);spin=AddScaled(old,angular,k);RecordCPU(scalar,ToCPU(k));}
 Set(body,35,velocity);Set(body,36,spin);
 }
 }
}
