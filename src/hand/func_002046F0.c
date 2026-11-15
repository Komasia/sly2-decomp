typedef int qword __attribute__((mode(TI)));
qword PosOfLo__FP2LO(void *p);
void SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(void *p, qword v);
// name: SafeHouse port (FaceObject)
void FaceObject__FP5ACTORP2LO(void *p, void *q)
{
    qword a, b, d;
    a = PosOfLo__FP2LO(q);
    b = PosOfLo__FP2LO(p);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(p, d);
}
