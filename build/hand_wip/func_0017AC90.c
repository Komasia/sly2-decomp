/* 8 diffs: (1) p->p5C->p19A4 chain gets v0/v1 swapped; (2) target loads g_clock.dt for the qmtc2 with `lw s0,4(s0)` (reusing the &g_clock s-reg); ours uses v1, shifting n50 into a0. Switch copy fixed by testing p->n50 == 1 in the case body (CSE keeps a copy). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern float D_002BE6C8, D_002BE6CC;
struct VTE { short d; short pad; void *pfn; };
struct C { char pad[0x1C]; float g1C; };
struct B { char pad[0x90]; struct C *p90; };
struct A { char pad[0xC]; struct VTE *vt; char pad2[0x58 - 0x10]; struct B *p58; char pad3[0x208 - 0x5C]; int n208; };
struct Y { char pad[0x60]; void *p60; };
struct X { char pad[0x19A4]; struct Y *p19A4; };
struct S { char pad[0x10]; struct A *p10; char pad2[0x50 - 0x14]; int n50; float g54; int pad3; struct X *p5C; int pad4; struct C *p64; };
struct OUT { char pad[0x30]; qword v; };
void func_00174B68(struct S *p);
void func_0017B1A8(struct S *p, int n);
void func_0017ABC8(struct S *p);
qword func_001A62E8(struct A *a);
void func_002309E8(void *a, int b, struct OUT *pm, int c, float g);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
void func_0017AC90(struct S *p) {
    qword v;
    int s;
    func_00174B68(p);
    {
        struct A *a = p->p10;
        struct VTE *e = &a->vt[33];
        v = ((qword (*)(void *))e->pfn)((char *)a + e->d);
    }
    do {
        s = p->n50;
        switch (s) {
        case 0:
        case 1:
            if (p->n50 == 1 && p->p10->n208) {
                func_0017B1A8(p, 3);
            } else if (p->p10->p58->p90 != p->p64 || p->p10->p58->p90->g1C < D_002DDED0.t) {
                func_0017B1A8(p, 2);
            } else if (GetZ(v) < 0.0f && p->n50 == 0) {
                func_0017B1A8(p, 1);
            } else {
                func_0017ABC8(p);
            }
            break;
        case 2:
            if (p->p10->n208) func_0017B1A8(p, 3);
            break;
        case 3:
            break;
        case 4:
        case 5: {
            struct OUT out;
            U a, b, t, vel, ud;
            qword tq, c;
            a.q = func_001A62E8(p->p10);
            {
                struct A *pa = p->p10;
                struct VTE *e = &pa->vt[33];
                b.q = ((qword (*)(void *))e->pfn)((char *)pa + e->d);
            }
            func_002309E8(p->p5C->p19A4->p60, 0, &out, 0, D_002DDED0.dt);
            t.q = out.v;
            t.f[2] += D_002BE6C8;
            tq = t.q;
            c = func_001A62E8(p->p10);
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(c) : "j"(tq), "j"(c));
            __asm__("qmtc2.ni %1, %0" : "=j"(ud.q) : "r"(*(int *)&D_002DDED0.dt));
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(vel.q) : "j"(ud.q), "j"(c));
            if (p->n50 == 4) {
                if (a.f[2] < t.f[2] || D_002BE6CC < D_002DDED0.t - p->g54) {
                    func_0017B1A8(p, 5);
                    break;
                }
                vel.f[2] = b.f[2];
            }
            {
                struct A *pa = p->p10;
                struct VTE *e = &pa->vt[35];
                ((void (*)(void *, qword))e->pfn)((char *)pa + e->d, vel.q);
            }
            break;
        }
        case 6:
            if (p->p10->n208) func_0017B1A8(p, -1);
            break;
        }
    } while (p->n50 != s);
}
