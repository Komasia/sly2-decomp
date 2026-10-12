/* 2 diffs: registers match, but g34 is stored last instead of second (7! store-order search, nA0 last: best 2) */
struct S { char pad[0x34]; float g34; char pad2[0x10]; float g48; int n4C; char pad3[0x8]; int n58; char pad4[0x8]; float g64; float g68; float g6C; char pad5[0x30]; int nA0; };
extern float D_002BE624, D_002BE628, D_002BE62C;
void func_001EEF68(struct S *p);
void func_00177E80(struct S *p) { func_001EEF68(p); p->n4C = -1; p->g64 = D_002BE62C; p->g68 = D_002BE624; p->g6C = D_002BE628; p->g48 = -1.0f; p->n58 = 0; p->g34 = -1.0f; p->nA0 = 1; }
