struct E { int a[6]; };
void func_00162250(void *p, struct E *pe, void *q, int n);
// name: SafeHouse port (ApplyTaskSms)
void ApplyTaskSms__FPvT0iT0i(void *p, void *q, int c, struct E *ae, int n)
{
    int i;
    for (i = 0; i < c; i++)
        func_00162250(p, &ae[i], q, n);
}
