/* func_00113708 (0x113708): factory (CLS::pfnNew) of class 186, derived from class 155: operator new of a zeroed
 * 0xD0-byte object; the inline constructors set the vtable (0x2CFE20) and the base fields. */
class M {
public:
    M();
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
    char pad[0x40 - 0x10];
    M m0;
    M m1;
    M m2;
    char pad2[0xD0 - 0xA0];
    virtual void F();
};

extern "C" void *func_00113708(void)
{
    return new X;
}
