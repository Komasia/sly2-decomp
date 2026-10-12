struct MSG { int cb; int nKind; };
void *func_001AE2A0(struct MSG *p);
void *func_001AE4F8(int cb) { struct MSG m; m.cb = cb; m.nKind = 0x10; return func_001AE2A0(&m); }
