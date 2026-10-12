struct S { char pad[0x38]; float g; };
extern float D_002C3C58;
void func_001A5C48(struct S *);
void func_001FF3E8(struct S *p) { func_001A5C48(p); if (p->g == 1e10f) p->g = D_002C3C58; }
