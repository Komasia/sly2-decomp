typedef int qword __attribute__((mode(TI)));
struct M { qword a[4]; };
qword func_0022CAD0(qword a, qword b);
void func_0022CCD0(struct M *pm, void *a, void *b, qword c);
void *func_0023320C(void *d, void *s, int n);
struct M *func_0022CB90(struct M *pr, void *a, void *b, qword c, qword d)
{
    struct M m;
    struct M *pm = &m;
    func_0022CCD0(pm, a, b, func_0022CAD0(c, d));
    func_0023320C(pr, pm, 0x40);
    return pr;
}
