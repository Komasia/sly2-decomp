typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x1420]; qword q1420; };
void func_001B6078(struct P *p, int n);
qword func_001A62E8(void *p);
void func_002046B0(struct P *p, qword q);
// name: SafeHouse port (StartMurrayThrow)
void StartMurrayThrow__FP6MURRAYP2LO(struct P *p, void *pv)
{
    qword a, b, d;
    func_001B6078(p, 7);
    if (pv) {
        a = func_001A62E8(pv);
        p->q1420 = a;
        b = func_001A62E8(p);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        func_002046B0(p, d);
    }
}
