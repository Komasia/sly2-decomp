struct K { short x; short y; union { short s; int i; } u; };
struct N { int a; struct K k; int d; struct N *next; };
struct P { char pad[0x3CA8]; struct N *head; };
void func_00149A50(struct P *p, int a, struct K k, int d);
void func_00149AB8(struct P *p, int a, struct K k, int d)
{
    struct N *n;
    for (n = p->head; n; n = n->next) {
        if (n->a == a && n->k.y == k.y &&
            ((n->k.y != -1 && n->k.u.s == k.u.s) || n->k.u.i == k.u.i) &&
            n->d == d)
            return;
    }
    func_00149A50(p, a, k, d);
}
