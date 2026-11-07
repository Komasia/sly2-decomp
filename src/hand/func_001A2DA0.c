void FRegionLanguages__FPiPUi(int *pn, int **pa);
void func_001A2BD0(int i);
void func_001A2DA0(int key)
{
    int tbl[14] = { 1, 2, 5, 4, 3, 6, 7, -1, -1, -1, -1, 0, -1, -1 };
    int i, j;
    int n;
    int *a;
    for (i = 0; i < 14; i++) {
        if (key == tbl[i]) {
            FRegionLanguages__FPiPUi(&n, &a);
            for (j = 0; j < n; j++) {
                if (i == a[j]) {
                    func_001A2BD0(i);
                    return;
                }
            }
        }
    }
    func_001A2BD0(-1);
}
