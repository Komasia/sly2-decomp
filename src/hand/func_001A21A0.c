/* FSlyImmune (0x1A21A0): Sly's vtable slot 76, whether he ignores a damage kind: in his states (+0x18C8) 3 / 8 / 21 / 22
 * the kind 0x4000; in state 7 what his interaction (+0x4C0, 0x194640) says; then the actors' FActorImmune.
 * SafeHouse damage.cpp. */
struct S { char pad[0x4C0]; char x4C0[0x18C8 - 0x4C0]; int x18C8; };
int func_00194640(void *pinter, int kind);
int FActorImmune__FP5ACTORi(struct S *psly, int kind);
// name: SafeHouse port (FSlyImmune)
int FSlyImmune__FP5ACTORi(struct S *psly, int kind)
{
    switch (psly->x18C8) {
    case 3:
    case 8:
    case 21:
    case 22:
        if (kind == 0x4000)
            return 1;
        break;
    case 7:
        if (func_00194640(psly->x4C0, kind))
            return 1;
        break;
    }
    return FActorImmune__FP5ACTORi(psly, kind);
}
