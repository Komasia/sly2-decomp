struct S { int a; float b; int c[2]; float d; int e[3]; float f; int g[3]; float h; char pad[0x54]; float i, j; };
extern float D_002A96E0, D_002A96E4;
extern char D_002C41B0[];
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
float atan2f(float y, float x);
float GLimitLm(void *p, float f) asm("GLimitLm__FP2LMf");
// name: SafeHouse port (InitCmeTilt)
void InitCmeTilt__FP7ZONECME(struct S *p)
{
    if (p->i == D_002A96E0 && p->j == D_002A96E4) {
        float a = p->b + p->d;
        float f = atan2f(p->h, sqrtf_(a * a + p->f * p->f));
        f = GLimitLm(D_002C41B0, f);
        p->j = f;
        p->i = f;
    }
}
