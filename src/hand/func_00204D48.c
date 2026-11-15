/* SetStepPhysScale (0x204D48): the STEP's speed scale gScale; the braking speeds are the defaults D_002C3CB8 with
 * x and y scaled by it and z by 1 / sqrt of it. */
typedef struct VECTOR { float x, y, z; } VECTOR;
extern VECTOR D_002C3CB8;   /* default braking speeds */
static __inline__ float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(g)); return r; }
/* the STEP fields used here */
struct STEP { char pad[0x1F0]; float gScale; VECTOR vBrake; };
// name: SafeHouse port (SetStepPhysScale)
void SetStepPhysScale__FP3ALOf(struct STEP *pstep, float gScale)
{
    pstep->vBrake = D_002C3CB8;
    pstep->vBrake.x *= gScale;
    pstep->vBrake.y *= gScale;
    pstep->vBrake.z *= 1.0f / SqrtF(gScale);
    pstep->gScale = gScale;
}
