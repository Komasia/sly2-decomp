struct S { char pad[0x28]; unsigned long fl; };
void SetCmFocusObject__FP2LOi(struct S *p, int f);
void SetShipState__FP2LOi(struct S *p, int f);
// name: SafeHouse port (SetHackShipFocus)
void SetHackShipFocus__FP2LOi(struct S *p, int f) { SetCmFocusObject__FP2LOi(p, f); if (f) SetShipState__FP2LOi(p, 1); else if ((int)(p->fl >> 60) & 1) SetShipState__FP2LOi(p, 0); }
