struct U { char pad[0xC]; float g; };
struct T { char pad[0xDC]; struct U *pu; };
struct S { char pad[0xE8]; struct T *pt; };
float func_001F8440(struct S *p) { struct U *pu = 0; if (p->pt) pu = p->pt->pu; if (pu) return pu->g; return 0.0f; }
