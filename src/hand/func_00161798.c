/* func_00161798: an integer from the current game's progress (the key D_003E0FB0). */
typedef struct CRef { int m_tagk; int m_n; } CRef;
extern int D_003E0FB0;
extern char D_003D4A60[];
void NProgress(CRef *pref, int key, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_00161798(void)
{
    CRef ref;
    int n;
    NProgress(&ref, D_003E0FB0, D_003D4A60);
    n = ref.m_n;
    Decref(&ref);
    return n;
}
