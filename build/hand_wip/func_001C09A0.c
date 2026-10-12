typedef int qword __attribute__((mode(TI)));
struct S { char pad[0xE0]; char xE0[4]; };
int func_001BF110(void *p);
int func_001C1700(struct S *p, int a, qword q0, qword q1, int c, void **ap);
int func_001BC9F0(void *pv, qword q);
int func_001C09A0(struct S *p, qword q)
{
    void *ap[0x80];
    int n, i;
    if (!func_001BF110(p->xE0)) return 0;
    n = func_001C1700(p, 0, q, q, 0x80, ap);
    for (i = 0; i < n; i++) {
        if (func_001BC9F0(ap[i], q)) return 0;
    }
    return 1;
}
