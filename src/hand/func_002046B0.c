/* SetStepPhysHeadingToward (0x2046B0): heads the STEP along a direction (atan2 of its y and x). */
typedef int qword __attribute__((mode(TI)));
float atan2f(float y, float x);
void SetStepPhysHeading__FP3ALOf(void *pstep, float rad);
static __inline__ float GetX(qword qw) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw)); return x; }
static __inline__ float GetY(qword qw) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(qw)); return y; }
// name: SafeHouse port (stepphys.h SetStepPhysHeadingToward, orig 0x2046B0: SetStepPhysHeading to atan2 of the direction)
void SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(void *pstep, qword vecDir) { SetStepPhysHeading__FP3ALOf(pstep, atan2f(GetY(vecDir), GetX(vecDir))); }
