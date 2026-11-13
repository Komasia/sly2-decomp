typedef int qword __attribute__((mode(TI)));
typedef struct HIT { qword q; char pad[0x50]; } HIT;
typedef struct S { char pad[0xE4]; int fWrap; } S;
extern float D_002C0AC0;
void EvalCrvS(S *p, qword *pv, int z, float t) asm("EvalCrvS__FP3CRVfP6VECTORT2");
float SWrapCrv__FP3CRVf(S *p, float t);
float SMinCrv__FP3CRV(S *p);
float SMaxCrv__FP3CRV(S *p);
int ChitPoly__FP7NAVPOLYG9VU_VECTORT1iP7POLYHIT(void *p, qword a, qword b, int c, HIT *ahit);


// name: SafeHouse port (NPathLeavesPoly)
int NPathLeavesPoly__FP7NAVPOLYP3CRViP6VECTORPff(void *p, S *s, int fForward, qword *pq, float *pt, float t)
{
    qword av[2];
    HIT ahit[2];
    float dt;
    int fWrapped;
    int c;

    EvalCrvS(s, &av[1], 0, t);
    dt = D_002C0AC0;
    if (!fForward) dt = -dt;
    fWrapped = 0;
    for (;;) {
        av[0] = av[1];
        t += dt;
        if (t <= SMinCrv__FP3CRV(s)) {
            if (fWrapped) break;
            fWrapped = 1;
            if (s->fWrap) t = SWrapCrv__FP3CRVf(s, t);
            else t = SMinCrv__FP3CRV(s);
        } else if (SMaxCrv__FP3CRV(s) <= t) {
            if (fWrapped) break;
            fWrapped = 1;
            if (s->fWrap) t = SWrapCrv__FP3CRVf(s, t);
            else t = SMaxCrv__FP3CRV(s);
        }
        EvalCrvS(s, &av[1], 0, t);
        c = ChitPoly__FP7NAVPOLYG9VU_VECTORT1iP7POLYHIT(p, av[0], av[1], 2, ahit);
        if (c > 0) {
            if (pt) *pt = t;
            if (pq) *pq = (ahit - 1)[c].q;
            return -1;
        }
    }
    return 3;
}
