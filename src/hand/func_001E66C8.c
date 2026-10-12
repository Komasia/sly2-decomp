struct S { char pad[0xE4]; int f; int c; int nEC; float *ag; };
float func_0011D898(float g, float gMax);
float func_001E66C8(struct S *p, float g)
{
    float gMax;
    if (!p->f) return g;
    gMax = p->ag[p->c - 1];
    if (0.0f <= g && g <= gMax) return g;
    return func_0011D898(g, gMax);
}
