typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M4 {qword a,b,c,d;};
struct S {char pad[0xA0];struct M4 mat;int mode;char padE4[4];int n;float *times;float *dist;qword *v;char padF8[0x140-0xF8];qword *in,*out;};
void func_00231368(struct S*);
static inline qword Move(qword a){qword r;__asm__ volatile("vmove.xyzw %0,%1":"=j"(r):"j"(a));return r;}
static inline qword InitialPoint(qword m0,qword m1,qword m2,qword m3,qword point){
 register qword value __asm__("vf5");
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(value):"j"(m0),"j"(m1),"j"(m2),"j"(m3),"j"(point));return value;
}
static inline qword PointInput(qword m0,qword m1,qword m2,qword m3,qword point){
 __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddaz.xyz $ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(point):"j"(m0),"j"(m1),"j"(m2),"j"(m3));return point;
}
static inline qword PointKept(qword value,qword m0,qword m1,qword m2,qword m3,qword point){
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(value):"j"(m0),"j"(m1),"j"(m2),"j"(m3),"j"(point));return value;
}
static inline qword Dir(qword m0,qword m1,qword m2,qword a) {__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m0),"j"(m1),"j"(m2));return a;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Max(qword a,qword b){__asm__ volatile("vmax.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Min(qword a,qword b){__asm__ volatile("vmini.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword PlusBc(float f){
 union U u;register qword r __asm__("vf3");
 __asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));u.q=r;return u.q;
}
static inline qword MinusBc(float f){
 union U u;register qword r __asm__("vf2");
 __asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));u.q=r;return u.q;
}
static inline qword *Points(const struct S*p){
 register qword *r __asm__("$5");
 __asm__("lw %0,%1":"=r"(r):"m"(p->v));return r;
}
void func_001E7BB8(struct S *p,qword *lo,qword *hi) {
 qword m0,m1,m2,m3,max,min,prev;
 int i;
 func_00231368(p);
 {
 qword *points=Points(p);
 {register struct M4 *m __asm__("$2")=&p->mat;
 __asm__("lqc2 %0,0x30(%8)\n\tlqc2 %1,0x10(%8)\n\tlqc2 %2,0x20(%8)\n\tlqc2 %3,%7":"=j"(m3),"=j"(m1),"=j"(m2),"=j"(m0):"m"(m->d),"m"(m->b),"m"(m->c),"m"(p->mat.a),"r"(m));
 }
 max=InitialPoint(m0,m1,m2,m3,points[0]);min=Move(max);
 if(p->mode==0) {
  {qword a=Move(m0),b=Move(m1),c=Move(m2),d=Move(m3);
  for(i=1;i<p->n;i++) {
   qword cur=PointInput(a,b,c,d,points[i]);
   max=Max(max,cur);min=Min(min,cur);
  }}
 } else {
  prev=Move(max);
  {qword r0=Move(m0),r1=Move(m1),r2=Move(m2);
  for(i=0;i<p->n-1;i++) {
   qword old=Move(prev);
   float dt=p->times[i+1]-p->times[i];
   qword plus,minus;
   prev=PointKept(prev,r0,r1,r2,m3,points[i+1]);
   plus=PlusBc(dt*0.333333343f);minus=MinusBc(dt*-0.333333343f);
   {qword a=AddScaled(old,Dir(r0,r1,r2,p->out[i]),plus);
    max=Max(max,a);min=Min(min,a);}
   {qword b=AddScaled(prev,Dir(r0,r1,r2,p->in[i+1]),minus);
    max=Max(max,b);min=Min(min,b);}
   min=Min(min,prev);max=Max(max,prev);
  }}
 }
 *lo=min;*hi=max;
 }
}
