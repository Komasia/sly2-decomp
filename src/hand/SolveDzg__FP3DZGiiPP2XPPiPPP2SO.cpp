struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
extern DLI *s_pdliFirst;
struct DZ { int n0; int pad4[3]; float g10; int pad14; int f18; int pad1C; DZ *pdzNext; };
struct DZG { int pad0[3]; DL dlC; int pad18[6]; DL dl30; int c3C; };
struct XP; struct SO;
extern "C" {
int PentFromDz(DZG *, DZ *) asm("PentFromDz__FP3DZGP2DZ");
void CalculateDzResponses(DZG *, int, DZ *, int) asm("CalculateDzResponses__FP3DZGiP2DZP5DZENT");
void RemoveDlEntry(DL *, void *) asm("RemoveDlEntry__FP2DLPv");
void AppendDlEntry(DL *, void *) asm("AppendDlEntry__FP2DLPv");
void EnforceDzgDz(DZG *, DZ *) asm("EnforceDzgDz__FP3DZGP2DZ");
}
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
void SolveDzg(DZG *pdzg, int a, int b, XP **ppxp, int *pn, SO ***pppso)
{
    DLI dli;
    DLI dliUnused;
    DZ *pdz;
    InitDli(&dli, &pdzg->dl30);
    while ((pdz = (DZ *)PvNextDli(&dli)) != 0) {
        if (pdz->n0 == 1) {
            if (!pdz->f18)
                CalculateDzResponses(pdzg, a, pdz, PentFromDz(pdzg, pdz));
            RemoveDlEntry(&pdzg->dl30, pdz);
            AppendDlEntry(&pdzg->dlC, pdz);
            pdzg->c3C++;
        }
    }
    EnforceDzgDz(pdzg, 0);
    s_pdliFirst = dli.m_pdliNext;
    for (;;) {
        DZ *pdzBest = 0;
        float gMin = -0.01f;
        for (DZ *pdzT = (DZ *)pdzg->dl30.head; pdzT; pdzT = pdzT->pdzNext) {
            if (pdzT->g10 < gMin) {
                gMin = pdzT->g10;
                pdzBest = pdzT;
            }
        }
        if (!pdzBest)
            break;
        if (!pdzBest->f18)
            CalculateDzResponses(pdzg, a, pdzBest, PentFromDz(pdzg, pdzBest));
        EnforceDzgDz(pdzg, pdzBest);
    }
}
