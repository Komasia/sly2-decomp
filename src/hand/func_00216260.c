struct S { char pad[0x84]; float x84; };
int func_00215F40(struct S *p);
float func_002161C8(struct S *p);
void func_00216260(struct S *p, float *pa, float *pb)
{
    int n = func_00215F40(p);
    float f = func_002161C8(p);
    float g = n * p->x84;
    if (pa)
        *pa = f;
    if (pb)
        *pb = g;
}
