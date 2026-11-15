/* func_001A7970 (0x1A7970): runs the 19 start-up stages (the table g_apfnStartup) under a progress bar (Sly 1 main.c Startup:
 * CProg with the colours complete blue, remaining grey, warning yellow, trouble red; func_001C2A78 / 001C2BA8 around it as
 * Sly 1's SetPhase / ClearPhase): prints the build banner, ticks the clock before each stage; from the stage func_001700D0 on the bar shows
 * the stages remaining. */
struct B { char data[0x70]; };
struct C { int c; } __attribute__((aligned(16)));
extern char D_002A6A58[], D_002C46D8[], D_002C46C0[], g_clock[];
extern void (*g_apfnStartup[])(void) __asm__("D_002BFCE0");
#define CSTARTUP 19
void func_001700D0(void);
struct B *__5CProgP4RGBAN31(struct B *b, struct C *c0, struct C *c1, struct C *c2, struct C *c3);
int printf(char *format, ...);
void func_001C2A78(int n);
void Begin__5CProg(struct B *b);
void UpdateClock__FP5CLOCKi(void *p, int n);
void SetRemain__5CProgi(struct B *b, int n);
void End__5CProg(struct B *b);
void func_001C2BA8(int n);
void func_001A7970(void)
{
    struct B b;
    struct C rgbaComplete, rgbaRemain, rgbaWarning, rgbaTrouble;
    unsigned int i;
    int fCount;
    {
    register unsigned int a2 __asm__("$5")=0x80003F3F;
    register unsigned int a3 __asm__("$6")=0x8000003F;
    register unsigned int a0 __asm__("$3")=0x807F0000;
    register unsigned int a1 __asm__("$2")=0x803F3F3F;
    rgbaWarning.c=a2;
    rgbaTrouble.c=a3;
    rgbaComplete.c=a0;
    rgbaRemain.c=a1;
    }
    __5CProgP4RGBAN31(&b, &rgbaComplete, &rgbaRemain, &rgbaWarning, &rgbaTrouble);
    printf(D_002A6A58, D_002C46D8, D_002C46C0, 0x2B0);
    func_001C2A78(1);
    Begin__5CProg(&b);
    fCount = 0;
    for (i = 0; i < CSTARTUP; i++) {
        UpdateClock__FP5CLOCKi(g_clock, 1);
        if (fCount)
            SetRemain__5CProgi(&b, CSTARTUP - i);
        else if (g_apfnStartup[i] == func_001700D0)
            fCount = 1;
        g_apfnStartup[i]();
    }
    SetRemain__5CProgi(&b, 0);
    End__5CProg(&b);
    func_001C2BA8(1);
}
