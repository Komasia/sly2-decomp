struct O { char pad[0x80]; int n80; };
struct S { char pad[0x4F8]; int c; struct O *ap[1]; };
int FVehicleAttachmentReady__FP13VEHICLEATTACH(struct O *po);
// name: SafeHouse port (FirstReadyAttachment)
struct O *FirstReadyAttachment__FP7VEHICLE(struct S *p) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct O *po = p->ap[i];
        if (FVehicleAttachmentReady__FP13VEHICLEATTACH(po) && po->n80 != 4) return po;
    }
    return 0;
}
