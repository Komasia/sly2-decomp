struct S { int a; int k; };
void func_00216BC8(struct S *p, int a, int b, int c);
void func_002174C8(struct S *p, int a, int b, int c);
void func_002177E0(struct S *p, int a, int b, int c);
void func_002159E0(struct S *p, int a, int b, int c)
{
    switch (p->k) {
    case 3:
        func_00216BC8(p, a, b, c);
        break;
    case 1:
        func_002174C8(p, a, b, c);
        break;
    case 6:
    case 7:
        func_002177E0(p, a, b, c);
        break;
    case 2:
    case 4:
    case 5:
    case 8:
        break;
    }
}
