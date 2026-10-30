typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct HIT { U a; U b; U normal; U otherNormal; float t; float u; char pad48[0x18]; };
struct ARENA { char pad[2]; };
struct O;
extern "C" {
ARENA *func_001AE478(ARENA *);
void func_001AE4A0(ARENA *, int);
int func_001C5570(void *, O *);
void func_0020FAA0(void *, qword, qword, int (*)(void *, O *), void *, int *, O ***);
O *PsoHitTestLineObjects(int, qword, qword, int, O **, HIT *) __asm__("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
extern char D_003DD490[];
extern qword D_002A2DC0;
}
static inline qword Splat(float f) { qword q; __asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f)); return q; }
extern "C" int func_001C6DE8(float lo, float hi, float threshold, qword point, int count, O **objects, qword *out)
{
    HIT hit;
    ARENA arena;
    U scalar;
    qword upper, lower;
    func_001AE478(&arena);
    qword h = Splat(hi);
    qword axis = D_002A2DC0;
    qword l = Splat(lo);
    __asm__ volatile("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(lower):"j"(point),"j"(axis),"j"(l));
    scalar.q = h;
    __asm__ volatile("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(upper):"j"(point),"j"(axis),"j"(h));
    scalar.q = l;
    if (!objects) func_0020FAA0(D_003DD490, point, upper, func_001C5570, 0, &count, &objects);
    if (hi > 0) {
        if (PsoHitTestLineObjects(0, point, upper, count, objects, &hit) && hit.t == 0) {
            if (hit.u == 1 || hit.otherNormal.f[2] < threshold) goto fail;
            *out = hit.b.q;
            func_001AE4A0(&arena, 2);
            return 1;
        }
    }
    if (lo < 0) {
        if (PsoHitTestLineObjects(0, point, lower, count, objects, &hit)) {
            if (hit.t == 0 || hit.normal.f[2] < threshold) { func_001AE4A0(&arena, 2); return 0; }
            *out = hit.a.q;
            func_001AE4A0(&arena, 2);
            return 1;
        }
    fail:
        func_001AE4A0(&arena, 2);
        return 0;
    }
    *out = point;
    func_001AE4A0(&arena, 2);
    return 1;
}
