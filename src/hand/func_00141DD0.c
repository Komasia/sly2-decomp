extern float D_002BD260;
extern float D_002BD264;
void func_001441E8(void *p, float f);
void func_00141DD0(void *p, int *pm)
{
    switch (*pm) {
    case 0x1D:
        func_001441E8(p, D_002BD260);
        break;
    case 0x2A:
        func_001441E8(p, D_002BD264);
        break;
    }
}
