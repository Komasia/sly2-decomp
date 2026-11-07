struct S { char pad[0x28]; unsigned long fl; };
void func_001C3FF0(struct S *p, int f);
void SetShipState__FP2LOi(struct S *p, int f);
// name: SafeHouse port (SetHackShipFocus)
void SetHackShipFocus__FP2LOi(struct S *p, int f) { func_001C3FF0(p, f); if (f) SetShipState__FP2LOi(p, 1); else if ((int)(p->fl >> 60) & 1) SetShipState__FP2LOi(p, 0); }
