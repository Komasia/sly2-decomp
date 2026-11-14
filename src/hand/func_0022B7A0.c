/* class: WR (SafeHouse wr.cpp / wr.h, 0x22B7A0: a glob's warp block bound to the WR its oid names - pushed on the
 * WR's list +0x8F0, +0xC the WR). */
struct WARP {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ struct WR *pwr;
};
struct WR {
    /* 0x000 */ char pad0[0x8f0];
    /* 0x8f0 */ char dlWarp[0xc];
};
void func_0011A070(void *pdl, struct WARP *pwarp);   /* pushed on the list */

void func_0022B7A0(struct WR *pwr, struct WARP *pwarp)
{
    func_0011A070(pwr->dlWarp, pwarp);
    pwarp->pwr = pwr;
}
