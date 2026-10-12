struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; };
void func_001EEF68(struct S *p);
void func_00209890(void *p, int n);
void func_0017B808(struct S *p) { func_001EEF68(p); func_00209890(p->p10, 0x20); p->n30 = -1; }
