struct E { int a[10]; };
struct S { char pad[0x128]; struct E *pe; };
extern struct E D_003E1A78[];
extern int *D_002C0BF8[];
int func_001BEE10(struct S *p, int n)
{
    if (!p->pe) return -1;
    return D_002C0BF8[p->pe - D_003E1A78][n];
}
