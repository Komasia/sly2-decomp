struct S { char pad[0xE4]; int x; };
float func_001E6620(struct S *p);
float func_001E6648(struct S *p);
int func_00182FE8(struct S *p, float *pg)
{
    if (p->x) {
        pg[0] = func_001E6620(p);
        pg[1] = func_001E6648(p);
        return 1;
    }
    return 0;
}
