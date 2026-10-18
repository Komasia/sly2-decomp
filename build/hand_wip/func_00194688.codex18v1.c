typedef int qword __attribute__((mode(TI)));
struct A;
typedef struct { short d; short pad; void (*pfn)(void *, ...); } VTE;
typedef struct { short d; short pad; void (*pfn)(void *, void *, qword *, int, float); } VTE3;
typedef union { VTE v; VTE3 v3; } VTU;
struct A { char pad[0x10]; int x10; char pad1[4]; int x18; int x1c; VTU *vt; };
struct LO { char pad[0x10]; int x10; char pad2[0x38 - 0x14]; float x38; };
typedef struct { struct LO *x0; struct A *x4; float x8; int xc; int x10; float x14; float x18; float x1c; qword x20; } E;
struct Y { char pad[0x18]; int x18; };
struct P {
    char pad[0x2CC]; struct LO *x2cc; char pad1[0x37C - 0x2D0]; struct LO *x37c; char pad2[0x4D4 - 0x380];
    struct LO *x4d4; struct Y *x4d8; char pad3[0xF5C - 0x4DC]; struct LO *xf5c; char pad4[0x1000 - 0xF60];
    int x1000; char pad5[0x18C4 - 0x1004]; struct LO *x18c4; char pad6[0x1F18 - 0x18C8]; struct LO *x1f18;
};
struct CLOCK { float t; float dt; };

#define OFF(T,M) ((unsigned)&((T*)0)->M)
#define CHECK(N,X) typedef char check_##N[(X)?1:-1]
CHECK(pointer,sizeof(void*)==4);
CHECK(word,sizeof(qword)==16);
CHECK(vte,sizeof(VTE)==8);
CHECK(vt3,sizeof(VTE3)==8);
CHECK(actor_priority,OFF(struct A,x10)==0x10);
CHECK(actor_tag,OFF(struct A,x18)==0x18);
CHECK(actor_flags,OFF(struct A,x1c)==0x1c);
CHECK(actor_vt,OFF(struct A,vt)==0x20);
CHECK(lo_test,OFF(struct LO,x10)==0x10);
CHECK(lo_radius,OFF(struct LO,x38)==0x38);
CHECK(record_size,sizeof(E)==0x30);
CHECK(record_lo,OFF(E,x0)==0);
CHECK(record_actor,OFF(E,x4)==4);
CHECK(record_distance,OFF(E,x8)==8);
CHECK(record_priority,OFF(E,xc)==0xc);
CHECK(record_flags,OFF(E,x10)==0x10);
CHECK(record_time,OFF(E,x14)==0x14);
CHECK(record_scalar,OFF(E,x18)==0x18);
CHECK(record_zero,OFF(E,x1c)==0x1c);
CHECK(record_point,OFF(E,x20)==0x20);
CHECK(point_alignment,__alignof__(E)==16);
CHECK(p_2cc,OFF(struct P,x2cc)==0x2cc);
CHECK(p_37c,OFF(struct P,x37c)==0x37c);
CHECK(p_4d4,OFF(struct P,x4d4)==0x4d4);
CHECK(p_4d8,OFF(struct P,x4d8)==0x4d8);
CHECK(p_f5c,OFF(struct P,xf5c)==0xf5c);
CHECK(p_1000,OFF(struct P,x1000)==0x1000);
CHECK(p_18c4,OFF(struct P,x18c4)==0x18c4);
CHECK(p_1f18,OFF(struct P,x1f18)==0x1f18);
CHECK(y_tag,OFF(struct Y,x18)==0x18);
CHECK(clock_time,OFF(struct CLOCK,t)==0);

extern struct CLOCK D_002DDED0;
extern struct P *D_002E1E40;
extern int D_002E1E4C;
extern float D_002BF664;
qword func_001A62E8(void *p);
void func_001AE5A0(void *dst, void *src, unsigned cb);
void *func_002333B4(void *p, int c, unsigned cb);
void *func_002332B8(void *dst, void *src, unsigned cb);
void func_00194688(void *unused, struct P *p, qword pos, struct LO *lo, struct A *incomingA, int n, E *ae)
{
    E e;
    register struct A*a __asm__("$20")=incomingA;
    register int i __asm__("$17");
    register int tag __asm__("$5");
    if (lo->x10) {
        qword q=func_001A62E8(lo);
        register qword returned __asm__("vf2"),input __asm__("vf3");
        register float radiusSquared __asm__("$f1"),distanceSquared __asm__("$f0");
        register unsigned distanceWord __asm__("$3");int outside;
        __asm__("qmtc2.ni %3,%0\n\tlwc1 %1,%4\n\tlqc2 %2,%5":"=j"(returned),"=f"(radiusSquared),"=j"(input):"r"(q),"m"(lo->x38),"m"(pos));
        __asm__("vsub.xyzw $vf1,%0,%3\n\tmul.s %1,%1,%1\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x %0,$vf0,$vf0w\n\tvadday.x $ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,%0,$vf1z\n\tqmfc2.ni %2,$vf1"
         :"+j"(returned),"+f"(radiusSquared),"=r"(distanceWord):"j"(input):"vf1");
        __asm__("mtc1 %1,%0":"=f"(distanceSquared):"r"(distanceWord));
        outside=radiusSquared<distanceSquared;if(outside)return;
    }
    if (lo == p->x4d4) return;
    if (lo == p->x2cc) return;
    if (a->x18 && p->x4d8 && a->x18 == p->x4d8->x18) return;
    if (lo == p->x37c) return;
    if (lo == p->xf5c) return;
    if (p == D_002E1E40) {
        if (lo == p->x18c4) return;
        if (lo == p->x1f18) return;
    }
    if (!(p->x1000 & a->x1c)) return;
    if (D_002E1E4C) {
        if (p->x4d4) return;
        if (p->xf5c) return;
        if (p == D_002E1E40) {
            if (p->x18c4) return;
            if (p->x1f18) return;
        }
    }
    a->vt[2].v.pfn((char *)a + a->vt[2].v.d, p, &e.x18);
    a->vt[3].v3.pfn((char *)a + a->vt[3].v3.d, p, &e.x20, 0, e.x18);
    {
        typedef void(*AdjustDistance)(void*,float*);
        register qword input __asm__("vf2"),difference __asm__("vf1");
        register float*distanceOutput __asm__("$5");register unsigned word __asm__("$2");
        register VTU*vtable __asm__("$3");register int delta __asm__("$4");register AdjustDistance adjust __asm__("$2");
        __asm__("lqc2 %0,%4\n\tori %1,%5,8\n\tlqc2 %2,%6\n\tlw %3,0x10(%7)"
         :"=j"(input),"=r"(distanceOutput),"=j"(difference),"=r"(word):"m"(pos),"p"(&e),"m"(e.x20),"r"(a));
        __asm__("vsub.xyzw %1,%5,%1\n\tlw %2,0x20(%6)\n\tvmul.xyz %1,%1,%1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\tsw %0,%3\n\tvsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tqmfc2.ni %0,%1\n\tmtc1 %0,$f0\n\tswc1 $f0,%4"
         :"+r"(word),"+j"(difference),"=r"(vtable),"=m"(e.xc),"=m"(e.x8):"j"(input),"r"(a):"$f0","vf2");
        __asm__("lh %0,0x20(%2)\n\tlw %1,0x24(%2)":"=r"(delta),"=r"(adjust):"r"(vtable):"memory");
        adjust((char*)a+delta,distanceOutput);
    }
    if (D_002BF664 < e.x8) return;
    __asm__("lw %0,%1":"=r"(tag):"m"(a->x18));
    {
        register E*cursor __asm__("$4");register int remaining __asm__("$6");
        register unsigned word __asm__("$3");register struct A*present __asm__("$2");
        if(!tag)goto ranking_sort;
        i=0;
        if(n<=0)goto ranking_sort;
        present=ae->x4;word=(unsigned)ae;
        if(!present)goto ranking_sort;
        cursor=ae;remaining=n-1;
ranking_scan:
        __asm__("lw $2,4(%0)\n\tlw %0,0x18($2)":"+r"(word)::"$2","memory");
        if((int)word==tag){
                register int stride __asm__("$16"),offset __asm__("$2");
                register E*entry __asm__("$4");register float incomingDistance __asm__("$f1"),existingDistance __asm__("$f0");
                __asm__("li %0,0x30\n\tlwc1 %1,%7\n\tmult %2,%5,%0\n\taddu %3,%2,%6\n\tlwc1 %4,8(%3)"
                 :"=&r"(stride),"=f"(incomingDistance),"=r"(offset),"=r"(entry),"=f"(existingDistance):"r"(i),"r"(ae),"m"(e.x8):"hi","lo","memory");
                if (incomingDistance < existingDistance) {
                    register void*end __asm__("$4");register int zero __asm__("$5"),bytes __asm__("$6");
                    func_001AE5A0(entry, (char*)ae+(offset+0x30), remaining * stride);
                    __asm__("mult $2,%3,%4\n\tdaddu %1,$zero,$zero\n\tli %2,0x30\n\taddu %0,$2,%5"
                     :"=r"(end),"=r"(zero),"=r"(bytes):"r"(n),"r"(stride),"r"(ae):"$2","hi","lo");
                    func_002333B4((char*)end-0x30,zero,bytes);
                    __asm__ __volatile__("mult $2,%0,%1\n\tlwc1 $f0,%3\n\taddu $3,$2,%2\n\tswc1 $f0,-0x28($3)"::"r"(n),"r"(stride),"r"(ae),"m"(D_002BF664):"$2","$3","$f0","hi","lo","memory");
                    goto ranking_sort;
                }
                return;
        }
        ++i;++cursor;--remaining;
        if(i>=n)goto ranking_sort;
        __asm__("lw %0,4(%1)":"=r"(present):"r"(cursor):"memory");
        word=(unsigned)cursor;
        if(present)goto ranking_scan;
    }
ranking_sort:
    i = n;
    {
        E*pe=ae+i;--pe;
        do {
            int previous=pe->xc;
            --i;
            if(e.xc<previous){++i;break;}
            if(previous==e.xc && pe->x8<e.x8){++i;break;}
            --pe;
        }while(i!=0);
    }
    if (i == n) return;
    {
        register int stride __asm__("$16")=0x30;
        register void*destination __asm__("$4"),*source __asm__("$5");register int bytes __asm__("$6");
        register unsigned owner __asm__("$16");
        __asm__("subu %2,%3,%4\n\tmult $2,%4,%5\n\tmult %2,%2,%5\n\taddu %0,$2,%6\n\taddiu %2,%2,-0x30\n\tdaddu %1,%0,$zero"
         :"=r"(destination),"=r"(source),"=r"(bytes):"r"(n),"r"(i),"r"(stride),"r"(ae):"$2","hi","lo");
        func_002332B8((char*)destination+0x30,source,bytes);
        owner=(unsigned)stride;
        __asm__ __volatile__("lui $3,%%hi(%6)\n\tmult $2,%1,%0\n\tlwc1 $f0,%%lo(%6)($3)\n\tsw %3,0(%5)\n\tsw %4,4(%5)\n\tswc1 $f0,0x14(%5)\n\taddu %0,$2,%2\n\tsw $zero,0x10(%5)\n\tsw $zero,0x1C(%5)\n\tlq $3,0(%5)\n\tlq $4,0x10(%5)\n\tlq $2,0x20(%5)\n\tsq $3,0(%0)\n\tsq $2,0x20(%0)\n\tsq $4,0x10(%0)"
         :"+r"(owner):"r"(i),"r"(ae),"r"(lo),"r"(a),"p"(&e),"i"(&D_002DDED0):"$2","$3","$4","$f0","hi","lo","memory");
    }
}
