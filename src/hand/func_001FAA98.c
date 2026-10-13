typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct LO;
struct S { qword v; int k; };
struct E { char pad[0x30]; M3 m; char pad2[0x90 - 0x60]; struct S vector; };
struct B { char pad[0x40]; M3 m; char pad2[0xA0 - 0x70]; struct LO *plo; };
struct X { char pad[0x5C]; struct B *pb; char pad2[0xE8 - 0x60]; struct E *pe; };
void func_0011B340(M3 *pd, M3 *ps);
qword func_001FA810(struct S *pv, struct B *pb, qword v);
static inline qword MulMV(M3 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v));
    return r;
}
static inline void MulMVIn(M3 *pm, qword *pv)
{
    __asm__("vmulax.xyz $ACC, %1, %0x\n\tvmadday.xyz $ACC, %2, %0y\n\tvmaddz.xyz %0, %3, %0z" : "+j"(*pv) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]));
}
qword func_001FAA98(struct X *p, qword v)
{
    struct B *pb = p->pb;
    M3 m;
    func_0011B340(&m, &pb->m);
    MulMVIn(&m, &v);
    MulMVIn(&p->pe->m, &v);
    return func_001FA810(&p->pe->vector, p->pb, MulMV(&pb->m, v));
}
