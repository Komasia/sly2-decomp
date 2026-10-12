typedef int qword __attribute__((mode(TI)));
struct S { int a, b, c, d; qword q; };
void func_00193A68(int, int, qword *, qword *);
void func_0019A4A0(int, qword, int, qword, qword, int, float *, int, int);
float func_0019AA58(struct S *s) {
    float r; qword a, b;
    func_00193A68(s->a, s->c, &a, &b);
    func_0019A4A0(s->b, s->q, s->c, a, b, 0, &r, 0, 0);
    return r;
}
