struct N { int a[3]; struct N *next; };
void func_0011CD98(void *pool, struct N *n);
void func_002296C0(char *p, struct N *n)
{
    while (n) {
        struct N *next = n->next;
        func_0011CD98(p + 0x40E8, n);
        n = next;
    }
}
