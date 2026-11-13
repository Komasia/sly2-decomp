typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Q { char pad[0x18]; float x18; float x1C; char pad2[0x30 - 0x20]; int x30; };
struct P { char pad[0x10]; void *p10; char pad2[0x30 - 0x14]; int x30; float x34; void *p38; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
void Drive__5AIJOBP6PADCTL(struct P *p, struct Q *q);
qword PosOfLo__FP2LO(void *p);
float atan2f(float y, float x);
void StampPadctlState__FP6PADCTL(struct Q *q);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (JOBBENTLEYATTACK::Drive)
void Drive__16JOBBENTLEYATTACKP6PADCTL(struct P *p, struct Q *q)
{
    Drive__5AIJOBP6PADCTL(p, q);
    if (p->x30 < 3) if (p->x30 >= 0) {
        qword a, b, d;
        float g;
        a = PosOfLo__FP2LO(p->p38);
        b = PosOfLo__FP2LO(p->p10);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        g = 1.0f;
        if (p->x30 == 0) g = 0.1f;
        q->x1C = g;
        q->x18 = atan2f(GetY(d), GetX(d));
        if (p->x30 == 2 && g_clock.t - p->x34 < 0.1f) {
            q->x30 |= 0x80;
            StampPadctlState__FP6PADCTL(q);
        }
    }
}
