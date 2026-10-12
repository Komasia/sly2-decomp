struct SMPA;
float RadNormalize(float rad);
float GSmoothA(float gCur, float dgCur, float gTarget, float dt, SMPA *psmpa, float *pdgNext);

float RadSmoothA(float radCur, float dradCur, float radTarget, float dt, SMPA *psmpa, float *pdradNext)
{
    float rad;
    rad = RadNormalize(radTarget - radCur);
    rad = GSmoothA(0.0f, dradCur, rad, dt, psmpa, pdradNext);
    rad = RadNormalize(radCur + rad);
    return rad;
}
