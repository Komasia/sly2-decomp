typedef struct { short d; short pad; void *pfn; } VTE;
typedef struct SUB {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x58 - 0x10];
    int x58;
    char pad5c[0x70 - 0x5C];
    int x70;
    int x74;
    int x78;
} SUB;
typedef struct OBJ {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x24 - 0x10];
    SUB *x24;
    char pad28[0x40 - 0x28];
    int x40;
    float x44;
    char pad48[0x25C - 0x48];
    int x25C;
    int x260;
    int x264;
} OBJ;
#include "clock.h"
extern char g_sw[];
void SetClockFactor__FP5CLOCKif(struct CLOCK *, float, int);
void PauseGame__FP9GAMEPAUSEi(void *, int);
void ResumeGame__FP9GAMEPAUSEi(void *, int);
void SetState__FP8SCREENRTi(SUB *, int);
void SetTimerTimers(SUB *, int) asm("SetTimerTimers__FP5TIMER6TIMERS");
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
void BuildShopList__FP4SHOP(OBJ *);
void SelectShopRow__FP4SHOPi(OBJ *, int);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
void func_001DC260(OBJ *p, int s)
{
    int old;
    if (!p->x24)
        s = -1;
    if (s == p->x40)
        return;
    if (p->x40 == -1) {
        SetClockFactor__FP5CLOCKif(&g_clock, 0.0f, 0);
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(p, 10);
        SetState__FP8SCREENRTi(p->x24, 1);
    }
    old = p->x40;
    p->x40 = s;
    p->x44 = g_clock.tReal;
    switch (s) {
    case -1:
        VCALL(p->x24, 50);
        SetClockFactor__FP5CLOCKif(&g_clock, 1.0f, 0);
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(p, 11);
        if (p->x24->x58 > 0)
            SetTimerTimers(p->x24, 1);
        p->x25C = s;
        p->x260 = s;
        p->x264 = s;
        break;
    case 0:
        p->x24->x74 = 0x4D4;
        p->x24->x70 = 0x4D5;
        p->x24->x78 = 0x4D6;
        if (old == 1) {
            SetState__FP8SCREENRTi(p->x24, 1);
            SetState__FP8SCREENRTi(p->x24, 2);
        } else {
            SetTimerTimers(p->x24, 2);
        }
        SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        break;
    case 1:
        p->x24->x74 = 0x49B;
        p->x24->x70 = 0x49C;
        p->x24->x78 = 0x49D;
        if (old == 0) {
            SetState__FP8SCREENRTi(p->x24, 1);
            SetState__FP8SCREENRTi(p->x24, 2);
        } else {
            SetTimerTimers(p->x24, 2);
        }
        SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        break;
    }
    BuildShopList__FP4SHOP(p);
    SelectShopRow__FP4SHOPi(p, 0);
    ((void (*)(void *, int))p->vt[14].pfn)((char *)p + p->vt[14].d, -1);
}
