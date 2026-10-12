struct O { char pad[0x28]; unsigned long fl; char pad2[0xD0]; struct O *p100; };
struct S { char pad[0x30]; int c; struct O *a[1]; char pad2[0x80]; int nB8; };
#define BIT60(o) ((int)((o)->fl >> 60) & 1)
int func_002022D8(struct S *p)
{
    int i;
    if (p->nB8) return 1;
    for (i = 0; i < p->c; i++) {
        struct O *o = p->a[i];
        if (BIT60(o) && (!o->p100 || !BIT60(o->p100))) return 1;
    }
    return 0;
}
