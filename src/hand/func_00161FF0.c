int func_00161FC8(int i);
int func_00161FF0(int c, int *ai)
{
    int grf = 0;
    int i;
    for (i = 0; i < c; i++)
        grf |= func_00161FC8(ai[i]);
    return grf;
}
