struct S { char pad[0x30]; int n30; };
void func_001EEF68(struct S *p);
void func_0017B590(struct S *p) { func_001EEF68(p); p->n30 = -1; }
