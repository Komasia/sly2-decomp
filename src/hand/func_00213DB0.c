void func_00213928(void *p, int k);
void func_00213B00(void *p, int k);
void func_00213DB0(void *p, int k, int *pk)
{
    if (k == *pk)
        return;
    if (*pk != -1)
        func_00213928(p, *pk);
    *pk = k;
    if (k != -1)
        func_00213B00(p, k);
}
