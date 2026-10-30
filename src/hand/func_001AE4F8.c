struct MSG { int cb; int nKind; };
void *PvAllocSwClearImpl__Fi(struct MSG *p);
void *func_001AE4F8(int cb) { struct MSG m; m.cb = cb; m.nKind = 0x10; return PvAllocSwClearImpl__Fi(&m); }
