typedef struct REC { int x0; int x4; int x8; } REC;
typedef struct OBJ { char pad[0x15C]; int x15C; char pad1[0x16C - 0x160]; void *x16C; } OBJ;
#define F(T, o) (*(T *)((char *)p + (o)))
#define A(o) ((char *)p + (o))

typedef struct SND { char pad[0xC]; int xC; } SND;
extern SND g_game;
extern char g_clock[];
extern float D_002BF3EC;
extern float D_002BF3F0;
extern float D_003E1BEC;

extern void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, void *pv);
extern void func_00141CD0(void *p, int n);
extern void func_0014D1D0(void *p, int n, float g);
extern void *PsndNewPlain__Fi(int n);
extern void SetSource__4CSndPv(void *p, int n);
extern void func_00258040(void *p, void *pv);
extern void SetJtJts__FP2JT3JTS4JTBS(void *p, int a, int b);
extern void SetJumpAnimState__FP4JUMPiP2LO(void *p, int a, int b);
extern REC *func_0018D6F8(void *p, int n);
extern void SetJtThrowState__FP7JTTHROWi(void *p, int n);
extern void StartInteract__FP5ACTORii3JTL(void *p, int a, int b, int c);
extern OBJ *PloAcquireProxyObject__FP2SWi(int oid, int n);
extern int func_00224610(OBJ *p);
extern void SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(void *p, REC *prec, OBJ *pobj);
extern void func_00141EA8(void *p, int n);
extern void ExplodeExpl__FP4EXPL(int x);
extern void SetJumpKind__FP4JUMPiiP2LO(void *p, int a, int b, int c);
extern void func_00141D38(void *p, int n);

void func_0018DA48(char *p, int n)
{
    g_game.xC = n;
    BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x3C, p);
    switch (n) {
    case 0x1D: {
        void *pv;
        func_00141CD0(p, n);
        func_0014D1D0(g_clock, 1, D_002BF3EC);
        D_003E1BEC = -1.0f;
        pv = PsndNewPlain__Fi(0x67);
        SetSource__4CSndPv(pv, 0);
        func_00258040(A(0x2044), pv);
        break;
    }
    case 0x2A: {
        void *pv;
        func_00141CD0(p, n);
        func_0014D1D0(g_clock, 1, D_002BF3F0);
        D_003E1BEC = 0.7f;
        pv = PsndNewPlain__Fi(0x66);
        SetSource__4CSndPv(pv, 0);
        func_00258040(A(0x2044), pv);
        break;
    }
    case 0x21:
        func_00141CD0(p, n);
        SetJtJts__FP2JT3JTS4JTBS(p, 9, -1);
        break;
    case 0x1B:
        func_00141CD0(p, n);
        SetJumpAnimState__FP4JUMPiP2LO(A(0x2C0), 0x13, 0);
        break;
    case 0x1A:
    case 0x25:
    case 0x26:
    case 0x29: {
        REC *prec = func_0018D6F8(p, n);
        OBJ *pobj;
        if ((unsigned int)(F(int, 0x11B4) - 4) < 3) {
            SetJtThrowState__FP7JTTHROWi(A(0x11B0), 7);
            break;
        }
        if (prec->x8) {
            StartInteract__FP5ACTORii3JTL(A(0x4C0), 0xB, prec->x8, 0);
            break;
        }
        pobj = PloAcquireProxyObject__FP2SWi(prec->x4, 0);
        if (!pobj)
            break;
        pobj->x15C = prec->x0;
        if (func_00224610(pobj)) {
            pobj->x16C = p;
            SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(p, prec, pobj);
        }
        F(OBJ *, 0x11C0) = pobj;
        func_00141EA8(p, n);
        SetJtJts__FP2JT3JTS4JTBS(p, 0x17, -1);
        SetJtThrowState__FP7JTTHROWi(A(0x11B0), 4);
        break;
    }
    case 0x22:
    case 0x23:
        F(int, 0x9BC) = n;
        if (n == 0x23)
            F(int, 0x130C) = F(int, 0x1FE0);
        else
            F(int, 0x130C) = F(int, 0x1FE4);
        StartInteract__FP5ACTORii3JTL(A(0x4C0), 0xB, 0, 0);
        break;
    case 0x18:
        func_00141CD0(p, n);
        SetJtJts__FP2JT3JTS4JTBS(p, 6, -1);
        break;
    case 0x19:
        func_00141CD0(p, n);
        SetJtJts__FP2JT3JTS4JTBS(p, 0x18, 0xC);
        break;
    case 0x27:
        func_00141CD0(p, n);
        SetJtJts__FP2JT3JTS4JTBS(p, 5, 9);
        break;
    case 0x28:
        func_00141CD0(p, n);
        StartInteract__FP5ACTORii3JTL(A(0x4C0), 2, 0, 0);
        break;
    case 0x1F:
        if (F(int, 0x204C))
            ExplodeExpl__FP4EXPL(F(int, 0x204C));
        func_00141CD0(p, n);
        SetJumpKind__FP4JUMPiiP2LO(A(0x2C0), 9, 0, 0);
        break;
    case 0x1E:
        func_00141CD0(p, n);
        SetJumpKind__FP4JUMPiiP2LO(A(0x2C0), 0xE, 0, 0);
        break;
    default:
        func_00141D38(p, n);
        break;
    }
}
