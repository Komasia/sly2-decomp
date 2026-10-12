struct WR; struct ONZ; struct WRE { char pad[0x30]; char onz[1]; };
enum ENSK { ENSK_Get, ENSK_Set };
WRE *PwreGetWrBend(WR *pwr, ENSK ensk);
void AddOnzOnze(ONZ *ponz, float uAmpl, float gFreq, float gPhase, float uRandom);
void AddWrBendNoise(WR *pwr, float uAmpl, float gFreq, float gPhase, float uRandom)
{
    WRE *pwre = PwreGetWrBend(pwr, ENSK_Set);
    AddOnzOnze((ONZ *)pwre->onz, uAmpl, gFreq, gPhase, uRandom);
}
