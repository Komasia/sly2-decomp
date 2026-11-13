struct CRef { int m_tagk; float m_tag; };
struct E { int x0, x4, x8, xC, x10; int x14; int x18; };
struct G { int pad[9]; int x24; };
struct GD { char pad[0x3B1C]; int x3B1C; };
struct B { char data[0x5464]; };
extern struct G D_003D9ED0;
extern struct E D_003D9EDC[];
extern struct GD g_sw;
extern struct B D_002E6604[];
int func_001B0108(struct G *g);
int KindDataAccess__FP4MENU(struct G *g);
void NProgress(struct CRef *ret, int a, void *b);
void Decref(struct CRef *) asm("Decref__4CRef");
char *func_0013E368(void *p, int n);
char *s1_strcpy(char *d, const char *s);
char *strcpy1(char *d, const char *s);
void func_001ADA20(char *buf)
{
    struct G *g = &D_003D9ED0;
    struct GD *gd;
    struct CRef ref;
    float f;
    if (!func_001B0108(g))
        return;
    gd = &g_sw;
    {
    struct E *e = &D_003D9EDC[g->x24];
    NProgress(&ref, gd->x3B1C, &D_002E6604[e->x14]);
    }
    f = ref.m_tag;
    Decref(&ref);
    switch (KindDataAccess__FP4MENU(g)) {
    case 0x1E:
        if (f != 0.0f)
            s1_strcpy(buf, func_0013E368(gd, 0x25));
        else
            s1_strcpy(buf, func_0013E368(gd, 0x26));
        break;
    case 0x1F:
        if (f != 0.0f)
            s1_strcpy(buf, func_0013E368(gd, 0x27));
        else
            s1_strcpy(buf, func_0013E368(gd, 0x26));
        break;
    case 0x19:
        s1_strcpy(buf, func_0013E368(gd, 0x29));
        if (f != 0.0f) {
            strcpy1(buf, "\n");
            strcpy1(buf, func_0013E368(gd, 0x25));
        }
        break;
    }
}
