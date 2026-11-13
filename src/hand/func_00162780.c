typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct S {
    char pad[0x7C]; int f7c;
    char pad1[0x8C - 0x80]; int f8c, f90, f94, f98;
    char pad2[0xA4 - 0x9C]; float fa4; void *fa8; int fac;
    char pad3[0xB8 - 0xB0]; void *fb8; void *fbc;
    char pad4[0xD0 - 0xC0]; int fd0;
    char pad5[0xE0 - 0xD4]; int fe0;
    char pad6[0xE8 - 0xE4]; int fe8;
};
extern char D_003D4A60[];
struct G { char pad[0x3A18]; char m3a18[0x10]; };
extern struct G g_sw;
void PostLoLoad__FP2LO(struct S *p);
int FJobCur__FP3JOB(struct S *p);
int func_00162670(struct S *p);
void ApplyTaskObjects__FPviiT0(struct S *p, int n, int c, int a);
void ApplyTaskSms__FPvT0iT0i(struct S *p, int n, int c, int a, int b);
void NProgress(CRef *pref, void *a, void *b);
void Decref(CRef *pref) asm("Decref__4CRef");
void *func_001D7E80(void *p, void *q, void *r);
void *PloFindSwNearest__FP2LO3OIDii(void *pg, int kind, int oid, void *owner);
// name: SafeHouse port (StartJob)
void StartJob__FP2SW(struct S *p)
{
    CRef ref;
    int *pn;
    PostLoLoad__FP2LO(p);
    if (!FJobCur__FP3JOB(p) && func_00162670(p)) {
        ApplyTaskObjects__FPviiT0(p, 5, p->f8c, p->f90);
        ApplyTaskSms__FPvT0iT0i(p, 5, p->f94, p->f98, 1);
    }
    pn = &p->fd0;
    if (*pn) {
        int n;
        NProgress(&ref, pn, D_003D4A60);
        n = ref.m_tag;
        Decref(&ref);
        p->f7c = n;
    }
    pn = &p->fe0;
    if (*pn) {
        float g;
        NProgress(&ref, pn, D_003D4A60);
        g = *(float *)&ref.m_tag;
        Decref(&ref);
        p->fa4 = g;
    }
    p->fa8 = func_001D7E80(g_sw.m3a18, &p->fe8, D_003D4A60);
    if (p->fac != -1)
        p->fb8 = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, p->fac, 0);
    p->fbc = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, 0x379, 0);
}
