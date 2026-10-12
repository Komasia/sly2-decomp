typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x218]; qword *pq; };
struct S { char pad[0xE4]; int xe4; };
struct V { float a[4]; };
void func_001E6F60(struct S *p, qword q, int a, struct V *pv, int b, int c, float *pg);
float func_001E6648(struct S *p);
void func_00183040(struct S *p, struct T *t, float *pg)
{
    struct V v;
    func_001E6F60(p, *t->pq, 0, &v, 0, 0, pg);
    if (!p->xe4) {
        float lim = func_001E6648(p) - 30.0f;
        float g = *pg;
        if (g < 30.0f) g = 30.0f;
        else if (lim < g) g = lim;
        *pg = g;
    }
}
