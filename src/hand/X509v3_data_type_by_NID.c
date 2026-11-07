struct X { int a; int b; };
struct X *PdetentryFind__FP8DETECTORi(int n);
int X509v3_data_type_by_NID(int n)
{
    struct X *p = PdetentryFind__FP8DETECTORi(n);
    if (p)
        return p->b;
    return -1;
}
