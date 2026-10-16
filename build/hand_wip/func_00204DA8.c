typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { char pad[0x80]; qword v; char pad2[0x40]; float dD0; };
union FLOATWORD {float value;int bits;};
struct P { char pad[0xE8]; struct E *pe; char pad2[0x260 - 0xEC]; union FLOATWORD g; };
void func_001F35C8(struct P *p, float g);
static inline qword FromFloat(float f,U *value) {
    register float word __asm__("$3")=f;
    register qword scalar __asm__("vf2");
    __asm__ __volatile__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(word));
    value->q=scalar;
    return value->q;
}
static inline qword FromWord(int bits,U *value) {
    register int word __asm__("$3")=bits;
    register qword scalar __asm__("vf3");
    __asm__ __volatile__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(word));
    value->q=scalar;
    return value->q;
}
void func_00204DA8(struct P *p, float g)
{
    float s = 0.1f;
    U a;
    register qword r __asm__("vf1");
    qword scalar;
    register struct E *pe __asm__("$2");
    s = (g > s) ? g : s;
    func_001F35C8(p, p->pe->dD0 * p->g.value / s);
    pe = p->pe;
    scalar=FromFloat(s,&a);
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(pe->v), "j"(scalar));
    scalar=FromWord(p->g.bits,&a);
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(r) : "j"(scalar));
    pe->v = r;
    p->g.value = s;
}
