typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } VEC;
typedef union { qword q; VEC v; } UV;
struct S { char pad[0x18C4]; void *p18c4; int n; };
qword func_001A62E8(void *p);
void PosActorFocus__FP5ACTORP9ACTORPOSE(struct S *p, UV *pv);
static __inline__ float GetZ(qword q)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q));
    return z;
}
// name: SafeHouse port (PosSlyFocus)
void PosSlyFocus__FP3SLYP9ACTORPOSE(struct S *p, UV *pv)
{
    switch (p->n) {
    case 3:
        PosActorFocus__FP5ACTORP9ACTORPOSE(p, pv);
        pv->v.z = GetZ(func_001A62E8(p->p18c4)) + -175.0f;
        break;
    case 0x16:
        PosActorFocus__FP5ACTORP9ACTORPOSE(p, pv);
        pv->v.z = GetZ(func_001A62E8(p->p18c4)) + -100.0f;
        break;
    case 0x15:
        pv->q = func_001A62E8(p);
        break;
    default:
        PosActorFocus__FP5ACTORP9ACTORPOSE(p, pv);
        break;
    }
}
