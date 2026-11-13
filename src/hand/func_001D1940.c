/* class: CID_4D, the vehicles (vt slot 78 = SetFocus; SafeHouse vehicle.h SetVehicleFocus): the base, then mode 2
 * in focus, or back to 0 from 2 out of it. */
struct VEHICLE {
    /* 0x000 */ char pad0[0x180];
    /* 0x180 */ int mode;
};
void SetCmFocusObject__FP2LOi(struct VEHICLE *plo, int fFocus);
void SetVehicleMode__FP7VEHICLEi(struct VEHICLE *pvehicle, int mode);

void func_001D1940(struct VEHICLE *pvehicle, int fFocus)
{
    SetCmFocusObject__FP2LOi(pvehicle, fFocus);
    if (fFocus != 0) {
        SetVehicleMode__FP7VEHICLEi(pvehicle, 2);
    } else if (pvehicle->mode == 2) {
        SetVehicleMode__FP7VEHICLEi(pvehicle, 0);
    }
}
