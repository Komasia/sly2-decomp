/* class: OVERLAY (SafeHouse overlay.cpp's State, orig 0x147410): the animated overlay's state (-1 off, 0 started,
 * 1 / 2 shown, 3 waiting for its dialog). Leaving -1 the overlay takes the screen: it becomes the owner, the sound
 * manager's flag 2 and clock factor 8 are cleared (the game clock stops), the game is paused, the overlay is added to
 * the world (vt slot 8) and its root registered when inactive. Going back to -1 undoes that (vt slot 9 removes it).
 * State 3 holds the overlay's animation (speed 0) until the dialog ends. The state's start is on the real clock.
 * Layout: SafeHouse port (overlay.cpp OVERLAY). */
#include "so.h"
struct LOROOT { struct LO *plo; };   /* the object's root node: its root object */
struct OVERLAY {
    /* 0x000 */ char pad[0xC];
    /* 0x00c */ VTENT *vt;
    /* 0x010 */ char pad1[0x14 - 0x10];
    /* 0x014 */ struct LOROOT *ploroot;
    /* 0x018 */ char pad2[0x150 - 0x18];
    /* 0x150 */ int state;      /* field: SafeHouse port */
    /* 0x154 */ float tState;   /* field: SafeHouse port */
    /* 0x158 */ char pad3[0x160 - 0x158];
    /* 0x160 */ void *pasega;   /* field: SafeHouse port */
};
#define VTS_AddLo 8
#define VTS_RemoveLo 9
#define VTS_RegisterLoTree 23
#define SOUNDMGRF_2 2              /* the sound manager flag the overlay clears while it is shown */
#define CLOCKFACTOR_Overlay 8      /* the clock factor the overlay sets to 0 while it is shown */
#include "clock.h"

extern struct OVERLAY *D_002DD644;   /* the overlay owning the screen (SafeHouse s_owner) */
extern char D_003DD040[];   /* the sound manager (g_sound) */
extern char g_sw[];
void SetSoundMgrFlags__FP8SOUNDMGRUii(void *psoundmgr, int grf, int fSet);
void SetClockFactor__FP5CLOCKif(struct CLOCK *pclock, int ifactor, float g);
void PauseGame__FP9GAMEPAUSEi(void *psw, int n);
void ResumeGame__FP9GAMEPAUSEi(void *psw, int n);
int FLoActive__FP2LO(struct OVERLAY *poverlay);
void AppendDlEntry__FP2DLPv(void *pdl, struct LOROOT *ploroot);
void SetAsegaAsegSpeed__FP5ASEGAf(void *pasega, float svu);
void func_00147410(struct OVERLAY *poverlay, int state)
{
    if (state == poverlay->state) return;
    switch (poverlay->state) {
    case -1:
        D_002DD644 = poverlay;
        SetSoundMgrFlags__FP8SOUNDMGRUii(D_003DD040, SOUNDMGRF_2, 0);
        SetClockFactor__FP5CLOCKif(&g_clock, CLOCKFACTOR_Overlay, 0.0f);
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        ((void (*)(void *))poverlay->vt[VTS_AddLo].pfn)(VT_THIS(poverlay, &poverlay->vt[VTS_AddLo]));
        if (!FLoActive__FP2LO(poverlay)) {
            struct LO *plo;
            AppendDlEntry__FP2DLPv(g_sw + 0x2C, poverlay->ploroot);   /* the world's root list */
            plo = poverlay->ploroot->plo;
            ((void (*)(void *))plo->pvt[VTS_RegisterLoTree].pfn)(VT_THIS(plo, &plo->pvt[VTS_RegisterLoTree]));
        }
        break;
    case 3:
        if (poverlay->pasega) SetAsegaAsegSpeed__FP5ASEGAf(poverlay->pasega, 1.0f);
        break;
    }
    poverlay->state = state;
    poverlay->tState = g_clock.tReal;
    switch (state) {
    case -1:
        D_002DD644 = 0;
        SetClockFactor__FP5CLOCKif(&g_clock, CLOCKFACTOR_Overlay, 1.0f);
        SetSoundMgrFlags__FP8SOUNDMGRUii(D_003DD040, SOUNDMGRF_2, 1);
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        ((void (*)(void *))poverlay->vt[VTS_RemoveLo].pfn)(VT_THIS(poverlay, &poverlay->vt[VTS_RemoveLo]));
        break;
    case 3:
        if (poverlay->pasega) SetAsegaAsegSpeed__FP5ASEGAf(poverlay->pasega, 0.0f);
        break;
    }
}
