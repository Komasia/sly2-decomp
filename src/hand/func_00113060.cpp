/* func_00113060 (0x113060): factory (CLS::pfnNew) of class 156, derived from class 155: operator new of a zeroed
 * 0xB0-byte object; the inline constructors set the vtable (0x2D04A0) and the base fields. */
extern "C" void *s1_memset(void *pv, int b, int cb) asm("memset");
class M {
public:
    M() { s1_memset(this, 0, sizeof(*this)); }
    int a[0x70 / 4];
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
    char pad2[0xB0 - 0xA0];
    virtual void F();
};

extern "C" void *func_00113060(void)
{
    return new X;
}
