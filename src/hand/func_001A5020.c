struct B { int x0; int x4; char pad[0x34]; int x3c; };
struct R { int x0; struct B *x4; };
struct R *func_001A4FB0(void *a, int n);
static inline int F(struct B *b) { if (!b) return 0; return b->x4 != b->x3c; }
void func_001A5020(void *a, struct B *b)
{
    if (F(b)) func_001A4FB0(a, 0)->x4 = b;
}
