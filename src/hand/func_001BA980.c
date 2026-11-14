struct F { int a[0x1C]; };
struct S { char pad[0x108C]; int n; char ab[0xC]; };
void *s1_memset(void *p, int c, int cb) asm("memset");
void *func_00205458(struct S *p, int oid);
void React__8JOBREACTP5AIMSG(void *p, struct F *pf);
void func_001BA980(struct S *p, int n)
{
    struct F f;
    void *po;
    s1_memset(p->ab, 0, 0xC);
    p->n = n;
    s1_memset(&f, 0, sizeof(f));
    f.a[0] = 0xF;
    po = func_00205458(p, 0x9C);
    if (po) React__8JOBREACTP5AIMSG(po, &f);
}
