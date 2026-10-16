typedef unsigned long ulong;
struct S { char pad[0x28]; ulong x28; };
unsigned long func_00259AE8(struct S *p)
{
    return (p->x28 >> 60) & 1;
}
