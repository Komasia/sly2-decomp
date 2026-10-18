typedef int qword __attribute__((mode(TI)));
struct U{qword q;};
struct X{char pad[0xE8];int pointCount;char padEC[0x1EC-0xEC];qword*planes;};
struct HIT{qword start,end,enterNormal,exitNormal;float first,last;int kind;X*enterOwner;X*exitOwner;};
struct SCALAR;
extern "C" {void func_001BD400(X*);SCALAR*func_002564B8(SCALAR*);void*func_002333B4(void*,int,unsigned);extern float D_002C0AB4;}
struct SCALAR{qword q;SCALAR(){(void)func_002564B8(this);}};
struct HOME{qword q;};
inline void*operator new(unsigned,void*p){return p;}
static inline qword ClearAndCopy(U*home,float*last,int*remaining,X*owner){register qword result __asm__("$3");register float one __asm__("$f23");register int count __asm__("$2");__asm__("vsub.xyzw $vf1,$vf0,$vf0\n\tli.s %1,%F4\n\tsqc2 $vf1,%3\n\tqmfc2.ni %0,$vf1\n\tlw %2,%5\n\taddiu %2,%2,-1":"=&r"(result),"=f"(one),"=r"(count),"=m"(home->q):"F"(1.0f),"m"(owner->pointCount):"vf1");*last=one;*remaining=count;return result;}
static inline float FirstDistance(HOME*dotHome,HOME*oneHome,const U&plane,const U&point,qword&cached,SCALAR*&next,HOME*nextHome){
 SCALAR*dot=(SCALAR*)dotHome;
 cached=plane.q;SCALAR*one=new((void*)oneHome)SCALAR;
 register qword unit __asm__("vf1"),result __asm__("vf2");
 register SCALAR*following __asm__("$4");
 __asm__("lqc2 $vf3,%3\n\tla %2,%a5\n\tlqc2 $vf4,%4\n\tvmul.xyz %1,$vf3,$vf4\n\tvaddw.x %0,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddaz.x $ACC,%0,%1z\n\tvmsubw.x %1,%0,$vf3w":"=&j"(unit),"=&j"(result),"=&r"(following):"m"(plane.q),"m"(point.q),"p"(nextHome):"vf3","vf4");
 register float raw __asm__("$2");
 __asm__("qmfc2.ni %0,%1":"=r"(raw):"j"(result));one->q=unit;
 dot->q=result;next=following;return raw;
}
static inline float Distance(HOME*dotHome,HOME*oneHome,const U&plane,const U&point,float&left,float&epsilon){
 SCALAR*dot=(SCALAR*)dotHome;SCALAR*one=new((void*)oneHome)SCALAR;
 register qword result __asm__("vf2"),unit __asm__("vf1");float value;
 register float capturedLeft __asm__("$f20")=left;register float bias __asm__("$f0")=D_002C0AB4;epsilon=bias;
 __asm__("lqc2 $vf3,%3\n\tadd.s %2,%2,%5\n\tlqc2 $vf4,%4\n\tvmul.xyz %0,$vf3,$vf4\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,$vf3w":"=&j"(result),"=&j"(unit),"+f"(capturedLeft):"m"(plane.q),"m"(point.q),"f"(bias):"vf3","vf4");
 __asm__("qmfc2.ni %0,%1":"=r"(value):"j"(result));one->q=unit;dot->q=result;left=capturedLeft;return value;
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
 register X*owner __asm__("$18");__asm__("daddu %0,%1,$zero":"=r"(owner):"r"(p));int limit=capacity;register HIT*records __asm__("$20")=out;
 int i=0;register int n __asm__("$17");float first,last;WORK work;work.a.q=a;work.b.q=b;
 func_001BD400(p);first=0;int planeLimit;work.exitNormal.q=ClearAndCopy(&work.enterNormal,&last,&planeLimit,owner);
 for(;i<planeLimit;i++,planeLimit=owner->pointCount-1){
  register qword*planeBase __asm__("$3")=owner->planes;register unsigned address __asm__("$2");register SCALAR*dotReceiver __asm__("$4");
  __asm__("sll %0,%2,4\n\tla %1,%a4\n\taddu %0,%0,%3":"=&r"(address),"=&r"(dotReceiver):"r"(i),"r"(planeBase),"p"(&work.dotA));
  {register qword word __asm__("$2")=*(qword*)address;work.plane.q=word;}(void)new((void*)dotReceiver)SCALAR;register qword cached __asm__("$17");SCALAR*next;float da=FirstDistance(&work.dotA,&work.oneA,work.plane,work.a,cached,next,&work.dotB);(void)new((void*)next)SCALAR;float epsilon;float db=Distance(&work.dotB,&work.oneB,work.plane,work.b,da,epsilon);
  db+=epsilon;
  if(da<0 && db<0)continue;
  if(0<da && 0<db){last=0;first=last;break;}
  float t=da/(da-db);
  if(da<0){last=(last<t)?last:t;{register qword snapshot __asm__("$3")=work.plane.q;work.exitNormal.q=snapshot;}}
  else{__asm__("sq %1,%0":"=m"(work.enterNormal.q):"r"(cached));first=(t<first)?first:t;}
  if(last<=first)break;
 }
 n=0;
 if(last<=first && limit>0){
  {register HIT*e __asm__("$16")=records;(void)func_002333B4(e,0,0x60);n=1;e->start=work.a.q;e->last=1;{register qword endpoint __asm__("$3");__asm__("lq %0,%2\n\tsw $zero,%1":"=r"(endpoint),"=m"(e->first):"m"(work.b.q));e->end=endpoint;}}
  goto done;
 }
 if(0<first && limit>0){
  register HIT*e __asm__("$16");register int clear __asm__("$5");register unsigned bytes __asm__("$6");register int stride __asm__("$2")=sizeof(HIT);
  __asm__("daddu %1,$zero,$zero\n\tmult $3,%3,%5\n\taddiu %2,$zero,96\n\taddiu %3,$zero,1\n\taddu %0,$3,%4":"=r"(e),"=&r"(clear),"=&r"(bytes),"+&r"(n):"r"(records),"r"(stride):"$3","hi","lo");
  (void)func_002333B4(e,clear,bytes);register float unity __asm__("$f0");
  __asm__("lq $3,%2\n\tli.s %1,%F3\n\tsq $3,%0":"=m"(e->start),"=f"(unity):"m"(work.a.q),"F"(1.0f):"$3");
  float inverse=unity-first;register qword interpolated __asm__("vf1"),negative __asm__("vf3");
  __asm__("mfc1 $2,%3\n\tlqc2 %0,%5\n\tqmtc2.ni $2,$vf2\n\tvsub.xyzw %1,$vf0,$vf0\n\tvsub.xyzw %1,%1,%0\n\tmfc1 $2,%4\n\tqmtc2.ni $2,%0\n\tlqc2 $vf4,%6\n\tsqc2 %0,%2\n\tlqc2 $vf5,%7\n\tsqc2 $vf2,%2\n\tvmulax.xyzw $ACC,$vf4,%0x\n\tvmaddx.xyzw %0,$vf5,$vf2x":"=j"(interpolated),"=j"(negative),"=m"(work.scalar.q):"f"(first),"f"(inverse),"m"(work.enterNormal.q),"m"(work.a.q),"m"(work.b.q):"$2","vf2","vf4","vf5");
  e->end=interpolated;e->exitNormal=negative;e->first=0;e->last=first;e->exitOwner=owner;
 }
 if(last<1 && n<limit){
  register HIT*e __asm__("$16");register int clear __asm__("$5");register unsigned bytes __asm__("$6");register int stride __asm__("$2")=sizeof(HIT);
  __asm__("daddu %1,$zero,$zero\n\tmult $3,%3,%5\n\taddiu %2,$zero,96\n\taddiu %3,%3,1\n\taddu %0,$3,%4":"=r"(e),"=&r"(clear),"=&r"(bytes),"+&r"(n):"r"(records),"r"(stride):"$3","hi","lo");
  (void)func_002333B4(e,clear,bytes);float inverse=1.0f-last;register qword interpolated __asm__("vf1"),negative __asm__("vf3"),endpoint __asm__("vf4");
  __asm__("lqc2 %2,%6\n\tvsub.xyzw %1,$vf0,$vf0\n\tvsub.xyzw %1,%1,%2\n\tmfc1 $2,%4\n\tlqc2 %2,%7\n\tqmtc2.ni $2,$vf2\n\tmfc1 $3,%5\n\tqmtc2.ni $3,%0\n\tlqc2 $vf5,%8\n\tsqc2 %0,%3\n\tsqc2 $vf2,%3\n\tvmulax.xyzw $ACC,$vf5,%0x\n\tvmaddx.xyzw %0,%2,$vf2x":"=j"(interpolated),"=j"(negative),"=j"(endpoint),"=m"(work.scalar.q):"f"(last),"f"(inverse),"m"(work.exitNormal.q),"m"(work.b.q),"m"(work.a.q):"$2","$3","vf2","vf5");
  register qword endpointWord __asm__("$2");
  __asm__("qmfc2.ni %0,%4\n\tsw %5,%1\n\tsqc2 %6,%2\n\tsqc2 %7,%3":"=&r"(endpointWord),"=m"(e->enterOwner),"=m"(e->start),"=m"(e->enterNormal):"j"(endpoint),"r"(owner),"j"(interpolated),"j"(negative));
  __asm__("sq %3,%0\n\tswc1 %4,%1\n\tswc1 %5,%2":"=m"(e->end),"=m"(e->first),"=m"(e->last):"r"(endpointWord),"f"(last),"f"(1.0f));
 }
 done:return n;
}

typedef char layout_PointerWidth[(sizeof(void*)==4)?1:-1];
typedef char layout_IntegerWidth[(sizeof(int)==4)?1:-1];
typedef char layout_UnsignedWidth[(sizeof(unsigned)==4)?1:-1];
typedef char layout_FloatWidth[(sizeof(float)==4)?1:-1];
typedef char layout_QwordWidth[(sizeof(qword)==16)?1:-1];
typedef char layout_QwordAlignment[(__alignof__(qword)==16)?1:-1];
typedef char layout_XPrefixSize[(sizeof(X)==0x1F0)?1:-1];
typedef char layout_XAlignment[(__alignof__(X)==4)?1:-1];
typedef char layout_WorkAlignment[(__alignof__(WORK)==16)?1:-1];
typedef char layout_InputPointWidth[(sizeof(((WORK*)0)->a.q)==16)?1:-1];
typedef char layout_InputEndWidth[(sizeof(((WORK*)0)->b.q)==16)?1:-1];
typedef char layout_HitNormalsSpan[(sizeof(((HIT*)0)->enterNormal)+sizeof(((HIT*)0)->exitNormal)==32)?1:-1];
typedef char layout_PlanePointerWidth[(sizeof(((X*)0)->planes)==4)?1:-1];
typedef char layout_PointCountWidth[(sizeof(((X*)0)->pointCount)==4)?1:-1];
