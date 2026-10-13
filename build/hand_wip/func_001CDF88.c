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
static inline void SetYZLo(float*p,float f){float*address=p;__asm__("swc1 %3,4(%2)\n\tswc1 %3,8(%2)":"=m"(p[1]),"=m"(p[2]):"r"(address),"f"(f));}
static inline void SetYZHi(float*p,float f){float*address=p;__asm__("swc1 %3,4(%2)\n\tswc1 %3,8(%2)":"=m"(p[1]),"=m"(p[2]):"r"(address),"f"(f));}
static inline void Init(struct DLI*i,struct DL*l){i->list=l;i->next=(void**)l;i->offset=l->offset;i->link=D_002DD2FC;}
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
 {float f=D_002A77D0;SetYZLo(lo.f,f);lo.f[0]=f;}
 {float f=D_002A77D4;SetYZHi(hi.f,f);hi.f[0]=f;}
 D_002DD2FC=&it;
 while((q=Next(&it))!=0){
  if(D_002DDED0.t>=q->time)q->vt[4].fn((char*)q+q->vt[4].delta);
  lo.q=Min(lo.q,Min(q->a,q->b));
  hi.q=Max(hi.q,Max(q->a,q->b));
 }
 if(p->size!=0){union U grow;grow.f[0]=grow.f[2]=grow.f[1]=p->size;lo.q=Sub(lo.q,grow.q);hi.q=Sub(hi.q,grow.q);}
 if(p->vt){
  union U mid,scale;
  register qword low __asm__("vf5")=lo.q;register qword high __asm__("vf3")=hi.q;register qword k __asm__("vf2")=Broadcast(.5f);
  scale.q=k;
  {register qword middle __asm__("vf4")=Mid(low,high,scale.q);mid.q=middle;}
  p->lo.q=low;p->hi.q=high;
  StoreX(&p->radius,Length(Sub(mid.q,high)));
  p->center=mid;
  func_001F4B58(p);
 }
 D_002DD2FC=it.link;
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char bounds_layout[(sizeof(qword)==16 && sizeof(union U)==16 && sizeof(struct DL)==12 && sizeof(struct DLI)==16 && sizeof(struct VTE)==8 && OFF(struct DLI,list)==0 && OFF(struct DLI,next)==4 && OFF(struct DLI,offset)==8 && OFF(struct DLI,link)==12 && OFF(struct S,time)==0x14 && OFF(struct S,a)==0x70 && OFF(struct S,b)==0x80 && OFF(struct S,vt)==0xEC && OFF(struct S,size)==0x154 && OFF(struct S,dl)==0x15C && OFF(struct S,lo)==0x170 && OFF(struct S,hi)==0x180 && OFF(struct S,center)==0x190 && OFF(struct S,radius)==0x1A0)?1:-1];
