struct X { char pad[0xE0]; int xE0; char pad1[0xEC - 0xE4]; float *ag; char pad2[0x14C - 0xF0]; float agSub[11]; };
int func_001E7668(struct X *p, float *pa, float *pb,float time);
void func_001E5FC8(struct X *p, int i);
static __inline__ float GLerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }
float func_001E64C8(struct X *p,float time)
{
    float a, b;
    float g;
    int i = func_001E7668(p, &a, &b,time);
    if (p->xE0 == 0) { g = GLerp(p->ag[i], p->ag[i + 1], a / b); } else { int j; func_001E5FC8(p, i); for (j = 1; j < 10; j++) if (a < p->agSub[j]) break; j--; g = (j + (a - p->agSub[j]) / (p->agSub[j + 1] - p->agSub[j])) * 0.1f; g = GLerp(p->ag[i], p->ag[i + 1], g); }
    return g;
}
