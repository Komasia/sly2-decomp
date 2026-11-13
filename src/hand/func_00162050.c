typedef struct CRef { int m_tagk; int m_tag; } CRef;
void func_002013D8(CRef *pref, void *p, int n, int c, int *pc, int *ai);
int func_00161FF0(int c, int *ai);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_00162050(void *p)
{
    int ai[8];
    CRef ref;
    int c;
    int grf;
    func_002013D8(&ref, p, 0x1050, 6, &c, ai);
    grf = func_00161FF0(c, ai);
    Decref(&ref);
    return grf;
}
