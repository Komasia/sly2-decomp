typedef struct { short d; short pad; void *pfn; } VTE;
struct O { char pad[0xC]; VTE *vt; };
struct E { int k; int h; struct O *po; };
void ApplyAseg__FP4ASEGiiffPP5ASEGA(int h, char *p, int fl, struct O **ppo, float g, float f);
void func_001F0198(int h, char *p, int a, int fl, struct O **ppo);
void StartK2__FP5KIND2P3ALOiP6K2PLAY(int h, char *p, int fl, struct O *po);
void StartK3__FP5KIND3iiP6K3PLAY(int h, char *p, int fl, struct O *po);
#define VC1(o) ((void (*)(void *))(o)->vt[1].pfn)((char *)(o) + (o)->vt[1].d)
// name: SafeHouse port (PlayKinde)
void PlayKinde__FP5KINDEP5GUARDif(struct E *pe, char *p, int fl, float g)
{
    switch (pe->k) {
    case -1:
        break;
    case 0:
        ApplyAseg__FP4ASEGiiffPP5ASEGA(pe->h, p, fl, &pe->po, g, 1.0f);
        VC1(pe->po);
        break;
    case 1:
        func_001F0198(pe->h, p, -1, fl, &pe->po);
        VC1(pe->po);
        break;
    case 2:
        pe->po = (struct O *)(p + 0xDB0);
        StartK2__FP5KIND2P3ALOiP6K2PLAY(pe->h, p, fl, pe->po);
        VC1(pe->po);
        break;
    case 3:
        pe->po = (struct O *)(p + 0xE20);
        StartK3__FP5KIND3iiP6K3PLAY(pe->h, p, fl, pe->po);
        VC1(pe->po);
        break;
    }
}
