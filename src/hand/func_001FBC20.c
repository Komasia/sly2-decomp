/* class: CSndPlain (SafeHouse sound.h: Kind(), 0x1FBC20 - the sound's bank entry, e.g. 2 a looper; -1 without one). */
struct SOUNDMGR;
extern struct SOUNDMGR D_003DD040;   /* g_sound */
struct CSNDPLAIN {
    /* 0x00 */ char pad0[0x60];
    /* 0x60 */ int sfxid;   /* field: SafeHouse port */
};
int *IsoundFromSfxid__FP8SOUNDMGRi(struct SOUNDMGR *psm, int sfxid);

int func_001FBC20(struct CSNDPLAIN *psnd)
{
    int *pkind = IsoundFromSfxid__FP8SOUNDMGRi(&D_003DD040, psnd->sfxid);
    int kind = -1;
    if (pkind != 0) {
        kind = *pkind;
    }
    return kind;
}
