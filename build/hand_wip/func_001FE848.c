struct U { char pad[0x40]; int n; };
struct T { char pad[0x60]; struct U *pu; };
struct S { char pad[0x200]; struct T *pt; };
static inline int ReturnPredicate(int value){register int predicate asm("a0")=value;register int result asm("v0");__asm__("daddu %0,%1,$zero":"=r"(result):"r"(predicate));return result;}
int func_001FE848(struct S *p, int n)
{
    struct U *pu; int f;
    if (p->pt) {
        pu = p->pt->pu;
        f = 0;
        if (n != -1 && pu->n == n) f = 1;
        return ReturnPredicate(f);
    }
    return 0;
}
