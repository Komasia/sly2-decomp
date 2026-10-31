void InitXfm__FP3XFM(void *p);
void func_001A6CA8(void *p, int n);
void func_00156CC8(char *p)
{
    unsigned int v;
    InitXfm__FP3XFM(p);
    func_001A6CA8(p, 0);
    v = *(unsigned int *)(p + 0x40);
    if ((v ^ 1) & 1) *(int *)v |= 2;
    else *(unsigned int *)(p + 0x40) = v | 2;
}
