/* func_001112A8 (0x1112A8): factory (CLS::pfnNew) of class 36, derived from class 35: operator new of a zeroed
 * 0x1A0-byte object; the inline constructors set the vtable (0x2D1D00) and the base fields. */
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
    char pad2[0x1A0 - 0x100 - 4];
    virtual void F();
};

extern "C" void *func_001112A8(void)
{
    return new X;
}
