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
struct WORK {struct DLI it;union U lo,hi,scratch,scale;};
static inline void SetYZLo(float*p,float f){float*address=p;__asm__("swc1 %3,4(%2)\n\tswc1 %3,8(%2)":"=m"(p[1]),"=m"(p[2]):"r"(address),"f"(f));}
static inline void SetYZHi(float*p,float f){float*address=p;__asm__("swc1 %3,4(%2)\n\tswc1 %3,8(%2)":"=m"(p[1]),"=m"(p[2]):"r"(address),"f"(f));}
static inline void Growth(union U*value,float size){__asm__("swc1 %3,%0\n\tswc1 %3,%1\n\tswc1 %3,%2":"=m"(value->f[0]),"=m"(value->f[2]),"=m"(value->f[1]):"f"(size));}
static inline void StoreCenter(struct S*p,qword center){__asm__("sqc2 %1,%0":"=m"(p->center.q):"j"(center));}
static inline void Init(struct DLI*i,struct DL*l){i->list=l;i->next=(void**)l;i->offset=l->offset;i->link=D_002DD2FC;}
static inline void*Next(struct DLI*i){void*p=*i->next;i->next=(void**)((char*)p+i->offset);return p;}
static inline qword Min(qword a,qword b){__asm__("vmini.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Max(qword a,qword b){__asm__("vmax.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Broadcast(float f,union U*value){register qword q __asm__("vf2");__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));value->q=q;return value->q;}
static inline qword Mid(qword a,qword b,qword k){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));return r;}
static inline qword Length(qword a){register qword d __asm__("vf1");register qword one __asm__("vf2");__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return d;}
static inline void StoreX(float*p,qword q){__asm__("sw %1,%0":"=m"(*p):"r"(q));}
void func_001CDF88(struct S*p){
 struct WORK work;
 struct S*q;
 Init(&work.it,&p->dl);
 {float f=D_002A77D0;SetYZLo(work.lo.f,f);work.lo.f[0]=f;}
 {float f=D_002A77D4;SetYZHi(work.hi.f,f);work.hi.f[0]=f;}
 D_002DD2FC=&work.it;
 while((q=Next(&work.it))!=0){
  if(D_002DDED0.t>=q->time)q->vt[4].fn((char*)q+q->vt[4].delta);
  work.lo.q=Min(work.lo.q,Min(q->a,q->b));
  work.hi.q=Max(work.hi.q,Max(q->a,q->b));
 }
 if(p->size!=0){Growth(&work.scratch,p->size);work.lo.q=Sub(work.lo.q,work.scratch.q);work.hi.q=Sub(work.hi.q,work.scratch.q);}
 if(p->vt){

  register qword low __asm__("vf5")=work.lo.q;register qword high __asm__("vf3")=work.hi.q;qword k=Broadcast(.5f,&work.scale);
  {register qword middle __asm__("vf4")=Mid(low,high,k);work.scratch.q=middle;}
  p->lo.q=low;p->hi.q=high;
  StoreX(&p->radius,Length(Sub(work.scratch.q,high)));
  StoreCenter(p,work.scratch.q);
  func_001F4B58(p);
 }
 D_002DD2FC=work.it.link;
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char bounds_layout[(sizeof(qword)==16 && sizeof(union U)==16 && sizeof(struct DL)==12 && sizeof(struct DLI)==16 && sizeof(struct VTE)==8 && OFF(struct DLI,list)==0 && OFF(struct DLI,next)==4 && OFF(struct DLI,offset)==8 && OFF(struct DLI,link)==12 && OFF(struct S,time)==0x14 && OFF(struct S,a)==0x70 && OFF(struct S,b)==0x80 && OFF(struct S,vt)==0xEC && OFF(struct S,size)==0x154 && OFF(struct S,dl)==0x15C && OFF(struct S,lo)==0x170 && OFF(struct S,hi)==0x180 && OFF(struct S,center)==0x190 && OFF(struct S,radius)==0x1A0)?1:-1];

typedef char native_work_layout[(sizeof(struct WORK)==0x50 && OFF(struct WORK,it)==0 && OFF(struct WORK,lo)==0x10 && OFF(struct WORK,hi)==0x20 && OFF(struct WORK,scratch)==0x30 && OFF(struct WORK,scale)==0x40)?1:-1];
