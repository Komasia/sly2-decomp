/* SaveToTarget (0x1AD3E0): saves into the chosen slot: it becomes the game slot (MC +0xFD50 = +0xFD58), the prompt's
 * +0x4C = 2; with no save progress (key D_003E0FE4) the prompt shows 0x22, else message 0x1A and the save runs
 * (func_001ABD40). SafeHouse menu.cpp. */
struct CRef { int m_tagk; int m_tag; };
struct G { char pad[0xFD50]; int xFD50; int xFD54; int xFD58; };
struct H { char pad[0x4C]; int x4C; };
extern struct G D_002E65E0;
extern struct H D_002E6550;
extern int D_003E0FE4;
extern char D_003D4A60[];
void NProgress(struct CRef *ret, int a, void *b);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_001ACB58(struct H *h, int n);
void func_001ABD40(struct G *g);
// name: SafeHouse port (SaveToTarget)
void SaveToTarget__Fv(void)
{
    struct G *g = &D_002E65E0;
    struct H *h = &D_002E6550;
    struct CRef ref;
    int t;
    g->xFD50 = g->xFD58;
    h->x4C = 2;
    NProgress(&ref, D_003E0FE4, D_003D4A60);
    t = ref.m_tag;
    Decref(&ref);
    if (!t) {
        func_001ACB58(h, 0x22);
    } else {
        func_001ACB58(h, 0x1A);
        func_001ABD40(g);
    }
}
