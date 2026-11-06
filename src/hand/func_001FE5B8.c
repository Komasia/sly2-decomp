struct S { char pad[0x68]; int fl; };
// name: SafeHouse port (SetSoundMgrFlags)
void SetSoundMgrFlags__FP8SOUNDMGRUii(struct S *p, int f, int fSet) { if (fSet) p->fl |= f; else p->fl &= ~f; }
