/* class: MOVEREF, a guard's current move (SafeHouse guard.h: the heading locked, message 0x25). */
struct AIJOB;
struct GUARD;
/* the guard's current move (GUARD +0xFD0; SafeHouse guard.h MOVEREF) */
struct MOVEREF {
    /* 0x0 */ struct AIJOB *pjob;      /* field: SafeHouse port */
    /* 0x4 */ int fHeadingLocked;      /* field: SafeHouse port - messages 0x25 / 0x26 */
    /* 0x8 */ int n8;
    /* 0xc */ struct GUARD *pguard;    /* field: SafeHouse port */
};

void func_002097C8(struct MOVEREF *pmove)
{
    pmove->fHeadingLocked = 1;
}
