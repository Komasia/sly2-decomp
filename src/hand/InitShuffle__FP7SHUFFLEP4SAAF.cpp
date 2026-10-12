struct SAAF { char pad[0xC]; float dtLoopMin; float dtLoopMax; };
struct SHUFFLE { char pad[0x50]; float dtPauseMin; float dtPauseMax; };
void InitSaa(SHUFFLE *p, SAAF *psaaf);
void InitShuffle(SHUFFLE *pshuffle, SAAF *psaaf)
{
    float dtMax, dtMin;
    InitSaa(pshuffle, psaaf);
    dtMin = psaaf->dtLoopMin;
    dtMax = psaaf->dtLoopMax;
    pshuffle->dtPauseMax = dtMax;
    pshuffle->dtPauseMin = dtMin;
}
