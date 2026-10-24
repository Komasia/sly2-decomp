// v4 (Claude agent, 2026-10-17): aligned 3 (v3 was 4). Separate stores D_0044BE00[0] = 0; p[1] = 0.0f; and the serve test on D_0044BD80.serve directly (no p reuse): store order + serve-in-v0 now right. Left: prologue only (target sd s0; lui s0; sd s1; sd ra; addiu s1 -- ours sd s1 first, the old luid tie). p assigned after func_00236A60: 8; &D[0]: same 3.
// v3 (Claude, from a permuter hint): chained `D_0044BE00[0] = p[1] = 0.0f;` and p reused for the serve test -> 4 diffs (was 6).
// WIP (Claude agent): 6 diffs, prologue save/lui scheduling only (target: sd s0; lui s0; sd s1; sd ra; addiu s1).
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; } ClientData;
typedef struct { char c[4]; } B4;
struct iob { int fd, busy, x8, xC; };
extern int D_0044BE00[2];
extern char D_0044BDC0[];
extern ClientData D_0044BD80;
extern int D_002C4A88;
extern struct iob D_0044BB80[32];
extern void *D_0044A640[2];
extern char D_0044B300[];
extern B4 D_0044B2C0[2];
extern B4 D_0044BDA8;
extern int D_002C4A7C;
extern int D_002C4A80;
void func_00236A60(int);
int func_00239450(void);
int func_002394A0(void);
void *func_0023ADA8(unsigned int, void *, void *);
void _sceFs_Rcv_Intr(void *);
void _sceFs_Poff_Intr(void *);
int sceSifBindRpc(ClientData *, unsigned int, unsigned int);
void _sceFsIobSemaMK(void);
int func_00234A60(int);
int func_00234A40(int);
int func_002375E0(void *, int, int, void *, int, void *, int, void *, void *, int);
int sceFsInit(void)
{
    int oldei, i;
    struct iob *io;
    B4 tmp;
    float *p = (float *)D_0044BE00;
    func_00236A60(0);
    D_0044BE00[0] = 0;
    p[1] = 0.0f;
    oldei = func_00239450();
    func_0023ADA8(0x80000011, _sceFs_Rcv_Intr, D_0044BDC0);
    func_0023ADA8(0x80000013, _sceFs_Poff_Intr, p);
    if (oldei) func_002394A0();
    while (1) {
        if (sceSifBindRpc(&D_0044BD80, 0x80000001, 0) < 0)
            return -22;
        if (D_0044BD80.serve != 0)
            break;
        i = 0x100000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    _sceFsIobSemaMK();
    func_00234A60(D_002C4A88);
    for (io = D_0044BB80; io < &D_0044BB80[32]; io++)
        { __asm__ volatile(""); io->busy = 0; }
    func_00234A40(D_002C4A88);
    D_0044A640[0] = D_0044B300;
    D_0044A640[1] = D_0044B300 + 0x440;
    if (func_002375E0(&D_0044BD80, 0xFF, 0, D_0044A640, 8, D_0044B2C0, 8, 0, 0, 0) < 0)
        return 0xFFFEFFFF;
    D_0044BDA8 = *(B4 *)((unsigned int)&D_0044B2C0[0] | 0x20000000);
    tmp = *(B4 *)((unsigned int)&D_0044B2C0[1] | 0x20000000);
    D_002C4A80 = *(int *)&tmp == 2;
    D_002C4A7C = 1;
    return 0;
}
