struct ONZE { float uAmpl; float gFreq; float gPhase; float uRandom; };
struct ONZ { float gMin; float gMax; float uBias; int connze; ONZE aonze[4]; };
float UNoise(float gFreq, float gPhase, float uRandom);
float UBias(float u, float uBias);
float GFromOnz(ONZ *ponz)
{
    float gAmpl;
    float gSum = 0.0f;
    gAmpl = gSum;
    int i;
    for (i = 0; i < ponz->connze; i++) {
        ONZE *ponze = &ponz->aonze[i];
        float u = UNoise(ponze->gFreq, ponze->gPhase, ponze->uRandom);
        gSum += ponze->uAmpl * u;
        gAmpl += ponze->uAmpl;
    }
    float u = UBias(gSum / gAmpl, ponz->uBias);
    return ponz->gMin + u * (ponz->gMax - ponz->gMin);
}
