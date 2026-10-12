struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_001EEF68(struct S *p);
void func_00174920(struct S *p) { func_001EEF68(p); p->n3C = 0; p->n30 = -1; }
