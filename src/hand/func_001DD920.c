typedef struct { char pad[0x10B4]; int fl; } PAD;
typedef struct {
    char pad[0x10];
    PAD *pad10;
    char pad14[0x24 - 0x14];
    void *x24;
} OBJ;
typedef struct { int ids; void (*pfn)(void); int k; int pad[5]; } ITEM;
typedef struct { char pad[0xFD50]; void *xFD50; void *xFD54; } BIG;
extern BIG D_002E65E0;
extern char D_002E6550[];
extern struct G g_sw;
extern char D_003D9ED0[];
extern ITEM D_003DA578[];
extern int D_002C35B8[];
extern char D_002C35F0[];
void func_001DD8E0(void);
void func_001DA808(OBJ *);
int GrfbtnTakePressedJoy(PAD *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
int func_00187DD0(PAD *, int);
void SetJoyPs2BtnHandled__FP6JOYPS2Ui(PAD *, int);
void AentOptions__FPv(int);
void func_001ACC38(void *, int);
void StartGameFromSave__FP2SW(void *);
void StartNewGameFromTitle__Fv(OBJ *);
int func_001A2C98(void);
void *PloFindSwNearest__FP2LO3OIDii(struct G *, int, int, int);
void FRegionLanguages__FPiPUi(int *, int **);
void *s1_memset(void *, int, int) asm("memset");
void PushPage__FP4MENUiPviUi(void *, int, ITEM *, void *, void *);
void func_001DD920(OBJ *p)
{
    void *pv;
    int c;
    int *ak;
    int i;
    func_001DA808(p);
    if (p->x24 == 0)
        return;
    if (p->pad10 == 0)
        return;
    if (GrfbtnTakePressedJoy(p->pad10, 0x800)) {
        if ((D_002E65E0.xFD50 = D_002E65E0.xFD54) != 0) {
            func_001ACC38(D_002E6550, 1);
            StartGameFromSave__FP2SW(D_002E65E0.xFD50);
        } else {
            StartNewGameFromTitle__Fv(p);
        }
        return;
    }
    if (func_00187DD0(p->pad10, 0x100) && (p->pad10->fl & 0x108) == 0x100) {
        SetJoyPs2BtnHandled__FP6JOYPS2Ui(p->pad10, 0x100);
        AentOptions__FPv(0);
        return;
    }
    if (func_001A2C98() < 2)
        return;
    if (!GrfbtnTakePressedJoy(p->pad10, 0x10))
        return;
    pv = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, 0x5D6, 0);
    if (pv == 0)
        return;
    FRegionLanguages__FPiPUi(&c, &ak);
    for (i = 0; i < c; i++) {
        int k = ak[i];
        ITEM *pi = &D_003DA578[i];
        s1_memset(pi, 0, sizeof(ITEM));
        pi->k = k;
        pi->ids = D_002C35B8[k];
        pi->pfn = func_001DD8E0;
    }
    PushPage__FP4MENUiPviUi(D_003D9ED0, c, D_003DA578, pv, D_002C35F0);
}
