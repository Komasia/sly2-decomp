/* 16 diffs: tail scheduling; target does lw pe first, both union sqc2 stores after vmulx, ld ra not hoisted. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { char pad[0x80]; qword v; char pad2[0x40]; float dD0; };
struct P { char pad[0xE8]; struct E *pe; char pad2[0x260 - 0xEC]; float g; };
void func_001F35C8(struct P *p, float g);
void func_00204DA8(struct P *p, float g)
{
    float s = 0.1f;
    U a;
    qword r;
    struct E *pe;
    s = (g > s) ? g : s;
    func_001F35C8(p, p->pe->dD0 * p->g / s);
    pe = p->pe;
    __asm__("qmtc2.ni %1, %0" : "=j"(a.q) : "r"(s));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(pe->v), "j"(a.q));
    __asm__("qmtc2.ni %1, %0" : "=j"(a.q) : "r"(*(int *)&p->g));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(r) : "j"(a.q));
    pe->v = r;
    p->g = s;
}
