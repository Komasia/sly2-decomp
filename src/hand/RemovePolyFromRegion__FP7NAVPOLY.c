/* RemovePolyFromRegion: take a navigation polygon out of its region (+0x1DC, func_001C1968). Layout: SafeHouse port
 * (nav.h NAVPOLY pregion). */
struct NAVREGION;
struct NAVPOLY {
    /* 0x000 */ char pad0[0x1dc];
    /* 0x1dc */ struct NAVREGION *pregion;   /* field: SafeHouse port */
};
void func_001C1968(struct NAVREGION *pregion, struct NAVPOLY *ppoly);

// name: SafeHouse port (RemovePolyFromRegion)
void RemovePolyFromRegion__FP7NAVPOLY(struct NAVPOLY *ppoly)
{
    struct NAVREGION *pregion = ppoly->pregion;
    if (pregion) {
        func_001C1968(pregion, ppoly);
        ppoly->pregion = 0;
    }
}
