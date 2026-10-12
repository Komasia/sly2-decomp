void func_001FE9F8(void *, float);
void func_001FEA60(void *, int, int, float);
void func_001FEDF0(void *p)
{
    int i, j;
    func_001FE9F8(p, 1.0f);
    for (i = 0; i < 8; i++) {
        if (i == 1) continue;
        for (j = 0; j < 4; j++) func_001FEA60(p, j, i, 1.0f);
    }
}
