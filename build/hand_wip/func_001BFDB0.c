typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct V { qword pos; };
struct T { struct V *apv[3]; };
extern qword D_002A2DC0;
void func_0011EE08(qword pos, qword a, qword b, U *pr, int x, int y);
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GetZ(qword v) { float z; __asm__("qmfc2.ni %0, %1\n\tpextuw %0, $0, %0" : "=r"(z) : "j"(v)); return z; }
qword func_001BFDB0(struct T *pt, qword pos)
{
    U r;
    qword a = pt->apv[0]->pos;
    qword b = pt->apv[1]->pos;
    qword c = pt->apv[2]->pos;
    qword eab = Sub(b, a);
    qword a2 = a, c2 = c;
    if (0.0f < GetZ(Cross(Sub(pos, a), eab))) {
        func_0011EE08(pos, a, b, &r, 0, 0);
    } else if (0.0f < GetZ(Cross(Sub(pos, b), Sub(c, b)))) {
        func_0011EE08(pos, b, c, &r, 0, 0);
    } else if (0.0f < GetZ(Cross(Sub(pos, c), Sub(a, c)))) {
        func_0011EE08(pos, c, a, &r, 0, 0);
    } else {
        qword n = Cross(eab, Sub(c2, a2));
        qword d = Sub(a2, pos);
        qword dot, one, k;
        float t;
        U u;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(dot), "=&j"(one) : "j"(d), "j"(n));
        { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(dot)); t = g / GetZ(n); }
        __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(t));
        u.q = k;
        { qword q; __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(q) : "j"(pos), "j"(D_002A2DC0), "j"(k)); r.q = q; }
    }
    return r.q;
}
