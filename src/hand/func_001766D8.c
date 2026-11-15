/* func_001766D8: an AIJOB subclass's Init: the base init, no state. */
struct AIJOBST { char pad[0x30]; int st; };
void Init__5AIJOB(struct AIJOBST *pjob);
void func_001766D8(struct AIJOBST *pjob) { Init__5AIJOB(pjob); pjob->st = -1; }
