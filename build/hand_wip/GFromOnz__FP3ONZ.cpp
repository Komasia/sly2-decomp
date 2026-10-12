struct ONZE { float uAmpl; float gFreq; float gPhase; float uRandom; };
struct ONZ { float gMin; float gMax; float s; int conze; ONZE aonze[4]; };
float UNoise(float a, float b, float c);
float GSmooth(float u, float s);
float GFromOnz(ONZ *ponz)
{
    float gSum, uSum;
    gSum = uSum = 0.0f;
    for (int i = 0; i < ponz->conze; i++) {
        ONZE *ponze = &ponz->aonze[i];
        float g = UNoise(ponze->gFreq, ponze->gPhase, ponze->uRandom);
        gSum += ponze->uAmpl * g;
        uSum += ponze->uAmpl;
    }
    float u = GSmooth(gSum / uSum, ponz->s);
    return ponz->gMin + u * (ponz->gMax - ponz->gMin);
}
