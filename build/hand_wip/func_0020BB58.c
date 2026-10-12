/* 10 diffs: only vf1/vf2 and v0/v1 register numbering differ */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct T { char pad[0x190]; qword v; };
struct R { char pad[0x40]; float g; };
struct S { struct T *pt; int h; int pad[2]; float f10; char pad2[0x50 - 0x14]; float f50; int n54; };
void func_001384C0(int h);
struct R *func_0020BB48(struct S *p);
qword func_0020BAD8(struct S *p);
void func_0020BB58(struct S *p, float g)
{
    struct T *pt;
    U b, a;
    qword q, r1, r2;
    if (p->n54 == 0) {
        p->f50 = 0.0f;
        p->f10 = 1.0f;
    } else {
        p->f50 = g;
        p->f10 = 1.0f - g;
    }
    func_001384C0(p->h);
    pt = p->pt;
    __asm__("qmtc2.ni %1, %0" : "=j"(a.q) : "r"(*(int *)&func_0020BB48(p)->g));
    b = a;
    q = func_0020BAD8(p);
    __asm__("qmtc2.ni %1, %0" : "=j"(b.q) : "r"(-1.0f));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r1) : "j"(q), "j"(b.q));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r2) : "j"(a.q), "j"(r1));
    pt->v = r2;
}
