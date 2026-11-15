extern float D_002BD260;
extern float D_002BD264;
void DrainActorPower__FP5ACTORf(void *p, float f);
void func_00141DD0(void *p, int *pm)
{
    switch (*pm) {
    case 0x1D:
        DrainActorPower__FP5ACTORf(p, D_002BD260);
        break;
    case 0x2A:
        DrainActorPower__FP5ACTORf(p, D_002BD264);
        break;
    }
}
