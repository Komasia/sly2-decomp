struct SMP {
    float gMaxSpeed;
    float gMinSpeed;
    float rSpeed;
};
struct SMPA : SMP {
    float gAccel;
};
float GSmooth(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext);

float GSmoothA(float gCur, float dgCur, float gTarget, float dt, SMPA *psmpa, float *pdgNext)
{
    float dgNext;
    float g = GSmooth(gCur, gTarget, dt, psmpa, &dgNext);
    if (psmpa->gAccel > 0.0f) {
        float ddg = psmpa->gAccel * dt;
        float dgMax = dgCur + ddg;
        float dgMin = dgCur - ddg;
        if (dgNext > dgMax) {
            dgNext = dgMax;
            g = gCur + dgCur * dt + 0.5f * psmpa->gAccel * dt * dt;
        } else if (dgNext < dgMin) {
            dgNext = dgMin;
            g = gCur + dgCur * dt - 0.5f * psmpa->gAccel * dt * dt;
        }
    }
    if (pdgNext)
        *pdgNext = dgNext;
    return g;
}
