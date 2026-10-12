typedef unsigned long ulong;
struct Q { char pad[0x68]; ulong t; };
struct S { int c; struct Q *a[8]; };
struct P { char pad[0x204]; struct S s; };
float func_001FE3F8(struct P *p)
{
    struct Q *q;
    if (p->s.c > 0) { q = *(p->s.a + p->s.c - 1); }
    else q = 0;
    if (!q) return 0.0f;
    return (float)q->t * (1.0f / 294912000.0f);
}
