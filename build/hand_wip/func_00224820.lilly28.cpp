// Trace a probe segment, record contacts, and apply the allowed impulse.
// lilly28 (Lilly, team T1586): 2/245 words differ from the original. Remaining diff: in the record block the original
// has `lw $v1,0x4334($v1); qmtc2.ni $v1,$vf2` (the loaded bits share the lui register $v1); ours allocates $a0 there.
// - One register pin: Pin() keeps `owner` in $21 (s5); without it count/owner swap s5/s6 (global.c priority 370 vs 375).
// - Allocation-only empty asm `"=r"(pt) : "0"(pt)` on hit.point: gives the lq pseudo the priority that puts it in $v0.
// - MkVuk*/ScaleK/AddScaledK take their scalar as a by-value struct TEMPORARY: that temp is the shared 0x60($sp)
//   home of the original (sqc2 vf,0x60 / qmfc2+sq 0x60), so there is no separate `scalar` local.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct O;
struct VE {short delta,pad;union {qword (*get)(void *);void (*set)(void *,qword);} f;};
struct NODE {char pad[0x70];V position;};
struct PHYS;
struct STATE {char pad[0x60];O *owner;};
struct O {char pad[0xC];VE *vt;char pad10[0x4C];NODE *rotation,*motion;char pad64[0x84];PHYS *physics;STATE *state;};
struct COLL {void *source;O *object;};
struct LSG {qword point;char remainder[0x50];};
struct HIT {O *owner;int field4;O *object;int filter,channel;char pad14[0xC];qword point,impulse;char pad40[0x20];};
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
static inline qword ScalarWord(unsigned int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarBits(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword CrossXYZ(qword a,qword b){__asm__("vopmula.xyz ACC,%1,%0\n\tvopmsub.xyz %0,%0,%1":"+j"(b):"j"(a));return b;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword QwDot(qword a, qword b){qword qw;qword vfOne;
 __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));return qw;}
// the extra "j"(qw) is allocation-only: it makes qw a VU-class pseudo, so the compiler's qmfc2 comes from the dot result (vf1)
static inline float GXOfQw(qword qw){float x;__asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw), "j"(qw));return x;}
static inline float Dot(qword a,qword b){return GXOfQw(QwDot(a,b));}
static inline qword AddScaled(qword old,qword v,qword k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(old):"j"(v),"j"(k));return old;}
struct VUK{qword q;};
static inline VUK MkVukBits(int n){VUK r;__asm__("qmtc2.ni %1,%0":"=j"(r.q):"r"(n));return r;}
static inline VUK MkVukFloat(float f){VUK r;__asm__("qmtc2.ni %1,%0":"=j"(r.q):"r"(f));return r;}
static inline VUK MkVuk(float f){VUK r;__asm__("mfc1 %0,%1":"=r"(r.q):"f"(f));return r;}
static inline qword ScaleK(qword v,VUK k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k.q));return r;}
static inline qword AddScaledK(qword old,qword v,VUK k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%2,%1x":"+j"(old):"j"(k.q),"j"(v));return old;}

static inline float Clamp(float f,float lo,float hi){float r;if(f<lo)r=lo;else if(hi<f)r=hi;else r=f;return r;}
static inline qword Get(O *o,int slot){VE *v=o->vt;return v[slot].f.get((char *)o+v[slot].delta);}
static inline void Set(O *o,int slot,qword q){VE *v=o->vt;v[slot].f.set((char *)o+v[slot].delta,q);}
static inline O *Pin(O *p){register O *r asm("$21");asm("daddu %0,%1,$zero":"=r"(r):"r"(p));return r;}
extern "C" void func_00224820(O *ownerIn,int filter,int channel,qword start,qword end,int queryCount,COLL **objects,int capacity,int *count,HIT *records){
 O *owner=Pin(ownerIn);LSG hit;
 COLL *collider=func_0014CC58(0,start,end,queryCount,objects,&hit);
 if(!collider)return;
 qword normal;
 O *chain=collider->object;
 {qword len,one;qword d=Sub(end,start);
 __asm__("vmul.xyz %2,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%2,%2y\n\tvmaddz.x %2,%1,%2z\n\tvsqrt Q,%2x\n\tvwaitq\n\tvaddq.x %2,$vf0,Q\n\tvdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%3,Q":"=&j"(normal),"=&j"(one),"=&j"(len):"j"(d));}
 O *object=func_001F7530(chain,filter);
 if(!object)return;
 O *body=object->state->owner;
 int i;
 for(i=0;i<*count;i++)if(records[i].object==object)break;
 if(i>=*count&&*count<capacity){
  HIT *record=&records[(*count)++];
  func_002333B4(record,0,0x60);
  record->impulse=ScaleK(normal,MkVukBits(*(int *)&D_002C4334));record->object=object;record->filter=filter;record->channel=channel;{qword pt=hit.point;__asm__("":"=r"(pt):"0"(pt));record->point=pt;}record->owner=owner;
 }
 if(!body->physics)return;
 float along=Dot(func_0022D348(body->motion,0,hit.point),normal);
 float ratio=along/D_002C4334.f;
 float response=Clamp(D_002C4320.a+ratio*(D_002C4320.b+ratio*D_002C4320.c),D_002BBB60.lo,D_002BBB60.hi);
 float fz=0.0f;
 if(fz<response){
 qword impulse=ScaleK(normal,MkVukFloat(response*D_002C4330));
 qword linear=func_001FAA00(body,impulse);
 qword angular=func_001FAA48(body,hit.point,impulse);
 qword delta=Sub(hit.point,body->rotation->position.q);
 float change=Dot(Add(linear,CrossXYZ(angular,delta)),normal);
 if(fz<change){
 qword velocity,spin;
  float x=(D_002C4334.f-along)/change;
  float one=1.0f;
 if(x<fz){}else if(one<x)fz=one;else fz=x;
 {velocity=AddScaledK(Get(body,33),linear,MkVuk(fz));}
 {spin=AddScaledK(Get(body,34),angular,MkVuk(fz));}
 Set(body,35,velocity);Set(body,36,spin);
 }
 }
}
