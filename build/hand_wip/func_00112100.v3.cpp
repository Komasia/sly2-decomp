// v3 (Claude agent, lane A8, 2026-10-23): aligned 3 -> 1. SUB written without virtuals: a `void *vt` member set in its ctor from a pinned `register void *p asm("$4")` (commented pin) gives the target a0 vtable reg. Left: `sw a0,0x170(s0)` comes after the return move. Y*/void* temps, volatile vt, store in Y ctor: same; a "memory" barrier fixes it but swaps the epilogue lq/ld.
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
extern "C" char D_002D2090[];
class SUB {
public:
    void *vt;
    SUB() { register void *p __asm__("$4") = D_002D2090; /* pin */ vt = p; }
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
