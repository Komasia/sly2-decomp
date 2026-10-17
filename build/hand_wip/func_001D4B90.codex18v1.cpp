extern char D_002C94A0[];
struct OBJ;
struct X;
extern "C" void func_001D4D30(X *,OBJ *);
extern "C" void *func_001AE4F8(int);
struct A { int x0; A() {} };
struct B : A {
    int x4;
    int x8;
    char *vt;
    B() {}
};
struct X : B {
    X(OBJ *p) {
 register char *vtable __asm__("$3")=D_002C94A0;
 x0=0;
 // Publish the vptr before zeroing the remaining header field.
 __asm__("sw %1,%0":"=m"(vt):"r"(vtable):"memory");
 x4=0;func_001D4D30(this,p);
}
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

#define OFF(T,F) ((unsigned int)&((T*)0)->F)
typedef char native_layout_0[(sizeof(int)==4)?1:-1];
typedef char native_layout_1[(sizeof(unsigned)==4)?1:-1];
typedef char native_layout_2[(sizeof(void*)==4)?1:-1];
typedef char native_layout_3[(sizeof(A)==4)?1:-1];
typedef char native_layout_4[(sizeof(B)==0x10)?1:-1];
typedef char native_layout_5[(sizeof(X)==0xB0)?1:-1];
typedef char native_layout_6[(OFF(X,x0)==0)?1:-1];
typedef char native_layout_7[(OFF(X,x4)==4)?1:-1];
typedef char native_layout_8[(OFF(X,vt)==0xC)?1:-1];
typedef char native_layout_9[(OFF(X,x10)==0x10)?1:-1];
typedef char native_layout_10[(OFF(X,x14)==0x14)?1:-1];
typedef char native_layout_11[(OFF(X,x18)==0x18)?1:-1];
typedef char native_layout_12[(OFF(X,x2C)==0x2C)?1:-1];
typedef char native_layout_13[(OFF(X,x38)==0x38)?1:-1];
typedef char native_layout_14[(OFF(OBJ,n)==0x4F8)?1:-1];
typedef char native_layout_15[(OFF(OBJ,a)==0x4FC)?1:-1];
