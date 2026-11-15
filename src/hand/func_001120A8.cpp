/* func_001120A8 (0x1120A8): factory (CLS::pfnNew) of class 87, derived from class 48 (SafeHouse: ALO): operator new
 * of a zeroed 0x1B0-byte object; the inline constructors set the vtable (0x2D77D8) and the base fields. */
class CRef {
public:
    CRef();
    int a[4];
};
class BASIC {
public:
    int m0; int m4; int m8;
    BASIC() { m0 = 0; m4 = 0; }
    virtual void F();
};
class X : public BASIC {
public:
    char pad[0x80 - 0x10];
    CRef ref;
    char pad2[0x150 - 0x90];
    virtual void F();
};
class Y : public X {
public:
    char padend[0x1b0 - 0x150];
    virtual void F();
};

extern "C" void *func_001120A8(void)
{
    return new Y;
}
