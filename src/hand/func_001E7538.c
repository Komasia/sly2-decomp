struct X { char pad[0xE8]; int c; float *ag; char pad2[0x178 - 0xF0]; int i; };
float GWrapCrv__FP3CRVf(struct X *p, float g);
// name: SafeHouse port (ISegCrvG)
int ISegCrvG__FP3CRVPfT1f(struct X *p, float *pdg, float *pdgSeg, float g)
{
    int i;
    g = GWrapCrv__FP3CRVf(p, g);
    i = p->i;
    if (p->ag[i] < g) { int n = p->c - 1; while (i < n) { if (g < p->ag[i]) break; i++; } i--; } else { while (i > 0) { if (p->ag[i] <= g) break; i--; } } { float g0 = p->ag[i]; if (pdg) *pdg = g - g0; if (pdgSeg) *pdgSeg = p->ag[i + 1] - g0; }
    p->i = i;
    return i;
}
