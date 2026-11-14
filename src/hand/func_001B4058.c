#include "clock.h"
struct S { char pad[0x10C]; float f10C; int x110; int x114; char x118[8]; int x120; char pad2[0x5C]; char x180[0xBC]; int x23C; volatile int x240; };
int func_001B41D0(struct S *p, int n);
int sceMpegGetPicture(void *a, int b, int c);
void func_001B3510(struct S *p);
void func_001B3700(struct S *p);
void FlushCache(int n);
int SignalSema(int n);
void func_001B32B8(void *p);
void func_001B4058(struct S *p)
{
    while (p->x240 == 1) func_001B41D0(p, 0);
    if (sceMpegGetPicture(p->x118, p->x110 + 0x285A80, 0x5CD) < 0) return;
    if (p->x120 == 0) {
        p->f10C = g_clock.tReal;
        func_001B3510(p);
        func_001B3700(p);
        FlushCache(0);
    }
    while (p->x240) func_001B41D0(p, 0);
    SignalSema(p->x23C);
    func_001B32B8(p->x180);
}
