struct X { char pad[0xE8]; int c; float *agEC; float *ag; char pad2[0x178 - 0xF4]; int i; };
float func_001E66C8(struct X *p, float g);
int func_001E7668(struct X *p, float *pdg, float *pdgSeg, float g)
{
    int i;
    g = func_001E66C8(p, g);
    i = p->i;
    if (p->ag[i] < g) { for (; i < p->c - 1; i++) if (g < p->ag[i]) break; i--; } else { for (; i > 0; i--) if (p->ag[i] <= g) break; }
    if (pdg) *pdg = g - p->ag[i];
    if (pdgSeg) *pdgSeg = p->ag[i + 1] - p->ag[i];
    p->i = i;
    return i;
}
