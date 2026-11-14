#include "clock.h"
struct S { char p0[0x34]; float g34; };
void func_001D9870(struct S *p);
void SetShopMsg__FP4SHOPii(struct S *p, int a, int b);
void func_001DA808(struct S *p) {
    func_001D9870(p);
    if (p->g34 <= g_clock.tReal) SetShopMsg__FP4SHOPii(p, -1, -1);
}
