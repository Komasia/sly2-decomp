typedef struct E { void (*pfn)(void *, void *); void *arg; struct E *next; } E;
struct S { char pad[0x34]; E *first; };
/* 4/36 differ: only prologue sq/daddu order (target: sq s2, sq s0, move s2, sq s1) */
void func_001A5D98(struct S *s)
{
    E *a[32];
    E *e = s->first;
    int n = 0;
    if (!e)
        return;
    do { a[n] = e; n++; e = e->next; } while (e);
    for (n--; n >= 0; n--) { e = a[n]; e->pfn(s, e->arg); }
}
