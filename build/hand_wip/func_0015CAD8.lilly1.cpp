// SLY2_ASM: gnu-reorder-db
// (Lilly's agent, T1648) fresh2 + pools as weak objects with a ctor: g++ then emits the `++__sn<pool> == 1` sentries
// itself (aligned 33 at gcse table size 71; 27 with the target's sentry pseudo order). See lilly2.cpp (24).
// (Claude agent) fresh1: real C++ static initialization (pattern from src/hand/func_002019F0.cpp)
typedef int qword __attribute__((mode(TI)));
extern "C" void *func_002333B4(void *, int, unsigned);
struct S1 {
    int a[4]; int x10; int pad[3]; qword q20; qword q30;
};
struct S2 {
    float x0, x4, x8, xC;
    int x10, x14;
    float x18;
    int x1C;
    qword q20;
    int x30;
    int x34;
    float x38, x3C;
    int x40[8];
    float x60;
    int x64;
    float x68;
    int x6C;
};
extern qword D_002A2DD0, D_002A2DA0, D_002A2DC0;
S1 D_002DE5B0 = { {0, 0, 0, 0}, -1, {0, 0, 0}, D_002A2DD0, D_002A2DA0 };
S2 D_002DE5F0 = { 750.0f, 750.0f, -1.0f, 1.0f, 0, 0, -1500.0f, 0, D_002A2DC0, 0, 200, 1.0f, 1.0f, {0,0,0,0,0,0,0,0}, 1.0f, 0, -1.0f };
struct SLOTHEAP {
    SLOTHEAP(int cb, int c, int align);
    int cb, c, align; void *head; int allocated; void *block;
};
extern SLOTHEAP D_004520A8 __attribute__((weak));
SLOTHEAP D_004520A8(0x14, 0x2000, 0x10);
extern SLOTHEAP D_004520D0 __attribute__((weak));
SLOTHEAP D_004520D0(0x18, 0x800, 0x10);
extern SLOTHEAP D_004520F8 __attribute__((weak));
SLOTHEAP D_004520F8(0x28, 0x200, 0x10);
extern SLOTHEAP D_00452120 __attribute__((weak));
SLOTHEAP D_00452120(0x1C, 0x800, 0x10);
extern SLOTHEAP D_00452148 __attribute__((weak));
SLOTHEAP D_00452148(0xC, 0xC8, 0x10);
extern SLOTHEAP D_00452170 __attribute__((weak));
SLOTHEAP D_00452170(0x14, 0x100, 0x10);

__asm__(".text\n"
        ".globl func_0015CAD8\n"
        ".type func_0015CAD8,@function\n"
        "func_0015CAD8:\n"
        ".size func_0015CAD8,620\n");
