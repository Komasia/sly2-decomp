typedef int qword __attribute__((mode(TI)));
struct SOURCE;
struct P { char pad[0x1C]; struct SOURCE *source; qword v; };
extern qword D_002A2DD0;
int func_0011D4D0(float, float, float);
void func_001FB658(struct P *, unsigned short, unsigned short);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return func_0011D4D0(X(a), X(b), 0.0001f) && func_0011D4D0(Y(a), Y(b), 0.0001f) && func_0011D4D0(Z(a), Z(b), 0.0001f);
}
void func_001FB2F8(struct P *p, struct SOURCE *source)
{
    p->source = source;
    if (source) func_001FB658(p, 0x200, 0x200);
    else if (FNear(D_002A2DD0, p->v)) func_001FB658(p, 0x200, 0);
}
