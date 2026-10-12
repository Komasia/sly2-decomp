struct S { char pad[0x10]; void *p10; char pad2[0x1C]; float g30; float g34; int n38; };
void func_001EEF68(struct S *p);
void func_00209890(void *p, int n);
void func_00179A58(struct S *p) { func_001EEF68(p); p->n38 = -1; p->g30 = p->g34 = 3.40282346638528859812e+38f; func_00209890(p->p10, 0x1E); }
