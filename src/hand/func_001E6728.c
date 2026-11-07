struct S { char pad[0xE4]; int fWrap; };
float SMinCrv__FP3CRV(struct S *p);
float SMaxCrv__FP3CRV(struct S *p);
float SWrapCrv__FP3CRVf(struct S *p, float g);
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
float func_001E6728(struct S *p, float g)
{
    if (p->fWrap) return SWrapCrv__FP3CRVf(p, g);
    return GClamp(g, SMinCrv__FP3CRV(p), SMaxCrv__FP3CRV(p));
}
