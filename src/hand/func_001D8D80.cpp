struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct FRAME {
    int a[4];
    FRAME();
    ~FRAME();
};
struct KEY;
struct TRIE;
struct KEYS { KEY *a[11]; };
struct GS { char pad[0x3B2C]; KEY *k[11]; };
extern "C" {
extern GS g_sw;
extern TRIE D_003E0EA8;
int func_001D7D30(TRIE *, char *);
CRef RefGetProgress(TRIE *, KEY *, char *) asm("RefGetProgress__FP4TRIEP3KEYPc");
CRef func_00258200(KEY *, CRef *, char *);
void func_002333B4(void *, int, unsigned int);
void ApplyVibrationSetting(void) asm("ApplyVibrationSetting__Fv");
}
static inline CRef Get(KEY *k, char *pb) { return RefGetProgress(&D_003E0EA8, k, pb); }
static inline CRef Set(KEY *k, CRef *r, char *pb) { return func_00258200(k, r, pb); }
// name: SafeHouse port (ResetSlotKeepSettings)
extern "C" void ResetSlotKeepSettings__FPci(char *pb, int f)
{
    FRAME frame;
    KEY *keys[11] = { g_sw.k[0], g_sw.k[7], g_sw.k[10], g_sw.k[8], g_sw.k[9], g_sw.k[1], g_sw.k[2], g_sw.k[3], g_sw.k[4], g_sw.k[5], g_sw.k[6] };
    CRef aref[11];
    unsigned int i;
    if (f && !func_001D7D30(&D_003E0EA8, pb))
        f = 0;
    if (f) {
        for (i = 0; i < 11; i++)
            aref[i] = Get(keys[i], pb);
    }
    func_002333B4(pb, 0, 0x5400);
    ApplyVibrationSetting();
    if (f) {
        for (i = 0; i < 11; i++)
        {
            CRef ref(aref[i]);
            const CRef &r = Set(keys[i], &ref, pb);
        }
    }
}
