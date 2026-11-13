/* UpdateOverlay (the photo overlays' update): state 0 goes to 1; in state 3 the end of its dialog (FDialogPlaying)
 * moves it to 2; in state 2 the end of its animation (none, or retracted) releases the animation (0x1306A8) and
 * ends the overlay (-1). The states are set by 0x147410. Layout: SafeHouse port (overlay.cpp OVERLAY). */
struct ASEGA;
struct OVERLAY {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ int state;            /* field: SafeHouse port */
    /* 0x154 */ char pad154[0x160 - 0x154];
    /* 0x160 */ struct ASEGA *pasega; /* field: SafeHouse port */
    /* 0x164 */ char pad164[0x170 - 0x164];
    /* 0x170 */ int dialog;           /* field: SafeHouse port */
};
extern char D_003DD040[];   /* the sound manager (g_sound) */
void func_00147410(struct OVERLAY *poverlay, int state);   /* SafeHouse: the overlay's state */
int FDialogPlaying__FP8SOUNDMGRi(void *psoundmgr, int dialog);
int FAsegaRetracted(struct ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
void func_001306A8(struct ASEGA **ppasega);   /* the ASEGA held released (null-safe) */

// name: SafeHouse port (UpdateOverlay)
void UpdateOverlay__FP2LO(struct OVERLAY *poverlay)
{
    switch (poverlay->state) {
    case 0:
        func_00147410(poverlay, 1);
        return;
    case 3:
        if (!FDialogPlaying__FP8SOUNDMGRi(D_003DD040, poverlay->dialog)) {
            func_00147410(poverlay, 2);
            return;
        }
        return;
    case 2:
        if (poverlay->pasega == 0 || FAsegaRetracted(poverlay->pasega)) {
            func_001306A8(&poverlay->pasega);
            func_00147410(poverlay, -1);
        }
        break;
    }
}
