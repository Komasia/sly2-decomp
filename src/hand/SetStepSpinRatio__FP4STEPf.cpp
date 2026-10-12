struct VECTOR3 { float x, y, z; };
extern VECTOR3 D_002C0248;
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(g)); return r; }
struct STEP { char pad[0x210]; VECTOR3 v; float r; };
void SetStepSpinRatio(STEP *pstep, float r)
{
    pstep->v = D_002C0248;
    pstep->v.x *= r;
    pstep->v.y *= r;
    pstep->v.z *= 1.0f / SqrtF(r);
    pstep->r = r;
}
