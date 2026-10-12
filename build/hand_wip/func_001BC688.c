typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct X { char pad[0xE8]; int cplane; char pad2[0x1EC - 0xEC]; qword *aplane; };
typedef struct HIT { qword v0; qword v10; qword v20; qword v30; float f40; float f44; int x48; struct X *p4C; struct X *p50; char pad[0x60 - 0x54]; } HIT;
void func_001BD400(struct X *p);
void func_002564B8(void *p);
void *func_002333B4(void *p, int c, int cb);
extern float D_002C0AB4;
static inline qword Zero(void) { qword r; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(r)); return r; }
static inline qword Neg(qword v) { qword r = Zero(); __asm__("vsub.xyzw %0, %0, %1" : "+j"(r) : "j"(v)); return r; }
#define LERP(r, a, b, t) do { \
    qword k1, k2; \
    __asm__("qmtc2.ni %1, %0" : "=j"(k2) : "r"(t)); \
    __asm__("qmtc2.ni %1, %0" : "=j"(k1) : "r"(1.0f - t)); \
    u.q = k1; \
    u.q = k2; \
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(k1), "j"(b), "j"(k2)); \
} while (0)
int func_001BC688(struct X *p, qword a, qword b, int cMax, HIT *ahit)
{
    int i = 0;
    int n;
    float tMin, tMax;
    U u;
    qword nMin, nMax;
    func_001BD400(p);
    tMin = 0.0f;
    tMax = 1.0f;
    nMin = Zero();
    nMax = nMin;
    for (; i < p->cplane - 1; i++) {
        qword plane;
        float da, db, t;
        plane = p->aplane[i];
        {
            U d1, one1;
            qword td, tone;
            func_002564B8(&d1);
            func_002564B8(&one1);
            __asm__("vmul.xyz %0, %3, %4\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %3w\n\tqmfc2.ni %2, %0" : "=j"(td), "=&j"(tone), "=r"(da) : "j"(plane), "j"(a));
            one1.q = tone;
            d1.q = td;
        }
        {
            U d2, one2;
            qword td, tone;
            func_002564B8(&d2);
            func_002564B8(&one2);
            __asm__("vmul.xyz %0, %3, %4\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %3w\n\tqmfc2.ni %2, %0" : "=j"(td), "=&j"(tone), "=r"(db) : "j"(plane), "j"(b));
            one2.q = tone;
            d2.q = td;
        }
        da += D_002C0AB4;
        db += D_002C0AB4;
        if (da < 0.0f && db < 0.0f)
            continue;
        if (0.0f < da && 0.0f < db) {
            tMax = 0.0f;
            tMin = tMax;
            break;
        }
        t = da / (da - db);
        if (da < 0.0f) {
            tMax = (tMax < t) ? tMax : t;
            nMax = plane;
        } else {
            nMin = plane;
            tMin = (tMin > t) ? tMin : t;
        }
        if (tMax <= tMin)
            break;
    }
    n = 0;
    if (tMax <= tMin) {
        if (cMax > 0) {
            HIT *pe = ahit;
            func_002333B4(pe, 0, 0x60);
            n = 1;
            pe->v0 = a;
            pe->f44 = 1.0f;
            pe->f40 = 0.0f;
            pe->v10 = b;
        }
        return n;
    }
    if (0.0f < tMin && cMax > 0) {
        HIT *pe = &ahit[n];
        func_002333B4(pe, 0, 0x60);
        n = 1;
        pe->v0 = a;
        { qword r; LERP(r, a, b, tMin); pe->v10 = r; }
        pe->v30 = Neg(nMin);
        pe->f40 = 0.0f;
        pe->f44 = tMin;
        pe->p50 = p;
    }
    if (tMax < 1.0f && n < cMax) {
        HIT *pe = &ahit[n++];
        func_002333B4(pe, 0, 0x60);
        pe->p4C = p;
        { qword r; LERP(r, a, b, tMax); pe->v0 = r; }
        pe->v20 = Neg(nMax);
        pe->v10 = b;
        pe->f40 = tMax;
        pe->f44 = 1.0f;
    }
    return n;
}
