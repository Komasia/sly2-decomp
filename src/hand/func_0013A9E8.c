/* InitBomb (the thrown objects, class 0x4F): InitSo, then no end time (FLT_MAX), the hit radii 200 (the player's too),
 * the impact noise on, the hits' contact kind 0x100 and state -10, kind 0, the update flag 2, and itself as its
 * launcher. Layout: SafeHouse port (projectile.cpp). */
struct BOMB { char pad[0x40]; int grfUpd; char pad2[0x150 - 0x44]; int kind; float tEnd; int svMin; float sRadius; float sRadiusPlayer;
    char pad3[0x1e0 - 0x164]; int fNoise; int n1E4; int paloAttach; int grfFilter; int nState; char pad4[0x200 - 0x1f4]; struct BOMB *plaunch; };
extern float D_002BC9C8;   /* 200: the hit radius */
extern float D_002A4B08;
void InitSo__FP2SO(struct BOMB *);
void InitBomb__FP4BOMB(struct BOMB *pbomb) {
    int grf;
    InitSo__FP2SO(pbomb);
    pbomb->tEnd = 3.40282346638528859812e+38f;
    pbomb->sRadius = D_002BC9C8;
    pbomb->sRadiusPlayer = D_002BC9C8;
    pbomb->fNoise = 1;
    pbomb->grfFilter = 0x100;
    pbomb->nState = -10;
    grf = pbomb->grfUpd;
    pbomb->kind = 0;
    if ((grf ^ 1) & 1) *(int *)grf |= 2;
    else pbomb->grfUpd = grf | 2;
    pbomb->plaunch = pbomb;
}
