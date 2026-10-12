struct CLOCK { char pad[0x3C]; float g3C; };
extern struct CLOCK D_002DDED0;
struct Q { char pad[0x10B4]; int n; };
extern struct Q D_002DFC00;
extern int D_003DA0B8;
struct N { int *an; int c; int pad[2]; int i; int pad2; struct N *next; };
struct P { struct N *head; int pad[2]; float g; };
void func_0014BF48(struct P *p, struct Q *q, unsigned short k)
{
    struct N *n;
    if (q != &D_002DFC00) return;
    if (k == q->n) return;
    if (!q->n) return;
    if (!D_003DA0B8) return;
    for (n = p->head; n; n = n->next) {
        int fDone = n->i >= n->c;
        if (!fDone) {
            if (n->an[n->i] == q->n) n->i++;
            else n->i = 0;
        }
    }
    p->g = D_002DDED0.g3C + 1.0f;
}
