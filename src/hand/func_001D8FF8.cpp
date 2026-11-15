struct CRef {
    int m_tagk;
    union { int m_tag; float m_g; };
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
#include "h3_progress.h"
/* g_sw +0x3B2C: the progress keys of the settings (see ResetSlotKeepSettings 0x1D8D80) */
enum KEYSETTING {
    KEYSETTING_Lang = 0, KEYSETTING_MixerMode = 1, KEYSETTING_MusicVolume = 2, KEYSETTING_EffectsVolume = 3,
    KEYSETTING_UseHeadset = 4, KEYSETTING_ScreenCenterX = 5, KEYSETTING_ScreenCenterY = 6
};
struct SW { char pad[0x3B2C]; KEY *apkeySetting[7]; };
struct DISP1 { unsigned long dx : 12; unsigned long dy : 11; unsigned long rest : 41; };
struct DISP2 { unsigned int dx : 12; unsigned int dy : 11; unsigned long rest : 41; };
struct GSR { char pad[0x18]; DISP1 d1; char pad20[0x40 - 0x20]; DISP2 d2; };   /* the GS display registers (DISPLAY1 / DISPLAY2 DX, DY) */
extern "C" {
extern SW g_sw;
extern char D_003DD040[];             /* the sound manager */
extern int D_003DD050;                /* headset in use */
extern GSR D_002DEB80;
CRef NProgress(KEY *pkey, char *pbSave);
int func_001A2C98(void);              /* the number of languages */
void func_001A2BD0(int lang);         /* set the language */
void SetSoundPlaybackMode(void *, int) asm("SetSoundPlaybackMode__FP8SOUNDMGRi");
void SetSoundChannelVolume(void *, int, int, float) asm("SetSoundChannelVolume__FP8SOUNDMGRiif");
unsigned int fptoui(float) asm("fptoui");
}
static inline int GetInt(KEY *pkey, char *pbSave) { return NProgress(pkey, pbSave).m_tag; }
static inline float GetFloat(KEY *pkey, char *pbSave) { return NProgress(pkey, pbSave).m_g; }
/* ApplyGameSettings (SafeHouse menu.cpp): make a save's settings take effect - language (when there is a choice),
 * mixer mode, music volume (channel 1) and effects volume (channels 0 and 3) as 1 - u, headset, and the screen
 * centre offset into the GS display registers (x + 636, y + 50 rounded to even). */
// name: SafeHouse port (ApplyGameSettings)
extern "C" void ApplyGameSettings__FP8GAMESAVE(char *pbSave)
{
    if (g_sw.apkeySetting[KEYSETTING_Lang] && func_001A2C98() >= 2)
        func_001A2BD0(GetInt(g_sw.apkeySetting[KEYSETTING_Lang], pbSave));
    if (g_sw.apkeySetting[KEYSETTING_MixerMode])
        SetSoundPlaybackMode(D_003DD040, GetInt(g_sw.apkeySetting[KEYSETTING_MixerMode], pbSave));
    if (g_sw.apkeySetting[KEYSETTING_MusicVolume])
        SetSoundChannelVolume(D_003DD040, 1, 1, 1.0f - GetFloat(g_sw.apkeySetting[KEYSETTING_MusicVolume], pbSave));
    if (g_sw.apkeySetting[KEYSETTING_EffectsVolume]) {
        SetSoundChannelVolume(D_003DD040, 0, 1, 1.0f - GetFloat(g_sw.apkeySetting[KEYSETTING_EffectsVolume], pbSave));
        SetSoundChannelVolume(D_003DD040, 3, 1, 1.0f - GetFloat(g_sw.apkeySetting[KEYSETTING_EffectsVolume], pbSave));
    }
    if (g_sw.apkeySetting[KEYSETTING_UseHeadset])
        D_003DD050 = GetInt(g_sw.apkeySetting[KEYSETTING_UseHeadset], pbSave);
    if (g_sw.apkeySetting[KEYSETTING_ScreenCenterX]) {
        float f = GetFloat(g_sw.apkeySetting[KEYSETTING_ScreenCenterX], pbSave);
        GSR *p = &D_002DEB80;
        p->d1.dx = p->d2.dx = fptoui(f + 636.0f);
    }
    if (g_sw.apkeySetting[KEYSETTING_ScreenCenterY]) {
        float f = GetFloat(g_sw.apkeySetting[KEYSETTING_ScreenCenterY], pbSave);
        GSR *p = &D_002DEB80;
        p->d1.dy = p->d2.dy = fptoui(f + 50.0f) & ~1;
    }
}
