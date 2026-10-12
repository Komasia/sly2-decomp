struct PINGPONG { char pad[0x1C]; int cframe; char pad2[0x60 - 0x20]; float dframe; float iframe; float dtPause; };
float UCompletePingpong(PINGPONG *ppingpong)
{
    float absDframe = ppingpong->dframe;
    float progress;

    if (absDframe < 0.0f)
    {
        absDframe = -absDframe;
        progress = (float)(ppingpong->cframe * 2) - ppingpong->iframe;
    }
    else
    {
        progress = ppingpong->iframe;
    }

    return (progress / absDframe) /
           (((float)(ppingpong->cframe * 2) / absDframe) + ppingpong->dtPause);
}
