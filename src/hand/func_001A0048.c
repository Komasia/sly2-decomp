typedef int qword __attribute__((mode(TI)));
typedef struct { union { qword q0; struct { void *x0; int x4; void *x8; int xc; } s; } u; qword q1; } E;
struct S { int x0; int c; int pad[2]; E a[1]; };
void func_001A0048(struct S *s, void *p0, void *p8)
{
    E *dst = s->a;
    E *src = dst;
    E *end = &s->a[s->c];
    for (; src < end; src++) {
        if (p0 && p0 == src->u.s.x0)
            continue;
        if (p8 && p8 == src->u.s.x8)
            continue;
        if (src != dst)
            *dst = *src;
        dst++;
    }
    s->c = dst - s->a;
}
