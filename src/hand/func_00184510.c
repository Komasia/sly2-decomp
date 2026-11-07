typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } VEC;
typedef union { qword q; VEC v; } UV;
struct S { char pad[0x110]; qword q110; char p1[0x3C]; void *p15c; };
extern int D_002DFB84;
extern float D_002BE908;
qword PosOfLo__FP2LO(void *p);
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct S *p, int n, qword q);
static __inline__ float GetZ(qword q)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q));
    return z;
}
// name: SafeHouse port (PosHookTarget)
void PosHookTarget__FP2LOiPv(struct S *p, int unused, UV *pv)
{
    if (pv) {
        if (D_002DFB84) {
            pv->q = PosOfLo__FP2LO(p->p15c);
            pv->v.z = pv->v.z + D_002BE908;
        } else {
            pv->q = ConvertPos__FP2LOT0G9VU_VECTOR(p, 0, p->q110);
            pv->v.z = GetZ(PosOfLo__FP2LO(p->p15c)) + D_002BE908;
        }
    }
}
