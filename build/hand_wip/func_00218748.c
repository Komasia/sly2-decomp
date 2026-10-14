struct E { char pad[0x10]; int f; void *p; };
struct S { char pad[8]; struct E *ae; };
void func_001FB018(void *p);
static inline struct E *Entries(const struct S *p){struct E *value;__asm__("lw %0,8(%1)":"=r"(value):"0"(p),"m"(p->ae));return value;}
void func_00218748(struct S *p, int i)
{
    void *q;
    p->ae[i].f = 1;
    q = Entries(p)[i].p;
    if (q)
        func_001FB018(q);
}
