/* func_001121B8 (0x1121B8): factory (CLS::pfnNew) of class 91, derived from class 90: operator new of a zeroed
 * 0x240-byte object; the inline constructors set the vtable (0x2D6928) and the base fields. */
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
    char padend[0x240 - 0x150];
    virtual void F();
};

extern "C" void *func_001121B8(void)
{
    return new Y;
}
