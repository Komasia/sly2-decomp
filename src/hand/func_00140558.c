struct VTE { short d; short pad; void (*pfn)(void *, int, void *, int, void *); };
struct SO { char pad[0xFE0]; struct SO *psoNext; };
struct P { char pad[0xC]; struct VTE *vt; char pad2[0x10E0 - 0x10]; int x10E0; };
extern struct SO *D_003E1444;
extern float D_002A4D18;
int NRankGuard__FP5GUARDP5ACTORPf(struct SO *pso, struct P *p, float *pg);
// name: SafeHouse port (PickActorTargets)
void PickActorTargets__FP5ACTOR(struct P *p)
{
    struct SO *pso, *pso0, *pso1;
    int n0, n1;
    float g0, g1;
    if (p->x10E0) return;
    g1 = D_002A4D18;
    pso1 = 0;
    pso0 = 0;
    n1 = -1;
    n0 = -1;
    g0 = g1;
    for (pso = D_003E1444; pso; pso = pso->psoNext) {
        float ag[2];
        int n = NRankGuard__FP5GUARDP5ACTORPf(pso, p, &ag[1]);
        float g = ag[1];
        if (g < g0) {
            g0 = g;
            n0 = n;
            pso0 = pso;
        }
        if (n1 < n || (n == n1 && g < g1)) {
            g1 = g;
            n1 = n;
            pso1 = pso;
        }
    }
    p->vt[95].pfn((char *)p + p->vt[95].d, n0, pso0, n1, pso1);
}
