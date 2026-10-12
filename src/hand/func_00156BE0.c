typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void func_00156780(struct O *o);
void func_00156548(void *x, qword q, int c, struct O **ppo);
void func_00156BE0(void *x, qword q, int c, struct O **ppo)
{
    if (*ppo) {
        struct O *o;
        struct VTE *e;
        func_00156780(*ppo);
        o = *ppo;
        e = &o->vt[2];
        e->pfn((char *)o + e->d);
        *ppo = 0;
    }
    if (x) {
        struct O *o;
        struct VTE *e;
        func_00156548(x, q, c, ppo);
        o = *ppo;
        e = &o->vt[1];
        e->pfn((char *)o + e->d);
    }
}
