typedef int qword __attribute__((mode(TI)));
struct Q { char pad[0x218]; qword *p218; };
struct P { char pad[0x10C]; float f10C; };
qword func_001A62E8(void *p);
float func_002458F0(float y, float x);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
void func_001834D0(struct P *p, struct Q *q, float *pg)
{
    qword a = *q->p218;
    qword b = func_001A62E8(p);
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    *pg = func_002458F0(GetY(d), GetX(d)) * p->f10C;
}
