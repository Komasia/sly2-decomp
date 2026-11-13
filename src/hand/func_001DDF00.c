struct O { char pad[0x5C]; int n; };
struct E { struct O *po; int a, b; };
struct G2 { char pad[0x48]; int c; struct E ae[1]; };
extern struct G2 D_003DA3C0;
extern struct G g_sw;
void *func_0013E368(struct G *g, int n);
void s1_strcpy(void *p, void *q);
void func_001DDF00(void *p, int i) {
    struct G2 *pg = &D_003DA3C0;
    if (i < pg->c) s1_strcpy(p, func_0013E368(&g_sw, pg->ae[i].po->n));
}
