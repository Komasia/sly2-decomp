struct S { char pad[0x10]; void *p10; char pad2[0x20]; int n34; };
void func_001EEF68(struct S *p);
void func_00209890(void *p, int n);
// name: SafeHouse port (JOBACT::Init)
void Init__6JOBACT(struct S *p) { func_001EEF68(p); func_00209890(p->p10, 0x18); p->n34 = -1; }
