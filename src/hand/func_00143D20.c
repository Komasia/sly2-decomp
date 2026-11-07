typedef int qword __attribute__((mode(TI)));
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
struct SO;
typedef struct { short d; short pad; qword (*pfn)(struct SO *); } VT;
struct G { char pad[0x88]; float g; };
struct SO { int x0, x4, x8; VT *vt; char pad[0xE8 - 0x10]; struct G *pg; char pad2[0x248 - 0xEC]; float z; };
qword PosOfLo__FP2LO(struct SO *p);
int FDropOnGround__FP6VECTORffiPv(qword *ppos, int a, int b, float f, float g);
// name: SafeHouse port (FActorBelowFloorSoon)
int FActorBelowFloorSoon__FP5ACTORf(struct SO *p, float dt)
{
    union { qword q; float f[4]; } pos;
    float h = p->z;
    h += dt * GetZ(p->vt[33].pfn((struct SO *)((char *)p + p->vt[33].d)));
    h += 0.5f * dt * dt * p->pg->g;
    if (h > 0.0f)
        return 0;
    pos.q = PosOfLo__FP2LO(p);
    return FDropOnGround__FP6VECTORffiPv(&pos.q, 0, 0, 0.0f, h);
}
