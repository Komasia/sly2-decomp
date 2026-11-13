/* class: SOUNDMGR, g_sound (SafeHouse spliceglue.cpp / sound.h: the music's sneak mode count lowered). */
struct SOUNDMGR {
    /* 0x00 */ char pad0[0x5c];
    /* 0x5c */ int fModeAlert;   /* field: SafeHouse port */
    /* 0x60 */ int fModeSneak;   /* field: SafeHouse port */
};

void func_001FEEC0(struct SOUNDMGR *psm)
{
    psm->fModeSneak--;
}
