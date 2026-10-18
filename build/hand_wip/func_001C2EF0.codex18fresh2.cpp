typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword a,b,c;};
struct WORK {M3 basis,matrix;int count;U start,target,offset,destination;};
struct VTE {short delta,pad;void(*fn)();};
struct SO {char pad0[0xC];VTE*vt;char pad10[0x70-0x10];qword position;};
struct OWNER {char pad0[0x150];SO*source;void*factory;SO*first;};
struct RANGE {float low,high;};
struct ANGLE_PAGE{char before[0xCF0];RANGE range;};
extern "C" {
extern char D_003DD490[];
extern qword D_002A2DC0,D_002A2DA0,D_002C0D60;
extern RANGE D_002C0CF0,D_002C0CF8,D_002C0CE0;
extern float D_002C0CE8,D_002C0CEC,D_002A76E8;
void*func_001C4840(void*);
qword func_001A62E8(void*);
float func_0011D448(float,float);
qword func_0011E1A0(float,float,float);
M3*func_0011B830(M3*,qword,qword);
qword func_001D69F0(qword,qword,qword,float);
int func_00132B10(SO*,int);
void func_001C6BD0(SO*,qword,qword,float,float);
SO*func_001CB250(void*,int);
void func_001C2DB8(OWNER*);
SO*func_001C2EF0(OWNER*,int);
}
static inline qword ReadVU(const qword*p){qword q;__asm__("lqc2 %0,0(%1)":"=j"(q):"r"(p),"m"(*p));return q;}
static inline qword ReadGPR(const qword*p){qword q;__asm__("lq %0,0(%1)":"=r"(q):"r"(p),"m"(*p));return q;}
static inline qword ToVU(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword ReadFallback(const qword*p){register qword q __asm__("$5");__asm__("lq %0,%1":"=r"(q):"m"(*p));return q;}
static inline qword ReadDestination(const U&home){register qword result __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(result):"m"(home.q));return result;}
static inline SO* EmptyFirst(){register SO*first __asm__("$20");__asm__("daddu %0,$zero,$zero":"=r"(first));return first;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Dot(qword a,qword b){qword one,d;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));return d;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword DirectionFromMatrix(const M3&matrix,M3&basis,const U&offset,const U&target){
 register qword row0 __asm__("vf2")=matrix.a,row1 __asm__("vf3")=matrix.b,row2 __asm__("vf4")=matrix.c;
 register qword point __asm__("vf5")=offset.q,result __asm__("vf1");
 basis.a=row0;basis.b=row1;basis.c=row2;
 row0=basis.a;row1=basis.b;row2=basis.c;
 // The native11B830 leaves its full row0 inVF1 before its final partialXYZ cross.
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(result):"j"(row0),"j"(row1),"j"(row2),"j"(point));
 register qword destination __asm__("vf5")=target.q;
 __asm__("vadd.xyzw %0,%1,%0":"+j"(result):"j"(destination));
 return result;
}
static inline void State(SO*p,int state){VTE*v=p->vt;((void(*)(void*,int))v[76].fn)((char*)p+v[76].delta,state);}
static inline void Reset(SO*p){VTE*v=p->vt;((void(*)(void*))v[8].fn)((char*)p+v[8].delta);}
static inline void Parent(SO*p,SO*parent){VTE*v=p->vt;((void(*)(void*,SO*))v[39].fn)((char*)p+v[39].delta,parent);}
static inline void Velocity(SO*p,qword velocity){VTE*v=p->vt;((void(*)(void*,qword))v[35].fn)((char*)p+v[35].delta,velocity);}
static inline qword NormalizeOr(qword value,qword fallback) {
    register qword vector __asm__("vf2")=value;
    register qword length __asm__("vf1");
    register qword one __asm__("vf4");
    register qword result __asm__("vf1");
    float scalar;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(length),"=&j"(one) : "j"(vector));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(length) : "j"(length));
    __asm__("mtc1 %1,%0" : "=f"(scalar) : "r"(length));
    if(scalar<0.0001f) result=fallback;
    else __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(result) : "j"(length),"j"(vector));
    return result;
}
static inline qword Perpendicular(const U&target,const U&start,const qword*up){
 register qword first __asm__("vf1")=target.q,second __asm__("vf2")=start.q,delta __asm__("vf3");
 __asm__("vsub.xyzw %0,%1,%2":"=j"(delta):"j"(first),"j"(second));
 register qword axis __asm__("vf1")=ReadVU(up);
 register qword projection __asm__("vf2"),one __asm__("vf4");
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(projection),"=&j"(one):"j"(delta),"j"(axis));
 __asm__("vmulx.xyzw %0,%1,%0x\n\tvsub.xyzw %0,%2,%0":"+j"(projection):"j"(axis),"j"(delta));
 return projection;
}
SO*func_001C2EF0(OWNER*p,int count){
 WORK work;work.count=count;const qword*up=&D_002A2DC0;
 int index=0;SO*first=EmptyFirst();
 for(;index<work.count;){
  SO*node;
  if(index==0)node=p->first;else{node=func_001CB250(p->factory,0);if(node && func_00132B10(node,0x5A))State(node,2);}
  if(!node)break;
  if(!first)first=node;
  work.start.q=p->source->position;
  qword targetValue=func_001A62E8(func_001C4840(D_003DD490));
  register ANGLE_PAGE*anglePage __asm__("$2");
  __asm__("sq %2,%0\n\tlui %1,%%hi(%3)":"=m"(work.target.q),"=r"(anglePage):"r"(targetValue),"i"(&D_002C0CF0));
  register RANGE*angleRange __asm__("$2");
  __asm__("addiu %0,%1,%%lo(%2)":"=r"(angleRange):"r"(anglePage),"i"(&D_002C0CF0));
  float angle=func_0011D448(D_002C0CF0.low,angleRange->high);
  qword sampledOffset=func_0011E1A0(angle,func_0011D448(D_002C0CF8.low,D_002C0CF8.high),-75.0f);
  register M3*matrixOutput __asm__("$4");
  __asm__("sq %2,%0\n\tla %1,%a3":"=m"(work.offset.q),"=r"(matrixOutput):"r"(sampledOffset),"p"(&work.matrix));
  qword perpendicular=Perpendicular(work.target,work.start,up);
  qword direction=NormalizeOr(perpendicular,ReadFallback(&D_002A2DA0));
  func_0011B830(matrixOutput,direction,ReadGPR(up));
  work.destination.q=DirectionFromMatrix(work.matrix,work.basis,work.offset,work.target);
  qword acceleration=D_002C0D60;
  float duration=func_0011D448(D_002C0CE0.low,D_002C0CE0.high);
  qword velocity=func_001D69F0(work.start.q,ReadDestination(work.destination),acceleration,duration);
  if(func_00132B10(node,0x5A)){
   float lifetime;
   if(func_00132B10(node,0x5B)||func_00132B10(node,0x5D))lifetime=(float)index*D_002C0CEC;
   else lifetime=D_002A76E8;
   func_001C6BD0(node,p->source->position,velocity,(float)index*D_002C0CE8,lifetime);
  }else{Reset(node);Parent(node,p->source);Velocity(node,velocity);}
  ++index;
 }
 func_001C2DB8(p);return first;
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char launch_layout[(sizeof(U)==16 && sizeof(M3)==0x30 && sizeof(VTE)==8 && sizeof(RANGE)==8 && sizeof(WORK)==0xB0 && OFF(SO,vt)==0xC && OFF(SO,position)==0x70 && OFF(OWNER,source)==0x150 && OFF(OWNER,factory)==0x154 && OFF(OWNER,first)==0x158 && OFF(RANGE,low)==0 && OFF(RANGE,high)==4 && OFF(WORK,basis)==0 && OFF(WORK,matrix)==0x30 && OFF(WORK,count)==0x60 && OFF(WORK,start)==0x70 && OFF(WORK,target)==0x80 && OFF(WORK,offset)==0x90 && OFF(WORK,destination)==0xA0)?1:-1];

typedef char target_angle_page_layout[(OFF(ANGLE_PAGE,range)==0xCF0 && sizeof(ANGLE_PAGE)==0xCF8)?1:-1];
