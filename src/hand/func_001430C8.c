/* GrfActorLookMask: the state-machine mask of what the actor looks at: by the look kind 8 (none), 0x10 / 0x100 shifted
 * by the target's direction in the actor's frame (0 ahead, 1 left, 2 right, 3 behind; D_002BD2C0 / D_002BD2C4), 0x1000,
 * 0x100. Layout: SafeHouse port (actor.h). */
typedef int qword __attribute__((mode(TI)));
struct ACTOR { char pad[0x10F8]; void *ploLook; int nLookKind; };   /* field: SafeHouse port (actor.h) */
extern float D_002BD2C0;
extern float D_002BD2C4;
qword PosOfLo__FP2LO(void *pactor);
qword ConvertPos__FP2LOT0G9VU_VECTOR(void *pm, struct ACTOR *pactor, qword v);
float atan2f(float y, float x);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GAbs(float g) { return g < 0.0f ? -g : g; }
// name: SafeHouse port (GrfActorLookMask)
int GrfActorLookMask__FP5ACTOR(struct ACTOR *pactor)
{
    int iDir;
    int grf;
    if (pactor->ploLook) {
        qword v = ConvertPos__FP2LOT0G9VU_VECTOR(0, pactor, PosOfLo__FP2LO(pactor->ploLook));
        float g = atan2f(GetY(v), GetX(v));
        float a = __builtin_fabsf(g);
        if (a < D_002BD2C0) iDir = 0;
        else if (D_002BD2C4 < a) iDir = 3;
        else if (0.0f < g) iDir = 1;
        else iDir = 2;
    }
    grf = 8;
    switch (pactor->nLookKind) {
    case -1: case 0: break;
    case 1: grf = 0x10 << iDir; break;
    case 2: grf = 0x100 << iDir; break;
    case 3: grf = 0x1000; break;
    case 4: grf = 0x100; break;
    }
    return grf;
}
