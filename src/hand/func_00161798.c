typedef struct CRef { int m_tagk; int m_tag; } CRef;
extern int D_003E0FB0;
extern char D_003D4A60[];
void NProgress(CRef *pref, int a, void *b);
void func_00129EC8(CRef *pref);
int func_00161798(void)
{
    CRef ref;
    int n;
    NProgress(&ref, D_003E0FB0, D_003D4A60);
    n = ref.m_tag;
    func_00129EC8(&ref);
    return n;
}
