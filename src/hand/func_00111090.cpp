/* func_00111090 (0x111090): factory (CLS::pfnNew) of class 27, derived from class 22 (SafeHouse: SHAPE): operator
 * new of a zeroed 0x160-byte object; the inline constructors set the vtable (0x2D1B60) and the base fields. */
class M {
public:
    M() {}
    char pad[0x150 - 0x10];
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
    char pad2[0x160 - 0x150 - 4];
    virtual void F();
};

extern "C" void *func_00111090(void)
{
    return new X;
}
