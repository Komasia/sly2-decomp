// (Lilly's agent, T1652) WIP, aligned 15/155 (20 raw), no pins. func_0015CAD8_v3.c + a STAND-IN `if (fNever)` block (3 dead calls,
// same trick as func_00219400 / func_001681F8): cprop folds it, jump deletes it, the final code is unchanged; it only grows the gcse
// expression table so the six %hi(D_002DD2Ex) counter pseudos get the game's s-registers. func_0015CAD8.lilly4.c (aligned 7) adds one
// pin for the 200; the remaining diffs are described there and in notes/150000.md (T1652).
typedef int qword __attribute__((mode(TI)));
typedef struct S1 { int a[4]; int x10; int pad[3]; qword q20; qword q30; } S1;
typedef struct S2 {
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
} S2;
extern S1 D_002DE5B0;
extern S2 D_002DE5F0;
extern qword D_002A2DD0, D_002A2DA0, D_002A2DC0;
extern int D_002DD2E0, D_002DD2E4, D_002DD2E8, D_002DD2EC, D_002DD2F0, D_002DD2F4;
extern char D_004520A8[], D_004520D0[], D_004520F8[], D_00452120[], D_00452148[], D_00452170[];
extern void *func_002333B4(void *, int, unsigned int);
extern void func_0011CCA8(void *, int, int, int);
void func_0015CAD8(int fInit, int prio)
{
    int fNever = 0;
    if (prio == 0xFFFF && fInit) {
        {
            S1 *p = &D_002DE5B0;
            S1 t;
            func_002333B4(&t, 0, sizeof(t));
            t.x10 = -1;
            t.q20 = D_002A2DD0;
            t.q30 = D_002A2DA0;
            *p = t;
        }
        {
            S2 *p = &D_002DE5F0;
            S2 t;
            func_002333B4(&t, 0, sizeof(t));
            t.xC = 1.0f;
            t.x0 = 750.0f;
            t.x3C = 1.0f;
            t.x4 = 750.0f;
            t.x60 = 1.0f;
            t.x34 = 200;
            t.x68 = -1.0f;
            t.x18 = -1500.0f;
            t.q20 = D_002A2DC0;
            t.x8 = -1.0f;
            t.x38 = 1.0f;
            *p = t;
        }
        if (++D_002DD2E0 == 1)
            func_0011CCA8(D_004520A8, 0x14, 0x2000, 0x10);
        if (++D_002DD2E4 == 1)
            func_0011CCA8(D_004520D0, 0x18, 0x800, 0x10);
        if (++D_002DD2E8 == 1)
            func_0011CCA8(D_004520F8, 0x28, 0x200, 0x10);
        if (++D_002DD2EC == 1)
            func_0011CCA8(D_00452120, 0x1C, 0x800, 0x10);
        if (++D_002DD2F0 == 1)
            func_0011CCA8(D_00452148, 0xC, 0xC8, 0x10);
        if (++D_002DD2F4 == 1)
            func_0011CCA8(D_00452170, 0x14, 0x100, 0x10);
        if (fNever) { /* STAND-IN for dead code the game had at gcse time (see top) */
            func_0011CCA8(0, 0, 0, 0);
            func_0011CCA8(0, 1, 0, 0);
            func_0011CCA8(0, 2, 0, 0);
        }
    }
}
