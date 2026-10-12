struct RGBA { unsigned char r, g, b, a; };
struct S {
    char pad[0x14]; struct RGBA c1; struct RGBA c0;
    char pad1c[4];
    float r, g, b, a2C, x30, x34, x38, a;
    float rA, gA, bA, x4C, x50, x54, x58, aA;
};
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin) return gMin;
    if (gMax < g) return gMax;
    return g;
}
void func_002160D8(struct S *p)
{
    float k = p->aA * 0.007874016f;
    float a;
    a = k * (float)p->c1.a;
    p->r = GMin(p->rA + (float)p->c1.r, 255.0f);
    p->g = GMin(p->gA + (float)p->c1.g, 255.0f);
    p->b = GMin(p->bA + (float)p->c1.b, 255.0f);
    p->a2C = p->x4C;
    p->x30 = p->x50;
    p->x34 = p->x54;
    p->x38 = p->x58;
    p->a = GClamp(a, 0.0f, 1.0f);
}
