typedef struct VECTOR { float x, y, z; } VECTOR;
extern VECTOR D_002C3CB8;
static __inline__ float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(g)); return r; }
struct S { char pad[0x1F0]; float g; VECTOR v; };
void func_00204D48(struct S *p, float g)
{
    p->v = D_002C3CB8;
    p->v.x *= g;
    p->v.y *= g;
    p->v.z *= 1.0f / SqrtF(g);
    p->g = g;
}
