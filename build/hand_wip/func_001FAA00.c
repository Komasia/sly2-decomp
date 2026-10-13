typedef int qword __attribute__((mode(TI)));
union SCALAR { qword q; float f[4]; };
union FLOATWORD { float value; int bits; };
struct PROJECTION { qword axis; int mode; };
struct LO;
struct B { char pad[0xB0]; struct PROJECTION projection; union FLOATWORD mass; };
struct A { char pad[0x58]; struct LO *space; char pad2[0xE8-0x5C]; struct B *state; };
qword func_001FA810(struct PROJECTION *,struct LO *,qword);
qword func_001FAA00(struct A *p,qword v) {
    union SCALAR scalar;
    register qword t __asm__("vf2"); register qword r __asm__("vf1");
    __asm__("qmtc2.ni %1,%0" : "=j"(t) : "r"(p->state->mass.bits));
    scalar.q=t;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(scalar.q),"j"(v));
    return func_001FA810(&p->state->projection,p->space,r);
}
