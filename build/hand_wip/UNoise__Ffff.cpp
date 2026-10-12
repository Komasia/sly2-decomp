struct CLOCK { float t; float dt; };
extern CLOCK g_clock __asm__("D_002DDED0");
float UNoise(int n);
static inline float GSmooth(float s) { return (3.0f - 2.0f * s) * s * s; }
float UNoise(float gFreq, float gPhase, float u1)
{
    float uRandom = u1;
    float t = gFreq * 2.0f * g_clock.t + gPhase;
    int n = (int)t;
    float u0 = UNoise(n);
    u1 = UNoise(n + 1);
    if (n & 1) {
        u0 *= uRandom;
        u1 = uRandom * (u1 - 1.0f) + 1.0f;
    } else {
        u1 *= uRandom;
        u0 = uRandom * (u0 - 1.0f) + 1.0f;
    }
    return u0 + (u1 - u0) * GSmooth(t - n);
}
