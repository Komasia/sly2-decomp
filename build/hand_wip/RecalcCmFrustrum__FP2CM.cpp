struct CM {
    char pad0[0x18]; float x18; float x1C; float x20; char pad1[0x3C - 0x24];
    float x3C; float x40; float x44; float x48; float x4C; float x50;
    char pad2[0x100 - 0x54]; char m100[0x150]; char m250[1];
};
extern "C" float tanf(float);
extern "C" float sqrtf(float);
void BuildProj(void *p, float a, float b, float c, float d, float e, float f);
void SetCmLookAt(CM *p, float g, void *pv);
void RecalcCm(CM *p);
static inline float GMax(float a, float b) { return a > b ? a : b; }
void RecalcCmFrustrum(CM *pcm)
{
    float t = tanf(pcm->x20 * 0.5f);
    float r = 1.0f / pcm->x20;
    float c = pcm->x3C;
    float c2 = c * c + 1.0f;
    float ty = t * c;
    float m = pcm->x18 * r;
    pcm->x44 = t;
    pcm->x40 = ty;
    pcm->x1C = GMax(1.0f, m);
    pcm->x48 = t * sqrtf(c2) * pcm->x4C + 1.0f;
    BuildProj(pcm->m100, 512.0f / (ty * 4096.0f), 224.0f / (t * 4096.0f), 0.0f, 0.0f, pcm->x4C, pcm->x50);
    SetCmLookAt(pcm, 1.0f, pcm->m250);
    RecalcCm(pcm);
}
