/* class: the screen player's entry (FSpriteAnimPlaying calls it): its part's +0x10 (through the entry's +0x8). */
typedef struct SPART10 { char pad0[0x10]; int n10; } SPART10;
typedef struct SREF {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ SPART10 *ppart;
} SREF;

int func_00218738(SREF *pref)
{
    return pref->ppart->n10;
}
