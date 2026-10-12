typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
typedef struct M { qword r0; qword r1; } M;
typedef struct A { char pad[0x1024]; int x1024; } A;
typedef struct B { char pad[0xE4]; int xE4; char pad1[0x1BC - 0xE8]; int x1BC; } B;
typedef struct C114 { char pad[0x10]; float g10; } C114;
typedef struct C { char pad[0x114]; C114 *p114; } C;
typedef struct S {
    A *p0; int x4; int x8; int pad0c[2]; B *p14; int pad18[2]; float g20; int pad24[2]; int x2C; int pad30[4];
    qword v40; float g50; int pad54[5]; C *p68;
} S;
typedef struct R { unsigned int x0; char pad[0x30 - 4]; float g30; int x34; int pad38; int x3C; } R;
typedef struct CLOCK { float t; float dt; } CLOCK;

extern CLOCK D_002DDED0;
extern char D_002BF348[];

extern float func_00204740(A *p);
extern int func_00132B10(B *p, int n);
extern float func_001E6648(B *p);
extern float func_001E6620(B *p);
extern void func_001E6F10(B *p, qword *pv, float g, int n);
extern qword func_001A62E8(A *p);
extern M *func_001A6318(A *p);
extern float func_0011D018(void *p, int n, float a, float b, float c);

static __inline__ qword BcF(float g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static __inline__ qword VMulX(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static __inline__ qword VAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
static __inline__ float GMin(float a, float b) { return a < b ? a : b; }
static __inline__ float GMax(float a, float b) { return a > b ? a : b; }

void func_0018A4E8(S *ps, R *pr)
{
    float g;
    VU u;

    if (ps->x8 != 0)
        return;
    pr->g30 = func_00204740(ps->p0);
    if (ps->p0->x1024 != (int)ps->p68)
        return;
    pr->x34 = 0;
    if (ps->x2C >= 3) goto tail;
    if (ps->x2C > 0) goto a12;
    if (ps->x2C == 0) goto c0;
    goto tail;
    {
    a12:
        if (func_00132B10(ps->p14, 0xC)) {
            B *pb = ps->p14;
            if (ps->x2C == 1) {
                g = ps->g20 + (ps->g50 * 125.0f) * ps->g50;
                if (pb->xE4 == 0) {
                    float h = func_001E6648(pb);
                    if (pb->x1BC & 2)
                        h += 100.0f;
                    g = GMin(g, h);
                }
            } else {
                g = ps->g20 - (ps->g50 * 125.0f) * ps->g50;
                if (pb->xE4 == 0) {
                    float h = func_001E6620(pb);
                    if (pb->x1BC & 1)
                        h -= 100.0f;
                    g = GMax(g, h);
                }
            }
            func_001E6F10(pb, &ps->v40, g, 0);
            ((float *)&ps->v40)[2] += 125.0f;
        } else if (ps->x2C == 1) {
            qword q = func_001A62E8(ps->p0);
            qword s = BcF((ps->g50 * 125.0f) * ps->g50);
            u.q = s;
            ps->v40 = VAdd(q, VMulX(func_001A6318(ps->p0)->r1, s));
            ((float *)&ps->v40)[2] += 50.0f;
        } else {
            qword q = func_001A62E8(ps->p0);
            qword s = BcF((ps->g50 * 125.0f) * ps->g50);
            u.q = s;
            ps->v40 = VSub(q, VMulX(func_001A6318(ps->p0)->r1, s));
            ((float *)&ps->v40)[2] += 50.0f;
        }
    }
    goto tail;
c0:
        ps->v40 = func_001A62E8(ps->p0);
        ((float *)&ps->v40)[2] += 50.0f;
tail:
    if (func_00132B10(ps->p14, 0xC) && ps->p14->xE4 == 0) {
        float k;
        float c = 30.0f;
        float h = func_001E6648(ps->p14) - c;
        float d = GMin((h - c) * 0.5f, 300.0f);
        float e = d + c;
        float x = ps->g20;
        h = h - d;
        if (x < e) {
            float t = GClamp((e - x) / d, 0.0f, 1.0f);
            k = -t * t * 150.0f;
        } else if (h < x) {
            float t = GClamp((x - h) / d, 0.0f, 1.0f);
            k = t * t * 150.0f;
        } else {
            k = 0.0f;
        }
        ps->p68->p114->g10 = func_0011D018(D_002BF348, 0, ps->p68->p114->g10, k, D_002DDED0.dt);
    }
    switch (ps->x8) {
    case 0:
    case 0xD:
        pr->x3C = 1;
        break;
    case 1:
    case 3:
    case 4:
        break;
    default:
        pr->x0 |= 1;
        break;
    }
}
