struct O { char pad[0x98]; short h98; };
struct S { char p0[0x58]; struct O *po; char p1[0x150-0x5C]; int n150; };
void UpdateSo__FP2SOf(struct S *p);
void SetVehiclePickupState__FP2LOi(struct S *p, int n);
// name: SafeHouse port (UpdateVehiclePickup)
void UpdateVehiclePickup__FP2LO(struct S *p) {
    UpdateSo__FP2SOf(p);
    if (p->n150 == 0 && p->po->h98 == 3) SetVehiclePickupState__FP2LOi(p, 1);
}
