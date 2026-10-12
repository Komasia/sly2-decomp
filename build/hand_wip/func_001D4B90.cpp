struct OBJ;
void *func_001AE4F8(int);
struct A { int x0; A() { x0 = 0; } };
struct B : A {
    int x4;
    int x8;
    virtual void F();
    B() { x4 = 0; }
};
struct X : B {
    X(OBJ *p) { func_001D4D30(this, p); }
    void *operator new(unsigned int cb) { return func_001AE4F8(cb); }
    static void func_001D4D30(X *, OBJ *);
    int x10;
    int x14;
    int x18;
    char pad1c[0x2C - 0x1C];
    int x2C;
    int pad30[2];
    int x38;
    char pad[0xB0 - 0x3C];
};
struct OBJ { char pad[0x4F8]; unsigned int n; X *a[8]; };
extern "C" void func_001D4B90(OBJ *p, int a, int b, int c, int d)
{
    if (p->n < 8) {
        X *it = new X(p);
        it->x14 = a;
        p->a[p->n++] = it;
        it->x2C = c;
        it->x38 = d;
        it->x18 = b;
    }
}
