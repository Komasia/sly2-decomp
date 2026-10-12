typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
int func_00173588(qword v, float r) {
    int f = 0;
    if (GetZ(v) > 0.0001f) {
        float x = GetX(v);
        if (-r < x && x < r) {
            float y = GetY(v);
            if (-r < y && y < r) f = 1;
        }
    }
    return f;
}
