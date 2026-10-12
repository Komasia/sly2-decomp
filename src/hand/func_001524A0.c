void ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA(void *paseg, void *palo, float a, float b, int n, void **pp);
void func_001524A0(char *p, void *paseg, int n)
{
    ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA(paseg, p, 0.0f, 1.0f, n | 1, (void **)(p + 0x408));
}
