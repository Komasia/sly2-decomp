/* class: MOVEREF, a guard's current move (SafeHouse aijobs.cpp / carry.cpp: the heading's frame (the guard's +0x1B0
 * rows) set unless the heading is locked). */
typedef int qword __attribute__((mode(TI)));
struct AIJOB;
struct M3ROWS {
    /* 0x00 */ qword a[3];
};
struct GUARD {
    /* 0x000 */ char pad0[0x1b0];
    /* 0x1b0 */ struct M3ROWS matHeading;   /* field: SafeHouse port (STEP matTarget) */
};
struct MOVEREF {
    /* 0x0 */ struct AIJOB *pjob;      /* field: SafeHouse port */
    /* 0x4 */ int fHeadingLocked;      /* field: SafeHouse port */
    /* 0x8 */ int n8;
    /* 0xc */ struct GUARD *pguard;    /* field: SafeHouse port */
};

void func_00209840(struct MOVEREF *pmove, struct M3ROWS *pmat)
{
    if (pmove->fHeadingLocked == 0) {
        struct GUARD *pguard = pmove->pguard;
        pguard->matHeading.a[0] = pmat->a[0];
        pguard->matHeading.a[1] = pmat->a[1];
        pguard->matHeading.a[2] = pmat->a[2];
    }
}
