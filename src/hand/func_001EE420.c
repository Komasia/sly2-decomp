struct T { int n; };
struct S { char pad[0x60]; int n60; };
int PsaiFromSaaShd__FP3SAAP3SHD(struct S *p, struct T *t);
int PsaiFromEyesShd__FP4EYESP3SHD(struct S *p, struct T *t)
{
    int f = 0;
    if (PsaiFromSaaShd__FP3SAAP3SHD(p, t) || t->n == p->n60) f = 1;
    return f;
}
