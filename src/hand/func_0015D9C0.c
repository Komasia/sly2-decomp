typedef struct CRef { int m_tagk; float m_g; } CRef;
struct X { char pad[0x110]; int i; };
struct G { char pad[0x3B58]; void *ap[9]; char pad2[0x4774 - 0x3B7C]; struct X *px; };
extern struct G g_sw;
extern char D_003D4A60[];
extern char D_002A5168[];
void NProgress(CRef *pref, void *p, void *q);
void Decref(CRef *pref) asm("Decref__4CRef");
float fmodf(float a, float b);
void fiprintf(char *pch, char *fmt, ...);
void func_0015D9C0(char *pch)
{
    struct G *pg = &g_sw;
    void *p;
    if (pg->px && (p = pg->ap[pg->px->i]) != 0) {
        CRef ref;
        float g;
        int h, m;
        NProgress(&ref, p, D_003D4A60);
        g = ref.m_g;
        Decref(&ref);
        h = (int)(g / 3600.0f);
        m = (int)(fmodf(g, 3600.0f) / 60.0f);
        fiprintf(pch, D_002A5168, h, m);
    }
}
