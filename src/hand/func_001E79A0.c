struct O { char pad[0x5C]; float *ag; };
struct S { char pad[0xE8]; int c; };
struct O *func_001E7840(struct S *p, int n);
float func_001E79A0(struct S *p)
{
    float g;
    if (p->c > 0) g = func_001E7840(p, 0)->ag[p->c - 1];
    else g = 0.0f;
    return g;
}
