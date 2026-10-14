typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M4 {qword a,b,c,d;};
struct S {char pad[0xEC];float *times,*dist;qword *v;char padF8[8];struct M4 mat;qword *in,*out;int segment;float lengths[11];};
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,qword*);
static inline float Mul(float a,float b){float r;__asm__("mul.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword PointKept(qword keep,qword m0,qword m1,qword m2,qword m3,qword a){__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(keep):"j"(m0),"j"(m1),"j"(m2),"j"(m3),"j"(a));return keep;}
static inline qword Dir(qword m0,qword m1,qword m2,qword a){qword r;__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m0),"j"(m1),"j"(m2),"j"(a));return r;}
static inline qword DirKept(qword keep,qword m0,qword m1,qword m2,qword a){__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(keep):"j"(m0),"j"(m1),"j"(m2),"j"(a));return keep;}
static inline qword Sub(qword a,qword b) {qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Len(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a),"=&j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
void func_001E5FC8(struct S*p,int i) {
 union U prev,cur,start,end,a,b;
 int j;
 float duration;
 if(i==p->segment)return;
 {qword v0=p->v[i],v1=p->v[i+1],t0=p->out[i],t1=p->in[i+1];
 struct M4 *m=&p->mat;qword m1=m->b,m2=m->c,m3=m->d;
 p->lengths[0]=0;
 {qword m0=p->mat.a;
 b.q=Dir(m0,m1,m2,t1);
 end.q=PointKept(t1,m0,m1,m2,m3,v1);
 start.q=PointKept(b.q,m0,m1,m2,m3,v0);
 a.q=DirKept(v0,m0,m1,m2,t0);
 }}
 duration=p->times[i+1]-p->times[i];
 for(j=0;j<11;j++) {
  func_00117120(duration,Mul((float)j,0.1f)*duration,1.0f,start.q,a.q,end.q,b.q,&cur.q,0,0);
  if(j>0)p->lengths[j]=p->lengths[j-1]+Len(Sub(prev.q,cur.q));
  prev.q=cur.q;
 }
 p->segment=i;
}
