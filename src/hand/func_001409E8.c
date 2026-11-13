typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; int (*pfn)(void *, void *); };
struct SO { char pad[0xC]; struct VTE *vt; char pad2[0xFE0 - 0x10]; struct SO *psoNext; };
struct X { char pad[0x104]; struct X *pxNext; };
struct P { char pad[0x10C4]; void *p10C4; };
extern struct SO *D_003E1444;
extern struct X *D_003E1468;
int func_001443D8(struct P *p);
qword PosOfLo__FP2LO(struct P *p);
void *func_00156698(void *a, qword pos, struct P *p);
int FGuardState(struct SO *pso, int n) asm("FGuardState__FP5GUARDi");
int FListenerHearsNoise__FP2LOP5NOISE(struct X *px, void *q);
void RemoveNoise__FP5NOISE(void *q);
// name: SafeHouse port (NActorPerceived)
int NActorPerceived__FP5ACTOR(struct P *p)
{
    int unused[4];
    void *q;
    int r;
    struct SO *pso;
    struct X *px;
    if (func_001443D8(p)) return 2;
    q = 0;
    if (p->p10C4) q = func_00156698(p->p10C4, PosOfLo__FP2LO(p), p);
    if (!q) return 2;
    r = 0;
    pso = D_003E1444;
    for (;;) {
        if (!pso) break;
        if (FGuardState(pso, 0x1D) || FGuardState(pso, 0xB)) { r = 2; break; }
        if (pso->vt[89].pfn((char *)pso + pso->vt[89].d, q)) { r = 1; break; }
        pso = pso->psoNext;
    }
    if (r == 0) {
        for (px = D_003E1468; px; px = px->pxNext)
            if (FListenerHearsNoise__FP2LOP5NOISE(px, q)) { r = 1; break; }
    }
    RemoveNoise__FP5NOISE(q);
    return r;
}
