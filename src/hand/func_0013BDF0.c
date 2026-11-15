/* InitBooty (cid 0x67): InitSo, the carried scale (1, 1, 1), no state (-1), update flag 2. Layout: SafeHouse port
 * (booty.cpp BOOTY). */
typedef int ti128 __attribute__((mode(TI)));
struct BOOTY { char pad[0x40]; int grfUpd; char pad2[0x170 - 0x44]; ti128 vecScaleCarried; char pad3[4]; int state; };
extern ti128 D_002A2DE0;   /* (1, 1, 1) */
void InitSo__FP2SO(struct BOOTY *);
void func_0013BDF0(struct BOOTY *pbooty) {
    int grf;
    InitSo__FP2SO(pbooty);
    pbooty->vecScaleCarried = D_002A2DE0; pbooty->state = -1; grf = pbooty->grfUpd;
    if ((grf ^ 1) & 1) *(int *)grf |= 2;
    else pbooty->grfUpd = grf | 2;
}
