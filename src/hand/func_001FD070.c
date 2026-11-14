/* class: SOUNDMGR (StartIop__9CSndPlain / StepSoundMood call it): the index of an entry of its +0xFC int array. */
typedef struct SOUNDMGR {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int *an;
} SOUNDMGR;

int func_001FD070(SOUNDMGR *psndmgr, int *pn)
{
    return pn - psndmgr->an;
}
