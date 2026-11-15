/* class: items (SafeHouse shop.cpp): set item n acquired or not (the progress value "powerUps" "mppukfAcquired"
 * "<n>"); an acquired item is remembered in g_game +0xC (SafeHouse "nItemC") and task event 0x3B is broadcast. */
#define TAGK_Bool 0x17
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(bool f) { m_tagk = TAGK_Bool; m_tag = f; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct G { char pad[0xC]; int nItem; };   /* g_game: the item last acquired */
extern G g_game;
extern char D_002A79A0[];   /* "%d" */
extern char D_002A79A8[];   /* "powerUps" */
extern char D_002A79B8[];   /* "mppukfAcquired" */
int sprintf(char *, const char *, ...) asm("sprintf");
CRef SetProgressPoCurrent(const CRef &, const char *, ...) asm("SetProgressPoCurrent__FP4CRefPci");
void BroadcastTaskEvent(G *, int, int) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void func_001DAF38(int item, int fAcquired)
{
    CRef ref;
    char achItem[0x20];
    sprintf(achItem, D_002A79A0, item);
    ref = SetProgressPoCurrent(CRef(fAcquired != 0), D_002A79A8, D_002A79B8, achItem, 0);
    if (fAcquired) {
        g_game.nItem = item;
        BroadcastTaskEvent(&g_game, 0x3B, 0);
    }
}
