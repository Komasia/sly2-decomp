/* class: CID_6C, the vehicle pickups (vt slot 26, a pool row taken again; SafeHouse vehiclebindings.cpp
 * ResetPickupSlot26): after the base 0x1CB518, state -1 then 0. */
struct LO;
void func_001CB518(struct LO *plo, struct LO *pproxy);   /* the base slot 26 */
void SetVehiclePickupState__FP2LOi(struct LO *plo, int state);

void func_001D4F10(struct LO *plo, struct LO *pproxy)
{
    func_001CB518(plo, pproxy);
    SetVehiclePickupState__FP2LOi(plo, -1);
    SetVehiclePickupState__FP2LOi(plo, 0);
}
