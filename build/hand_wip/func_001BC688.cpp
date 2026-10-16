typedef int qword __attribute__((mode(TI)));
struct U{qword q;};
struct X{char pad[0xE8];int pointCount;char padEC[0x1EC-0xEC];qword*planes;};
struct HIT{qword start,end,enterNormal,exitNormal;float first,last;int kind;X*enterOwner;X*exitOwner;};
struct SCALAR;
extern "C" {void func_001BD400(X*);SCALAR*func_002564B8(SCALAR*);void*func_002333B4(void*,int,unsigned);extern float D_002C0AB4;}
struct SCALAR{qword q;SCALAR(){(void)func_002564B8(this);}};
struct HOME{qword q;};
inline void*operator new(unsigned,void*p){return p;}
static inline qword Zero(){qword r;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Neg(qword v){qword r=Zero();__asm__("vsub.xyzw %0,%0,%1":"+j"(r):"j"(v));return r;}
static inline qword Read(const U*p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(p->q));return r;}
static inline qword Lerp(U*scalar,qword a,qword b,float t){
 qword first,second,r;
 __asm__("qmtc2.ni %1,%0":"=j"(second):"r"(t));
 __asm__("qmtc2.ni %1,%0":"=j"(first):"r"(1.0f-t));
 scalar->q=first;qword lhs=scalar->q;scalar->q=second;
 __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(lhs),"j"(b),"j"(scalar->q));return r;
}
static inline float FirstDistance(HOME*dotHome,HOME*oneHome,const U&plane,const U&point,qword&cached){
 SCALAR*dot=new((void*)dotHome)SCALAR;
 cached=plane.q;SCALAR*one=new((void*)oneHome)SCALAR;
 register qword normal __asm__("vf3")=Read(&plane),position __asm__("vf4")=Read(&point);
 register qword result __asm__("vf2"),unit __asm__("vf1");float value;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w":"=&j"(result),"=&j"(unit):"j"(normal),"j"(position));
 one->q=unit;
 __asm__("vadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"+j"(result):"j"(one->q),"j"(normal));
 dot->q=result;
 __asm__("qmfc2.ni %0,%1":"=r"(value):"j"(dot->q));return value;
}
static inline float Distance(HOME*dotHome,HOME*oneHome,const U&plane,const U&point){
 SCALAR*dot=new((void*)dotHome)SCALAR;SCALAR*one=new((void*)oneHome)SCALAR;
 register qword normal __asm__("vf3")=Read(&plane),position __asm__("vf4")=Read(&point);
 register qword result __asm__("vf2"),unit __asm__("vf1");float value;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w":"=&j"(result),"=&j"(unit):"j"(normal),"j"(position));
 one->q=unit;
 __asm__("vadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"+j"(result):"j"(one->q),"j"(normal));
 dot->q=result;
 __asm__("qmfc2.ni %0,%1":"=r"(value):"j"(dot->q));return value;
}
struct WORK{U scalar;HOME dotA,oneA,dotB,oneB;U enterNormal,exitNormal,plane,a,b;};
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char SCALAR_Size[sizeof(SCALAR)==16?1:-1];
typedef char HOME_Size[sizeof(HOME)==16?1:-1];
typedef char HIT_Size[sizeof(HIT)==96?1:-1];
typedef char WORK_Size[sizeof(WORK)==160?1:-1];
typedef char U_Align[__alignof__(U)==16?1:-1];
typedef char SCALAR_Align[__alignof__(SCALAR)==16?1:-1];
typedef char HOME_Align[__alignof__(HOME)==16?1:-1];
typedef char HIT_Align[__alignof__(HIT)==16?1:-1];
typedef char WORK_Align[__alignof__(WORK)==16?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char SCALAR_q_Offset[FIELD_OFFSET(SCALAR,q)==0?1:-1];
typedef char HOME_q_Offset[FIELD_OFFSET(HOME,q)==0?1:-1];
typedef char X_pointCount_Offset[FIELD_OFFSET(X,pointCount)==232?1:-1];
typedef char X_planes_Offset[FIELD_OFFSET(X,planes)==492?1:-1];
typedef char HIT_start_Offset[FIELD_OFFSET(HIT,start)==0?1:-1];
typedef char HIT_end_Offset[FIELD_OFFSET(HIT,end)==16?1:-1];
typedef char HIT_enterNormal_Offset[FIELD_OFFSET(HIT,enterNormal)==32?1:-1];
typedef char HIT_exitNormal_Offset[FIELD_OFFSET(HIT,exitNormal)==48?1:-1];
typedef char HIT_first_Offset[FIELD_OFFSET(HIT,first)==64?1:-1];
typedef char HIT_last_Offset[FIELD_OFFSET(HIT,last)==68?1:-1];
typedef char HIT_kind_Offset[FIELD_OFFSET(HIT,kind)==72?1:-1];
typedef char HIT_enterOwner_Offset[FIELD_OFFSET(HIT,enterOwner)==76?1:-1];
typedef char HIT_exitOwner_Offset[FIELD_OFFSET(HIT,exitOwner)==80?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==0?1:-1];
typedef char WORK_dotA_Offset[FIELD_OFFSET(WORK,dotA)==16?1:-1];
typedef char WORK_oneA_Offset[FIELD_OFFSET(WORK,oneA)==32?1:-1];
typedef char WORK_dotB_Offset[FIELD_OFFSET(WORK,dotB)==48?1:-1];
typedef char WORK_oneB_Offset[FIELD_OFFSET(WORK,oneB)==64?1:-1];
typedef char WORK_enterNormal_Offset[FIELD_OFFSET(WORK,enterNormal)==80?1:-1];
typedef char WORK_exitNormal_Offset[FIELD_OFFSET(WORK,exitNormal)==96?1:-1];
typedef char WORK_plane_Offset[FIELD_OFFSET(WORK,plane)==112?1:-1];
typedef char WORK_a_Offset[FIELD_OFFSET(WORK,a)==128?1:-1];
typedef char WORK_b_Offset[FIELD_OFFSET(WORK,b)==144?1:-1];
extern "C" int func_001BC688(X*p,qword a,qword b,int capacity,HIT*out){
 int i=0,n;float first,last;WORK work;work.a.q=a;work.b.q=b;
 func_001BD400(p);first=0;last=1;work.enterNormal.q=Zero();work.exitNormal.q=work.enterNormal.q;
 for(;i<p->pointCount-1;i++){
  work.plane.q=p->planes[i];qword cached;float da=FirstDistance(&work.dotA,&work.oneA,work.plane,work.a,cached);float db=Distance(&work.dotB,&work.oneB,work.plane,work.b);
  da+=D_002C0AB4;db+=D_002C0AB4;
  if(da<0 && db<0)continue;
  if(0<da && 0<db){last=0;first=last;break;}
  float t=da/(da-db);
  if(da<0){last=(t<last)?t:last;work.exitNormal.q=work.plane.q;}
  else{work.enterNormal.q=cached;first=(first<t)?t:first;}
  if(last<=first)break;
 }
 n=0;
 if(last<=first){
  if(capacity>0){HIT*e=out;(void)func_002333B4(e,0,0x60);n=1;e->start=work.a.q;e->last=1;e->first=0;e->end=work.b.q;}
  return n;
 }
 if(0<first && capacity>0){
  HIT*e=&out[n];(void)func_002333B4(e,0,0x60);n=1;e->start=work.a.q;
  e->end=Lerp(&work.scalar,Read(&work.a),Read(&work.b),first);e->exitNormal=Neg(Read(&work.enterNormal));e->first=0;e->last=first;e->exitOwner=p;
 }
 if(last<1 && n<capacity){
  HIT*e=&out[n++];(void)func_002333B4(e,0,0x60);e->enterOwner=p;
  e->start=Lerp(&work.scalar,Read(&work.a),Read(&work.b),last);e->enterNormal=Neg(Read(&work.exitNormal));e->end=work.b.q;e->first=last;e->last=1;
 }
 return n;
}
