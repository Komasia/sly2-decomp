struct WR;
struct ONZ;
enum ENSK { ENSK_Nil = -1, ENSK_Get = 0, ENSK_Set = 1 };
struct WRE { char pad[0x80]; char onz[1]; };
WRE *PwreGetWrBend(WR *pwr, ENSK ensk);
void AddOnzOnze(ONZ *ponz, float uAmpl, float gFreq, float gPhase, float uRandom);
void AddWrSwivelNoise(WR *pwr, float uAmpl, float gFreq, float gPhase, float uRandom)
{
    WRE *pwre = PwreGetWrBend(pwr, ENSK_Set);
    AddOnzOnze((ONZ *)pwre->onz, uAmpl, gFreq, gPhase, uRandom);
}
