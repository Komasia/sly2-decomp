/* func_00110CD0 (0x110CD0): factory (CLS::pfnNew) of class 11, derived from class 10 (SafeHouse: PATH): operator
 * new of a zeroed 0x1E0-byte object; the inline constructors set the vtable (0x2D56F8) and the base fields. */
class M {
public:
    M() {}
    char pad[0x1B0 - 0x10];
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
    char pad2[0x1E0 - 0x1B4];
    virtual void F();
};

extern "C" void *func_00110CD0(void)
{
    return new X;
}
