struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(float g);
};
extern "C" {
CRef RefAddOption(void *a, void *b, CRef *pref) asm("RefAddOption__FP5BASICiP4CRef");
CRef RefEnsureOption(void *a, void *b, CRef *pref) asm("RefEnsureOption__FP5BASICiP4CRef");
CRef RefSetOption(void *a, void *b, CRef *pref) asm("RefSetOption__FP5BASICiP4CRef");
CRef RefGetOption(void *a, void *b) asm("RefGetOption__FP5BASICi");
CRef RefOpObjectOption__FiP4CRefP6CFrame4BIFK(void *pbasic, CRef *aref, void *pv, int op);
}
// name: Sly 1 bif.cpp RefOpObjectOption (the add / ensure / set / get option switch on the BIFK, 0x6C..0x6F)
CRef RefOpObjectOption__FiP4CRefP6CFrame4BIFK(void *pbasic, CRef *aref, void *pv, int op)
{
    CRef ref;
    void *a = aref[0].u.pv;
    void *b = aref[1].u.pv;
    switch (op) {
    case 0x6C:
        ref = RefAddOption(a, b, &aref[2]);
        break;
    case 0x6D:
        ref = RefEnsureOption(a, b, &aref[2]);
        break;
    case 0x6E:
        ref = RefSetOption(a, b, &aref[2]);
        break;
    case 0x6F:
        ref = RefGetOption(a, b);
        break;
    }
    return ref;
}
