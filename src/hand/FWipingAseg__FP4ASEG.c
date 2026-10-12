struct ASEG { char pad[0x84]; int c; int a[1]; };
int FWipingAseg__FP4ASEG(struct ASEG *paseg, int n)
{
    int i;
    for (i = 0; i < paseg->c; i++) {
        if (paseg->a[i] == n) return 1;
    }
    return 0;
}
