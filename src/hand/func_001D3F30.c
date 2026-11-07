struct E { int a[2]; char b[0x58]; };
struct S { char pad[0x190]; int c; int pad2[3]; struct E ae[8]; };
void SetAloOverlapNothing__FP3ALOT0(struct S *p, void *q);
void func_001F4DA8(struct S *p, void *q, void *pe);
// name: SafeHouse port (VehicleRemoveContacts)
void VehicleRemoveContacts__FP3ALOT0(struct S *p, void *q) {
    int i;
    SetAloOverlapNothing__FP3ALOT0(p, q);
    for (i = 0; i < p->c; i++) func_001F4DA8(p, q, p->ae[i].b);
}
