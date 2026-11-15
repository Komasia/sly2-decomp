#include "so.h"
struct X14 { struct LO *plo; };
struct P { char pad[0xC]; VTENT *vt; char pad1[0x14 - 0x10]; struct X14 *px14; char pad2[0x150 - 0x18]; int state; float tState; char pad3[0x160 - 0x158]; void *p160; };
#include "clock.h"

extern struct P *D_002DD644;
extern char D_003DD040[];
extern char g_sw[];
void SetSoundMgrFlags__FP8SOUNDMGRUii(void *p, int a, int b);
void SetClockFactor__FP5CLOCKif(struct CLOCK *p, int a, float g);
void PauseGame__FP9GAMEPAUSEi(void *p, int a);
void ResumeGame__FP9GAMEPAUSEi(void *p, int a);
int FLoActive__FP2LO(struct P *p);
void AppendDlEntry__FP2DLPv(void *p, struct X14 *px);
void SetAsegaAsegSpeed__FP5ASEGAf(void *p, float g);
void func_00147410(struct P *p, int state)
{
    if (state == p->state) return;
    switch (p->state) {
    case -1:
        D_002DD644 = p;
        SetSoundMgrFlags__FP8SOUNDMGRUii(D_003DD040, 2, 0);
        SetClockFactor__FP5CLOCKif(&g_clock, 8, 0.0f);
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        ((void (*)(void *))p->vt[8].pfn)(VT_THIS(p, &p->vt[8]));
        if (!FLoActive__FP2LO(p)) {
            struct LO *plo;
            AppendDlEntry__FP2DLPv(g_sw + 0x2C, p->px14);
            plo = p->px14->plo;
            ((void (*)(void *))plo->pvt[23].pfn)(VT_THIS(plo, &plo->pvt[23]));
        }
        break;
    case 3:
        if (p->p160) SetAsegaAsegSpeed__FP5ASEGAf(p->p160, 1.0f);
        break;
    }
    p->state = state;
    p->tState = g_clock.tReal;
    switch (state) {
    case -1:
        D_002DD644 = 0;
        SetClockFactor__FP5CLOCKif(&g_clock, 8, 1.0f);
        SetSoundMgrFlags__FP8SOUNDMGRUii(D_003DD040, 2, 1);
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        ((void (*)(void *))p->vt[9].pfn)(VT_THIS(p, &p->vt[9]));
        break;
    case 3:
        if (p->p160) SetAsegaAsegSpeed__FP5ASEGAf(p->p160, 0.0f);
        break;
    }
}
