// Rebuild mesh samples in path-local coordinates.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword a,b,c;};
struct M4 {qword a,b,c,d;};
struct PART {char pad[20];};
struct MODEL {char pad40[0x40];M4 matrix;};
struct ME {int n;MODEL *model;char pad8[32];};
struct E {int n;char pad4[8];qword *src;char pad10[12];U *dst;};
struct NODE {PART *part;int n;E *entries;NODE *next;};
struct RESET {
 void*owner;
 char pad4[0xC];
 U zero;
 float limit;
 char pad24[0x18];
 PART*parts;
 ME*models;
 void*positions;
};
struct P {
 char pad80[0x80];
 RESET reset;
 char padD0[0xC];
 NODE*head;
 char padE0[0x70];
 void*path;
};
struct AL {int cb,align;AL(int n,int a){cb=n;align=a;}};
extern char D_002C44F0[];
extern "C" {
void func_001F36A8(P*);
M3 *func_001A6318(P*);
void func_0016EF00(void*,int);
void CopyAb(void*,const void*,unsigned) __asm__("CopyAb__FPvT0Ui");
void *func_001AE1D0(AL*);
void func_001E6F60(void*,qword,void*,qword*,qword*,float*,float*);
M3 *func_0011B830(M3*,qword,qword);
void func_001E9858(P*);
}
static inline void *Alloc(const AL&a){return func_001AE1D0((AL*)&a);}
static inline qword Point(M4*m,qword a) {
 qword r=m->a;
 __asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddaz.xyz ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w"
    :"+j"(r):"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));
 return r;
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Transform(M3*m,qword a){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m->a),"j"(m->b),"j"(m->c));return a;}
static inline M3 Transpose(const M3&m) return r {
 qword low,high,zlow,zhigh;
 __asm__("pextlw %0,%2,%1":"=r"(low):"r"(m.a),"r"(m.b));
 __asm__("pextuw %0,%2,%1":"=r"(high):"r"(m.a),"r"(m.b));
 __asm__("pextlw %0,$zero,%1":"=r"(zlow):"r"(m.c));
 __asm__("pextuw %0,$zero,%1":"=r"(zhigh):"r"(m.c));
 __asm__("pcpyld %0,%2,%1":"=r"(r.a):"r"(low),"r"(zlow));
 __asm__("pcpyud %0,%1,%2":"=r"(r.b):"r"(low),"r"(zlow));
 __asm__("pcpyld %0,%2,%1":"=r"(r.c):"r"(high),"r"(zhigh));
}
void func_001E9858(P*p){
 qword buf[128];
 U hit,dir;
 M3 basis;
 float distance;
 U axis;
 func_001F36A8(p);
 if(p->path && p->head){
  axis.q=func_001A6318(p)->c;
  NODE *node;
  for(node=p->head;node;node=node->next){
   int modelIndex=node->part-p->reset.parts;
   MODEL *model=p->reset.models[modelIndex].model;
   p->reset.models[modelIndex].model=(MODEL*)D_002C44F0;
   func_0016EF00(&p->reset,modelIndex);
   int j;
   for(j=0;j<node->n;j++){
    E*e=&node->entries[j];
    CopyAb(buf,e->src,e->n*16);
    U*out=(U*)Alloc(AL(e->n*16,16));e->dst=out;
    qword *src=buf;
    int k;
    for(k=0;k<e->n;k++){
     U point;point.q=Point(&model->matrix,*src);
     func_001E6F60(p->path,point.q,0,&hit.q,&dir.q,&distance,0);
     func_0011B830(&basis,dir.q,axis.q);
     M3 inverse=Transpose(basis);
     out->q=Transform(&inverse,Sub(point.q,hit.q));
     out->f[3]=distance;
     src++;out++;
    }
   }
  }
 }
}
