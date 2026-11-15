/* func_00113840 (0x113840): factory (CLS::pfnNew) of class 191, derived from class 155: operator new of a zeroed
 * 0x50-byte object; the inline constructors set the vtable (0x2CFC20) and the base fields. */
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
    char pad[0x30 - 0x10];
    M m;
    virtual void F();
};

extern "C" void *func_00113840(void)
{
    return new X;
}
