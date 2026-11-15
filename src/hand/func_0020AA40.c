/* AddGuardAction (0x20AA40, option 233): adds an action oid to the guard's list (at most 8). */
struct GUARD { char pad[0xEB8]; int aoidAction[8]; unsigned int coidAction; };
// name: SafeHouse port (AddGuardAction)
void AddGuardAction__FP2LOi(struct GUARD *pguard, int oid) { if (oid != -1) { if (pguard->coidAction < 8) pguard->aoidAction[pguard->coidAction++] = oid; } }
