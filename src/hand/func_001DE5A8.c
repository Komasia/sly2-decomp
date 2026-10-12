struct S { char pad[0x70]; unsigned long fl; };
struct S *func_001F56F8(void *p);
struct S *func_001DE5A8(void *p) {
    struct S *ps = func_001F56F8(p);
    ps->fl |= 0x20;
    return ps;
}
