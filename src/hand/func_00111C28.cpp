/* func_00111C28 (0x111C28): factory (CLS::pfnNew) of class 73, derived from class 71: operator new of a zeroed
 * 0x390-byte object; the inline constructors set the vtable (0x2D1080) and the base fields. */
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
    char pad_174[0x174 - 0x150];
    int n174;
    char padend[0x390 - 0x178];
    Y() { n174 = 0; }
    virtual void F();
};

extern "C" void *func_00111C28(void)
{
    return new Y;
}
