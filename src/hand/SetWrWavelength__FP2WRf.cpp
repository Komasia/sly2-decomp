struct WR; struct WRE { char pad[0x64]; float x; };
enum ENSK { ENSK_Get, ENSK_Set };
WRE *PwreGetWrCircle(WR *pwr, ENSK ensk);
void SetWrWavelength(WR *pwr, float sWavelength)
{
    WRE *pwre = PwreGetWrCircle(pwr, ENSK_Set);
    if (sWavelength == 0.0f)
        pwre->x = 0.0f;
    else
        pwre->x = 1.0f / sWavelength;
}
