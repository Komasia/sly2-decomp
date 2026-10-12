struct S { char pad[0x298]; int a; char pad2[0x90]; int b; };
int func_00209A68(struct S *p, int n);
int func_00207598(struct S *p) { if (p->b || p->a) return 1; return func_00209A68(p, 0x2A) != 0; }
