// NEAR MISS (Claude agent): ~150/172 positional (structure+logic complete): line-sphere intersection into LSG. Remaining: center/pos1 param homes (target lqc2 from stack, no qmtc2), 1.0 range test branch shape, f20/f21 setup order.
typedef int qword __attribute__((mode(TI)));
struct PLANE { qword q; };
struct LSG { qword apos[2]; PLANE aplane[2]; float at[2]; int c; };
extern "C" {
extern qword D_002A2DA0;
void func_00119390(PLANE *pplane, qword vecNormal, qword vecPos);
int func_0014C748(qword posCenter, float sRadius, qword pos0, qword pos1, int cMax, LSG *plsg);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline float Dot(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}

static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %4x" : "=j"(r) : "j"(v1.q), "j"(v2.q), "j"(f1.q), "j"(f2.q));
    return r;
}

static inline qword Normalize(qword v, qword vDefault)
{
    qword t, r;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(r), "=&j"(t) : "j"(v));
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(r));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    if (g < 0.0001f)
        return vDefault;
    __asm__("vdiv Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, Q" : "=j"(r) : "j"(r), "j"(v));
    return r;
}

int func_0014C748(qword posCenter, float sRadius, qword pos0, qword pos1, int cMax, LSG *plsg)
{
    float at[2];
    int i;
    if (cMax > 0) {
        qword d = Sub(pos0, posCenter);
        float c = Dot(d, d) - sRadius * sRadius;
        qword dir = Sub(pos1, pos0);
        float b = Dot(dir, d);
        float a = Dot(dir, dir);
        float disc;
        b = b + b;
        disc = b * b - a * (c * 4.0f);
        if (disc < 0.0001f)
            return 0;
        disc = __builtin_sqrtf(disc);
        {
            float t0 = (-b - disc) / (a + a);
            float t1 = (-b + disc) / (a + a);
            at[0] = t0;
            at[1] = t1;
            if (t0 < 0.0f && t1 < 0.0f)
                return 0;
            if (1.0f < t0) if (1.0f < t1)
                goto fail;
        }
        at[1] = (1.0f < at[1] ? 1.0f : at[1]);
        at[0] = (0.0f < at[0] ? at[0] : 0.0f);
        for (i = 0; i < 2; i++) {
            float t = at[i];
            qword pos;
            plsg->at[i] = t;
            pos = VecCombo(VU_FLOAT(t), pos1, VU_FLOAT(1.0f - t), pos0);
            plsg->apos[i] = pos;
            func_00119390(&plsg->aplane[i], Normalize(Sub(pos, posCenter), D_002A2DA0), pos);
        }
        plsg->c = 1;
        return 1;
    }
fail:
    return 0;
}
