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
static inline qword Point(const M4&m,qword a){qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]),"j"(m.r[3]),"j"(a));return r;}
static inline qword Bc(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword AddScaled2(qword a,qword b,qword c,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(b),"j"(c),"j"(s));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sq(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword Sqrt(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float Float(qword a){float r;__asm__("mtc1 %1,%0":"=f"(r):"r"(a));return r;}
static inline qword Norm(qword a,qword l){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(l));return r;}
static inline float Abs(float a){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(a));return r;}
void func_001E9090(S*p){
 U scalar;
 M4 inverse;
 qword prev,prevVelocity;
 float dt=D_002DDED0.dt;
 int n=p->path->count;
 int i;
 prev=Point(p->first->matrix,p->start);
 p->position[0].q=prev;
 U *initialVelocity=p->velocity;
 prevVelocity=func_0022D348(p->first,0,prev);
 initialVelocity[0].q=prevVelocity;
 for(i=1;i<n;i++){
   qword velocity,position,delta,length,direction;
   scalar.q=Bc(-p->damping);
   qword drag=scalar.q;
   scalar.q=Bc(dt);
   velocity=AddScaled(p->velocity[i].q,AddScaled(p->force,p->velocity[i].q,drag),scalar.q);
   scalar.q=Bc(dt*.5f);
   position=AddScaled2(p->position[i].q,p->velocity[i].q,velocity,scalar.q);
   delta=Sub(position,prev);
   length=Sqrt(Sq(delta));
   if(Float(length)<.0001f)direction=D_002A2DA0;else direction=Norm(delta,length);
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
