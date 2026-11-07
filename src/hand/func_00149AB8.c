struct K { short x; short y; union { short s; int i; } u; };
struct N { int a; struct K k; int d; struct N *next; };
struct P { char pad[0x3CA8]; struct N *head; };
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(struct P *p, int a, struct K k, int d);
// name: SafeHouse port (PostDeferredCall)
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(struct P *p, int a, struct K k, int d)
{
    struct N *n;
    for (n = p->head; n; n = n->next) {
        if (n->a == a && n->k.y == k.y &&
            ((n->k.y != -1 && n->k.u.s == k.u.s) || n->k.u.i == k.u.i) &&
            n->d == d)
            return;
    }
    PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(p, a, k, d);
}
