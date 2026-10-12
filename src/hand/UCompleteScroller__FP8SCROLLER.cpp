struct SCROLLER { char pad[0x24]; short du; short dv; char pad2[0x50 - 0x28]; float duSpeed; float dvSpeed; float duMax; float dvMax; };
float UCompleteScroller(SCROLLER *pscroller)
{
    float uComp = 0.0f;

    if (pscroller->duSpeed != 0.0f)
        uComp = ((pscroller->du * (1.0f / 4096.0f)) / pscroller->duMax) * 0.5f;
    else
        uComp = 0.5f;

    if (pscroller->dvSpeed != 0.0f)
        uComp += ((pscroller->dv * (1.0f / 4096.0f)) / pscroller->dvMax) * 0.5f;
    else
        uComp += 0.5f;

    return uComp;
}
