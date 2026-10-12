extern int D_002E1E54;
void func_001A2C48(int *pa, int **ppb);
void func_001A2BD0(int n)
{
    if (n == -1) {
        int a;
        int *pb;
        func_001A2C48(&a, &pb);
        D_002E1E54 = *pb;
    } else {
        D_002E1E54 = n;
    }
}
