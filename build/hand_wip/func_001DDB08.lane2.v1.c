typedef struct { int m_tagk; int m_tag; } CRef;
typedef struct G G;
extern G D_003D4A60;
extern void *D_003E0FAC;
extern void *D_002E1E40;
extern void *D_002DD5BC;
extern void *D_002F7900;
CRef *func_001291A8(CRef *, const CRef *);
void func_00129EC8(CRef *);
CRef *func_00258200(CRef *,void *,const CRef *,G *);
void func_001440D0(void *, int);
void func_00165E38(G *);
static inline void SetRef(void *pv, const CRef *pref, G *pg)
{
    CRef tmp;
    CRef ret;
    func_001291A8(&tmp, pref);
    func_00258200(&ret, pv, &tmp, pg);
    func_00129EC8(&ret);
    func_00129EC8(&tmp);
}
void func_001DDB08(void)
{
    G *pg = &D_003D4A60;
    CRef ref;
    ref.m_tagk = 0x16;
    ref.m_tag = 0;
    SetRef(D_003E0FAC, &ref, pg);
    func_00129EC8(&ref);
    if (D_002E1E40)
        func_001440D0(D_002E1E40, 1);
    if (D_002DD5BC)
        func_001440D0(D_002DD5BC, 1);
    if (D_002F7900)
        func_001440D0(D_002F7900, 1);
    func_00165E38(pg);
}
