struct X;
class CSave {
public:
    X *m_p0;
    X *m_p4;
    int m_n8;
    int m_nC;
    inline CSave(X *px, int nF4, int nF8);
    inline CSave(X *px, int nF0, int nF4, int fOwner);
    inline ~CSave();
};
struct X {
    char pad00[0x18]; int f18;
    char pad[0x54 - 0x1C]; int n54;
    char pad1[0x7C - 0x58]; X *f7c;
    char pad2[0xB8 - 0x80]; int fB8; int fBC; int fC0;
    char pad3[0xF0 - 0xC4]; int fF0; int fF4; int fF8;
};
inline CSave::CSave(X *px, int nF4, int nF8)
{
    m_p0 = 0;
    m_p4 = px;
    if (px) {
        m_n8 = px->fF4;
        px->fF4 = nF4;
        m_nC = m_p4->fF8;
        m_p4->fF8 = nF8;
    }
}
inline CSave::CSave(X *px, int nF0, int nF4, int fOwner)
{
    m_p0 = px;
    m_p4 = 0;
    if (px) {
        m_n8 = px->fF0;
        px->fF0 = nF0;
        m_nC = m_p0->fF4;
        m_p0->fF4 = nF4;
    }
}
inline CSave::~CSave()
{
    if (m_p0) {
        m_p0->fF0 = m_n8;
        m_p0->fF4 = m_nC;
    }
    if (m_p4) {
        m_p4->fF4 = m_n8;
        m_p4->fF8 = m_nC;
    }
}
struct CRef { int m_tagk; int m_tag; };
class FRAME {
public:
    int a[4];
    FRAME();
    ~FRAME();
};
struct G { char pad[0x3BF4]; int f3bf4; char pad2[0x3C38 - 0x3BF8]; int f3c38; int f3c3c; };
struct SS { int pad[4]; int f10; int f14; int oid; };
extern G g_sw;
extern char D_002A5238[];
extern "C" void func_00165C98(int *pc, X ***papx);
extern "C" void RestoreTask(X *p) asm("RestoreTask__FP4TASK");
extern "C" X *PloFindSwNearest(G *pg, int kind, int oid, void *owner) asm("PloFindSwNearest__FP2LO3OIDii");
extern "C" void ChangeTaskState(X *p, int n) asm("ChangeTaskState__FP4TASKi");
extern "C" void SetProgressPoCurrent(CRef *pref, CRef *parg, void *pv, int n) asm("SetProgressPoCurrent__FP4CRefPci");
extern "C" void Decref(CRef *pref) asm("Decref__4CRef");
extern "C" void SetTaskState(X *p, int n) asm("SetTaskState__FP4TASKi");
// name: SafeHouse port (StartQueuedTask)
extern "C" void StartQueuedTask__FP2SS(SS *ps)
{
    if (!(g_sw.f3bf4 & 8))
        return;
    FRAME fr;
    int c;
    X **apx;
    int i;
    func_00165C98(&c, &apx);
    for (i = 0; i < c; i++) {
        X *pxT = apx[i];
        CSave save(pxT, 3, 0);
        RestoreTask(pxT);
    }
    X *px = PloFindSwNearest(&g_sw, 0x105, ps->oid, 0);
    ps->f10 = px->f7c->f18;
    ps->f14 = px->f18;
    CSave save(px, 3, 0);
    ChangeTaskState(px, 1);
    int nC0 = px->fC0;
    if (nC0 != -1) {
        CRef refRet;
        CRef ref;
        ref.m_tagk = 0x15;
        ref.m_tag = nC0;
        SetProgressPoCurrent(&refRet, &ref, D_002A5238, 0);
        Decref(&refRet);
        Decref(&ref);
    }
    for (i = 0; i < c; i++) {
        X *pxT = apx[i];
        CSave save2(pxT, 3, 0);
        SetTaskState(pxT, -1);
    }
    g_sw.f3c38 = px->fB8;
    g_sw.f3c3c = -1;
    g_sw.f3bf4 = (g_sw.f3bf4 & ~8) | 4;
}
