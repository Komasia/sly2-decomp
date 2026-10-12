typedef int qword __attribute__((mode(TI)));
struct B { char pad[0x70]; qword pos; };
struct A { char pad[0x5C]; struct B *pb; };
qword func_001FAB48(struct A *p, qword *pv, qword q)
{
    qword r, c, s;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(q), "j"(p->pb->pos));
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(c) : "j"(pv[1]), "j"(r));
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(s) : "j"(pv[0]), "j"(c));
    return s;
}
