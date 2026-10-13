// WIP: 21/71 differences; load/readback ordering and final call delay slot.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } MATRIX4;
struct A { MATRIX4 m; char pad[0x30]; qword v70; char pad2[0x20]; void *pA0; };
struct B { char pad[0x40]; MATRIX4 m; };
struct S { int x0; struct A *p4; struct A *p8; struct B *pC; MATRIX4 m10; MATRIX4 m50; qword v90; qword vA0; qword vB0;
    union{float value;int bits;}length0,length1; float gC8; };
extern "C" float func_0011E4B0(qword a, qword b, qword *pv);
extern "C" qword func_0022FCC8(void *space, void *p, qword v);
static inline qword MulSubPinned(MATRIX4*pm,qword vi,qword bi){
 register qword a __asm__("vf2")=pm->r[0],b __asm__("vf4")=pm->r[1],c __asm__("vf3")=pm->r[2],d __asm__("vf5")=pm->r[3],point __asm__("vf6")=vi,right __asm__("vf1")=bi;
 __asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddaz.xyz ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w\n\tvsub.xyzw %0,%0,%5":"+j"(a):"j"(b),"j"(c),"j"(d),"j"(point),"j"(right));return a;
}
extern "C" void func_00186930(struct S*p){
 register qword a __asm__("vf2"),b __asm__("vf4"),c __asm__("vf3"),d __asm__("vf5"),point __asm__("vf6"),right __asm__("vf1");
 register int bits __asm__("$2");
 p->m10=p->p4->m;
 p->m50=p->p8->m;
 right=p->p8->v70;
 a=MulSubPinned(&p->pC->m,p->vB0,right);
 b=p->p4->v70;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(c),"=&j"(d):"j"(a));
 __asm__("vsub.xyzw %0,%0,%1":"+j"(right):"j"(b));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(c));
 __asm__("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tqmfc2.ni %2,%4":"=j"(b),"=&j"(point),"=r"(bits):"j"(right),"j"(c));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(b));
 p->length1.bits=bits;
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(b));
 p->length0.bits=bits;
 p->gC8=func_0011E4B0(right,a,&p->v90);
 p->v90=func_0022FCC8(0,p->p8->pA0,p->v90);
}
