// WIP: geometric cache update; 101/161 instruction differences.
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; } U;
typedef union F { float value; int bits; } F;
struct M4 { U row[4]; };
struct LSG { U position[2],normal[2]; float parameter[2]; int tag48; void *owner; int tag50; void *edge; int tag58; void *next; };
struct MODEL { char pad[0x14]; void *table; };
struct SELECTOR { char pad[0x30]; struct MODEL *model; };
struct P {
    char pad[0x60];void *context;
    char pad64[0x1030-0x64];struct MODEL *model;struct SELECTOR *selector;
    char pad1038[0x18C8-0x1038];int manual;
    char pad18CC[0x18D8-0x18CC];int state;
    int reserved18DC;struct MODEL *other;
};
struct AUX { void *component;char pad4[0xA0-4];U point;char padB0[0x10];float radius0,radius1; };
struct O {char pad[0xA8];struct AUX *aux;};
struct CACHE { void *table;int present;float radius;int reserved;U desired,center,hit0,hit1,end; };
extern U D_002A2DC0;
extern F D_002BF340,D_002BF344;
void *func_0012F938(void*,int);
void func_001300B8(void*,float,struct P*,float,void*,void*,struct M4*,int);
int func_0014C748(qword,float,qword,qword,int,struct LSG*);
static inline qword Scalar2(float f){register int bits __asm__("$2");register qword r __asm__("vf2");__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword Scalar(float f){int bits;qword r;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword Low(void){register int bits __asm__("$2");register qword r __asm__("vf8");__asm__("lw %0,%1":"=r"(bits):"m"(D_002BF340.bits));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword High(void){register int bits __asm__("$2");register qword r __asm__("vf7");__asm__("lw %0,%1":"=r"(bits):"m"(D_002BF344.bits));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword Read(U*v){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(v->q));return r;}
static inline qword AddScaled(qword a,qword b,qword k){register qword r __asm__("vf4");__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=&j"(r):"j"(a),"j"(b),"j"(k));return r;}
static inline qword Offset(qword a,qword b,qword k){__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(k));return a;}
static inline qword Transform(struct M4 *m,U *point){register qword p __asm__("vf6")=point->q;register qword r __asm__("vf3")=m->row[0].q;register qword y __asm__("vf5")=m->row[1].q;register qword z __asm__("vf4")=m->row[2].q;register qword t __asm__("vf2")=m->row[3].q;__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(y),"j"(z),"j"(t),"j"(p));return r;}
static inline qword Difference(qword a,qword b){__asm__("vsub.xyzw %0,%1,%0":"+j"(b):"j"(a));return b;}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline struct MODEL *Select(struct P *p){
    if(!p->manual){
        if(p->state<6)goto standard;
        if(p->state<10)return p->other;
        if(p->state>=14)goto standard;
        if(p->state<12)goto standard;
        return p->other;
standard:return p->selector->model;
    }
    if(p->selector)return p->selector->model;
    return p->model;
}
static inline float Property(void*table,int key,float f){float*r=(float*)func_0012F938(table,key);if(r)f=*r;return f;}
void func_00189C40(struct P*p,void *first,float height,struct O*second,int unused,struct CACHE *cache){
    struct M4 m0;
    U scalar;
    struct M4 m1,m2;
    struct LSG hit;
    U desired;
    struct MODEL *model;
    float offset,zero;
    qword k,position,low,high;
    model=Select(p);
    if(model->table==cache->table)return;
    cache->table=model->table;
    offset=Property(model->table,0x16A,0.0f);
    zero=0.0f;
    func_001300B8(model->table,offset,p,zero,first,p->context,&m0,0);
    k=Scalar2(-height);
    desired.q=AddScaled(m0.row[3].q,D_002A2DC0.q,k);
    scalar.q=k;
    func_001300B8(model->table,offset,p,zero,second,p->context,&m1,0);
    func_001300B8(model->table,offset,p,zero,second->aux->component,p->context,&m2,0);
    position=Transform(&m2,&second->aux->point);
    position=Difference(desired.q,position);
    position=Add(m1.row[3].q,position);
    cache->center.q=position;
    low=Low();
    scalar.q=low;
    high=High();
    scalar.q=high;
    cache->radius=second->aux->radius0+second->aux->radius1+10.0f;
    cache->present=func_0014C748(position,cache->radius,Offset(Read(&desired),D_002A2DC0.q,low),Offset(desired.q,D_002A2DC0.q,high),1,&hit)>0;
    cache->hit0=hit.position[0];
    cache->desired=desired;
    cache->hit1=hit.position[1];
    k=Scalar(-cache->radius);
    cache->end.q=Offset(cache->center.q,D_002A2DC0.q,k);
    scalar.q=k;
}
