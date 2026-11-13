/* ReleaseReachObject: the object held by a reach (Sly's cane held out, the gang's grabs) let go: the grab's flight
 * and held-pose controllers deleted. Layout: SafeHouse port (reach.h REACH). */
struct CTRL;
struct LO;
struct REACH {
    /* 0x00 */ char pad0[0x94];
    /* 0x94 */ struct CTRL *pctrl94;   /* field: SafeHouse port - grab flight and held local pose */
    /* 0x98 */ struct CTRL *pctrl98;
    /* 0x9c */ struct CTRL *pctrl9C;
    /* 0xa0 */ struct LO *ploHeld;     /* field: SafeHouse port */
};
void DeleteCtrl__FPP4CTRL(struct CTRL **ppctrl);

// name: SafeHouse port (ReleaseReachObject)
void ReleaseReachObject__FP5REACH(struct REACH *preach)
{
    if (preach->ploHeld != 0) {
        DeleteCtrl__FPP4CTRL(&preach->pctrl94);
        DeleteCtrl__FPP4CTRL(&preach->pctrl98);
        DeleteCtrl__FPP4CTRL(&preach->pctrl9C);
        preach->ploHeld = 0;
    }
}
