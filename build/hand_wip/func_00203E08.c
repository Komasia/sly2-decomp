typedef int qword __attribute__((mode(TI)));
typedef struct {qword a[4];} M4;
union V {qword q;float f[4];};
struct X {char pad40[0x40];M4 m;};
struct B {union V *v;};
struct M {struct X *px;char pad4[0xC];struct B *pb;char pad14[8];int count;char pad20[0x5C];union V *points;};
struct S {char pad258[0x258];struct M *pm0,*pm1;};
struct CLK {float time,dt;};
extern struct CLK D_002DDED0;
extern float D_002C3C68[];
M4 func_0011C318(M4 *);
M4 *func_0011C168(M4 *,M4 *,M4 *);
float func_0011D018(float,float,float,float *,float *);
void func_00203E08(struct S *p)
{
    M4 m;
    union V v;
    M4 mm,mi;
    M4 *pmm,*pmi;
    union V *goal,*old,*velocity;
    int i,j;
    struct CLK *clock;
    float *pv;
    float *pt,*ps,*pd;
    if(!p->pm0 || !p->pm1)return;
    goal=p->pm1->points;
    old=p->pm0->points;
    velocity=p->pm0->pb->v;
    pmi=&mi;pmm=&mm;
    mi=func_0011C318(&p->pm0->px->m);
    func_0011C168(pmm,pmi,&p->pm1->px->m);
    m=mm;
    i=p->pm1->count;
    pv=v.f;
    clock=&D_002DDED0;
    while(--i>=0){
        __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(v.q) : "0"(m.a[0]),"j"(m.a[1]),"j"(m.a[2]),"j"(m.a[3]),"j"(goal->q));
        pt=pv;ps=old->f;pd=velocity->f;
        j=3;
        while(--j>=0){
            float next=func_0011D018(*ps,*pt,clock->dt,D_002C3C68,0);
            *pd=(next-*ps)/clock->dt;
            ++pt;++ps;++pd;
        }
        ++goal;++old;++velocity;
    }
}
