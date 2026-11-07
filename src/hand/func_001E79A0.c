struct O { char pad[0x5C]; float *ag; };
struct S { char pad[0xE8]; int c; };
struct O *PropeEnsure__FP2LOi(struct S *p, int n);
float func_001E79A0(struct S *p)
{
    float g;
    if (p->c > 0) g = PropeEnsure__FP2LOi(p, 0)->ag[p->c - 1];
    else g = 0.0f;
    return g;
}
