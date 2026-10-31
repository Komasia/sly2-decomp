struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct SAI { int a; };
struct SCROLLER { char pad[0x24]; short du; short dv; char pad2[0x34 - 0x28]; struct SAI sai; char pad3[0x50 - 0x38];
    float duSpeed; float dvSpeed; float duMax; float dvMax; float sdu; float sdv; };
int func_0011A1E8(struct SAI *psai);
float func_00245A18(float x, float y);
void SetSaiDuDv__FP3SAIff(struct SCROLLER *p, float du, float dv);
void UpdateScroller__FP8SCROLLERf(struct SCROLLER *p)
{
    float du, dv;
    if (func_0011A1E8(&p->sai)) return;
    du = func_00245A18(p->du * (1.0f / 4096.0f) + p->duSpeed * p->sdu * g_clock.dt, p->duMax);
    dv = func_00245A18(p->dv * (1.0f / 4096.0f) + p->dvSpeed * p->sdv * g_clock.dt, p->dvMax);
    SetSaiDuDv__FP3SAIff(p, du, dv);
}
