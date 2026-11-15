/* func_00110D60 (0x110D60): factory (CLS::pfnNew) of class 13, derived from class 10 (SafeHouse: PATH): operator
 * new of a zeroed 0x1D0-byte object; the inline constructors set the vtable (0x2D6FE8) and the base fields. */
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
    char pad2[0x1D0 - 0x1B4];
    virtual void F();
};

extern "C" void *func_00110D60(void)
{
    return new X;
}
