struct S { char pad[0x18]; void *p18; };
int func_0017EEB8(struct S *p);
int func_0017DCB8(void *p);
int func_0017EE78(struct S *p) { if (!func_0017EEB8(p)) return 0; return func_0017DCB8(p->p18); }
