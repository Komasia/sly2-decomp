/* func_00110EC0 (0x110EC0): factory (CLS::pfnNew) of class 19, derived from class 18: operator new of a zeroed
 * 0x140-byte object; the inline constructors set the vtable (0x2D2978) and the base fields. */
class M {
public:
    M() {}
    char pad[0x120 - 0x10];
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
    char pad2[0x140 - 0x120 - 4];
    virtual void F();
};

extern "C" void *func_00110EC0(void)
{
    return new X;
}
