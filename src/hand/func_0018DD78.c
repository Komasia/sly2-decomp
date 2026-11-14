struct S { char pad[0x2044]; void *p2044; };
#include "clock.h"
extern int D_003E1BEC;
void SetClockFactor__FP5CLOCKif(struct CLOCK *pclock, int n, float g);
void Stop__4CSndf(void *p, float g);
void func_00258040(void **pp, int n);
void func_00141E28(struct S *p, int n);
void func_0018DD78(struct S *p, int n)
{
    if (n == 0x1D || n == 0x2A) {
        void **pp;
        SetClockFactor__FP5CLOCKif(&g_clock, 1, 1.0f);
        pp = &p->p2044;
        if (*pp) {
            Stop__4CSndf(*pp, 0.0f);
            func_00258040(pp, 0);
        }
        D_003E1BEC = 0;
    } else {
        func_00141E28(p, n);
    }
}
