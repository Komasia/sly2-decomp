struct S { char pad[0x3A8]; int c; int a[1]; };
int func_00132B10(void *o, int n);
int func_002089F0(struct S *p, void *o)
{
    int i;
    for (i = 0; i < p->c; i++) {
        if (func_00132B10(o, p->a[i])) return 1;
    }
    return 0;
}
