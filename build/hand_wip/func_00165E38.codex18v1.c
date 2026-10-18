// Property-backed menu selection.
typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct G { char pad[0x3B1C]; void *f3b1c; char pad2[0x3B28 - 0x3B20]; void *f3b28; char pad3[0x3B7C - 0x3B2C]; void *a3b7c[0]; };
struct Q { int a[4]; int f10; int f14; int f18; };
extern struct G D_003DD490;
extern struct Q D_002DEB30;
extern void *D_002DEB4C;
extern char D_003DA530[];
extern char D_002A3828[];
CRef*func_002581C0(CRef *pref, void *a, void *b);
void func_00129EC8(CRef *pref);
int func_001D9880(void *p);
void func_001D54B8(void);
void func_001DD888(void *p);
void *func_00210B98(int n);
void func_0022B490(struct G *pg, void *p, int a, int b, int c, int d);
static inline struct G*StableGameAddress(char*high){struct G*game;const unsigned address=0x3DD490;__asm__("addiu %0,%1,%2":"=&r"(game):"r"(high),"i"((short)(address&0xffff)));return game;}
static inline int SmallProperty(int value){return value<100;}
void func_00165E38(void *pv)
{
    CRef ref;
    float g;
    register int n __asm__("$16");
    void *ps;
    const unsigned gameAddress=0x3DD490;
    register char*initialHigh __asm__("$2");
    struct G*game,*zeroGame;void*property;
    register struct G*firstGame __asm__("$2");
    register char*gameHigh __asm__("$20");
    __asm__("lui %0,%1":"=r"(initialHigh):"i"((gameAddress+0x8000)>>16));
    gameHigh=initialHigh;
    __asm__("addiu %0,%1,%2":"=r"(firstGame):"r"(initialHigh),"i"((short)(gameAddress&0xffff)));
    func_002581C0(&ref, firstGame->f3b1c, pv);
    g = *(float *)&ref.m_tag;
    func_00129EC8(&ref);
    if (func_001D9880(D_003DA530)) {
        if (g == 0.0f) {
            func_001D54B8();
            func_001DD888(D_003DA530);
            return;
        }
    } else if (g == 0.0f) {
        D_002DEB4C = pv;
        D_002DEB30.f10 = -1;
        D_002DEB30.f14 = -1;
        D_002DEB30.f18 = 0x62F;
        zeroGame=StableGameAddress(gameHigh);
        func_0022B490(zeroGame, func_00210B98(0), 0x189, -1, 0x48, -1);
        return;
    }
    game=StableGameAddress(gameHigh);property=game->f3b28;
    D_002DEB4C = pv;
    D_002DEB30.f10 = -1;
    D_002DEB30.f14 = -1;
    D_002DEB30.f18 = -1;
    func_002581C0(&ref, property, pv);
    __asm__("lw %0,%1":"=r"(n):"m"(ref.m_tag));
    func_00129EC8(&ref);
    ps = func_00210B98(n);
    property=game->a3b7c[n];
    n=0;
    if (property) {
        func_002581C0(&ref, property, pv);
        __asm__("lw %0,%1":"=r"(n):"m"(ref.m_tag));
        func_00129EC8(&ref);
    }
    if (!SmallProperty(n) || !ps)
        ps = D_002A3828;
    func_0022B490((struct G*)(gameHigh+(short)(gameAddress&0xffff)), ps, 0x189, -1, 0x40, -1);
}

#define OFFSET(t,m) ((unsigned)&(((t*)0)->m))
typedef char layout_pointer[sizeof(void*)==4?1:-1];
typedef char layout_int[sizeof(int)==4?1:-1];
typedef char layout_float[sizeof(float)==4?1:-1];
typedef char layout_CRef[sizeof(CRef)==8?1:-1];
typedef char layout_CRef_kind[OFFSET(CRef,m_tagk)==0?1:-1];
typedef char layout_CRef_value[OFFSET(CRef,m_tag)==4?1:-1];
typedef char layout_G_prefix[sizeof(struct G)==0x3B7C?1:-1];
typedef char layout_G_first[OFFSET(struct G,f3b1c)==0x3B1C?1:-1];
typedef char layout_G_second[OFFSET(struct G,f3b28)==0x3B28?1:-1];
typedef char layout_G_slots[OFFSET(struct G,a3b7c)==0x3B7C?1:-1];
typedef char layout_Q[sizeof(struct Q)==0x1C?1:-1];
typedef char layout_Q_first[OFFSET(struct Q,f10)==0x10?1:-1];
typedef char layout_Q_second[OFFSET(struct Q,f14)==0x14?1:-1];
typedef char layout_Q_third[OFFSET(struct Q,f18)==0x18?1:-1];
