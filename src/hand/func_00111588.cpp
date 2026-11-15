/* func_00111588 (0x111588): factory (CLS::pfnNew) of class 48 (SafeHouse: ALO), derived from class 2 (SafeHouse:
 * LO): operator new of a zeroed 0x150-byte object; the inline constructors set the vtable (0x2D9978) and the base
 * fields. */
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
};

extern "C" void *func_00111588(void)
{
    return new X;
}
