void func_001A5270(void *p);
void func_001A6CA8(void *p, int n);
void func_0015DC80(char *p)
{
    unsigned int v;
    func_001A5270(p);
    func_001A6CA8(p, 1);
    v = *(unsigned int *)(p + 0x40);
    if ((v ^ 1) & 1) *(int *)v |= 0xA;
    else *(unsigned int *)(p + 0x40) = v | 0xA;
}
