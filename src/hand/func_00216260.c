struct S { char pad[0x84]; float x84; };
int StrWrapped__FP7FONTBRX(struct S *p);
float func_002161C8(struct S *p);
void func_00216260(struct S *p, float *pa, float *pb)
{
    int n = StrWrapped__FP7FONTBRX(p);
    float f = func_002161C8(p);
    float g = n * p->x84;
    if (pa)
        *pa = f;
    if (pb)
        *pb = g;
}
