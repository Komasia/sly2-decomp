struct R { char pad[0xC]; int c; char dl[0xC]; };
struct Q { char pad[0x20]; struct R *pr; int n; float t; };
struct S { char pad[0x28C]; char dl[0xC]; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern char g_game[];
void RemoveDlEntry__FP2DLPv(void *pdl, void *pv);
void AppendDlEntry__FP2DLPv(void *pdl, void *pv);
void func_001619A0(void *g, int n, struct S *p);
void func_00181B60(struct S *p, struct R *r);
void func_00181EB0(struct S *p, struct Q *q, int n)
{
    struct R *r;
    if (n == q->n) return;
    q->n = n;
    q->t = g_clock.t;
    if (n != 2) return;
    r = q->pr;
    r->c--;
    RemoveDlEntry__FP2DLPv(r->dl, q);
    AppendDlEntry__FP2DLPv(p->dl, q);
    if (!r->c) func_001619A0(g_game, 0x3A, p);
    func_00181B60(p, r);
}
