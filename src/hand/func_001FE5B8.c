struct S { char pad[0x68]; int fl; };
void func_001FE5B8(struct S *p, int f, int fSet) { if (fSet) p->fl |= f; else p->fl &= ~f; }
