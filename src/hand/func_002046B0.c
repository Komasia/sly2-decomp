typedef int qword __attribute__((mode(TI)));
float atan2f(float y, float x);
void SetStepPhysHeading__FP3ALOf(void *p, float g);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (stepphys.h SetStepPhysHeadingToward, orig 0x2046B0: SetStepPhysHeading to atan2 of the direction)
void SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(void *p, qword v) { SetStepPhysHeading__FP3ALOf(p, atan2f(GetY(v), GetX(v))); }
