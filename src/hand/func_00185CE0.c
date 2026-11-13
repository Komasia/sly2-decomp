/* class: CID_09, a PNTS kind (vt slot 15 = PostLoad; SafeHouse climbsurf.cpp module): PostLoLoad, then the zone at
 * +0x110 gets its camera (UpdateZoneCamera(zone, 0)). */
struct LO;
struct PNTS09 {
    /* 0x000 */ char pad0[0x110];
    /* 0x110 */ struct LO *pzone;
};
void PostLoLoad__FP2LO(struct PNTS09 *plo);
void UpdateZoneCamera__FP2LOi(struct LO *pzone, int n);

void func_00185CE0(struct PNTS09 *p)
{
    struct LO *pzone;
    PostLoLoad__FP2LO(p);
    pzone = p->pzone;
    if (pzone != 0) {
        UpdateZoneCamera__FP2LOi(pzone, 0);
    }
}
