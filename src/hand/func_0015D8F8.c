typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct X { char pad[0x110]; int i; };
struct G { char pad[0x3B7C]; void *ap[9]; char pad2[0x4774 - 0x3BA0]; struct X *px; };
extern struct G g_sw;
extern char D_003D4A60[];
extern void *D_002BE2F8[];
extern char D_002A5160[];
void NProgress(CRef *pref, void *p, void *q);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_001DAEA8(void *p);
void fiprintf(char *pch, char *fmt, ...);
void func_0015D8F8(char *pch)
{
    struct G *pg = &g_sw;
    void *p;
    if (pg->px && (p = pg->ap[pg->px->i]) != 0) {
        CRef ref;
        int n;
        NProgress(&ref, p, D_003D4A60);
        n = ref.m_tag;
        Decref(&ref);
        n = n * 95 / 100;
        if (func_001DAEA8(D_002BE2F8[pg->px->i]))
            n += 5;
        fiprintf(pch, D_002A5160, n);
    }
}
