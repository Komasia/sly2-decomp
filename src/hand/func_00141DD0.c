/* The actor's power drained by a hit (message kind 0x1D or 0x2A: D_002BD260 / D_002BD264). */
extern float D_002BD260;
extern float D_002BD264;
void DrainActorPower__FP5ACTORf(void *pactor, float f);
void func_00141DD0(void *pactor, int *pmsg)
{
    switch (*pmsg) {
    case 0x1D:
        DrainActorPower__FP5ACTORf(pactor, D_002BD260);
        break;
    case 0x2A:
        DrainActorPower__FP5ACTORf(pactor, D_002BD264);
        break;
    }
}
