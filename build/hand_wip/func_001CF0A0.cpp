typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M3 {U r[3];M3(){} M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};struct M4 {qword a,b,c,d;};
struct PHYS {qword accel,axis;float rate,scale;};
struct S {char pad[0x40];M3 mat;qword pos,prev,vel;PHYS phys;qword omega;float gE0,gE4;};
extern struct CLOCK {float time;union{float dt;int dtbits;};} D_002DDED0;
extern "C" {
int func_001CF010(qword);int func_001CEFC8(qword);int func_001CF058(qword);
M3 func_0011B500(qword,float);M4 *func_0015BFD8(M4*,PHYS*);
void func_001CF0A0(S*);
}
static inline qword Bc(float f){U u;qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));u.q=q;return q;}
static inline qword BcBits(int f){U u;qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));u.q=q;return q;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Sq(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Sqrt(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float Float(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline U Norm(qword a,float f) return result {qword r,l=Bc(f);__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(l),"j"(a));result.q=r;}
static inline qword Dir(const M3 &a,qword b){qword r;__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b));return r;}
static inline M3 Mul(const M3 &a,const M3 &b) return r {
__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b.r[0].q));
__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b.r[1].q));
__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b.r[2].q));
}
static inline qword Point(const M4 &m,qword a){qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.a),"j"(m.b),"j"(m.c),"j"(m.d),"j"(a));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
void func_001CF0A0(S*p){
 if(!func_001CF010(p->omega)) {
  qword omega=Scale(p->omega,Bc(p->gE4*D_002DDED0.dt+1.0f));
  p->omega=omega;
  float length=Float(Sqrt(Sq(omega)));
  if(0.0001f<length){
   U axis=Norm(omega,length);
   M3 rot;
   rot=func_0011B500(axis.q,length*D_002DDED0.dt);
   p->mat=Mul(rot,p->mat);
  }
 }
 p->prev=p->pos;
 int moving=0;
 if(!func_001CEFC8(p->vel) || !func_001CF058(p->phys.accel))moving=1;
 if(moving){
  M4 mat;
  func_0015BFD8(&mat,&p->phys);
  qword v=Point(mat,p->vel);
  p->vel=v;
  p->pos=AddScaled(p->pos,v,BcBits(D_002DDED0.dtbits));
 }
}
