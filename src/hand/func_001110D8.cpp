/* func_001110D8 (0x1110D8): factory (CLS::pfnNew) of class 28, derived from class 3 (SafeHouse: LOX): operator new
 * of a zeroed 0x460-byte object; the inline constructors set the vtable (0x2CB5D8) and the base fields. */
class E {
public:
    E() {}
    int a[8];
};
class BASIC {
public:
    int m0; int m4; int m8;
    BASIC() { m0 = 0; m4 = 0; }
    virtual void F();
};
class X : public BASIC {
public:
    char pad[0x60 - 0x10];
    E ae[32];
    virtual void F();
};

extern "C" void *func_001110D8(void)
{
    return new X;
}
