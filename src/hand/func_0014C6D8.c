typedef int qword __attribute__((mode(TI)));
struct A { char pad[0x70]; qword q70; };
struct P { struct A *pa; int pad; float f8; int pad2; unsigned long ul10; };
int func_00118668(int n, int m, qword a, qword b, int c, float *d);
int func_0014C748(qword q, qword a, qword b, int c, float *d, float f);
int func_0014C6D8(struct P *p, int n, qword a, qword b, int c, float *d)
{
    if (n) return func_00118668(n, 0x7FFFFFFF, a, b, c, d);
    if (p->ul10 & (1UL << 49)) return func_0014C748(p->pa->q70, a, b, c, d, p->f8);
    return 0;
}
