typedef unsigned long ulong;
struct S { int a[4]; ulong f; };
int func_00229D60(void *p, struct S *q)
{
    return !((q->f >> 50) & 1);
}
