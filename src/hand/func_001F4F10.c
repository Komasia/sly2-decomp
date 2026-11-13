typedef unsigned long ulong;
struct S8 { int a, b; };
struct N { int n0; struct N *next; };
struct E { char pad[0x64]; struct N *pn; int pad2; int n6C; };
struct P { char pad[0xEC]; struct E *pe; char pad2[0x148 - 0xF0]; ulong fl; };
struct G;
extern struct G g_sw;
extern struct S8 D_002A8278;
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(struct G *, struct P *, struct S8, int);
// name: SafeHouse port (NotifyAloContacts 0x1F4F10, ALO vt slot 58)
void NotifyAloContacts(struct P *p) asm("NotifyAloContacts__FP3ALO");
void NotifyAloContacts(struct P *p)
{
    struct E *pe = p->pe;
    struct N *pn;
    if (pe->n6C) {
        PostDeferredCall__FPvUi15PFNDEFERREDCALLi(&g_sw, p, D_002A8278, 0);
    } else if (p->fl & 0x3000000) {
        for (pn = pe->pn; pn; pn = pn->next) {
            if (pn->n0) {
                PostDeferredCall__FPvUi15PFNDEFERREDCALLi(&g_sw, p, D_002A8278, 0);
                break;
            }
        }
    }
}
