extern char D_002C94A0[];
struct OBJ;
struct X;
extern "C" void func_001D4D30(X *,OBJ *);
extern "C" void *func_001AE4F8(int);
struct A { int x0; A() { x0 = 0; } };
struct B : A {
    int x4;
    int x8;
    char *vt;
    B() {x4=0;}
};
struct X : B {
    X(OBJ *p) {register char *vtable __asm__("$3")=D_002C94A0;vt=vtable;func_001D4D30(this,p);}
    void *operator new(unsigned int cb) { return func_001AE4F8(cb); }
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
extern "C" void func_001D4B90(OBJ *p, int a, int b, int inputC, int inputD)
{
    register int c __asm__("$20")=inputC;
    register int d __asm__("$21")=inputD;
    if (p->n < 8) {
        X *it = new X(p);
        unsigned int index=p->n;
        it->x14=a;
        it->x18=b;
        p->a[index]=it;
        p->n=index+1;
        it->x38=d;
        it->x2C=c;
    }
}
