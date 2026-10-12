struct S { char pad[0x148]; unsigned long grf; };
void func_001F2108(struct S *);
void func_001320C8(struct S *p) { func_001F2108(p); p->grf |= 0x8000L << 19; }
