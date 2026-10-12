typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } V;
struct T { int a, b, c, d; qword q; };
struct S { int a, b; };
void func_001E6F10(int, V *, int);
qword func_001A6F00(int, int, qword);
float func_0019ABB8(struct T *);
void func_0011D9E0(float (*)(struct T *), struct T *, float, float, float, int, float *, float);
float func_0019ABF0(struct S *s) {
    V v; struct T t; float r;
    int b = s->b;
    func_001E6F10(b, &v, 0);
    t.a = s->a;
    t.b = b;
    t.q = func_001A6F00(0, b, v.q);
    func_0011D9E0(func_0019ABB8, &t, 0.5f, 0.25f, 0.25f, 0, &r, 3.0f);
    return r;
}
