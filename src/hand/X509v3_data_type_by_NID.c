struct X { int a; int b; };
struct X *func_00154180(int n);
int X509v3_data_type_by_NID(int n)
{
    struct X *p = func_00154180(n);
    if (p)
        return p->b;
    return -1;
}
