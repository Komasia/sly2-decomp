struct OBJ;
void *func_001AE4F8(int);
struct A { int x0; int x4; A() { x0 = 0; x4 = 0; } };
struct B : A {
    int x8;
    virtual void F();
};
struct X : B {
    X(OBJ *p) { func_001D4D30(this, p); }
    void *operator new(unsigned int cb) { return func_001AE4F8(cb); }
    static void func_001D4D30(X *, OBJ *);
    char pad[0xB0 - 0x10];
};
struct OBJ { char pad[0x4F8]; int c; X *a[1]; };
extern "C" {
void func_001C3DF8(OBJ *);
void func_001D4DE0(X *, X *);
void func_001D1410(OBJ *p)
{
    int i;
    func_001C3DF8(p);
    for (i = 0; i < p->c; i++) {
        X *old = p->a[i];
        X *n = new X(p);
        func_001D4DE0(n, old);
        p->a[i] = n;
    }
}
}
