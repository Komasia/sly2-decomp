struct CRef { int tagk; int tag; };
void func_001D8A38(struct CRef *r, char *s, int a);
void Decref(struct CRef *r) asm("Decref__4CRef");
extern char D_002A8A78[];
int func_00210B28(void)
{
    struct CRef r;
    int v;
    func_001D8A38(&r, D_002A8A78, 0);
    v = r.tag;
    Decref(&r);
    return v;
}
