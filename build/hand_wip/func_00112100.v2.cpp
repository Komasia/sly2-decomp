// WIP v2 (Claude agent, 2026-10-17): 4 diffs. CRef ctor as inline calling extern void func_00167310 fixes the X vtable reg (v0). Left: SUB vtable a0 vs v1 + return move last.
extern "C" void func_00167310(void *);
class CRef {
public:
    CRef() { func_00167310(this); }
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
    char pad2[0x170 - 0x90];
    virtual void F();
};
class SUB {
public:
    SUB() {}
    virtual void G();
};
class Y : public X {
public:
    SUB sub;
    char padend[0x1a0 - 0x174];
    virtual void F();
};

extern "C" void *func_00112100(void)
{
    return new Y;
}
