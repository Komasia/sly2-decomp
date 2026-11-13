struct CRef { int m_tagk; int m_tag; };
struct G { char pad[0x3B54]; int x3B54; };
struct H { char pad[0x4C]; int x4C; };
struct S { char pad[0xFD50]; void *xFD50; };
extern struct G g_sw;
extern struct H D_002E6550;
extern int D_002DEB4C;
extern char D_003D4A60[], D_002E65A0[];
int func_0020E040(struct G *g);
int func_00210AE0(void);
void NProgress(struct CRef *ret, int a, void *b);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_001ACB58(struct H *h, int n);
void func_001ABCE8(struct S *s);
void func_001ADE38(void *p);
// name: SafeHouse port (hudwidget.cpp HudAutoSave(fForce), "// 0x1ABD98"; same body)
void HudAutoSave(struct S *s, int force) asm("HudAutoSave__FP4SAVEi");
void HudAutoSave(struct S *s, int force)
{
    struct G *g;
    struct CRef ref;
    int t;
    if (!s->xFD50)
        return;
    g = &g_sw;
    if (func_0020E040(g))
        return;
    if (D_002DEB4C)
        return;
    if (!func_00210AE0() && !force)
        return;
    NProgress(&ref, g->x3B54, D_003D4A60);
    t = ref.m_tag;
    Decref(&ref);
    if (!t) {
        D_002E6550.x4C = 3;
        func_001ACB58(&D_002E6550, 0x22);
    } else {
        func_001ABCE8(s);
        func_001ADE38(D_002E65A0);
    }
}
