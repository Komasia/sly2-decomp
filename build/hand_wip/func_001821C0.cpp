
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];int i[4];} U;
struct M3 {qword r[3];};
struct M4 {U r[4];};
struct N {qword pos,dir;char pad20[0x50-0x20];float lateral,roll;char pad58[8];N*next;};
struct E {char pad[0x10];N*first;char pad14[0x1C];};
struct P {char pad[0x1C4];void*model;int count;E entries[1];};
extern qword D_002A2DC0;
extern "C" void func_001F3C70(P*);
extern "C" M3 func_0011B830(qword,qword);
extern "C" M3 func_0011B500(qword,float);
extern "C" qword*func_00256D18(qword*,qword);
extern "C" void func_001A5EE8(void*,M4*,float,float);
extern "C" float fabsf(float);
static inline qword Load(const qword*p){register qword r __asm__("vf7");__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScaled(qword a,qword b,float f){qword k;U u;__asm__("qmtc2.ni %1,%0":"=j"(k):"r"(f));u.q=k;__asm__("vadda.xyzw ACC,$vf0,%0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(k));return a;}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}

extern "C" void func_001821C0(P*p){
 int i;M3 m;M4 mm;qword pos;
 func_001F3C70(p);
 if(!p->model)return;
 i=0;if(i>=p->count)return;
next_entry:{
  N*n=((N**)((int)p+i*0x30))[0x1DC/4];
  while(n){M4*pm=&mm;
   pos=Load(&n->pos);
   m=func_0011B830(n->dir,D_002A2DC0);
   if(1.0f<fabsf(n->lateral))pos=AddScaled(pos,Cross(D_002A2DC0,n->dir),n->lateral);
   {float roll=n->roll;register float epsilon __asm__("$f1")=0.01f;if(epsilon<fabsf(roll))m=Mul(m,func_0011B500(D_002A2DC0,roll));}
   func_00256D18(&mm.r[3].q,pos);
   pm->r[0].q=m.r[0];pm->r[1].q=m.r[1];pm->r[2].q=m.r[2];
   mm.r[0].i[3]=mm.r[1].i[3]=mm.r[2].i[3]=0;
   pm->r[3].f[3]=1.0f;
   func_001A5EE8(p->model,pm,1.0f,1.0f);
   n=n->next;
  }
 }
 if(++i<p->count)goto next_entry;
}
