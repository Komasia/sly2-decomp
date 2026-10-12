struct SMP;
float RadNormalize(float rad);
float GSmooth(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext);

float RadSmooth(float radCur, float radTarget, float dt, SMP *psmp, float *pdradNext)
{
    float rad;
    rad = RadNormalize(radTarget - radCur);
    rad = GSmooth(0.0f, rad, dt, psmp, pdradNext);
    rad = RadNormalize(radCur + rad);
    return rad;
}
