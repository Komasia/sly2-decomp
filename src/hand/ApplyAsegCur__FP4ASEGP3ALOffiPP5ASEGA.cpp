struct ASEG; struct ALO;
struct VTE { short d; short pad; void (*pfn)(); };
struct ASEGA { int pad[3]; VTE *vt; };
void func_00130658(ASEGA **);
void ApplyAseg(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega);
void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega)
{
    func_00130658(ppasega);
    if (paseg)
    {
        ApplyAseg(paseg, paloRoot, t, svt, grfapl, ppasega);
        ASEGA *pasega = *ppasega;
        ((void (*)(void *))pasega->vt[1].pfn)((char *)pasega + pasega->vt[1].d);
    }
}
