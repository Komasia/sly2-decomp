typedef int qword __attribute__((mode(TI)));
struct LO { char pad[0x28]; unsigned long flags; };
struct S { char pad[0x3EB8]; int c; struct LO *list[1]; };
extern float D_002A7708;
qword PosOfLo__FP2LO(struct LO*);
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b)); return r; }
static inline float LenSq(qword a) {
    qword d,one; float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d),"=&j"(one) : "j"(a));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d));
    return f;
}
// name: SafeHouse port (PloNearestPlayer)
struct LO *PloNearestPlayer__FP6VECTORG9VU_VECTOR(struct S*p,qword v) {
    struct LO *best=0; int i=0;
    float minimum=D_002A7708;
    for(;i<p->c;++i) {
        struct LO *lo=p->list[i];
        if((int)(lo->flags>>60)&1) {
            float dist=LenSq(Sub(v,PosOfLo__FP2LO(lo)));
            if(dist<minimum) { minimum=dist; best=lo; }
        }
    }
    return best;
}
