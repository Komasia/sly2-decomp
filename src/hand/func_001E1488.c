typedef int qword __attribute__((mode(TI)));
struct CMD { char pad[0x10]; qword q; float x, y, z; int pad2; float f; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
void func_001E1488(void *pq, qword a, qword v, float f)
{
    struct CMD *p = func_001E01F8(pq, 0x3F, 1);
    p->q = a;
    p->x = GetX(v) * 0.017453294f;
    p->y = GetY(v) * 0.017453294f;
    p->z = GetZ(v) * 0.017453294f;
    p->f = f;
}
