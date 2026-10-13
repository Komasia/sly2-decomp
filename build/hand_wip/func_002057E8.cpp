// WIP: 47/73 instruction differences. Math/data table reconstructed; VU and scalar scheduling remain. See notes/200000.md.

typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct M3 { qword r[3]; };
struct S { char pad[0x218]; qword *origin; int pad21C; float radius; };
extern "C" {
struct M3 *func_001A6318(struct S *p);
qword func_001A62E8(struct S *p);
extern int D_002C3CC8[2][3];
}
static inline qword Load(qword *p)
{
    qword r;
    __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*p));
    return r;
}
static inline qword Scale(qword v, qword k)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
extern "C" void func_002057E8(struct S *p, qword out[2][3])
{
    qword point[5];
    U scalar, origin, right, forward;
    qword positive, negative;
    origin.q = *p->origin;
    right.q = func_001A6318(p)->r[0];
    forward.q = Load(&func_001A6318(p)->r[1]);
    point[0] = func_001A62E8(p);
    float radius = p->radius;
    __asm__("qmtc2.ni %1, %0" : "=j"(positive) : "r"(radius));
    __asm__("qmtc2.ni %1, %0" : "=j"(negative) : "r"(-radius));
    scalar.q = positive;
    point[1] = Add(origin.q, Scale(right.q, positive));
    point[2] = Add(origin.q, Scale(forward.q, positive));
    point[3] = Add(origin.q, Scale(right.q, negative));
    point[4] = Add(origin.q, Scale(forward.q, negative));
    scalar.q = negative;
    for (unsigned i = 0; i < 2; i++) {
        for (unsigned j = 0; j < 3; j++) {
            out[i][j] = point[D_002C3CC8[i][j]];
        }
    }
}
