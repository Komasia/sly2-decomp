struct T { char pad[0x1C]; int x1C; int x20; int x24; int x28; };
struct S { char pad[0x114]; struct T *x114; char x118[0x58]; int x170; char pad2[0x6C]; int x1E0; };
void Spool(struct T *t) asm("Spool__18CBinaryAsyncStream");
void FlushCache(int n);
int func_0024F770(void *p, int a, int n);
void Skip(struct T *t, int r) asm("Skip__18CBinaryAsyncStreami");
int func_001B41D0(struct S *p, int wait)
{
    int n, r;
    n = p->x114->x1C - p->x114->x24;
    while (n == 0) {
        if (!p->x114->x28) return 2;
        Spool(p->x114);
        n = p->x114->x1C - p->x114->x24;
        if (n == 0 && !wait) return 0;
    }
    FlushCache(0);
    r = func_0024F770(p->x118, p->x114->x20 + p->x114->x24, n);
    Skip(p->x114, r);
    if (r) return 0;
    if (p->x170 >= n && p->x1E0 >= n) return 2;
    return 1;
}
