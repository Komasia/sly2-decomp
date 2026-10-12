typedef int qword __attribute__((mode(TI)));
qword func_001A62E8(void *p);
void func_001FAA98(void *p, qword q);
void func_001FAA48(void *p, qword a, qword b)
{
    qword r, c, d;
    d = func_001A62E8(p);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(d));
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(c) : "j"(r), "j"(b));
    func_001FAA98(p, c);
}
