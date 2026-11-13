struct CRef { int tagk; int tag; };
extern char D_003D4A60[];
extern char D_002A8AA0[];
void NProgress(struct CRef *r, int *p, void *q);
void Decref(struct CRef *r) asm("Decref__4CRef");
void fiprintf(void *f, const char *fmt, ...);
void func_00210ED8(void *f, int **pp)
{
    int *p = *pp;
    if (p && *p) {
        char *fmt = D_002A8AA0;
        struct CRef r;
        int v;
        NProgress(&r, p, D_003D4A60);
        v = r.tag;
        Decref(&r);
        fiprintf(f, fmt, v);
    }
}
