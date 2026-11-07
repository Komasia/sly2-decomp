struct ENTRY;
struct S { char pad[0x2C0]; long mask; };
struct ENTRY *PkindeBest__FP5GUARDUl(struct S *p, long mask);
struct ENTRY *func_00209BC0(struct S *p)
{
    return PkindeBest__FP5GUARDUl(p, p->mask);
}
