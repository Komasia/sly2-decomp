struct DB { union { int w; unsigned char b[4]; } u; int pad[9]; };
extern char D_002DFB40[];
extern struct DB D_002DEB80[2];
extern char D_002DEDC0[], D_002DF260[], D_002DF010[], D_002DF4B0[], D_002DF700[], D_002DF720[];
extern int D_002DFB4C, D_002DFB50;
void InitCritSect(void *p) asm("InitCritSect__FP8CRITSECT");
void sceGsResetGraph(int a, int b, int c, int d);
void sceGsSetDefDBuff(struct DB *p, int a, int b, int c, int d, int e, int f);
void BuildClearGifs(void *p, int *pc, int n) asm("BuildClearGifs__FP2QWG4RGBAi");
void func_0016FAF8(int a, void *p, int n);
void func_00170048(void);
int SemaCreate(int a, int b) asm("SemaCreate__Fii");
void VBlankS_Interrupt(void) asm("VBlankS_Interrupt__Fi");
void ResetGs(void) asm("ResetGs__Fv");
void func_00234700(int a, void (*pfn)(void), int b);
void func_00235178(int a);
void GS_Interrupt(void) asm("GS_Interrupt__Fi");
void func_001700D0(void) {
    int i;
    int c;
    InitCritSect(D_002DFB40);
    sceGsResetGraph(0, 1, 2, 1);
    sceGsSetDefDBuff(D_002DEB80, 0, 0x200, 0xE0, 3, 0x30, 0);
    for (i = 0; i < 2; i++) {
        D_002DEB80[i].u.w &= ~1;
        D_002DEB80[i].u.b[1] = 0x80;
        D_002DEB80[i].u.w |= 0x20;
    }
    c = 0x80000000;
    BuildClearGifs(D_002DEDC0, &c, 3);
    c = 0x80000000;
    BuildClearGifs(D_002DF260, &c, 3);
    c = 0x80000000;
    BuildClearGifs(D_002DF010, &c, 2);
    c = 0x80000000;
    BuildClearGifs(D_002DF4B0, &c, 1);
    func_0016FAF8(2, D_002DF700, 1);
    func_0016FAF8(2, D_002DF720, 0);
    func_00170048();
    D_002DFB4C = SemaCreate(0, 1);
    D_002DFB50 = SemaCreate(0, 1);
    func_00234700(2, VBlankS_Interrupt, 0);
    func_00235178(2);
    func_00234700(0, ResetGs, 0);
    func_00235178(0);
    GS_Interrupt();
    *(volatile int *)0x10003010 = 0;
}
