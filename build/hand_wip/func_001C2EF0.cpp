typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword a,b,c;};
struct WORK {M3 basis,matrix;int count;U start,target,offset,destination;};
struct VTE {short delta,pad;void(*fn)();};
struct SO {char pad0[0xC];VTE*vt;char pad10[0x70-0x10];qword position;};
struct OWNER {char pad0[0x150];SO*source;void*factory;SO*first;};
struct RANGE {float low,high;};
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
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Dot(qword a,qword b){qword one,d;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));return d;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Root(qword d){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return d;}
static inline float Scalar(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Norm(qword q,qword len){qword r;__asm__ __volatile__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(q),"j"(len));return r;}
static inline qword Dir(M3*m,qword q){qword r;__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m->a),"j"(m->b),"j"(m->c),"j"(q));return r;}
static inline void State(SO*p,int state){VTE*v=p->vt;((void(*)(void*,int))v[76].fn)((char*)p+v[76].delta,state);}
static inline void Reset(SO*p){VTE*v=p->vt;((void(*)(void*))v[8].fn)((char*)p+v[8].delta);}
static inline void Parent(SO*p,SO*parent){VTE*v=p->vt;((void(*)(void*,SO*))v[39].fn)((char*)p+v[39].delta,parent);}
static inline void Velocity(SO*p,qword velocity){VTE*v=p->vt;((void(*)(void*,qword))v[35].fn)((char*)p+v[35].delta,velocity);}
SO*func_001C2EF0(OWNER*p,int count){
 WORK work;work.count=count;const qword*up=&D_002A2DC0;
 int index=0;SO*first=0;
 for(;index<work.count;){
  SO*node;
  if(index==0)node=p->first;else{node=func_001CB250(p->factory,0);if(node && func_00132B10(node,0x5A))State(node,2);}
  if(!node)break;
  if(!first)first=node;
  work.start.q=p->source->position;
  work.target.q=func_001A62E8(func_001C4840(D_003DD490));
  float angle=func_0011D448(D_002C0CF0.low,D_002C0CF0.high);
  work.offset.q=func_0011E1A0(angle,func_0011D448(D_002C0CF8.low,D_002C0CF8.high),-75.0f);
  qword axis=ReadVU(up);
  qword delta=Sub(work.target.q,work.start.q);
  qword perpendicular=Sub(delta,Scale(axis,Dot(delta,axis)));
  qword length=Root(Dot(perpendicular,perpendicular));
  qword direction;
  if(Scalar(length)<0.0001f)direction=D_002A2DA0;else direction=Norm(perpendicular,length);
  func_0011B830(&work.matrix,direction,ReadGPR(up));work.basis=work.matrix;
  work.destination.q=Add(work.target.q,Dir(&work.basis,work.offset.q));
  qword acceleration=D_002C0D60;
  float duration=func_0011D448(D_002C0CE0.low,D_002C0CE0.high);
  qword velocity=func_001D69F0(work.start.q,work.destination.q,acceleration,duration);
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
