typedef struct { int m_tagk; int m_tag; } CRef;
typedef struct G G;
extern G D_003D4A60;
extern void *D_003E0FD8;
extern int D_002C2D8C;
void func_001291A8(CRef *, CRef *);
void func_00129EC8(CRef *);
void func_00258200(CRef *, void *, CRef *, G *);
static inline void SetRef2(void *pv, CRef *pref, G *pg)
{
    CRef tmp;
    CRef ret;
    func_001291A8(&tmp, pref);
    func_00258200(&ret, pv, &tmp, pg);
    func_00129EC8(&ret);
    func_00129EC8(&tmp);
}
static inline void SetRef(void *pv, CRef *pref)
{
    CRef tmp;
    CRef ret;
    func_001291A8(&tmp, pref);
    func_00258200(&ret, pv, &tmp, &D_003D4A60);
    func_00129EC8(&ret);
    func_00129EC8(&tmp);
}
void func_001D54B8(void)
{
    CRef ref;
    switch (D_002C2D8C) {
    case 2:
        ref.m_tagk = 0x17;
        ref.m_tag = 0;
        SetRef2(D_003E0FD8, &ref, &D_003D4A60);
        func_00129EC8(&ref);
        break;
    case 3:
        ref.m_tagk = 0x17;
        ref.m_tag = 1;
        SetRef(D_003E0FD8, &ref);
        func_00129EC8(&ref);
        break;
    }
}
