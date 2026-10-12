struct S { char pad[0xE4]; int fWrap; };
float func_001E6620(struct S *p);
float func_001E6648(struct S *p);
float func_001E66C8(struct S *p, float g);
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
float func_001E6728(struct S *p, float g)
{
    if (p->fWrap) return func_001E66C8(p, g);
    return GClamp(g, func_001E6620(p), func_001E6648(p));
}
