struct WR; struct WRE;
enum ENSK { ENSK_0 };
enum WREK { WREK_Circle = 0, WREK_Bend = 1 };
WRE *PwreGetWrCur(WR *pwr, ENSK ensk, WREK wrek);
WRE *PwreGetWrCircle(WR *pwr, ENSK ensk)
{
    return PwreGetWrCur(pwr, ensk, WREK_Circle);
}
