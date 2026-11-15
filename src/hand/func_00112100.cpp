// func_00112100 MATCH (Claude agent, lane A12, 2026-10-23), from v3 (1): commented pin on the SUB vtable pointer (a0, as the target) plus a commented volatile empty asm before the vt store, which keeps `sw a0,0x170` ahead of the return move (sched2 tie-break).
/* func_00112100 (0x112100): factory (CLS::pfnNew) of class 88, derived from class 48 (SafeHouse: ALO): operator new
 * of a zeroed 0x1A0-byte object; the inline constructors set the vtable (0x2D20D0) and the base fields. */
extern "C" void __7GLOBSET(void *);   /* GLOBSET::GLOBSET() (0x167310) */
/* stand-in for the SO::globset member (named Globset so its inline constructor does not collide with __7GLOBSET) */
class Globset {
public:
    Globset() { __7GLOBSET(this); }
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
    Globset globset;
    char pad2[0x170 - 0x90];
    virtual void F();
};
extern "C" char D_002D2090[];
class SUB {
public:
    void *vt;
    SUB() { register void *p __asm__("$4") = D_002D2090; /* pin */ __asm__ volatile(""); /* scheduling barrier (toolchain emulation) */ vt = p; }
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
