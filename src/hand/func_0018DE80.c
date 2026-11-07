struct S { char pad[0x18C8]; int n; };
void GetSlyLaunchTarget__FP3SLYPvf(struct S *p, int *pf);
void func_0018DE80(struct S *p, int *pf)
{
    GetSlyLaunchTarget__FP3SLYPvf(p, pf);
    switch (p->n) {
    case 0: case 1: case 5: case 10: case 12:
        *pf = 1;
    }
}
