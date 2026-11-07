typedef int qword __attribute__((mode(TI)));
qword func_001A62E8(void *p);
void func_002046B0(void *p, qword v);
// name: SafeHouse port (FaceObject)
void FaceObject__FP5ACTORP2LO(void *p, void *q)
{
    qword a, b, d;
    a = func_001A62E8(q);
    b = func_001A62E8(p);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    func_002046B0(p, d);
}
