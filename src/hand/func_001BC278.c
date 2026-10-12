typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
extern float D_002C0AB0;
int func_001BC278(qword a, qword b, qword c)
{
    float g = (GetX(a) - GetX(b)) * (GetY(b) - GetY(c)) - (GetY(a) - GetY(b)) * (GetX(b) - GetX(c));
    if (g < -D_002C0AB0) return -1;
    if (D_002C0AB0 < g) return 1;
    return 0;
}
