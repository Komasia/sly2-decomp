
struct S { char pad[0xE8]; int c; };
float func_001E6630(struct S *p);
float func_001E6610(struct S *p);
float func_001E77E8(struct S *p)
{
    float a = func_001E6630(p);
    return (a - func_001E6610(p)) / (p->c * 10.0f);
}
