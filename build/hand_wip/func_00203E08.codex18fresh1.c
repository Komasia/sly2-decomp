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
M4 *func_0011C318(M4 *,const M4 *);
M4 *func_0011C168(M4 *,const M4 *,const M4 *);
float func_0011D018(float,float,float,float *,float *);
static __inline__ void CopyMatrix(M4 *destination,const M4 *source) {
    __asm__("lq $a0,%6\n\tlq $v1,%5\n\tlq $a1,%7\n\tlq $v0,%4\n\tsq $v1,%1\n\tsq $a0,%2\n\tsq $a1,%3\n\tsq $v0,%0"
      :"=m"(destination->a[0]),"=m"(destination->a[1]),"=m"(destination->a[2]),"=m"(destination->a[3])
      :"m"(source->a[0]),"m"(source->a[1]),"m"(source->a[2]),"m"(source->a[3]):"a0","v1","a1","v0");
}
void func_00203E08(struct S *input)
{
    void *context=input;
    M4 m;
    union V v;
    M4 mm,mi;
    M4 *pmm,*pmi;
    union V *old;
    register union V *velocity __asm__("$20");
    int i,j;
    register struct M *firstSource __asm__("$3");
    register struct M *secondSource __asm__("$4");
    struct CLK *clock;
    float *pv;
    float *pt,*ps,*pd;
    __asm__("lw %0,%1":"=r"(firstSource):"m"(((struct S*)context)->pm0));
    if(!firstSource)return;
    __asm__("lw %0,%1":"=r"(secondSource):"m"(((struct S*)context)->pm1));
    if(!secondSource)return;
    velocity=firstSource->pb->v;
    pd=secondSource->points->f;
    old=firstSource->points;
    pmi=&mi;pmm=&mm;
    func_0011C318(pmi,&firstSource->px->m);
    func_0011C168(pmm,pmi,&((struct S*)context)->pm1->px->m);
    CopyMatrix(&m,&mm);
    i=((struct S*)context)->pm1->count;
    if(--i>=0){
    pv=v.f;
    clock=&D_002DDED0;
    do{
        register float *nextGoal __asm__("$22");
        int nextIndex=i-1;
        context=old+1;
        __asm__("addiu %0,%1,16":"=r"(nextGoal):"r"(pd));
        __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(v.q) : "0"(m.a[0]),"j"(m.a[1]),"j"(m.a[2]),"j"(m.a[3]),"j"(*(qword*)pd));
        pd=velocity->f;
        __asm__("addiu %0,%0,16":"+r"(velocity));
        pt=pv;ps=old->f;
        j=3;
        while(--j>=0){
            float next=func_0011D018(*ps,*pt,clock->dt,D_002C3C68,0);
            *pd=(next-*ps)/clock->dt;
            ++pt;++ps;++pd;
        }
        pd=nextGoal;old=context;
        i=nextIndex;
    }while(i>=0);
    }
}
