/* func_00111DE8 (0x111DE8): factory (CLS::pfnNew) of class 78, derived from class 50 (SafeHouse: SO): operator new
 * of a zeroed 0x230-byte object; the inline constructors set the vtable (0x2D5B30) and the base fields. */
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
    char padend[0x230 - 0x178];
    Y() { n174 = 0; }
    virtual void F();
};

extern "C" void *func_00111DE8(void)
{
    return new Y;
}
