// SLY2_ASM: gnu-reorder-db
// (Lilly's agent, T1648) WIP, aligned 24/155 (best C draft func_0015CAD8_v3.c is 21).
// This is a C++ __static_initialization_and_destruction_0. The six `if (++counter == 1)` guards are NOT
// source code: g++ 2.95 emits them itself ("sentries", common ints named __sn<asm name>) for weak / template
// static objects with constructors (decl2.c get_sentry). So D_002DD2E0..F4 are compiler-made sentries of
// the pools D_004520A8..D_00452170, and their real names hash like __sn<real pool asm name>.
// The two memset temps are aggregate initializers with a non-constant element (the D_002A2Dx0 vectors):
// EMITO / EMITV defaults that func_00159118 (InitEmitb-like) copies into EMITB+0x10 / +0x50.
// Left (see notes/150000.md T1648): sentry %hi pseudo order (needs gcse table size 75/77, we have 71),
// DD0/DA0 hi v0/v1 swap, s1/a2 issue order, CLQ g2 store goes through `this` (target: sp-relative and
// both CLQ stores last), loop end / 200 register choice.
typedef int qword __attribute__((mode(TI)));

struct S1 { int a[4]; int x10; int pad[3]; qword q20; qword q30; };

// Sly 1 CLQ (util.h): quadratic {g0, g1, g2, gUnused}; EMITV+0x60 = {1, 0, -1}.
struct CLQ {
    float g0, g1, g2, gUnused;
    CLQ(float a, float c) { g2 = c; g0 = a; }
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
    CLQ clq60;
};

extern qword D_002A2DD0, D_002A2DA0, D_002A2DC0;

S1 D_002DE5B0 = { {0, 0, 0, 0}, -1, {0, 0, 0}, D_002A2DD0, D_002A2DA0 };
S2 D_002DE5F0 = { 750.0f, 750.0f, -1.0f, 1.0f, 0, 0, -1500.0f, 0, D_002A2DC0, 0, 200, 1.0f, 1.0f,
                  {0, 0, 0, 0, 0, 0, 0, 0}, CLQ(1.0f, -1.0f) };

// func_0011CCA8 returns its first argument: a g++ constructor (ctors return `this`).
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
