/* UpdateSlyReach: Sly's reach (SLY +0x17D0) is updated unless he is in an attack mode (+0x18D8). */
struct REACH;
struct SLY {
    /* 0x0000 */ char pad0[0x17d0];
    /* 0x17d0 */ char reach[0x18d8 - 0x17d0];   /* the REACH (BindReach, SafeHouse port sly.cpp) */
    /* 0x18d8 */ int attackMode;                /* field: SafeHouse port (sly.h "the attack mode (+0x18D8)") */
};
void UpdateReach(struct REACH *preach) asm("UpdateReach__FP5REACH");

// name: SafeHouse port (UpdateSlyReach)
void UpdateSlyReach__FP3SLY(struct SLY *psly)
{
    if (psly->attackMode == 0)
        UpdateReach((struct REACH *)psly->reach);
}
