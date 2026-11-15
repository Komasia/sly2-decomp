#include "clock.h"
extern float D_002C3DB4;
struct S { int a; float t; };
// name: SafeHouse port (aipursuit.h FTargetrecExpired, orig 0x20A7E0)
int FTargetrecExpired__FP9TARGETREC(struct S *p) { return g_clock.t - p->t > D_002C3DB4; }
