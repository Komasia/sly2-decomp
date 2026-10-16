typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VUF;
struct M3 { qword r[3]; };
struct LM { float gMin; float gMax; };
struct POLY { float a; float b; float c; };
struct S150 { char pad[0x18]; float g18; float g1C; };
struct S1030 { char pad[0x1C]; float g1C; char pad20[0x20]; float g40; };
struct P {
    char pad0[0x28]; unsigned long ul28; char pad30[0x150 - 0x30]; struct S150 *p150; char pad154[0x190 - 0x154];
    qword v190; char pad1A0[8]; float g1A8; char pad1AC[4]; struct M3 m1B0; char pad1E0[0x2C0 - 0x1E0];
    char x2C0[0x4C0 - 0x2C0]; char x4C0[0xDF0 - 0x4C0]; char xDF0[0x1030 - 0xDF0]; struct S1030 *p1030; int x1034;
    int x1038; char pad103C[0x10DC - 0x103C]; int x10DC; char pad10E0[0x1320 - 0x10E0]; char x1320[0x13D0 - 0x1320];
    int x13D0; char pad13D4[0x13E0 - 0x13D4]; char x13E0[0x1410 - 0x13E0]; qword v1410; char pad1420[0x14E0 - 0x1420];
    int x14E0; char pad14E4[0x14F0 - 0x14E4]; char x14F0[0x1520 - 0x14F0]; qword v1520; char pad1530[0x15F0 - 0x1530];
    int x15F0; char pad15F4[0x1600 - 0x15F4]; char x1600[0x16B0 - 0x1600]; int x16B0; char pad16B4[0x181C - 0x16B4]; int x181C;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern char D_003DD490[];
extern struct LM D_002BBB60;
extern struct POLY D_002BC940;
extern struct POLY D_002BC950;
extern float D_002BC960;
extern float D_002BC934;
void func_001403D0(struct P *p);
void func_00194A40(void *pv, struct P *p, int n);
void func_00134D30(struct P *p);
void func_00134850(struct P *p);
void func_00204660(struct P *p, float g);
int func_001430C8(struct P *p);
void func_001F1350(int a, int b);
void func_0020BB58(void *pv, float g);
void func_0020BC08(void *pv);
void func_00197F98(void *pv);
void func_00191A10(void *pv);
void func_002046F0(struct P *p, int n);
qword func_0011E1A0(float a, float b, float c);
void func_001A0450(struct P *p, void *pv, int n);
qword func_00204E38(struct P *p, struct S1030 *px, float g);
void func_00131A00(struct S1030 *px, float g);
float func_0011CF60(float g);
float func_0011CFE0(float g, float dg);
void func_00135EB0(struct P *p);
void func_001A1358(void *pv);

static __inline__ float GEval(struct POLY *pp, float t) { return pp->a + t * (pp->b + t * pp->c); }
static __inline__ float GClamp(float g, struct LM *plm)
{
    float lo = plm->gMin;
    float hi = plm->gMax;
    if (g < lo) return lo;
    if (hi < g) return hi;
    return g;
}
static __inline__ float LenXY(qword v)
{
    qword l;
    float g;
    __asm__("vmul.xy %0, %1, %1" : "=j"(l) : "j"(v));
    __asm__("vaddy.x %0, %1, %1y" : "=j"(l) : "j"(l));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    return g;
}
static __inline__ qword MulT(struct M3 *pm, qword v)
{
    qword r, t0, t1, t2, one;
    r = pm->r[0];
    __asm__("vmul.xyzw %1, %0, %5\n\tvmaxw.xyzw %4, $vf0, $vf0w\n\tvmul.xyzw %2, %6, %5\n\tvmul.xyzw %3, %7, %5\n\t"
            "vadday.x $ACC, %1, %1y\n\tvmaddz.x %0, %4, %1z\n\tvaddax.y $ACC, %2, %2x\n\tvmaddz.y %0, %4, %2z\n\t"
            "vaddax.z $ACC, %3, %3x\n\tvmaddy.z %0, %4, %3y"
            : "+j"(r), "=&j"(t0), "=&j"(t1), "=&j"(t2), "=&j"(one) : "j"(v), "j"(pm->r[1]), "j"(pm->r[2]));
    return r;
}
static __inline__ void SetVel(struct P *p, qword v, void *pv, int n)
{
    p->v190 = v;
    p->v190 = MulT(&p->m1B0, v);
    p->x1038 = -1;
    func_001A0450(p, pv, n);
}
static __inline__ void Pull(struct P *p)
{
    VUF u;
    qword v = func_00204E38(p, p->p1030, p->p1030->g1C);
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(-1.0f));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(u.q));
    p->v190 = r;
}
static __inline__ void Kick(void *pv, float g)
{
    func_0020BB58(pv, g);
    func_0020BC08(pv);
}

void func_00134DA8(struct P *p)
{
    func_001403D0(p);
    if (((p->ul28 >> 60) & 1) == 0)
        return;
    func_00194A40(D_003DD490, p, 0xF8FE);
    func_00134D30(p);
    func_00134850(p);
    switch (p->x13D0) {
    case 0:
        if (p->x181C) {
            func_00204660(p, D_002BC934);
            break;
        }
        func_001F1350(p->x1034, func_001430C8(p));
        break;
    case 1:
        func_00204660(p, p->p150->g18);
        Kick(p->x1320, 1.0f);
        break;
    case 7:
        func_00204660(p, p->p150->g18);
        Kick(p->x1600, p->p150->g1C);
        break;
    case 2:
        func_00197F98(p->x2C0);
        break;
    case 3:
        func_00191A10(p->x4C0);
        break;
    case 4:
    case 8:
    case 9:
    case 12:
    case 13:
        break;
    case 5:
        func_002046F0(p, p->x10DC);
        SetVel(p, func_0011E1A0(p->p150->g18 + 3.1415927f, p->p150->g1C * LenXY(p->v1410) * p->p1030->g40, 0.0f), p->x13E0, p->x14E0);
        break;
    case 6:
        if (p->x16B0 == 1) {
            float g0 = GClamp(GEval(&D_002BC940, p->p150->g1C), &D_002BBB60);
            float g1 = GClamp(GEval(&D_002BC950, p->p150->g1C), &D_002BBB60);
            float z = 0.0f;
            if (z < p->p150->g1C) {
                float d = func_0011CF60(p->p150->g18 - p->g1A8);
                func_00204660(p, p->g1A8 + func_0011CFE0(d, g1 * D_002BC960 * D_002DDED0.dt));
            }
            SetVel(p, func_0011E1A0(p->p150->g18 + 3.1415927f, g0 * LenXY(p->v1520) * p->p1030->g40, z), p->x14F0, p->x15F0);
        }
        break;
    case 10:
        Pull(p);
        break;
    case 11:
        Pull(p);
        func_00131A00(p->p1030, p->p150->g1C);
        func_00204660(p, p->p150->g18);
        break;
    case 14:
        Pull(p);
        func_00204660(p, p->p150->g18);
        break;
    }
    func_00135EB0(p);
    func_001A1358(p->xDF0);
}
