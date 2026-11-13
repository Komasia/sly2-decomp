void InitXfm__FP3XFM(void *p);
void InitBtn(void *p) asm("InitBtn__FP3BTN");
void func_001A6CA8(void *p, int n);
void InitVolbtn__FP6VOLBTN(char *p)
{
    unsigned int v;
    InitXfm__FP3XFM(p);
    InitBtn(p + 0x130);
    *(int *)(p + 0x1CC) = 1;
    func_001A6CA8(p, 0);
    v = *(unsigned int *)(p + 0x40);
    if ((v ^ 1) & 1) *(int *)v |= 2;
    else *(unsigned int *)(p + 0x40) = v | 2;
}
