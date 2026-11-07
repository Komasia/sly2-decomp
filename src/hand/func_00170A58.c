struct G;
extern struct G g_sw;
struct N { int k; int b; char pad[0x10]; struct N *next; };
struct S { char pad[0x50]; struct N *pn; };
struct S *PloFindSwNearest__FP2LO3OIDii(struct G *pg, int k, int b, struct S *p);
int func_001709A8(struct S *p);
void func_001E9C30(struct S *p);
// name: SafeHouse port (PostLoadCmdlist)
void PostLoadCmdlist__FP7CMDLIST(struct S *p) {
    struct N *pn;
    for (pn = p->pn; pn; pn = pn->next) {
        switch (pn->k) {
        case 6: {
            struct S *o = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, pn->b, p);
            if (o && func_001709A8(o) == -1) func_001E9C30(o);
            break;
        }
        case 0:
            p = PloFindSwNearest__FP2LO3OIDii(&g_sw, p ? 4 : 5, pn->b, p);
            break;
        }
    }
}
