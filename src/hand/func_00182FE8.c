struct S { char pad[0xE4]; int x; };
float SMinCrv__FP3CRV(struct S *p);
float func_001E6648(struct S *p);
int func_00182FE8(struct S *p, float *pg)
{
    if (p->x) {
        pg[0] = SMinCrv__FP3CRV(p);
        pg[1] = func_001E6648(p);
        return 1;
    }
    return 0;
}
