typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {qword r[4];M4(){}};
struct SPACE {char pad[0x40];M4 matrix;};
struct PATH;
struct VT {short delta,pad;M4*(*f)(PATH*);};
struct PATH {char pad[0xC];VT*vt;char pad10[0xE8-0x10];int count;char padEC[4];float *distance;U *position;};
struct S {qword force,field10,start,end;SPACE *first,*last;PATH *path;int mode;int field50;U *position,*velocity;float *distance;float damping;};
struct CLOCK {float time,dt;};
extern CLOCK D_002DDED0;
extern qword D_002A2DA0;
extern "C" qword func_0022D348(SPACE*,SPACE*,qword);
extern "C" M4*func_0011C318(M4*,M4*);
extern "C" void func_001E95B0(S*,float);
extern "C" void func_001E6330(PATH*);
extern "C" void func_001E9090(S*);
static inline qword Point(const M4&m,qword a){qword r=m.r[0];
__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m.r[1]),"j"(m.r[2]),"j"(m.r[3]),"j"(a));return r;}
static inline qword ScalarStored(float f,U&out){qword value;__asm__("qmtc2 %2,%0\n\tsqc2 %0,%1":"=&j"(value),"=m"(out.q):"r"(f));return out.q;}
static inline qword Bc(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword AddScaled2(qword a,qword b,qword c,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(b),"j"(c),"j"(s));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sq(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword Sqrt(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float Float(qword a){float r;__asm__("mtc1 %1,%0":"=f"(r):"r"(a));return r;}
static inline float Abs(float a){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(a));return r;}
static inline qword ChainSq(qword a){register qword r __asm__("vf1"),one __asm__("vf3");__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Unit(qword delta,qword length){register qword direction __asm__("vf3");__asm__ volatile("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(direction):"j"(delta),"j"(length));return direction;}
static inline qword ReturnedVelocity(qword bits){register qword result __asm__("vf7");__asm__("qmtc2.ni %1,%0":"=j"(result):"r"(bits));return result;}
void func_001E9090(S*p){
 U scalar;
 M4 inverse;
 U previousPoint;
 typedef char chain_previous_point_extent[(sizeof(previousPoint)==16)?1:-1];
 typedef char chain_previous_point_alignment[(__alignof__(previousPoint)==16)?1:-1];
 qword prev,prevVelocity;
 float dt=D_002DDED0.dt;
 int n;
 int i;
 {
   register SPACE *first __asm__("$3");
   register PATH *path __asm__("$6");
   register M4 *matrix __asm__("$2");
   __asm__("lw %0,%3\n\tlw %1,%4\n\taddiu %2,%0,%5"
      :"=&r"(first),"=&r"(path),"=r"(matrix)
      :"m"(p->first),"m"(p->path),"I"(0x40));
   register qword row0 __asm__("vf5"),row3 __asm__("vf4"),start __asm__("vf3"),row1 __asm__("vf2"),row2 __asm__("vf1");
   register U *destination __asm__("$3");
   __asm__("lqc2 %0,0x40(%6)\n\tlqc2 %1,0x30(%7)\n\tlqc2 %2,%8\n\tlqc2 %3,0x10(%7)\n\tlqc2 %4,0x20(%7)\n\tlw %5,%9"
      :"=j"(row0),"=j"(row3),"=j"(start),"=j"(row1),"=j"(row2),"=r"(destination)
      :"r"(first),"r"(matrix),"m"(p->start),"m"(p->position):"memory");
   register qword point __asm__("vf6");
   __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
      :"+j"(point):"j"(row0),"j"(row1),"j"(row2),"j"(row3),"j"(start));
   n=path->count;
   destination->q=point;
   U *initialVelocity=p->velocity;
   previousPoint.q=point;
   prevVelocity=ReturnedVelocity(func_0022D348(p->first,0,point));
   initialVelocity[0].q=prevVelocity;
 }
 prev=previousPoint.q;
 for(i=1;i<n;i++){
   qword velocity,position;
   register qword delta __asm__("vf2");
   register qword length __asm__("vf1");
   qword direction;
   qword drag=ScalarStored(-p->damping,scalar);
   scalar.q=Bc(dt);
   velocity=AddScaled(p->velocity[i].q,AddScaled(p->force,p->velocity[i].q,drag),scalar.q);
   scalar.q=Bc(dt*.5f);
   position=AddScaled2(p->position[i].q,p->velocity[i].q,velocity,scalar.q);
   delta=Sub(position,prev);
   register qword fallback __asm__("8");
   __asm__("lq %0,%1":"=r"(fallback):"m"(D_002A2DA0));
   length=Sqrt(ChainSq(delta));
   if(Float(length)<.0001f)direction=fallback;else direction=Unit(delta,length);
   {
    float projection=-Float(Dot(Sub(velocity,prevVelocity),direction));
    float distance=Abs(p->distance[i]-p->distance[i-1]);
    scalar.q=Bc(projection);
    prevVelocity=AddScaled(velocity,direction,scalar.q);
    scalar.q=Bc(distance);
    prev=AddScaled(prev,direction,scalar.q);
   }
   p->position[i].q=prev;
   p->velocity[i].q=prevVelocity;
 }
 if(p->mode==2){
  p->position[n-1].q=Point(p->last->matrix,p->end);
  func_001E95B0(p,p->distance[n-2]+Float(Sqrt(Sq(Sub(p->position[n-2].q,p->position[n-1].q)))));
  n=p->path->count;
 }
 {
  PATH *path=p->path;
  VT *entry=&path->vt[31];
  M4 *world=entry->f((PATH*)((char*)path+entry->delta));
  func_0011C318(&inverse,world);
 }
 for(i=0;i<n;i++)p->path->position[i].q=Point(inverse,p->position[i].q);
 func_001E6330(p->path);
}

#define OFF(T,f) ((unsigned)&((T*)0)->f)
typedef char verified_chain_layout_0[(sizeof(qword)==16)?1:-1];
typedef char verified_chain_layout_1[(__alignof__(qword)==16)?1:-1];
typedef char verified_chain_layout_2[(sizeof(void*)==4)?1:-1];
typedef char verified_chain_layout_3[(sizeof(int)==4)?1:-1];
typedef char verified_chain_layout_4[(sizeof(float)==4)?1:-1];
typedef char verified_chain_layout_5[(sizeof(short)==2)?1:-1];
typedef char verified_chain_layout_6[(sizeof(U)==16)?1:-1];
typedef char verified_chain_layout_7[(__alignof__(U)==16)?1:-1];
typedef char verified_chain_layout_8[(OFF(U,q)==0)?1:-1];
typedef char verified_chain_layout_9[(OFF(U,f)==0)?1:-1];
typedef char verified_chain_layout_10[(sizeof(M4)==0x40)?1:-1];
typedef char verified_chain_layout_11[(__alignof__(M4)==16)?1:-1];
typedef char verified_chain_layout_12[(OFF(M4,r)==0)?1:-1];
typedef char verified_chain_layout_13[(sizeof(SPACE)==0x80)?1:-1];
typedef char verified_chain_layout_14[(OFF(SPACE,matrix)==0x40)?1:-1];
typedef char verified_chain_layout_15[(sizeof(VT)==8)?1:-1];
typedef char verified_chain_layout_16[(OFF(VT,delta)==0)?1:-1];
typedef char verified_chain_layout_17[(OFF(VT,pad)==2)?1:-1];
typedef char verified_chain_layout_18[(OFF(VT,f)==4)?1:-1];
typedef char verified_chain_layout_19[(sizeof(PATH)==0xF8)?1:-1];
typedef char verified_chain_layout_20[(OFF(PATH,vt)==0xC)?1:-1];
typedef char verified_chain_layout_21[(OFF(PATH,count)==0xE8)?1:-1];
typedef char verified_chain_layout_22[(OFF(PATH,distance)==0xF0)?1:-1];
typedef char verified_chain_layout_23[(OFF(PATH,position)==0xF4)?1:-1];
typedef char verified_chain_layout_24[(sizeof(S)==0x70)?1:-1];
typedef char verified_chain_layout_25[(__alignof__(S)==16)?1:-1];
typedef char verified_chain_layout_26[(OFF(S,force)==0)?1:-1];
typedef char verified_chain_layout_27[(OFF(S,field10)==0x10)?1:-1];
typedef char verified_chain_layout_28[(OFF(S,start)==0x20)?1:-1];
typedef char verified_chain_layout_29[(OFF(S,end)==0x30)?1:-1];
typedef char verified_chain_layout_30[(OFF(S,first)==0x40)?1:-1];
typedef char verified_chain_layout_31[(OFF(S,last)==0x44)?1:-1];
typedef char verified_chain_layout_32[(OFF(S,path)==0x48)?1:-1];
typedef char verified_chain_layout_33[(OFF(S,mode)==0x4C)?1:-1];
typedef char verified_chain_layout_34[(OFF(S,field50)==0x50)?1:-1];
typedef char verified_chain_layout_35[(OFF(S,position)==0x54)?1:-1];
typedef char verified_chain_layout_36[(OFF(S,velocity)==0x58)?1:-1];
typedef char verified_chain_layout_37[(OFF(S,distance)==0x5C)?1:-1];
typedef char verified_chain_layout_38[(OFF(S,damping)==0x60)?1:-1];
typedef char verified_chain_layout_39[(sizeof(CLOCK)==8)?1:-1];
typedef char verified_chain_layout_40[(OFF(CLOCK,time)==0)?1:-1];
typedef char verified_chain_layout_41[(OFF(CLOCK,dt)==4)?1:-1];
