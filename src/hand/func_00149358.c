void LoadShapeFromBrx__FP5SHAPEP18CBinaryInputStream(void *p);
void func_00148738(void *p, void *q);
void LoadVolbtnFromBrx__FP6VOLBTNP18CBinaryInputStream(char *p)
{
    LoadShapeFromBrx__FP5SHAPEP18CBinaryInputStream(p);
    func_00148738(p + 0x130, p);
    if (*(int *)(p + 0x2C8)) *(int *)(p + 0x1D4) = 1;
}
