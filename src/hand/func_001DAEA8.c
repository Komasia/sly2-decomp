typedef struct CRef { int tagk; int tag; } CRef;
extern char D_002A79A0[], D_002A79A8[], D_002A79B8[];
void fiprintf(char *pch, char *fmt, int n);
void func_001D8A38(CRef *pref, char *a, char *b, char *c, int d);
void func_00129658(CRef *pref, CRef *prefSrc);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_001DAEA8(int n) {
    CRef ref;
    char ach[0x20];
    CRef tmp;
    int r;
    if (n == -1) return 0;
    ref.tagk = -1;
    fiprintf(ach, D_002A79A0, n);
    func_001D8A38(&tmp, D_002A79A8, D_002A79B8, ach, 0);
    func_00129658(&ref, &tmp);
    Decref(&tmp);
    r = ref.tag;
    Decref(&ref);
    return r;
}
