struct SCROLLER { char pad[0x60]; float su; float sv; };
void SetScrollerMasterSpeeds(SCROLLER *pscroller, float su, float sv)
{
    pscroller->su = su;
    pscroller->sv = sv;
}
