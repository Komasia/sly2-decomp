extern int *D_003E1C48;
int func_00210A88(void);
int func_00210A98(void)
{
    int i = func_00210A88();
    if (i == -1)
        return -1;
    return D_003E1C48[i];
}
