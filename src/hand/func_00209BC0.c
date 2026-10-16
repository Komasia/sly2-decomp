struct ENTRY;
struct S { char pad[0x2C0]; long mask; };
struct ENTRY *func_00209AD0(struct S *p, long mask);
struct ENTRY *func_00209BC0(struct S *p)
{
    return func_00209AD0(p, p->mask);
}
