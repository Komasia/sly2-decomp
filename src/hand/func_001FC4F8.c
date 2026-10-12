struct S { char pad[0x3B8]; int fl; };
int func_001FC4F8(struct S *p) { return (p->fl & 4) ? 2 : 1; }
