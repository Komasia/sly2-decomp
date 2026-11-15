// name: SafeHouse port (savedata.h, orig 0x1D82B8: a save's game percent; suggested by h3)
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    void Decref();
};
#include "h3_progress.h"
#define CEPISODE 9
#define NPERCENT_VAULT 0x1A                     /* each vault counts 26 */
struct SW { char pad[0x3B7C]; KEY *apkeyPercent[CEPISODE]; };   /* each episode's "percent_complete" key */
extern SW g_sw;
extern int D_002C2DC0[];                        /* each episode's weight */
extern char D_002A78F0[];                       /* "fVault" */
CRef NProgress(KEY *pkey, unsigned char *pbSave) asm("NProgress");
extern "C" int SymFromName(NAMETABLE *pnametable, char *pchz) asm("SymFromName__FP6LAYOUTPc");
static inline int NGet(KEY *pkey, unsigned char *pbSave)
{
    CRef ref = NProgress(pkey, pbSave);
    return ref.m_tag;
}
static inline int Clamp(int n, int lo, int hi)
{
    if (n < lo)
        return lo;
    if (n > hi)
        return hi;
    return n;
}
static inline int NFind(LAYOUT *playout, char *pchz) { return SymFromName(&playout->nametable, pchz); }

/* class: progress (SafeHouse savedata.h NGamePercent, orig 0x1D82B8): a save's game percent - each episode's
 * percent_complete by its weight, plus 26 for each vault (the "fVault" bool entries of the layout, bit sets
 * counted bit by bit), out of the total; 0 or 100 exactly only when nothing / everything is done, else 1..99. */
extern "C" int NGamePercent__FPvPUc(LAYOUT *playout, unsigned char *pbSave)
{
    int sum = 0;
    int total = 0;
    int iepisode;
    int symVault;
    for (iepisode = 0; iepisode < CEPISODE; iepisode++) {
        KEY *pkey = g_sw.apkeyPercent[iepisode];
        int weight = D_002C2DC0[iepisode];
        total += weight * 100;
        if (pkey)
            sum += NGet(pkey, pbSave) * weight;
    }
    symVault = NFind(playout, D_002A78F0);
    total += 0xD0;                              /* 8 vaults * 26 */
    for (int ient = 0; ient < playout->cent; ient++) {
        PENT *pent = &playout->aent[ient];
        if (pent->kind == PROGK_Bool && pent->ch == symVault) {
            unsigned char *pb = pbSave + pent->ib;
            if (pent->fIndexed) {
                int cbit = pent->fIndexed;
                int ibit;
                for (ibit = 0; ibit < cbit; ibit++) {
                    unsigned char b = 1 << (ibit % 8);
                    if (pb[ibit / 8] & b)
                        sum += NPERCENT_VAULT;
                }
            } else {
                if (*pb)
                    sum += NPERCENT_VAULT;
            }
        }
    }
    if (sum == 0)
        return 0;
    if (sum == total)
        return 100;
    {
        return Clamp(sum * 100 / total, 1, 99);
    }
}
