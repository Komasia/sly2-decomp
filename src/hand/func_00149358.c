void LoadShapeFromBrx__FP5SHAPEP18CBinaryInputStream(void *p);
void LoadBtn(void *p, void *q) asm("LoadBtn__FP3BTNP3ALO");
void LoadVolbtnFromBrx__FP6VOLBTNP18CBinaryInputStream(char *p)
{
    LoadShapeFromBrx__FP5SHAPEP18CBinaryInputStream(p);
    LoadBtn(p + 0x130, p);
    if (*(int *)(p + 0x2C8)) *(int *)(p + 0x1D4) = 1;
}
