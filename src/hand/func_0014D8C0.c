// name: SafeHouse port (cm.h: orig 0x14D8C0 CutCm)
void CutCm(char *p) asm("CutCm__FP2CM");
void CutCm(char *p)
{
    int n = *(int *)(p + 0x300);
    int m = 1;
    if (m < n) m = n;
    *(int *)(p + 0x300) = m;
}
