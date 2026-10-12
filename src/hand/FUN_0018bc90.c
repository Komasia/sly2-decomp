int func_001AAB48(void *p);
int func_00244450(int n, int *a, int *b);
int func_001AAB68(int n);
int func_001AABC0(void *p, int n);
int FUN_0018bc90(void *a0, void *a1, void *a2, int *a3)
{
    int buf[2];
    int r = func_001AAB48(a1);
    if (r != 0x1D)
        return r;
    r = func_001AAB68(func_00244450(0, &buf[0], &buf[1]));
    if (a3)
        *a3 = buf[1];
    if (r == 0x22)
        r = func_001AABC0(a2, buf[1]);
    return r;
}
