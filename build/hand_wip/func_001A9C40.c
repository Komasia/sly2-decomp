/* WIP 2/62: only the order of the two initial lw (target loads b->px first into v0, a->px into v1). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct X { char pad[0x70]; qword pos; };
struct S { struct X *px; int x4; float r; };
extern qword D_002A2DC0;
void func_001A7C18(void *p, struct S *a, struct S *b, qword pos, qword dir, int k, int x, int y, int n, float g);
void func_001A9C40(void *p, struct S *a, struct S *b, int n)
{
    qword pb, d, l, one, dir, pos, pa;
    float rsum, len2, g, r2;
    U u;
    pa = a->px->pos;
    pb = b->px->pos;
    rsum = a->r + b->r;
    r2 = rsum * rsum;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pa), "j"(pb));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(d));
    __asm__ __volatile__("qmfc2.ni %0, %1" : "=r"(len2) : "j"(l));
    if (r2 < len2)
        return;
    if (len2 < 1e-4f) {
        g = 0.0f;
        dir = D_002A2DC0;
    } else {
        qword s;
        float t;
        __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(t) : "f"(len2));
        g = t;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
        u.q = s;
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(dir) : "j"(s), "j"(d));
    }
    {
        qword s;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(-a->r));
        u.q = s;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(pos) : "j"(pa), "j"(dir), "j"(s));
    }
    func_001A7C18(p, a, b, pos, dir, 7, 0, 0, n, g - rsum);
}
