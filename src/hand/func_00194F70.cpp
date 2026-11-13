// MATCH (w3lane3, 2026-10-25): TrackJt = UpdateJtGrabCandidates(SW *psw, STEPPLAYER *pstepplayer, int ccand, JTGRABCAND *ajtgrabcand)
// (name and structures from src/hand/UpdateJtCandidates.cpp, the GatherJtGrabCandidates port that calls it).
// Merges this frame's sorted grab candidates into the four the world keeps (SW::ajtgrabcand): an old candidate
// whose object is found again takes the new distance and smooths its parameter towards the new one (wrapping
// around the spot's range), one that is gone is dropped, and the remaining new ones are linked and appended.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;

struct LO;
struct STEPPLAYER;
struct SMP { float g0, g4, g8; };

struct VTGRAB1 { short d; short pad; int (*pfn)(void *, float *); };
struct VTGRAB3 { short d; short pad; void (*pfn)(void *, STEPPLAYER *, qword *, void *, float); };
union VTGRAB { VTGRAB1 v1; VTGRAB3 v3; };
struct VTLO { short d; short pad; void (*pfn)(void *, qword); };

struct GRABSPOT {
    char pad0[0x14];
    int nUnk14;          // hint text id, -1 for none
    char pad18[0x20 - 0x18];
    VTGRAB *pvt;         // slot 1: int FGetWrapRange(float *pasRange)
};
struct LO { char pad0[0xC]; VTLO *pvt; };

struct JTGRABCAND {
    LO *plo;
    GRABSPOT *pspot;
    float sDist;
    int nPriority;
    LO *ploUnk10;
    float tUnk14;
    float sParam;
    float dsParam;
    qword qwPos;
};
struct SW { char pad0[0x4678]; int cjtgrabcand; JTGRABCAND ajtgrabcand[4]; };
struct STEPPLAYER { char pad0[0x9C4]; int idUnk9C4; };
struct CLOCK { float t; float dt; };

extern "C" {
extern CLOCK g_clock;
extern int D_002E1E50;
extern float D_002BF710, D_002BF714;
extern SMP D_002BF718;
extern char g_game[];
int func_00194F48(const void *, const void *);   // JTGRABCAND compare for qsort
void qsort(void *base, uint c, uint cb, int (*pfnCmp)(const void *, const void *)) asm("qsort");   // qsort
void *s1_memmove(void *dst, const void *src, uint cb) asm("s1_memmove");   // memmove
float GSmooth(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext) asm("GSmooth__FfffP3SMPPf");   // GSmooth
void FadeAloOut(LO *plo, float g) asm("FadeAloOut__FP3ALOf");
void BroadcastTaskEvent(void *pv, int msg, LO *plo) asm("BroadcastTaskEvent__FP2SWiP2LO");
LO *PloNewJtAura(SW *psw, int id, JTGRABCAND *pcand) asm("PloNewJtAura__FP2LOiP5JTENT");
void TrackJt(SW *psw, STEPPLAYER *pstepplayer, int ccand, JTGRABCAND *ajtgrabcand) asm("TrackJt__FP5ACTORP5JTENTiP10JTGRABCAND");
}

// name: SafeHouse port (TrackJt)
void TrackJt(SW *psw, STEPPLAYER *pstepplayer, int ccand, JTGRABCAND *ajtgrabcand)
{
    float asRange[2];
    qword qwPos;
    int i, j;
    JTGRABCAND *pcandOld, *pcand;
    if (ccand > 0) {
        qsort(ajtgrabcand, ccand, sizeof(JTGRABCAND), func_00194F48);
        if (ajtgrabcand->pspot->nUnk14 != -1)
            ajtgrabcand->nPriority = 1;
    }
    JTGRABCAND *ajtgrabcandOld = psw->ajtgrabcand;
    for (i = psw->cjtgrabcand; --i >= 0; ) {
        pcandOld = &psw->ajtgrabcand[i];
        // Search the new candidates from the end; the drop code sits in the loop's exit test (its calls stop gcc
        // from duplicating the test in front of the loop, giving the original's jump-to-test entry).
        j = ccand;
        for (;;) {
            if (--j < 0) {
                // Not seen this frame: drop it.
                if (pcandOld->ploUnk10)
                    FadeAloOut(pcandOld->ploUnk10, 0.5f);
                s1_memmove(pcandOld, pcandOld + 1, (3 - i) * (int)sizeof(JTGRABCAND));
                psw->cjtgrabcand--;
                break;
            }
            pcand = &ajtgrabcand[j];
            if (pcandOld->plo == pcand->plo) {
                pcandOld->sDist = pcand->sDist;
                if (!pcandOld->ploUnk10) {
                    pcandOld->sParam = pcand->sParam;
                    pcandOld->dsParam = 0.0f;
                } else {
                    float sRange;
                    int fWrap = pcand->pspot->pvt[1].v1.pfn((char *)pcand->pspot + pcand->pspot->pvt[1].v1.d, asRange);
                    if (fWrap) {
                        float ds;
                        sRange = asRange[1] - asRange[0];
                        float sNew = pcand->sParam;
                        float sOld = pcandOld->sParam;
                        ds = sNew - sOld;
                        // Move the new parameter to the wrap of the range closest to the old one.
                        if (sRange * 0.5f < ds) {
                            ds -= sRange;
                            pcand->sParam = sOld + ds;
                        } else if (ds < sRange * -0.5f) {
                            ds += sRange;
                            pcand->sParam = sOld + ds;
                        } else {
                            fWrap = 0;
                        }
                    }
                    if (D_002E1E50) {
                        float dt = g_clock.dt;
                        float dsPrev = pcandOld->dsParam;
                        float dsNew = dsPrev + dt * ((pcand->sParam - pcandOld->sParam) * D_002BF710 + (pcand->dsParam - dsPrev) * D_002BF714);
                        float dsAvg;
                        pcandOld->dsParam = dsNew;
                        dsAvg = (dsPrev + dsNew) * 0.5f;
                        pcandOld->sParam = pcandOld->sParam + dt * dsAvg;
                    } else {
                        pcandOld->sParam = GSmooth(pcandOld->sParam, pcand->sParam, g_clock.dt, &D_002BF718, &pcandOld->dsParam);
                    }
                    if (fWrap) {
                        if (asRange[1] < pcandOld->sParam)
                            pcandOld->sParam = pcandOld->sParam - sRange;
                        else if (pcandOld->sParam < asRange[0])
                            pcandOld->sParam = pcandOld->sParam + sRange;
                    }
                    GRABSPOT *pspot = pcandOld->pspot;
                    pspot->pvt[3].v3.pfn((char *)pspot + pspot->pvt[3].v3.d, pstepplayer, &qwPos, 0, pcandOld->sParam);
                    pcandOld->ploUnk10->pvt[29].pfn((char *)pcandOld->ploUnk10 + pcandOld->ploUnk10->pvt[29].d, qwPos);
                }
                s1_memmove(pcand, pcand + 1, (ccand - j) * (int)sizeof(JTGRABCAND) - (int)sizeof(JTGRABCAND));
                ccand--;
                break;
            }
        }
    }
    for (j = 0; j < ccand; j++) {
        pcand = &ajtgrabcand[j];
        if (pstepplayer->idUnk9C4 && pcand->nPriority == 1) {
            register LO *plo asm("$6"); // the one register pin: the original keeps the link result in a2, global-alloc would pick v0
            plo = PloNewJtAura(psw, pstepplayer->idUnk9C4, pcand);
            if (!plo)
                break;
            pcand->ploUnk10 = plo;
        }
        psw->ajtgrabcand[psw->cjtgrabcand++] = *pcand;
        BroadcastTaskEvent(g_game, 0x3D, pcand->plo);
    }
    qsort(ajtgrabcandOld, psw->cjtgrabcand, sizeof(JTGRABCAND), func_00194F48);
}
