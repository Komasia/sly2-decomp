struct S { char pad[0x4E]; short c; };
void SetDirty__4CSndUiUi(struct S *, int, int);
// name: SafeHouse port (CSnd::Resume)
void Resume__4CSnd(struct S *p) { if (--p->c == 0) SetDirty__4CSndUiUi(p, 6, 4); }
