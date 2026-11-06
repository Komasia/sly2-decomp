struct S { char pad[0x50]; unsigned short fl; };
void func_001FB6A8(struct S *);
void RemoveActive__4CSnd(struct S *);
// name: SafeHouse port (CSnd::SetDirty)
void SetDirty__4CSndUiUi(struct S *p, unsigned short m, unsigned short v)
{
    p->fl = (p->fl & ~m) | (v & m);
    if (p->fl) func_001FB6A8(p); else RemoveActive__4CSnd(p);
}
