struct S { char p0[0x160]; void *p160; int a164; };
void func_001F36A8(struct S *p);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *a, struct S *p, int b, int c, int *pn);
void SetVehiclePickupState__FP2LOi(struct S *p, int n);
// name: SafeHouse port (vehicle.h PostLoadVehiclePickup, orig 0x1D4EC8)
void PostLoadVehiclePickup__FP2LO(struct S *p) {
    func_001F36A8(p);
    ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(p->p160, p, -1, 0, &p->a164);
    SetVehiclePickupState__FP2LOi(p, 0);
}
