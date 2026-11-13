void InitSo__FP2SO(void *p);
void InitBtn(void *p) asm("InitBtn__FP3BTN");
void InitButton__FP6BUTTON(char *p)
{
    unsigned int v;
    InitSo__FP2SO(p);
    InitBtn(p + 0x150);
    v = *(unsigned int *)(p + 0x40);
    if ((v ^ 1) & 1) *(int *)v |= 2;
    else *(unsigned int *)(p + 0x40) = v | 2;
}
