struct S { char pad[0x150]; int a; int b; int c; };
// name: SafeHouse port (pocket.cpp "orig: 0x001C2DB8 ClearReward")
void ClearReward(struct S *p) asm("ClearReward__FP2LO");
void ClearReward(struct S *p) { p->c = 0; p->b = 0; p->a = 0; }
