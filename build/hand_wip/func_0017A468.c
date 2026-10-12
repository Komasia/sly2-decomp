typedef int qword __attribute__((mode(TI)));
struct B { char pad[0x90]; qword v; };
struct C { char pad[0x30]; qword v; };
struct A { char pad[0x60]; struct C *p60; char pad2[0xF90 - 0x64]; struct B *pF90; };
struct O {
    char pad[0x10];
    struct A *p10;
    char pad2[0x50 - 0x14];
    qword v50;
    char pad3[0x70 - 0x60];
    qword m[3];
};
void func_0017A468(struct O *p)
{
    struct A *a = p->p10;
    qword *m = p->m;
    qword d, t;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(p->v50), "j"(a->p60->v));
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(t) : "j"(a->pF90->v), "j"(m[0]), "j"(m[1]), "j"(m[2]));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(d), "j"(t));
    p->v50 = d;
}
