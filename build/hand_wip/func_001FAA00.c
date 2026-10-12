typedef int qword __attribute__((mode(TI)));
struct B { char pad[0xB0]; char sub[0x20]; int nD0; };
struct A { char pad[0x58]; int n58; char pad2[0xE8 - 0x5C]; struct B *pb; };
void func_001FA810(void *p, int n, qword q);
void func_001FAA00(struct A *p, qword v)
{
    union { qword q; float f; } u;
    qword r, t;
    __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(p->pb->nD0));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r), "=j"(t) : "j"(v), "1"(t));
    u.q = t;
    func_001FA810(p->pb->sub, p->n58, r);
}
