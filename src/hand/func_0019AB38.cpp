typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } V;
class A0 { public: char pad[0x190]; };
class O { public: int pad[8]; virtual void f1(); virtual void f2(); virtual void f3(int, V *, int); };
class Y : public A0, public O { };
struct S { int *px; Y *py; int pad[2]; qword q; };
extern qword D_002A2DD0;
extern "C" void func_0019A4A0(int *, qword, Y *, qword, qword, int, float *, int, int);
extern "C" float func_0019AB38(S *s) {
    V v; float r;
    s->py->f3(*s->px, &v, 0);
    func_0019A4A0(s->px, s->q, s->py, v.q, D_002A2DD0, 0, &r, 0, 0);
    return r;
}
