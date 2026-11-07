typedef int qword __attribute__((mode(TI)));
struct M { float a[12]; };
struct S { char pad[0x17C]; int x17c; char p1[0xC]; int x18c; };
extern qword D_002A2DD0;
extern char D_002BE8D0[], D_002BE8E0[];
void ApplyAloGravity__FP3ALO(struct S *p);
void *MatJtLo__FP2LO(struct S *p);
void LevelMatrix3__FP7MATRIX3T0Pv(void *p, int n, struct M *pm);
void AccelAloTowardRotation__FP3ALOP7MATRIX3P3CLQG9VU_VECTORT2(struct S *p, struct M *pm, void *a, qword q, void *b);
// name: SafeHouse port (ApplyHideGravity)
void ApplyHideGravity__FP3ALO(struct S *p)
{
    ApplyAloGravity__FP3ALO(p);
    if (p->x18c && !p->x17c) {
        struct M m;
        LevelMatrix3__FP7MATRIX3T0Pv(MatJtLo__FP2LO(p), 0, &m);
        AccelAloTowardRotation__FP3ALOP7MATRIX3P3CLQG9VU_VECTORT2(p, &m, D_002BE8D0, D_002A2DD0, D_002BE8E0);
    }
}
