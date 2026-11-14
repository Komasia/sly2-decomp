struct S { char pad[0x394]; int n; int a[1]; };
void *s1_memmove(void *d, void *s, int n) asm("memmove");
// name: SafeHouse port (RemoveTargetClass)
void RemoveTargetClass__FPvi(struct S *p, int x)
{
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->a[i] == x) {
            s1_memmove(p->a + i, p->a + i + 1, (p->n - i) * 4 - 4);
            p->n--;
        }
    }
}
