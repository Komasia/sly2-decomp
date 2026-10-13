// Follow the sampled target using Hermite velocity and lifetime spin.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; }; struct M4 { qword r[4]; };
union U { qword q; float f; };
struct X {char pad[0x60];void *data;};
struct S {char pad[0x14];float start,duration;X *x;char pad20[0x40-0x20];M3 mat;qword pos,prev,vel,accel;char padB0[0xF0-0xB0];qword axis;float angle;};
extern struct CLOCK {float t,dt;} D_002DDED0;
extern "C" {
void func_002309E8(void*,int,M4*,int,float);
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,int);
M3 func_0011B500(qword,float);
void func_001CFE88(S*);
}
static inline qword Bc(float f) {U u;qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));u.q=r;return u.q;}
static inline qword ToVu(qword v) {qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword s){__asm__("vmulx.xyzw %0,%0,%1x":"+j"(a):"j"(s));return a;}
static inline qword Blend(qword d,qword v,qword a,qword s1,qword s2,qword s3){__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddax.xyzw $ACC,%0,%4x\n\tvmaddx.xyzw %0,%2,%5x":"+j"(v):"j"(d),"j"(a),"j"(s1),"j"(s2),"j"(s3));return v;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline M3 Mul(const M3 &a,const M3 &b) return r {
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[1]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[2]));
}
void func_001CFE88(S *p) {
 CLOCK *clock=&D_002DDED0;
 if(clock->t<p->start)return;
 M4 m;
 M3 spin;
 p->prev=p->pos;
 float remain=Max(clock->dt,p->start+p->duration-clock->t);
 func_002309E8(p->x->data,0,&m,0,remain);
 qword v=p->vel,vvu=ToVu(v);
 qword delta=Sub(m.r[3],p->pos);
 qword w2=Bc(-0.5f),w1=Bc(1.5f/remain),w3=Bc(0.25f),dt=Bc(remain);
 qword endvel=Blend(delta,vvu,Scale(p->accel,dt),w1,w2,w3);
 func_00117120(remain,clock->dt,1.0f,p->pos,v,m.r[3],endvel,&p->pos,&p->vel,0);
 spin=func_0011B500(p->axis,p->angle*remain/p->duration);
 p->mat=Mul(spin,*(M3*)&m);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char follow_layout[(sizeof(qword)==16 && sizeof(M3)==0x30 && sizeof(M4)==0x40 && sizeof(U)==16 && OFF(CLOCK,t)==0 && OFF(CLOCK,dt)==4 && OFF(X,data)==0x60 && OFF(S,start)==0x14 && OFF(S,duration)==0x18 && OFF(S,x)==0x1C && OFF(S,mat)==0x40 && OFF(S,pos)==0x70 && OFF(S,prev)==0x80 && OFF(S,vel)==0x90 && OFF(S,accel)==0xA0 && OFF(S,axis)==0xF0 && OFF(S,angle)==0x100)?1:-1];
