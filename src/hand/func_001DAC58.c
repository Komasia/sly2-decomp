/* DrawGadgetIcons (SafeHouse shop.cpp): on the open gadget menu, mark each gadget the player has put in one of
 * its three ability slots with that slot's button icon (D_002C3268[slot], the icon font at scale D_002C3264) in a
 * 32 x 32 box at the entry's position. */
#include "cid.h"
typedef struct { float x, y, dx, dy; char pad[0x10]; } TXT;
typedef struct { char ab[0xA0]; } FONT;
typedef struct { int key; int a; int b; } SLOT;   /* an ability slot: its gadget */
typedef struct { char pad[0x1180]; SLOT aslot[3]; } Q;
typedef struct { int key; char pad[0x10]; float x; float y; char pad1c[4]; } GADGETENT;   /* field: SafeHouse port */
typedef struct GADGETMENU {           /* field: SafeHouse port (shop.cpp) */
    /* 0x00 */ char pad[0x24];
    /* 0x24 */ void *ploScreen;
    /* 0x28 */ char pad28[0x4C - 0x28];
    /* 0x4c */ int cent;
    /* 0x50 */ GADGETENT *aent;
} GADGETMENU;
extern struct G g_sw;
extern float D_002C3264;              /* the icon scale (0.66) */
extern int D_002C3268[];              /* the slots' button icons */
int FVisible__FP8SCREENRT(void *);
Q *PloPlayerPo__FP2SW(struct G *);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
void func_00258438(TXT *, float, float);
void func_00258448(TXT *, float, float);
void func_00258458(TXT *, unsigned int *);
void func_00258470(TXT *, int);
void func_00258478(TXT *, int);
FONT *func_00215AC0(FONT *, int, float);
void func_002163B0(FONT *, TXT *, int);
static inline float Zero(void){float z;__asm__ volatile("mtc1 $zero,%0":"=f"(z));return z;}
// name: SafeHouse port (DrawGadgetIcons)
void DrawGadgetIcons__FP7FONTBRX(GADGETMENU *pmenu)
{
    Q *q;
    int ient;
    if (pmenu->ploScreen == 0)
        return;
    if (!FVisible__FP8SCREENRT(pmenu->ploScreen))
        return;
    q = PloPlayerPo__FP2SW(&g_sw);
    if (q == 0)
        return;
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(q, CID_ACTOR))
        return;
    for (ient = 0; ient < pmenu->cent; ient++) {
        GADGETENT *pent = &pmenu->aent[ient];
        int islot;
        for (islot = 0; islot < 3; islot++) {
            if (pent->key == q->aslot[islot].key) {
                TXT txt;
                unsigned int rgba[2];
                FONT font;
                {float z=Zero();func_00258438(&txt,z,z);}
                func_00258448(&txt, 640.0f, 448.0f * 1.1f);
                rgba[0] = 0xFF808080;
                func_00258458(&txt, rgba);
                func_00258470(&txt, 0);
                func_00258478(&txt, 0);
                func_00215AC0(&font, D_002C3268[islot], D_002C3264);
                {float x=pent->x;float y=pent->y;txt.y=y;txt.x=x;}
                txt.dx = 32.0f;
                txt.dy = 32.0f;
                func_002163B0(&font, &txt, 0x13);
                break;
            }
        }
    }
}
