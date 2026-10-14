typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M4 {qword a,b,c,d;};
struct S {char pad[0xA0];struct M4 mat;int mode;char padE4[4];int n;float *times;float *dist;qword *v;char padF8[0x140-0xF8];qword *in,*out;};
void func_00231368(struct S*);
static inline qword Move(qword a){qword r;__asm__ volatile("vmove.xyzw %0,%1":"=j"(r):"j"(a));return r;}
static inline qword Point(qword m0,qword m1,qword m2,qword m3,qword a) {qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m0),"j"(m1),"j"(m2),"j"(m3),"j"(a));return r;}
static inline qword Dir(qword m0,qword m1,qword m2,qword a) {__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m0),"j"(m1),"j"(m2));return a;}
static inline qword Bc(float f){union U u;qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));u.q=r;return u.q;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Max(qword a,qword b){__asm__ volatile("vmax.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Min(qword a,qword b){__asm__ volatile("vmini.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
void func_001E7BB8(struct S *p,qword *lo,qword *hi) {
 qword m0,m1,m2,m3,max,min,prev;
 int i;
 func_00231368(p);
 {struct M4 *m=&p->mat;m3=m->d;m1=m->b;m2=m->c;m0=m->a;}
 max=Point(m0,m1,m2,m3,p->v[0]);min=Move(max);
 if(p->mode==0) {
  {qword a=Move(m0),b=Move(m1),c=Move(m2),d=Move(m3);
  for(i=1;i<p->n;i++) {
   qword cur=Point(a,b,c,d,p->v[i]);
   max=Max(max,cur);min=Min(min,cur);
  }}
 } else {
  prev=Move(max);
  {qword r0=Move(m0),r1=Move(m1),r2=Move(m2);
  for(i=0;i<p->n-1;i++) {
   qword old=Move(prev);
   float dt=p->times[i+1]-p->times[i];
   qword plus,minus;
   prev=Point(r0,r1,r2,m3,p->v[i+1]);
   plus=Bc(dt*0.333333343f);minus=Bc(dt*-0.333333343f);
   {qword a=AddScaled(old,Dir(r0,r1,r2,p->out[i]),plus);
    max=Max(max,a);min=Min(min,a);}
   {qword b=AddScaled(prev,Dir(r0,r1,r2,p->in[i+1]),minus);
    max=Max(max,b);min=Min(min,b);}
   min=Min(min,prev);max=Max(max,prev);
  }}
 }
 *lo=min;*hi=max;
}
