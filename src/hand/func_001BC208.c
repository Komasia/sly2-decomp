typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
int func_001BC208(qword a, qword b)
{
    if (GetX(a) < GetX(b)) return -1;
    if (GetX(b) < GetX(a)) return 1;
    if (GetY(a) < GetY(b)) return -1;
    if (GetY(b) < GetY(a)) return 1;
    return 0;
}
