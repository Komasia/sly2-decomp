struct K { int a, b; };
struct S { char pad[0x164]; struct K k; };
void ComputeLight__FP11LIGHTPARAMS(struct S *p);
void func_001A3650(struct S *p, struct K *pk) { p->k = *pk; ComputeLight__FP11LIGHTPARAMS(p); }
