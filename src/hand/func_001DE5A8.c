struct S { char pad[0x70]; unsigned long fl; };
struct S *func_001F56F8(void *p);
// name: SafeHouse port (AddLaserAttachment)
struct S *AddLaserAttachment__FP3ALO(void *p) {
    struct S *ps = func_001F56F8(p);
    ps->fl |= 0x20;
    return ps;
}
