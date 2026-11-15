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
#include "h3_progress.h"
/* g_sw +0x3B2C: the progress keys of the 11 settings ("flags" <name>); 0..6 as ApplyGameSettings (0x1D8FF8) uses
 * them: lang, nMixerMode, uMusicVolume, uEffectsVolume, fUseHeadset, dxScreenCenter, dyScreenCenter; 7..10 the
 * flags fNoVibration, fReverseLookAround, fReverseAim, fAutosaveWarned (SafeHouse menu.cpp, order not checked) */
#define CKEYSETTING 11
struct SW { char pad[0x3B2C]; KEY *apkeySetting[CKEYSETTING]; };
extern "C" {
extern SW g_sw;
extern LAYOUT D_003E0EA8;             /* the progress layout */
int func_001D7D30(LAYOUT *playout, char *pbSave);   /* the save has the layout's identity */
CRef RefGetProgress(LAYOUT *playout, KEY *pkey, char *pbSave) asm("RefGetProgress__FP4TRIEP3KEYPc");
CRef func_00258200(KEY *pkey, CRef *pref, char *pbSave);   /* set a progress value */
void s1_memset(void *, int, unsigned int) asm("memset");
void ApplyVibrationSetting(void) asm("ApplyVibrationSetting__Fv");
}
static inline CRef Get(KEY *pkey, char *pbSave) { return RefGetProgress(&D_003E0EA8, pkey, pbSave); }
static inline CRef Set(KEY *pkey, CRef *pref, char *pbSave) { return func_00258200(pkey, pref, pbSave); }
/* ResetSlotKeepSettings (SafeHouse menu.cpp, orig 0x1D8D80): clear a save's values; with fKeep (and when the save
 * has this layout's identity) its 11 settings are kept: read before, written back after. The vibration option is
 * written into the cleared record (ApplyVibrationSetting). */
// name: SafeHouse port (ResetSlotKeepSettings)
extern "C" void ResetSlotKeepSettings__FPci(char *pbSave, int fKeep)
{
    FRAME frame;
    KEY *apkey[CKEYSETTING] = { g_sw.apkeySetting[0], g_sw.apkeySetting[7], g_sw.apkeySetting[10], g_sw.apkeySetting[8],
                                g_sw.apkeySetting[9], g_sw.apkeySetting[1], g_sw.apkeySetting[2], g_sw.apkeySetting[3],
                                g_sw.apkeySetting[4], g_sw.apkeySetting[5], g_sw.apkeySetting[6] };
    CRef aref[CKEYSETTING];
    unsigned int ikey;
    if (fKeep && !func_001D7D30(&D_003E0EA8, pbSave))
        fKeep = 0;
    if (fKeep) {
        for (ikey = 0; ikey < CKEYSETTING; ikey++)
            aref[ikey] = Get(apkey[ikey], pbSave);
    }
    s1_memset(pbSave, 0, CB_GAMESAVEVALUES);
    ApplyVibrationSetting();
    if (fKeep) {
        for (ikey = 0; ikey < CKEYSETTING; ikey++)
        {
            CRef ref(aref[ikey]);
            const CRef &r = Set(apkey[ikey], &ref, pbSave);
        }
    }
}
