/* func_00111260 (0x111260): factory (CLS::pfnNew) of class 35, derived from class 3 (SafeHouse: LOX): operator new
 * of a zeroed 0x180-byte object; the inline constructors set the vtable (0x2D1EE8) and the base fields. */
class M {
public:
    M() {}
    char pad[0x100 - 0x10];
    virtual void G();
};
class BASIC {
public:
    int m0; int m4; int m8;
    BASIC() { m0 = 0; m4 = 0; }
    virtual void F();
};
class X : public BASIC, public M {
public:
    char pad2[0x180 - 0x100 - 4];
    virtual void F();
};

extern "C" void *func_00111260(void)
{
    return new X;
}
