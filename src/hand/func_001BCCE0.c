extern float D_002C0AB8;
float func_001E6648(void *s);
int FPolyPointOnRegion__FP7NAVPOLYP9NAVREGIONffPfPv(void *s, void *x, float t, float dt, float *pt, int k);
int NPolyClearSide__FP7NAVPOLYP9NAVREGIONiff(void *s, void *x, float a, float b, int k);

// name: SafeHouse port (NPolyWay)
int NPolyWay__FP7NAVPOLYP9NAVREGIONPfif(void *s, void *x, float *pt, int mode, float t)
{
    float at[2];
    float tB, d, f;
    int fShort, a, b;

    if (!FPolyPointOnRegion__FP7NAVPOLYP9NAVREGIONffPfPv(s, x, t, func_001E6648(s) * 0.5f, &at[0], 0) &&
        !FPolyPointOnRegion__FP7NAVPOLYP9NAVREGIONffPfPv(s, x, t, func_001E6648(s) * 0.5f, &at[0], 1)) return 4;
    t = at[0];
    if (!FPolyPointOnRegion__FP7NAVPOLYP9NAVREGIONffPfPv(s, x, *pt, func_001E6648(s) * 0.5f, &at[1], 0) &&
        !FPolyPointOnRegion__FP7NAVPOLYP9NAVREGIONffPfPv(s, x, *pt, func_001E6648(s) * 0.5f, &at[1], 1)) return 4;
    tB = at[1];
    *pt = tB;
    d = tB - t;
    if (d < 0.0f) d += func_001E6648(s);
    switch (mode) {
    case 2: f = D_002C0AB8 + 1.0f; break;
    case 1: f = 1.0f - D_002C0AB8; break;
    default: f = 1.0f; break;
    }
    fShort = (d < func_001E6648(s) * f * 0.5f) ? 1 : 0;
    a = NPolyClearSide__FP7NAVPOLYP9NAVREGIONiff(s, x, t, tB, 1);
    b = NPolyClearSide__FP7NAVPOLYP9NAVREGIONiff(s, x, t, tB, 0);
    if (b < a) return 1;
    if (a < b) return 2;
    if (a != 2) return fShort ? 2 : 1;
    return 4;
}
