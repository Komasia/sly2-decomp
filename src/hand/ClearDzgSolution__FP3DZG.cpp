struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct DLE { void *pvNext; void *pvPrev; };
struct DZS {
    char pad0[0xC];
    float gC;
    float g10;
    char pad14[0xC];
    DLE dle;
};
struct DZG {
    int cdzsMax;
    int cdzs;
    DZS *adzs;
    DL dlA;
    DL dlB;
    DL dlC;
    DL dlD;
    int n3C;
};

extern "C" {
void ClearDl(DL *pdl) asm("ClearDl__FP2DL");
void ClearDle(DLE *pdle) asm("ClearDle__FP3DLE");
void AppendDlEntry(DL *pdl, void *pv) asm("AppendDlEntry__FP2DLPv");
}

void ClearDzgSolution(DZG *pdzg)
{
    int i;

    pdzg->n3C = 0;
    ClearDl(&pdzg->dlA);
    ClearDl(&pdzg->dlB);
    ClearDl(&pdzg->dlC);
    ClearDl(&pdzg->dlD);

    for (i = 0; i < pdzg->cdzs; i++) {
        DZS *pdzs = &pdzg->adzs[i];
        pdzs->gC = pdzs->g10 = 0.0f;
        ClearDle(&pdzs->dle);
        AppendDlEntry(&pdzg->dlD, pdzs);
    }
}
