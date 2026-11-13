/* ResetVehiclePlacement: the base reset (func_001CB518), then the vehicle's state. */
struct LO;
void func_001CB518(struct LO *plo);
void ResetVehicleState(struct LO *plo) asm("ResetVehicleState__FP2LO");

// name: SafeHouse port (ResetVehiclePlacement)
void ResetVehiclePlacement__FP2LO(struct LO *plo)
{
    func_001CB518(plo);
    ResetVehicleState(plo);
}
