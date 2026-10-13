typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct DL {void*first,*last;int offset;};
struct DLI {struct DL*list;void**next;int offset;struct DLI*link;};
struct VTE {short delta,pad;void(*fn)(void*);};
struct S {char pad[0x14];float time;char pad18[0x70-0x18];qword a,b;char pad90[0xEC-0x90];struct VTE*vt;char padF0[0x154-0xF0];float size;int pad158;struct DL dl;int pad168;union U lo,hi,center;float radius;};
extern struct DLI *D_002DD2FC;
extern struct CLOCK {float t;} D_002DDED0;
extern float D_002A77D0,D_002A77D4;
void func_001F4B58(struct S*);
static inline void Init(struct DLI*i,struct DL*l){i->list=l;i->next=(void**)l;i->offset=l->offset;i->link=D_002DD2FC;D_002DD2FC=i;}
static inline void*Next(struct DLI*i){void*p=*i->next;i->next=(void**)((char*)p+i->offset);return p;}
static inline qword Min(qword a,qword b){__asm__("vmini.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Max(qword a,qword b){__asm__("vmax.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Broadcast(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Mid(qword a,qword b,qword k){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));return r;}
static inline qword Length(qword a){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w":"=j"(d),"=j"(one):"j"(a));__asm__("vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return d;}
static inline void StoreX(float*p,qword q){__asm__("sw %1,%0":"=m"(*p):"r"(q));}
void func_001CDF88(struct S*p){
 struct DLI it;
 union U lo,hi;
 struct S*q;
 Init(&it,&p->dl);
 lo.f[0]=lo.f[1]=lo.f[2]=D_002A77D0;
 hi.f[0]=hi.f[1]=hi.f[2]=D_002A77D4;
 while((q=Next(&it))!=0){
  if(q->time<=D_002DDED0.t)q->vt[4].fn((char*)q+q->vt[4].delta);
  lo.q=Min(lo.q,Min(q->a,q->b));
  hi.q=Max(hi.q,Max(q->a,q->b));
 }
 if(p->size!=0){union U grow;grow.f[1]=grow.f[2]=grow.f[0]=p->size;lo.q=Sub(lo.q,grow.q);hi.q=Sub(hi.q,grow.q);}
 if(p->vt){
  union U mid,scale;
  qword k=Broadcast(.5f);
  scale.q=k;
  mid.q=Mid(lo.q,hi.q,k);
  p->lo=lo;p->hi=hi;
  StoreX(&p->radius,Length(Sub(mid.q,hi.q)));
  p->center=mid;
  func_001F4B58(p);
 }
 D_002DD2FC=it.link;
}
