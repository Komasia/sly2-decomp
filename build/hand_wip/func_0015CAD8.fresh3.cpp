// SLY2_ASM: gnu-reorder-db
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
struct SLOTHEAP;
extern "C" SLOTHEAP *func_0011CCA8(SLOTHEAP*,int,int,int);
struct SLOTHEAP { int bytes,count,alignment;void *head;int allocated;void *block; };
extern int D_002DD2E0,D_002DD2E4,D_002DD2E8,D_002DD2EC,D_002DD2F0,D_002DD2F4;
struct POOLA;extern POOLA D_004520A8;
extern SLOTHEAP ViewA __asm__("D_004520A8");
struct POOLA:SLOTHEAP{POOLA(){if(D_002DD2E0++==0)func_0011CCA8(&ViewA,0x14,0x2000,0x10);}};
POOLA D_004520A8;
struct POOLB;extern POOLB D_004520D0;
extern SLOTHEAP ViewB __asm__("D_004520D0");
struct POOLB:SLOTHEAP{POOLB(){if(D_002DD2E4++==0)func_0011CCA8(&ViewB,0x18,0x800,0x10);}};
POOLB D_004520D0;
struct POOLC;extern POOLC D_004520F8;
extern SLOTHEAP ViewC __asm__("D_004520F8");
struct POOLC:SLOTHEAP{POOLC(){if(D_002DD2E8++==0)func_0011CCA8(&ViewC,0x28,0x200,0x10);}};
POOLC D_004520F8;
struct POOLD;extern POOLD D_00452120;
extern SLOTHEAP ViewD __asm__("D_00452120");
struct POOLD:SLOTHEAP{POOLD(){if(D_002DD2EC++==0)func_0011CCA8(&ViewD,0x1C,0x800,0x10);}};
POOLD D_00452120;
struct POOLE;extern POOLE D_00452148;
extern SLOTHEAP ViewE __asm__("D_00452148");
struct POOLE:SLOTHEAP{POOLE(){if(D_002DD2F0++==0)func_0011CCA8(&ViewE,0xC,0xC8,0x10);}};
POOLE D_00452148;
struct POOLF;extern POOLF D_00452170;
extern SLOTHEAP ViewF __asm__("D_00452170");
struct POOLF:SLOTHEAP{POOLF(){if(D_002DD2F4++==0)func_0011CCA8(&ViewF,0x14,0x100,0x10);}};
POOLF D_00452170;

__asm__(".text\n"
        ".globl func_0015CAD8\n"
        ".type func_0015CAD8,@function\n"
        "func_0015CAD8:\n"
        ".size func_0015CAD8,620\n");
