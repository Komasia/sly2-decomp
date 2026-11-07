struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(bool f) { m_tagk = 0x17; m_tag = f; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct G { char pad[0xC]; int n; };
extern G g_game;
extern char D_002A79A0[];
extern char D_002A79A8[];
extern char D_002A79B8[];
int func_0021ECD8(char *, const char *, ...);
CRef SetProgressPoCurrent(const CRef &, const char *, ...) asm("SetProgressPoCurrent__FP4CRefPci");
void BroadcastTaskEvent(G *, int, int) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void func_001DAF38(int n, int f)
{
    CRef ref;
    char buf[0x20];
    func_0021ECD8(buf, D_002A79A0, n);
    ref = SetProgressPoCurrent(CRef(f != 0), D_002A79A8, D_002A79B8, buf, 0);
    if (f) {
        g_game.n = n;
        BroadcastTaskEvent(&g_game, 0x3B, 0);
    }
}
